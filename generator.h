#ifndef GENERATOR_H
#define GENERATOR_H
#include "core.h"

inline void generate_variables(autonomous & autonom){
    for(auto & i : autonom.variables){
        std::string tmp = "\tpublic static double & = %;\n";
        tmp.replace(tmp.find("&"),1,i.first);
        tmp.replace(tmp.find("%"),1,std::to_string(i.second));
        autonom.generic.insert(autonom.var_ptr,tmp);
        autonom.var_ptr += tmp.size();
    }
}

inline void generate_states(autonomous & autonom){
    for(auto & i : autonom.states){
        std::string tmp = "\tprivate int & = 0;\n";
        tmp.replace(tmp.find("&"),1,i.substr(0));
        // tmp.replace(tmp.find("%"),1,std::to_string(i.second));
        autonom.generic.insert(autonom.var_ptr,tmp);
        autonom.var_ptr += tmp.size();
    }
}

inline void generate_code(autonomous & autonom){
    for(auto & i : autonom.code){
        auto lines = split(i.second,'\n');
        std::size_t pos = -1;
        for(auto & line : lines){
            if(line[line.find_first_not_of(" \t") != std::string::npos ? line.find_first_not_of(" \t") : 0] == '!'){
                std::string loc = "{}\n";
                auto parsed = split(line.substr(line.find_first_of("!")), ' ');
                for(auto & state : parsed){
                    loc.insert(loc.size() - 2, state.substr(state.find_first_not_of("!")));
                    loc.insert(loc.size() - 2, " = 1;");
                }
                loc.insert(loc.size() - 2, i.first.substr(1));
                loc.insert(loc.size() - 2, " = 0;");
                pos = i.second.find(line.substr(line.find_first_not_of("\t ")),pos + 1);
                i.second.erase(pos,i.second.find_first_of("\n",pos ) - pos);
            

                i.second.insert(pos,loc);
                // std::cout<<std::string(i.second.begin(),i.second.end())<<std::endl;
            }
        }
    }
}

inline void generate_functions(autonomous & autonom){
    for(auto & i : autonom.code){
        std::string tmp = "\n\tpublic void state_&(){\nif(& == 1){\n%}\n}";
        tmp.replace(tmp.find("&"),1,i.first.substr(1));
        tmp.replace(tmp.find("&"),1,i.first.substr(1));
        tmp.replace(tmp.find("%"),1,i.second);

        int p = tmp.find_first_of("\n",1);

        while(p != std::string::npos){
            tmp.insert(p+1,"\t\t");
            p = tmp.find_first_of("\n", p + 1);
        }

        tmp.erase(tmp.find_last_of("\t"), 1);
        
        autonom.generic.insert(autonom.var_ptr,tmp);
        autonom.var_ptr += tmp.size();
    }
}

inline void generate_state_machine(autonomous & autonom){
    autonom.insert_ptr = autonom.generic.find("#{}#");
    std::size_t n = 0;
    std::string nt = "";
    for(int i = autonom.insert_ptr-1; autonom.generic[i] == ' '; --i){
        n++;
        nt.append(" ");
    }
    autonom.generic.replace(autonom.insert_ptr,4,"");
    
    autonom.insert_ptr -= n;
    // auto tabs = autonom.generic.substr(autonom.insert_ptr-n,autonom.insert_ptr);
    // bool real = 0;
    for(auto & i : autonom.code){
        std::string state = nt + "state_&();\n";
        
        // autonom.generic.insert(autonom.insert_ptr,tabs);
        auto pos = state.find_first_of("&");
        state = state.erase(pos,1);
        state = state.insert(pos,i.first.substr(1));
        autonom.generic.insert(autonom.insert_ptr,state);

    }
}

#endif