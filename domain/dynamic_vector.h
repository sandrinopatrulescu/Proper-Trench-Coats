//
// Created by kamui on 23.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_DYNAMIC_VECTOR_H
#define A45_915_PATRULESCU_SANDRINO_DYNAMIC_VECTOR_H

#include <exception>
#include <stdexcept>
#include <iostream>
#include "../exceptions/dynamic_vector_exceptions.h"

template<typename TElem>
class DynamicVector{
private:
    TElem* elements;
    int size{};
    int capacity{};
public:
    void destroy();
    DynamicVector();
    explicit  DynamicVector(int capacity);
    DynamicVector(const DynamicVector &vector);
    DynamicVector& operator=(const DynamicVector<TElem>& vector);
    ~DynamicVector();

    int length() const;
    int search(TElem element);
    const TElem& get_element(int position) const;
    void set_element(int position, TElem element);
    void add_to_position(int position, TElem element);
    void remove_from_position(int position);
    void remove(TElem element);
    void replace(TElem old_element, TElem new_element);
};


template<typename TElem>
void DynamicVector<TElem>::destroy() {
    delete[] elements;
    size = 0;
    capacity = 0;
}


template<typename TElem>
DynamicVector<TElem>::DynamicVector() {
    capacity = 10;
    size = 0;
    elements = new TElem[capacity];
//    std::cout << "DynamicVector default constructed" << std::endl;
}


template<typename TElem>
DynamicVector<TElem>::DynamicVector(int capacity) {
    this->size = 0;
    this->capacity = capacity;
    if(capacity < 0){
        throw DynamicVectorException("Invalid value for capacity!\n");
    }
    this->elements = new TElem[capacity];
//    std::cout << "DynamicVector constructed" << std::endl;
}


template<typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector &vector) {
    size = vector.size;
    capacity = vector.capacity;
    elements = new TElem[size];
    int index;
    for(index = 0; index < size; index = index + 1){
        elements[index] = vector.elements[index];
    }
//    std::cout << "DynamicVector copied" << std::endl;
}


template<typename TElem>
DynamicVector<TElem> & DynamicVector<TElem>::operator=(const DynamicVector<TElem> &vector) {
//    std::cout << "DynamicVector assigned ";
    if(this == &vector){
//        std::cout << "& returned same object dereferenced" << std::endl;
        return *this;
    }
    else
    {
        size = vector.size;
        capacity = vector.capacity;
        TElem* new_elements;
        new_elements = new TElem[size];
        int index;
        for(index = 0; index < size; index = index + 1) {
            new_elements[index] = vector.elements[index];
        }
        delete[] elements;
        elements = new_elements;
//        std::cout << "& allocated new vector" << std::endl;
        return *this;
    }
}


template<typename TElem>
DynamicVector<TElem>::~DynamicVector<TElem>() {
    delete[] this->elements;
    this->size = 0;
    this->capacity = 0;
//    std::cout << "DynamicVector destroyed" << std::endl;
}


template<typename TElem>
int DynamicVector<TElem>::length() const{
    return this->size;
}


template<typename TElem>
int DynamicVector<TElem>::search(TElem element) {
    int index;
    for(index = 0; index < this->size; index = index + 1){
        if(element == this->elements[index])
            return index;
    }
    return -1;
}

template<typename TElem>
const TElem& DynamicVector<TElem>::get_element(int position) const{
    if(position < 0  || position >= this->size){
        throw DynamicVectorException("Invalid position for getting element from DynamicVector!\n");
    }
    else{
        return this->elements[position];
    }
}

template<typename TElem>
void DynamicVector<TElem>::set_element(int position, TElem element) {
    if(position < 0  || position >= this->size){
        throw DynamicVectorException("Invalid position for setting element in Dynamic Vector!\n");
    }
    else{
        this->elements[position] = element;
    }
}

template<typename TElem>
void DynamicVector<TElem>::add_to_position(int position, TElem element) {
    if(position < 0 || position > this->size){
        throw DynamicVectorException("Invalid position for adding an element to DynamicArray!\n");
    }
    else{
        if(this->size == this->capacity)
        {
            this->capacity = 2 * this->capacity;
            TElem* new_vector;
            new_vector = new TElem[this->capacity];
            int index;
            for(index = 0; index < this->size; index = index + 1)
            {
                new_vector[index] = this->elements[index];
            }
            delete[] this->elements;
            this->elements = new_vector;
        }
        this->size = this->size + 1;
        int index;
        for(index = this->size - 1; index > position; index = index - 1)
        {
            this->elements[index] = this->elements[index - 1];
        }
        this->elements[position] = element;
    }
}

template<typename TElem>
void DynamicVector<TElem>::remove_from_position(int position) {
    if(position < 0 || position >= this->size){
        throw DynamicVectorException("Invalid position for removing an element from DynamicArray!\n");
    }
    else{
        int index;
        for(index = position; index < this->size - 1; index = index + 1)
        {
            this->elements[index] = this->elements[index + 1];
        }
        this->size = this->size - 1;
    }
    if(this->size <= this->capacity / 4){
        this->capacity = 2 * this->size + !this->size;
        TElem* new_vector;
        new_vector = new TElem[this->capacity];
        int index;
        for(index = 0; index < this->size; index = index + 1)
        {
            new_vector[index] = this->elements[index];
        }
       delete[] this->elements;
        this->elements = new_vector;
    }
}

template<typename TElem>
void DynamicVector<TElem>::remove(TElem element) {
    int position = this->search(element);
    this->remove_from_position(position);
}

template<typename TElem>
void DynamicVector<TElem>::replace(TElem old_element, TElem new_element) {
    int position = this->search(old_element);
    this->set_element(position, new_element);
}


#endif //A45_915_PATRULESCU_SANDRINO_DYNAMIC_VECTOR_H
