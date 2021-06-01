//
// Created by kamui on 26.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_MENU_UI_H
#define A45_915_PATRULESCU_SANDRINO_MENU_UI_H

#include "../service/admin.h"
#include "../service/user.h"

class MenuUI{
private:
    Admin<TrenchCoat, std::string> &admin;
    UserMode &user;
    std::string print_options[3][6];
    int menu_count;
    int options_count[3];
    using VoidUIFunctions = void (MenuUI::*)();
    VoidUIFunctions void_ui_functions[3][5];
    using BoolUIFunctions = bool (MenuUI::*)();
    BoolUIFunctions bool_ui_functions[3];
public:
    MenuUI(Admin<TrenchCoat, std::string> &admin, UserMode &user): admin(admin), user(user){
        menu_count = 2;

        options_count[0] = 2; // at start: admin or user
        options_count[1] = 4; // inside admin
        options_count[2] = 3; // inside user

        print_options[0][0] = "     0. Exit!\n";
        print_options[0][1] = "     1. Administrator mode.\n";
        print_options[0][2] = "     2. User mode.\n";

        print_options[1][0] = "     0. Exit!\n";
        print_options[1][1] = "     1. Add.\n";
        print_options[1][2] = "     2. Update.\n";
        print_options[1][3] = "     3. Remove.\n";
        print_options[1][4] = "     4. List.\n";
        print_options[1][5] = "     5. Go back to mode selection.\n";

        print_options[2][0] = "     0. Exit!\n";
        print_options[2][1] = "     1. Browse items.\n";
        print_options[2][2] = "     2. Shopping cart.\n";
        print_options[2][3] = "     3. Go back to mode selection.\n";

        void_ui_functions[1][1] = &MenuUI::ui_admin_add;
        void_ui_functions[1][2] = &MenuUI::ui_admin_update;
        void_ui_functions[1][3] = &MenuUI::ui_admin_remove;
        void_ui_functions[1][4] = &MenuUI::ui_admin_list;
        
        void_ui_functions[2][1] = &MenuUI::ui_user_browse;
        void_ui_functions[2][2] = &MenuUI::ui_list_shopping_cart;
        void_ui_functions[2][3] = &MenuUI::ui_display_shopping_cart;

        bool_ui_functions[1] = &MenuUI::ui_admin_menu;
        bool_ui_functions[2] = &MenuUI::ui_user_menu;


//        std::cout << "MenuUI constructor\n";
    }
    void run_ui();
    void ui_print_options(int number);
    void ui_main_menu();
    bool ui_admin_menu();
    bool ui_user_menu();
    void ui_admin_add();
    void ui_admin_update();
    void ui_admin_remove();
    void ui_admin_list();

    void ui_user_browse();
    /// \attention shows price per item
    void ui_list_shopping_cart();
    void ui_display_shopping_cart();
};

#endif //A45_915_PATRULESCU_SANDRINO_MENU_UI_H
