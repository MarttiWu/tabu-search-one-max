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
    Initialization();
    best_value = value = FitnessFunction(bitstr);
    best_bitstr = bitstr;
    record_bitstr[0] = best_bitstr;
    record_value[0] = best_value;
    int it=1;
    //stopping condition
    while (it<iter&&best_value<bits){
        vector<int> neighbor = select_neighbor(bitstr);
        int neighbor_value = FitnessFunction(neighbor);
        //accept better solution
        if (neighbor_value>value){
            bitstr = neighbor;
            value = neighbor_value;
        }
        else{
            //accept worse solution for probability of Pa
            if ( ((double)rand()/RAND_MAX) < Pa(value,neighbor_value) ){
                bitstr = neighbor;
                value = neighbor_value;
            }
            //doesn't accept for probability (1-Pa)
        }
        
        value = FitnessFunction(bitstr);
        
        if (value>best_value){
            best_value = value;
            best_bitstr = bitstr;
        }
        
        record_bitstr[it] = best_bitstr;
        record_value[it] = best_value;
        
        anneal();
        it++;
    }
    
    for (int i=it;i<record_value.size();i++){
        record_bitstr[i] = best_bitstr;
        record_value[i] = best_value;
    }
}

void TS::Initialization(){
    for (int i=bits-1;i>=0;i--){
        bitstr[i] = rand()%2;
    }
}



