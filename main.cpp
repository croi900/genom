#include "generator.h"
#include "parser.h"
#include "verifier.h"
#include <iostream>

int main(){
    autonomous autonom;
    load_template("template.adt",autonom);
    parse_file("auto.adl",autonom);

    generate_variables(autonom);
    generate_states(autonom);

    generate_code(autonom);
    generate_functions(autonom);

    generate_state_machine(autonom);
    valid(autonom);

    std::cout<<autonom.generic;

}

//DACA SE REPETA VARIABILELE SE VA SALVA CEA MAI RECENTA VERSIUNE
//GRIJA LA STADII SIMULTANE CARE FOLOSESC ACELEASI VARIABILE COMUNE