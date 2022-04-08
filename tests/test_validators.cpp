//
// Created by kamui on 24.03.2021.
//

#include <cassert>
#include <cstring>
#include "test_validators.h"
#include "../domain/trench_coat.h"
#include "../validators/trench_coat_validator.h"
#include "../exceptions/trench_coat_exceptions.h"

void TestValidators::test_trench_coat_validator() {
//    assert(false);
    TrenchCoat tc1{102, "pink", 200, 5, "photo 1"};
    assert(TrenchCoatValidator::validate(tc1) == true);

    tc1.set_size(137);
    assert(TrenchCoatValidator::validate(tc1) == true);
    tc1.set_size(101);
    try{
        TrenchCoatValidator::validate(tc1);
    }
    catch (TrenchCoatValidatorException& tcve){
        assert(strcmp(tcve.what(), "Invalid size for TrenchCoat!\n") == 0);
    }
    tc1.set_size(138);
    try{
        TrenchCoatValidator::validate(tc1);
    }
    catch (TrenchCoatValidatorException& tcve){
        assert(strcmp(tcve.what(), "Invalid size for TrenchCoat!\n") == 0);
    }
    tc1.set_size(117);

    tc1.set_colour("");
    try{
        TrenchCoatValidator::validate(tc1);
    }
    catch (TrenchCoatValidatorException& tcve){
        assert(strcmp(tcve.what(), "Invalid colour for TrenchCoat!\n") == 0);
    }
    tc1.set_colour("red");
    assert(TrenchCoatValidator::validate(tc1) == true);

    tc1.set_price(0);
    try{
        TrenchCoatValidator::validate(tc1);
    }
    catch (TrenchCoatValidatorException& tcve){
        assert(strcmp(tcve.what(), "Invalid price for TrenchCoat!\n") == 0);
    }
    tc1.set_price(1);
    assert(TrenchCoatValidator::validate(tc1) == true);

    tc1.set_quantity(-1);
    try{
        TrenchCoatValidator::validate(tc1);
    }
    catch (TrenchCoatValidatorException& tcve){
        assert(strcmp(tcve.what(), "Invalid quantity for TrenchCoat!\n") == 0);
    }
    tc1.set_quantity(0);
    assert(TrenchCoatValidator::validate(tc1) == true);

    tc1.set_photograph("");
    try{
        TrenchCoatValidator::validate(tc1);
    }
    catch (TrenchCoatValidatorException& tcve){
        assert(strcmp(tcve.what(), "Invalid photograph for TrenchCoat!\n") == 0);
    }
    tc1.set_photograph("link 7");
    assert(TrenchCoatValidator::validate(tc1) == true);
}
void TestValidators::run_all_validators() {

    test_trench_coat_validator();
}
