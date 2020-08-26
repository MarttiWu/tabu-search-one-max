//
//  TS.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/8.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include "TS.hpp"

TS::TS(){
    bits = 10;
    bitstr = new int [10];
    memset(bitstr, 0, 10);
    iter = 5;
    max_bitstr = new int [10];
    memset(max_bitstr, 0, 10);
    tabu_list = new int [10];
    memset(tabu_list, 0, 10);
}

TS::TS(int b,int iterations){
    bits = b;
    bitstr = new int [bits];
    memset(bitstr, 0, bits);
    iter = iterations;
    max_bitstr = new int [bits];
    memset(max_bitstr, 0, bits);
    tabu_list = new int [bits];
    memset(tabu_list, 0, bits);
}

int TS::Sum(int *str){
    int sum=0;
    for (int i=0;i<bits;i++){
        sum+=str[i];
    }
    return sum;
}

void TS::form_neighbor1(){
    //clear() does not free memory, dangerous!
    //should be modified...
    neighbor.clear();
    for (int i=0;i<bits;i++){
        int *tempstr = new int [bits];
        memset(tempstr, 0, bits);
        for (int j=0;j<bits;j++){
            tempstr[j] = bitstr[j];
        }
        if (tempstr[i])
            tempstr[i]=0;
        else
            tempstr[i]=1;
        neighbor.push_back(tempstr);
    }
}

void TS::form_neighbor2(){
}

int *TS::select_neighbor(int *str){
    form_neighbor1();
    int *opt = new int [bits];
    memset(opt, 0, bits);
    int max = 0;
    for (int i=0;i<bits;i++){
        if (tabu_list[i]==0){
            int temp = Sum(neighbor[i]);
            if (temp>max){
                max = temp;
                //
                opt = neighbor[i];
                tabu_index = i;
            }
        }
    }
    return opt;
}

int *TS::pardon(){
    int max = 0;
    int *opt = new int [bits];
    memset(opt, 0, bits);
    for (int i=0;i<bits;i++){
        if (tabu_list[i]>0){
            int temp = Sum(neighbor[i]);
            if (temp>max){
                max = temp;
                opt = neighbor[i];
                tabu_index = i;
            }
        }
    }
    return opt;
}

void TS::update_tabu_list(){
    for (int i=0;i<bits;i++){
        if (tabu_list[i]>0)
            tabu_list[i]--;
    }
    tabu_list[tabu_index] = TABU_LENGTH;
}

void TS::run(){
    init_point();
    int it=0;
    int max=Sum(bitstr);
    while (it<iter&&max<bits){
        int *candidate = select_neighbor(bitstr);
        int sum=Sum(candidate);
        if (sum>max){
            max=sum;
            bitstr = candidate;
            update_tabu_list();
        }
        else {
            cout<<"pardon hurray!"<<endl;
            candidate = pardon();
            max = Sum(candidate);
            bitstr = candidate;
            update_tabu_list();
        }
        it++;
    }
    for (int i=0;i<bits;i++)
        max_bitstr[i]=bitstr[i];
    Max = max;
    cout<<"max: "<<max<<endl;
}

void TS::init_point(){
    for (int i=bits-1;i>=0;i--){
        bitstr[i] = rand()%2;
    }
}



