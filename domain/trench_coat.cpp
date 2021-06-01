//
// Created by kamui on 23.03.2021.
//

#include "trench_coat.h"
#include<ostream>
#include <vector>
#include <utils.h>

TrenchCoat::TrenchCoat() {
    size = 0;
    colour = "void";
    price = 0;
    quantity = 0;
    photograph = "invalid url";

}


TrenchCoat::TrenchCoat(int size, std::string colour, int price, int quantity, std::string photograph) {
    this->size = size;
    this->colour = std::move(colour);
    this->price = price;
    this->quantity= quantity;
    this->photograph = std::move(photograph);
}


TrenchCoat::TrenchCoat(const TrenchCoat &trench_coat) {
    size = trench_coat.size;
    colour = trench_coat.colour;
    price = trench_coat.price;
    quantity = trench_coat.quantity;
    photograph = trench_coat.photograph;
}


TrenchCoat& TrenchCoat::operator=(const TrenchCoat &trench_coat) {
    size = trench_coat.get_size();
    colour = trench_coat.get_colour();
    price = trench_coat.get_price();
    quantity = trench_coat.get_quantity();
    photograph = trench_coat.get_photograph();
    return *this;
}


TrenchCoat::~TrenchCoat() {
//    std::cout<<"TrenchCoat destroyed.\n"<<std::endl;
}


bool TrenchCoat::operator==(TrenchCoat const&trench_coat) const {
    if(size != trench_coat.get_size()){
        return false;
    }
    if(colour != trench_coat.get_colour()){
        return false;
    }
    if(price != trench_coat.get_price()){
        return false;
    }
    if(quantity != trench_coat.get_quantity()){
        return false;
    }
    if(photograph != trench_coat.photograph){
        return false;
    }
    return true;
}


bool TrenchCoat::operator!=(const TrenchCoat &trench_coat) const {
    return !(trench_coat == *this);
}


std::string TrenchCoat::get_id() const {
    return this->photograph;
}


int TrenchCoat::get_size() const {
    return this->size;
}


std::string TrenchCoat::get_colour() const{
    return this->colour;
}


int TrenchCoat::get_price() const {
    return this->price;
}


std::string TrenchCoat::get_photograph() const {
    return this->photograph;
}


int TrenchCoat::get_quantity() const {
    return this->quantity;
}


void TrenchCoat::set_size(int new_size) {
    this->size = new_size;
}


void TrenchCoat::set_colour(std::string new_colour) {
    this->colour = std::move(new_colour);
}

void TrenchCoat::set_price(int new_price) {
    this->price = new_price;
}

void TrenchCoat::set_quantity(int new_quantity) {
    this->quantity = new_quantity;
}

void TrenchCoat::set_photograph(std::string new_photograph) {
    this->photograph = std::move(new_photograph);
}


std::string TrenchCoat::printable() const {
    std::string result;
    result = result + "Size: " + std::to_string(this->size);
    result = result + ", Colour: " + this->colour;
    result = result + ", Price: " + std::to_string(this->price);
    result = result + ", Quantity: " + std::to_string(this->quantity);
    result = result + ", Photograph: " + this->photograph + "\n";
    return result;
}

std::ostream &operator<<(std::ostream &os, const TrenchCoat &tc) {
    // second variant
//    os << tc.printable();

//    os << "Size: " + std::to_string(tc.size);
//    os << " Colour: " + tc.colour;
//    os << " Price: " + std::to_string(tc.price);
//    os << " Quantity: " + std::to_string(tc.quantity);
//    os << " Photograph: " + tc.photograph + "\n";

    os << std::to_string(tc.size) << ",";
    os << tc.colour << ",";
    os << std::to_string(tc.price) << ",";
    os << std::to_string(tc.quantity) << ",";
    os << tc.photograph << "\n";
    return os;
}

std::istream &operator>>(std::istream &is, TrenchCoat &tc) {
//    is >> tc.size;
//    is.sync();
//    getline(is, tc.colour);
//    is >> tc.price >> tc.quantity;
//    is.sync();
//    getline(is, tc.photograph);
//    is.sync();

    std::string line;
    getline(is, line);
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 5) {
        return is;
    }
    tc.size = std::stoi(tokens[0]);
    tc.colour = tokens[1];
    tc.price = std::stoi(tokens[2]);
    tc.quantity = std::stoi(tokens[3]);
    tc.photograph = tokens[4];
    return is;
}


bool size_is(const TrenchCoat& tc, void** argv){
    return (tc.get_size() == *(int *)argv[0]);
}
