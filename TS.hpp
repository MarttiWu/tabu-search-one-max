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

using namespace std;

class TS{
public:
    TS();
    TS(int b,int iterations);
    void run();
    
    void Initialization();
    int FitnessFunction(vector<int> str);
    void form_neighbor1();
    void form_neighbor2();
    vector<int> select_neighbor(vector<int> str);
    vector<int> pardon();
    void update_tabu_list();
    vector<int> get_record_bitstr(int it){return record_bitstr[it];}
    int get_record_value(int it){return record_value[it];}
private:
    int bits;
    int iter;
    int tabu_length;
    vector<int> tabu_list;
    int tabu_index;
    vector<vector<int> > neighbor;
    
    vector<int> bitstr;
    int value;
    vector<int> best_bitstr;
    int best_value;
    vector<vector<int> > record_bitstr;
    vector<int> record_value;
};

#endif /* TS_hpp */
