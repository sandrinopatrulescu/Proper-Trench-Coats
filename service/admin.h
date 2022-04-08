//
// Created by kamui on 24.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_ADMIN_H
#define A45_915_PATRULESCU_SANDRINO_ADMIN_H

#include <test_repository.h>
#include "../validators/trench_coat_validator.h"
#include <memory>

template<typename TElem, typename  ID>
class Admin{
private:
    Repository<TElem, ID>* repo;
    std::shared_ptr<Repository<TElem, ID>> repo_shared_ptr{nullptr};
//    std::shared_ptr<Repository<TElem, ID>> repo_shared_ptr{repo};
    TrenchCoatValidator trench_coat_validator;
public:
    Admin();
    explicit Admin(std::shared_ptr<Repository<TElem, ID>> repo_ptr, TrenchCoatValidator tc_validator);
    bool add_service(int size, const std::string &colour, int price, int quantity, const std::string &photo);
    bool remove_service(const std::string& photo);
    bool update_service(const std::string& old_photo, int new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photo);
    std::string list_service();
    std::vector<TrenchCoat> getAll() const;

};


template<typename TElem, typename ID>
Admin<TElem, ID>::Admin() {
//    std::cout << "Admin constructed" << std::endl;
}


template<typename TElem, typename ID>
Admin<TElem, ID>::Admin(std::shared_ptr<Repository<TElem, ID>> repo_ptr, TrenchCoatValidator tc_validator) {
    repo_shared_ptr = repo_ptr;
    trench_coat_validator = tc_validator;
}


template<typename TElem, typename ID>
bool Admin<TElem, ID>::add_service(int size, const std::string& colour, int price, int quantity, const std::string& photo) {
    TrenchCoat trench_coat(size, colour, price, quantity, photo);
    int validation_status = trench_coat_validator.validate(trench_coat);
    if(validation_status){
        int repository_status = repo_shared_ptr->add_to_repo(trench_coat);
        if(repository_status){
            return true;
        }
    }
    return false;
}


template<typename TElem, typename ID>
bool Admin<TElem, ID>::update_service(const std::string& old_photo, int new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photo){
    TrenchCoat new_trench_coat(new_size, new_colour, new_price, new_quantity, new_photo);
    int validation_status = trench_coat_validator.validate(new_trench_coat);
    if(validation_status){
        int repository_status = repo_shared_ptr->update_in_repo(old_photo, new_trench_coat);
        if(repository_status){
            return true;
        }
    }
    return false;
}


template<typename TElem, typename ID>
bool Admin<TElem, ID>::remove_service(const std::string& photo) {
    int repository_status = repo_shared_ptr->remove_from_repo(photo);
    if(repository_status){
        return true;
    }
    return false;
}


template<typename TElem, typename ID>
std::string Admin<TElem, ID>::list_service() {
    int size = repo_shared_ptr->size();
    TElem elements[size];
    repo_shared_ptr->get_all(elements);
    int index = 0;
    std::string result;
    while (index < size){
        result = result + elements[index].printable();
        index = index + 1;
    }
    if (size == 0){
        return "Repository is empty!\n";
    }
    else{
        return result;
    }
}

template<typename TElem, typename ID>
std::vector<TrenchCoat> Admin<TElem, ID>::getAll() const {
    std::vector<TrenchCoat> result = this->repo_shared_ptr->get_all();
    return result;
}


#endif //A45_915_PATRULESCU_SANDRINO_ADMIN_H
