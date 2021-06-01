//
// Created by kamui on 24.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_TEST_SERVICE_H
#define A45_915_PATRULESCU_SANDRINO_TEST_SERVICE_H

#include "../service/admin.h"
#include "../exceptions/trench_coat_exceptions.h"
#include "../service/user.h"
#include <cassert>
class TestService{
public:
    void run_all_service();
};


template<typename TElem, typename  ID>
class TestAdmin{
private:
    std::shared_ptr<Repository<TElem, ID>> repo_shared_ptr{nullptr};
    TrenchCoatValidator trenchCoatValidator;
    Admin<TElem, ID> admin;
public:
    TestAdmin();
    explicit TestAdmin(std::shared_ptr<Repository<TElem, ID>> repo_ptr, TrenchCoatValidator tc_validator);
    void run_all_admin();
    void test_add_service();
    void test_remove_service();
    void test_update_service();
    void test_list_service();
//    void test(){
//        assert(1==1);
//        TrenchCoat tc1(120, "red", 200, 4, "link 1");
//        repo.add_to_repo(tc1);
//        admin.add_service(121, "blue", 400, 6, "link 2");
//        std::cout << repo.size();
//    }
};


class TestShoppingCart{
private:
    ShoppingCart& _shopping_cart;
public:
    explicit TestShoppingCart(ShoppingCart& shopping_cart): _shopping_cart(shopping_cart){
        ;
    }
    void test_shopping_cart();
};

class TestUserMode{
private:
    ShoppingCart& shoppingCart;
    UserMode& userMode;
public:
    explicit TestUserMode(UserMode& user_mode, ShoppingCart& shopping_cart): userMode(user_mode), shoppingCart(shopping_cart) {
            ;
    }
    void test_user_mode();
};

template<typename TElem, typename ID>
TestAdmin<TElem, ID>::TestAdmin() {
    std::cout << "TestAdmin default constructor" << std::endl;
}


template<typename TElem, typename ID>
TestAdmin<TElem, ID>::TestAdmin(std::shared_ptr<Repository<TElem, ID>> repo_ptr, TrenchCoatValidator tc_validator):repo_shared_ptr(repo_ptr), trenchCoatValidator(tc_validator), admin(repo_ptr, tc_validator) {
//    repo_shared_ptr = repo_ptr;
//    trenchCoatValidator = tc_validator;
//    admin = Admin<TElem, ID>(repo_shared_ptr, tc_validator);
}


template<typename TElem, typename ID>
void TestAdmin<TElem, ID>::test_add_service() {
    TrenchCoat tc1(120, "purple", 2000, 100, "link 3");
    repo_shared_ptr->add_to_repo(tc1);
//    TrenchCoat tc2(131, "yellow", 6000, 120, "link 4");
    assert(admin.add_service(107, "yellow", 10000, 100, "link 5") == true);
    assert(admin.add_service(119, "crimson", 400, 12, "link 1") == true);
    assert(repo_shared_ptr->size() == 3);
//    assert(0);

    try{
        admin.add_service(100, "cream", 6000, 200, "link 2");
    }
    catch (TrenchCoatValidatorException &e){
        assert(std::string(e.what()) == std::string("Invalid size for TrenchCoat!\n"));
    }

    try{
        admin.add_service(103, "cream", 6000, 200, "link 1");
    }
    catch (RepositoryException &e){
        assert(std::string(e.what()) == std::string("Repo cannot add: Element with given ID already exists!\n"));
    }
    assert(repo_shared_ptr->size() == 3);
}


template<typename TElem, typename ID>
void TestAdmin<TElem, ID>::test_remove_service() {
    int size = repo_shared_ptr->size();
    try {
        admin.remove_service("garbage");
    }
    catch (RepositoryException &e) {
        assert(std::string(e.what()) == std::string("Repo cannot remove: Element with given ID doesn't exist!\n"));
    }
    assert(size == repo_shared_ptr->size());
    assert(admin.remove_service("link 5") == true);
    assert(repo_shared_ptr->size() == size - 1);
}


template<typename TElem, typename ID>
void TestAdmin<TElem, ID>::test_update_service() {
    assert(admin.update_service("link 1", 133, "pink", 1200, 30, "link 1 new") == true);

    try {
        admin.update_service("link 1 new", 138, "magenta", 400, 50, "linking park");
    }
    catch (TrenchCoatValidatorException &e) {
        assert(std::string(e.what()) == std::string("Invalid size for TrenchCoat!\n"));
    }
    try{
        admin.update_service("link 1 new", 136, "red", 1201, 31, "link 3");
    }
    catch (RepositoryException &e) {
        assert(std::string(e.what()) == std::string("Repo cannot update: ID of given element belongs to an existing object!\n"));
    }
    try{
        admin.update_service("link 70", 127, "black", 1264, 100, "link 10");
    }
    catch (RepositoryException &e) {
        assert(std::string(e.what()) == std::string("Repo cannot update: No element with given ID!\n"));
    }
}


template<typename TElem, typename ID>
void TestAdmin<TElem, ID>::test_list_service() {
//    TrenchCoat tc1(120, "purple", 2000, 100, "link 3");
//    assert(admin.add_service(107, "yellow", 10000, 100, "link 5") == true); - removed
//    assert(admin.add_service(119, "crimson", 400, 12, "link 1") == true); - updated to ("link 1", 133, "pink", 1200, 30, "link 1 new")
    std::string result = admin.list_service();
    std::string expected_result;
    expected_result = expected_result + "Size: 120, Colour: purple, Price: 2000, Quantity: 100, Photograph: link 3\n";
    expected_result = expected_result + "Size: 133, Colour: pink, Price: 1200, Quantity: 30, Photograph: link 1 new\n";
    assert(result == expected_result);
//    std::cout << result;
    admin.remove_service("link 3");
    admin.remove_service("link 1 new");
    assert(repo_shared_ptr->size() == 0);
    result = admin.list_service();
    assert(result == "Repository is empty!\n");
}


template<typename TElem, typename ID>
void TestAdmin<TElem, ID>::run_all_admin() {
    test_add_service();
    test_remove_service();
    test_update_service();
    test_list_service();
}


#endif //A45_915_PATRULESCU_SANDRINO_TEST_SERVICE_H
