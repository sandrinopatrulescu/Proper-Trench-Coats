//
// Created by kamui on 23.03.2021.
//

#include <cassert>
#include <cstring>
#include "test_domain.h"
#include "../domain/dynamic_vector.h"



//TestTrenchCoat(){
////    std::cout<<"TestTrenchCoat constructed"<<std::endl;
//}

//TestTrenchCoat::TestTrenchCoat(int size, std::string colour, int price, int quantity, std::string photograph) : trench_coat(0, "red", 0, 0, "link"){
//    this->trench_coat.set_size(size);
//    this->trench_coat.set_colour(colour);
//    this->trench_coat.set_price(price);
//    this->trench_coat.set_quantity(quantity);
//    this->trench_coat.set_photograph(photograph);
//}

void TestTrenchCoat::run_all_trench_coat() {
    test_getters();
    test_copy();
    test_setters();
    test_operator_equal();
    test_printable();
    test_streams();
}


void TestTrenchCoat::test_getters() {
    TrenchCoat trenchCoat;
    assert(trenchCoat.get_size() == 0);
    assert(trenchCoat.get_colour() == "void");
    assert(trenchCoat.get_price() == 0);
    assert(trenchCoat.get_quantity() == 0);
    assert(trenchCoat.get_photograph() == "invalid url");
    assert(trenchCoat.get_id() == "invalid url");

    trenchCoat = TrenchCoat{23, "yellow", 99, 3, "trench 1"};
    assert(trenchCoat.get_size() == 23);
    assert(trenchCoat.get_colour() == "yellow");
    assert(trenchCoat.get_price() == 99);
    assert(trenchCoat.get_quantity() == 3);
    assert(trenchCoat.get_photograph() == "trench 1");
    assert(trenchCoat.get_id() == "trench 1");

    TrenchCoat trenchCoat2{40, "blue", 120, 1, "trench 2"};
    assert(trenchCoat2.get_size() == 40);
    assert(trenchCoat2.get_colour() == "blue");
    assert(trenchCoat2.get_price() == 120);
    assert(trenchCoat2.get_quantity() == 1);
    assert(trenchCoat2.get_photograph() == "trench 2");
}


void TestTrenchCoat::test_copy() {
    TrenchCoat tc1{69, "black", 200, 4, "photo 3"}, tc2;
    tc2 = tc1;
    assert(tc2.get_size() == tc1.get_size());
    assert(tc2.get_colour() == tc1.get_colour());
    assert(tc2.get_price() == tc1.get_price());
    assert(tc2.get_quantity() == tc1.get_quantity());
    assert(tc2.get_photograph() == tc1.get_photograph());

    TrenchCoat tc3{tc2};
    assert(tc3.get_size() == tc1.get_size());
    assert(tc3.get_colour() == tc1.get_colour());
    assert(tc3.get_price() == tc1.get_price());
    assert(tc3.get_quantity() == tc1.get_quantity());
    assert(tc3.get_photograph() == tc1.get_photograph());
}


void TestTrenchCoat::test_setters() {
    TrenchCoat trench_coat;
    trench_coat.set_size(66);
    assert(trench_coat.get_size() == 66);
    trench_coat.set_colour("red");
    assert(trench_coat.get_colour() == "red");
    trench_coat.set_price(20);
    assert(trench_coat.get_price() == 20);
    trench_coat.set_quantity(10);
    assert(trench_coat.get_quantity() == 10);
    trench_coat.set_photograph("photo 2");
    assert(trench_coat.get_photograph() == "photo 2");
}


void TestTrenchCoat::test_operator_equal() {
    TrenchCoat tc1, tc2;
    assert(tc1 == tc2);
    tc1.set_size(20);
    assert(tc1 != tc2);
    tc1 = TrenchCoat{};
    tc1.set_colour("yellow");
    assert(tc1 != tc2);
    tc1 = TrenchCoat{};
    tc1.set_price(100);
    assert(tc1 != tc2);
    tc1 = TrenchCoat{};
    tc1.set_quantity(10);
    assert(tc1 != tc2);
    tc1 = TrenchCoat{};
    tc1.set_photograph("link 77");
    assert(tc1 != tc2);
}


void TestTrenchCoat::test_printable() {
    TrenchCoat trench_coat{40, "cyan", 100, 10, "photo 3"};
    std::string str_trench = trench_coat.printable();
    assert(str_trench == "Size: 40, Colour: cyan, Price: 100, Quantity: 10, Photograph: photo 3\n");
}


void TestTrenchCoat::test_streams() {
//    TrenchCoat trenchCoat{130, "pink", 2000, 10, "photo 17"};
//    std::stringstream ss;
//    ss << trenchCoat;
//    int size, price, quantity;
//    std::string write_result, colour, photograph;
//    std::cin.sync();
//    // Method 1 of testing operator<< overloading
//    std::getline(ss, write_result);
////    std::cout << write_result; // required for Method 1
//
////    Method 2 of testing operator<<  - UGLY
//    ss << trenchCoat;
//    ss >> write_result;
//    assert(write_result == "Size:");
//    ss >> size;
//    assert(size == trenchCoat.get_size());
//    ss >> write_result;
//    assert(write_result == "Colour:");
//    ss >> colour;
//    assert(colour == trenchCoat.get_colour());
//    ss >> write_result;
//    assert(write_result == "Price:");
//    ss >> price;
//    assert(price == trenchCoat.get_price());
//    ss >> write_result;
//    assert(write_result == "Quantity:");
//    ss >> quantity;
//    assert(quantity == trenchCoat.get_quantity());
//    ss >> write_result;
//    assert(write_result == "Photograph:");
//    char a;
//    ss.read(&a, 1);
//    getline(ss, photograph);
//    assert(photograph == trenchCoat.get_photograph());
//    ss >> write_result;
////    assert(write_result == "\n");
//    TrenchCoat tc2{size, colour, price, quantity, photograph};
//    assert(tc2 == trenchCoat);
//
//    ss.clear();
//    ss >> trenchCoat;
//    ss >> size;
//    ss >> colour;
//    ss >> price;
//    ss >> quantity;
//    ss >> photograph;
//
//    TrenchCoat tc3{size, colour, price, quantity, photograph};
//    assert(tc3 == trenchCoat);
////    std::cout<<tc3; // not required for Method 2

    // operator<< overloading;
    TrenchCoat tc1{131, "pink", 4672, 66, "link 0"};
    std::stringstream outputStream;
    outputStream << tc1;
    assert(outputStream.str() == "131,pink,4672,66,link 0\n");

    // operator>> overloading
    std::stringstream ss;
    ss << "120,blue,2150,10,link 1\n";
    TrenchCoat tc;
    ss >> tc;
    assert(tc.get_size() == 120);
    assert(tc.get_colour() == "blue");
    assert(tc.get_price() == 2150);
    assert(tc.get_quantity() == 10);
    assert(tc.get_photograph() == "link 1");

}

void TestDynamicVector::run_all_dynamic_vector() {
    DynamicVector<int> v(10);
    try{
        DynamicVector<int> v1(-4);
    }catch (DynamicVectorException& dve){
        assert(strcmp(dve.what(), "Invalid value for capacity!\n") == 0);
    }
    assert(v.length() == 0);

    v.add_to_position(0, 7);
    assert(v.length() == 1);
    assert(v.get_element(0) == 7);

    v.add_to_position(1, 12);
    v.add_to_position(2, -5);
    v.add_to_position(3, 45);
    assert(v.length() == 4);

    try{
        v.get_element(-1);
    }
    catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for getting element from DynamicVector!\n") == 0);
    }

    try{
        v.get_element(v.length());
    }
    catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for getting element from DynamicVector!\n") == 0);
    }

    try{
        v.set_element(-1, 15);
    }
    catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for setting element in Dynamic Vector!\n") == 0);
    }

    try{
        v.set_element(v.length(), 99);
    }
    catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for setting element in Dynamic Vector!\n") == 0);
    }

    try{
        v.add_to_position(-1, 7);
    }catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for adding an element to DynamicArray!\n") == 0);
    }

    try{
        v.add_to_position(v.length() + 1, 7);
    }catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for adding an element to DynamicArray!\n") == 0);
    }
    assert(v.length() == 4);

    assert(v.search(0) == -1);
    assert(v.search(7) == 0);
    assert(v.search(45) == 3);
    v.set_element(2, -8);
    assert(v.search(-5) == -1);
    assert(v.search(-8) == 2);

    int removed = v.get_element(1);
    v.remove_from_position(1);
    assert(v.length() == 3);
    assert(v.search(removed) == -1);
    try{
        v.remove_from_position(-1);
    }
    catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for removing an element from DynamicArray!\n") == 0);
    }
    try{
        v.remove_from_position(v.length());
    }
    catch (DynamicVectorException &dve){
        assert(strcmp(dve.what(), "Invalid position for removing an element from DynamicArray!\n") == 0);
    }
    v.add_to_position(0, 2);
    v.add_to_position(0, -1);
    assert(v.length() == 5);
    assert(v.search(-1) == 0);
    v.add_to_position(5, 21);
    v.add_to_position(6, 23);
    v.add_to_position(7, 25);
    v.add_to_position(8, 27);
    v.add_to_position(9, 29);
    v.add_to_position(10, 31);

    for(int index = 1; index <= 6; index = index + 1){
        v.remove_from_position(5);
    }
    for(int index = 1; index <= 3; index = index + 1){
        v.remove_from_position(1);
    }

    assert(v.length() == 2);
    DynamicVector<int> dv2{v};
    assert(dv2.length() == v.length());
    for(int index = 0; index < v.length(); index = index + 1){
        assert(dv2.get_element(index) == v.get_element(index));
    }

    DynamicVector<int> dv3;
    dv3 = v;
    assert(dv3.length() == v.length());
    for(int index = 0; index < v.length(); index = index + 1){
        assert(dv3.get_element(index) == v.get_element(index));
    }
    v = v;
    assert(dv3.length() == v.length());
    for(int index = 0; index < v.length(); index = index + 1){
        assert(dv3.get_element(index) == v.get_element(index));
    }

}





void TestDomain::run_all_domain() {
    TestTrenchCoat test_trench_coat;
    test_trench_coat.run_all_trench_coat();

    TestDynamicVector test_dynamic_vector;
    test_dynamic_vector.run_all_dynamic_vector();
}

