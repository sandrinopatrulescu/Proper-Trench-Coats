//
// Created by kamui on 24.03.2021.
//

#include "test_service.h"


void TestService::run_all_service() {
    std::shared_ptr<Repository<TrenchCoat, std::string>> repo(new Repository<TrenchCoat, std::string>);
    TrenchCoatValidator tc_valid;
    TestAdmin<TrenchCoat, std::string> test_admin(repo, tc_valid);
    test_admin.run_all_admin();

    ShoppingCart shopping_cart(10);
    TestShoppingCart test_shopping_cart(shopping_cart);
    test_shopping_cart.test_shopping_cart();

    TrenchCoat tc1(120, "blue", 250, 4, "l 80");
    TrenchCoat tc2(132, "red", 750, 2, "l 81");
    TrenchCoat tc3(125, "pink", 200, 8, "l 82");
    TrenchCoat tc4(132, "red", 300, 5, "l n83");
    repo->add_to_repo(tc1);
    repo->add_to_repo(tc2);
    repo->add_to_repo(tc3);
    repo->add_to_repo(tc4);

    UserMode user_mode(repo);
    TestUserMode test_user_mode(user_mode, shopping_cart);
    test_user_mode.test_user_mode();




//    Repository<TrenchCoat, std::string> repo;
//    TrenchCoatValidator tc_valid;
//    TestAdmin<TrenchCoat, std::string> test_admin, test_admin2(repo, tc_valid);
//    TrenchCoat tc1(112, "green", 500, 12, "link 3");
//    repo.add_to_repo(tc1);
//    test_admin2.test();
//    test_admin.test();
//    Admin<TrenchCoat, std::string> admin, admin2{&repo, tc_valid};
//    assert(admin.add_service(112, "brown", 200, 20, "link 2"));
//    admin2.add_service(112, "brown", 200, 20, "link 2");
//    std::cout << std::endl << repo.size();
//
//    Repository<TrenchCoat, std::string> repo69;
//    repo69.add_to_repo(tc1);
//    assert(repo69.size() == 1);
//    Admin<TrenchCoat, std::string> admin69(&repo69, tc_valid);
//    admin69.add_service(112, "brown", 200, 20, "link 2");
//    std::cout << std::endl << repo69.size();
}

void TestShoppingCart::test_shopping_cart() {
        assert(_shopping_cart.cart_size() == 0);
        assert(_shopping_cart.cart_price() == 0);
        assert(_shopping_cart.cart_list() == "Shopping cart is empty!\n"); //	"\tTotal price: 0\n"
        TrenchCoat tc1(120, "red", 500, 1, "l 66");
        _shopping_cart.cart_add(tc1);
        assert(_shopping_cart.cart_size() == 1);
        assert(_shopping_cart.cart_price() == 500);
        tc1.set_quantity(1);
        std::string result = _shopping_cart.cart_list();
        assert(result == tc1.printable() + "\tTotal price: 500\n");
        tc1.set_quantity(9);
        _shopping_cart.cart_add(tc1);
        assert(_shopping_cart.cart_size() == 1);
        assert(_shopping_cart.cart_price() == 500 * 10);
        tc1.set_photograph("l 67");
        tc1.set_price(100);
        tc1.set_quantity(10);
        _shopping_cart.cart_add(tc1);
        assert(_shopping_cart.cart_size() == 2);
        assert(_shopping_cart.cart_price() == 6000);

}

void TestUserMode::test_user_mode() {
    //breakpoint to check repo
//    assert(userMode.get_elements_size() == 0);
//    assert(userMode.browse_prepare(101) == false);
//    assert(userMode.browse_prepare(138) == false);
//    assert(userMode.browse_prepare(-1) == true);
//    assert(userMode.get_elements_size() == 4);
//    TrenchCoat elements[4];
//    userMode.get_elements(elements);
//    assert(userMode.browse_get_current() == elements[0].printable());
//    userMode.browse_next();
//    assert(userMode.browse_get_current() == elements[1].printable());
//    userMode.browse_next();
//    assert(userMode.browse_get_current() == elements[2].printable());
//    userMode.browse_next();
//    assert(userMode.browse_get_current() == elements[3].printable());
//    userMode.browse_next();
//    assert(userMode.browse_get_current() == elements[0].printable());
//    userMode.browse_add();
//    userMode.get_elements(elements);
//    assert(elements[0].get_quantity() == 3);
//    assert(shoppingCart.cart_size() == 3);
//    assert(shoppingCart.cart_price() == 6250);
//    assert(userMode.getShoppingCartSum() == 6250);
//    assert(userMode.get_from_repo(elements[0].get_id()).get_quantity() == 3);
//    userMode.get_elements(elements);
//    assert(userMode.browse_prepare(132) == true);
//    assert(userMode.browse_get_current() == elements[1].printable());
//    userMode.browse_next();
//    assert(userMode.browse_get_current() == elements[3].printable());
//    userMode.browse_next();
//    assert(userMode.browse_get_current() == elements[1].printable());
//
//    assert(userMode.basket_to_string() == shoppingCart.cart_list());
//    assert(userMode.getShoppingCartSum() == 6250);

}
