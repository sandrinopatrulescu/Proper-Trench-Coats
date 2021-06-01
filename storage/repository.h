//
// Created by kamui on 24.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_REPOSITORY_H
#define A45_915_PATRULESCU_SANDRINO_REPOSITORY_H

#include <iostream>
#include <vector>
#include "../domain/dynamic_vector.h"
#include "../exceptions/repository_exceptions.h"


template<typename TElem, typename ID>
class Repository{
private:
    DynamicVector<TElem> data;
public:
    Repository();
//    Repository(const Repository &arg_repo);
//    Repository& operator=(Repository arg_repo);
    ~Repository<TElem, ID>();
    virtual int size() const;
    virtual bool search_by_id(const ID &id) const;
    virtual bool add_to_repo(const TElem &element);
    virtual bool remove_from_repo(const ID &id);
    virtual bool update_in_repo(const ID &id, const TElem &new_element);
    virtual TElem get_element(const ID &id) const;

    /// \def gets all elements from the repository
    /// \param result - an array of TElements of the size of the repository
    virtual void get_all(TElem result[]);
    virtual std::vector<TElem> get_all() const;
    virtual int filter(TElem result[], bool (*filter_function)(const TElem&, void **), void** argv);
    TElem iterate();
};


template<typename TElem, typename ID>
Repository<TElem, ID>::Repository() {
//    std::cout <<"Repository default constructor" << std::endl;
}

//template<typename TElem, typename ID>
//Repository<TElem, ID>::Repository(const Repository &arg_repo) {
////    std::cout <<"Repository copy constructor" << std::endl;
//    int index = 0;
//    while(index < arg_repo.size()){
//        data.add_to_position(index, arg_repo.data.get_element(index));
//        index = index + 1;
//    }
//    int index = 0;
//    while(index < arg_repo.size()){
//        data.add_to_position(index, arg_repo.data.get_element(index));
//        index = index + 1;
//    }
//}


//template<typename TElem, typename ID>
//Repository<TElem, ID> &Repository<TElem, ID>::operator=(Repository arg_repo) {
////    data.destroy();
////    data = arg_repo.data;
////    for(int index = 0; index < arg_repo.size(); data.add_to_position(index, arg_repo.get_element(index)), index = index + 1);
//
//    this->data = arg_repo.data;
//    return *this;
//}


template<typename TElem, typename ID>
Repository<TElem, ID>::~Repository<TElem, ID>() {
//    std::cout <<"Repository default destroyer" << std::endl;
}


template<typename TElem, typename ID>
int Repository<TElem,ID>::size() const{
    return this->data.length();
}


template<typename TElem, typename ID>
bool Repository<TElem,ID>::search_by_id(const ID &id) const{
    int index = 0;
    while(index < this->data.length()){
        TElem element;
        element = this->data.get_element(index);
        if(element.get_id() == id){
            return true;
        }
        index = index + 1;
    }
    return false;
}

template<typename TElem, typename ID>
bool Repository<TElem,ID>::add_to_repo(const TElem &element) {
    ID id;
    if (this->search_by_id(element.get_id()) == true){
        throw RepositoryException("Repo cannot add: Element with given ID already exists!\n");
    }
    else {
        this->data.add_to_position(this->size(), element);
        return true;
    }
}

template<typename TElem, typename ID>
bool Repository<TElem,ID>::remove_from_repo(const ID &id) {
    if (search_by_id(id) == false){
        throw RepositoryException("Repo cannot remove: Element with given ID doesn't exist!\n");
    }
    else{
        TElem elem = this->get_element(id);
        data.remove(elem);
        return true;
    }
}

template<typename TElem, typename ID>
bool Repository<TElem,ID>::update_in_repo(const ID &id, const TElem &new_element) {
    TElem old_elem, existing;
    // verify and get element of old ID
    if (this->search_by_id(id) == false){
        throw RepositoryException("Repo cannot update: No element with given ID!\n");
    }
    else {
        old_elem = this->get_element(id);
    }
    if (this->search_by_id(new_element.get_id()) == true){
        existing = this->get_element(new_element.get_id());
        if (existing != old_elem){
            throw RepositoryException("Repo cannot update: ID of given element belongs to an existing object!\n");
        }
    }
    this->data.replace(old_elem, new_element);
    return true;
}


template<typename TElem, typename ID>
TElem Repository<TElem,ID>::get_element(const ID &id) const{
    int index = 0;
    TElem element;
    while (index < this->size()){
        element = data.get_element(index);
        if (element.get_id() == id){
            break;
        }
        index = index + 1;
    }
    if(index == this->size()){
        throw RepositoryException("Repo cannot get: Given ID belongs to NO element!\n");
    }
    else{
        return element;
    }
}


template<typename TElem, typename ID>
void Repository<TElem,ID>::get_all(TElem result[]) {
    int index = 0;
    while(index < data.length()){
        result[index] = data.get_element(index);
        index = index + 1;
    }
}

template<typename TElem, typename ID>
int Repository<TElem, ID>::filter(TElem result[], bool (*filter_function)(const TElem&, void**), void** argv) {
    int size = 0, index = 0;
    while (index < data.length()) {
        TElem current = data.get_element(index);
        if(filter_function(current, argv) == true) {
            result[size] = current;
            size = size + 1;
        }
        index = index + 1;
    }
    return size;
}

template<typename TElem, typename ID>
TElem Repository<TElem, ID>::iterate() {
    static TElem element;
    static int state = 0;
    static int index = 0;
    switch (state) {
        case 0:
            state = 1;
            for(index = 0; index < data.length(); index = index + 1){
                return data.get_element(index);
                case 1:
                    ;
            }
    }
    state = 0;
//    index = 0;
    return iterate();
}

template<typename TElem, typename ID>
std::vector<TElem> Repository<TElem, ID>::get_all() const {
    std::vector<TElem> result;
    for (int index = 0; index < data.length(); ++index) {
        result.push_back(data.get_element(index));
    }
    return result;
}


#endif //A45_915_PATRULESCU_SANDRINO_REPOSITORY_H
