#ifndef PARSER_H
#define PARSER_H

#include "core.h"


inline void process_action(const std::string & line, autonomous & autonom, std::string & cur_state)
{
    auto parsed = split(line, ' ');
    // autonom.statics[parsed[0]] = std::vector<std::string>(parsed.begin() + 1, parsed.end());
    // parsed[0] = 
    for(auto i = parsed.begin()+1; i != parsed.end(); ++i){
        if((*i).find('=') != std::string::npos){
            autonom.variables[(*i).substr(0, (*i).find_first_of("=-)(*&^%$#@!:;\'\"{}[].,<>/?+_-"))] = std::stod((*i).substr(
                (*i).find('=') + 1
            ));
        }else{
            autonom.variables[*i] = 0;    
        }
    }
    cur_state = parsed[0];
}

inline void process_spline(const std::string & line, autonomous & autonom, std::string & cur_state)
{
    auto parsed = split(line, ' ');
    
    auto spline_name = parsed[0].substr(1,parsed[0].find_first_of("=-)(*&^%$#@!:;\'\"{}[].,<>/?+-",1));
    auto spline_data = parsed[1].substr(1,parsed[1].size()-1);

    auto elems = split(spline_data,',');

    autonom.variables[spline_name + "_x"] = std::stod(elems[0]);    
    autonom.variables[spline_name + "_y"] = std::stod(elems[1]);    
    autonom.variables[spline_name + "_h"] = std::stod(elems[2]);    

    for(auto i = parsed.begin() + 2; i < parsed.end(); i++){
        autonom.automata.insert({spline_name,*i});
    }
    
}

inline void process_states(const std::string & line, autonomous & autonom, std::string & cur_state){
    auto parsed = split(line.substr(line.find_first_of("!")), ' ');
    for(auto & state : parsed){
        // std::cout<<cur_state<<" "<<state<<"\n";
        autonom.automata.insert({cur_state.substr(cur_state.find_first_not_of("#")),state.substr(state.find_first_not_of("!"))});
    }
}

inline void parse_file(const char *filename, autonomous & autonom){
    std::ifstream in(filename);

    std::string line; 
    std::string cur_state;

    bool found = false;
    while (std::getline(in, line))
    {
        if(line[0] == '#'){
            found = true;
            process_action(line,autonom,cur_state);
            autonom.states.insert(line.substr(1,line.find_first_of(" \t") - 1));
        }else if(line[0] == '@'){
            process_spline(line,autonom,cur_state);
            autonom.states.insert(line.substr(1,line.find_first_of(" \t") - 1));
        }else if(line[line.find_first_not_of(" \t") != std::string::npos ? line.find_first_not_of(" \t") : 0] == '!'){
            process_states(line,autonom,cur_state);    

            autonom.code[cur_state].append(line);
            autonom.code[cur_state].append("\n");
        
        }else if(found == true){
            autonom.code[cur_state].append(line);
            autonom.code[cur_state].append("\n");
        }

        if(line[0] == '&'){
            //process_state_macine()
            //return;
        }
        
        
    }
}

#endif