//
// Created by kamui on 26.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_USER_H
#define A45_915_PATRULESCU_SANDRINO_USER_H

#include <memory>
#include <vector>
#include "../domain/trench_coat.h"
#include "../storage/repository.h"
#include "csvAndhtml_repo.h"

class ShoppingCart{
private:
    std::vector<TrenchCoat> cart_data;
    int size;
    int price;
    std::string file_type;
public:
    explicit ShoppingCart(int max_size, const std::string& file_type_="none") : file_type{file_type_}{
        size = 0;
        price = 0;
    }
    int cart_size() const;
    int cart_price() const;
    void cart_add(const TrenchCoat&);
    std::string cart_list();
    void set_file(const std::string &file_type_);
    void display();
    void write();

};

class UserMode{
    friend class ShoppingCart;
private:
    std::shared_ptr<Repository<TrenchCoat, std::string>> repository{nullptr};
    WriteToFileRepository<TrenchCoat, std::string> *shopping_cart = nullptr;
    std::string file_type;
    TrenchCoat* elements = nullptr; // will be used for storing copy of the elements, in order to print them
    int size_of_elements; // will count how many distinct elements will be displayed
    int current; // hold the index of the current element available for showing to the user
    int price;
    void addToShoppingCart(TrenchCoat tc);
public:
    UserMode(std::shared_ptr<Repository<TrenchCoat, std::string>> repository_smart_ptr_): repository{repository_smart_ptr_} {
//        std::cout << "UserMode constructor\n";
        ;
        size_of_elements = 0;
        current = 0;
        price = 0;
    }
    ~UserMode(){
        if (shopping_cart != NULL){
            delete shopping_cart;
        }

    }
    /// \def makes available the elements for using add, get_current and next;
    /// \param desired_size - integer
    /// \return
    bool browse_prepare(int desired_size);
    int get_elements_size() const;
    std::string browse_get_current();
    void browse_next();
    void browse_add();

    void setShoppingCartSaveFileType(const std::string &file_type_);
    std::string getShoppingCartSaveFileType() const
    std::string basket_to_string();
    int getShoppingCartSum() const;
    std::string printableShoppingCart() const;
    void displayShoppingCart() const;

    void get_elements(TrenchCoat result[]);
    TrenchCoat get_from_repo(const std::string& id);
};

#endif //A45_915_PATRULESCU_SANDRINO_USER_H
