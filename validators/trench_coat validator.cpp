//
// Created by kamui on 24.03.2021.
//

#include <cstring>
#include "trench_coat validator.h"
#include "../exceptions/trench_coat_exceptions.h"


bool TrenchCoatValidator::validate(TrenchCoat &trench_coat) {
    if(trench_coat.get_size() < 102 || trench_coat.get_size() > 137){
        throw TrenchCoatValidatorException("Invalid size for TrenchCoat!\n");
    }
    if(trench_coat.get_colour().empty()){
        throw TrenchCoatValidatorException("Invalid colour for TrenchCoat!\n");
    }
    if(trench_coat.get_price() <= 0){
        throw TrenchCoatValidatorException("Invalid price for TrenchCoat!\n");
    }
    if(trench_coat.get_quantity() < 0){
        throw TrenchCoatValidatorException("Invalid quantity for TrenchCoat!\n");
    }
    if(trench_coat.get_photograph().empty()){
        throw TrenchCoatValidatorException("Invalid photograph for TrenchCoat!\n");
    }
    return true;

}
