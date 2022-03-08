#pragma once

#include "core.h"

#include <cassert>
#include <iostream>

std::unordered_set<std::string> reached;

inline void dfs_automata(autonomous & autonom, std::string state){
    reached.insert(state);
    
    for(auto & i : autonom.automata){
        if(i.first == state && reached.find(i.first) == reached.end()){
            dfs_automata(autonom,i.first);
        }
    }
}

inline bool valid(autonomous & autonom){
    // assert(autonom.states.find("start") != autonom.states.end());

    dfs_automata(autonom,"start");  

    for(auto & i : reached){
        std::cout<<i<<std::endl;
    }

    return false;
}