#ifndef CORE_H
#define CORE_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <fstream>


inline std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

//DACA SE REPETA VARIABILELE SE VA SALVA CEA MAI RECENTA VERSIUNE
//GRIJA LA STADII SIMULTANE CARE FOLOSESC ACELEASI VARIABILE COMUNE
struct autonomous{
    std::string generic; // partea care e peste tot
    std::unordered_map<std::string, std::string> code;
    std::unordered_map<std::string, double> variables;

    std::unordered_multimap<std::string, std::string> automata;

    std::unordered_set<std::string> states;

    uint64_t insert_ptr;
    uint64_t var_ptr;
};

inline void load_template(const char *filename, autonomous & autonom){
    std::ifstream in(filename);
    std::stringstream ss;

    ss << in.rdbuf();
    
    autonom.generic = ss.str();

    autonom.var_ptr = autonom.generic.find("{##}");
    autonom.generic.replace(autonom.var_ptr,4,"");

   
    
}

#endif