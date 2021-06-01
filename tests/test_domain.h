//
// Created by kamui on 23.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_TEST_DOMAIN_H
#define A45_915_PATRULESCU_SANDRINO_TEST_DOMAIN_H

#include "../domain/trench_coat.h"
#include <sstream>
#endif //A45_915_PATRULESCU_SANDRINO_TEST_DOMAIN_H




class TestTrenchCoat{
//private:
//    TrenchCoat trench_coat;
public:
//    TestTrenchCoat(int size, std::string colour, int price, int quantity, std::string photograph);
//    ~TestTrenchCoat();
    void run_all_trench_coat();
private:
    void test_getters();
    void test_copy();
    void test_setters();
    void test_operator_equal();
    void test_printable();
    void test_streams();

};

class TestDynamicVector{
public:
    void run_all_dynamic_vector();


};

class TestDomain{
public:
    void run_all_domain();
};
