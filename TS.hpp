//
//  TS.hpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/8.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#ifndef TS_hpp
#define TS_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <vector>
#include <algorithm>
#define TABU_LENGTH 30

using namespace std;

class TS{
public:
    TS();
    TS(int b,int iterations);
    void run();
    
    void init_point();
    int Sum(int *str);
    int get_max(){return Max;}
    void form_neighbor1();
    void form_neighbor2();
    int *select_neighbor(int *str);
    int *pardon();
    void update_tabu_list();
private:
    int *bitstr;
    int iter;
    int bits;
    int Max;
    int *max_bitstr;
    int *tabu_list;
    int tabu_index;
    vector<int *> neighbor;
};

#endif /* TS_hpp */
