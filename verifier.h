#pragma once

#include "core.h"

#include <cassert>
#include <iostream>

static std::unordered_set<std::string> reached;

inline void dfs_automata(autonomous & autonom, std::string state){
    reached.insert(state);
    
    for(auto & i : autonom.automata){
        if(i.first == state && reached.find(i.second) == reached.end()){
            dfs_automata(autonom,i.second);
        }
    }
}

inline bool valid(autonomous & autonom){
    // assert(autonom.states.find("start") != autonom.states.end());

    dfs_automata(autonom,"start");  

    for(auto & i : autonom.states){
        if(reached.find(i) == reached.end()){
            std::cerr<<"Automata has unreachable states\n";
            return false;
        }
        // std::cout<<i<<std::endl;
    }
    //     std::cout<<std::endl;

    // for(auto & i : reached){
    //     // if(reached.find(i) == reached.end()){
    //     //     std::cerr<<"Automata has unreachable states\n";
    //     //     return false;
    //     // }
    //     std::cout<<i<<std::endl;
    // }
    return true;
}