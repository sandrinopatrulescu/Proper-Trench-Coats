//
// Created by kamui on 26.03.2021.
//

#include "menu_ui.h"


void MenuUI::run_ui(){
    ui_main_menu();

}


void MenuUI::ui_print_options(int number) {
    std::cout << "\n\n";
    for(int index = 0; index <= options_count[number]; index = index + 1){
        std::cout << print_options[number][index];
    }
    if(number != 0){
        std::cout << print_options[number][options_count[number] + 1];
    }
    std::cout << "Enter option number: ";
}


void MenuUI::ui_main_menu(){
    std::string user_input;
    int running, parsed_user_input;
    running = true;
    while (running){
        ui_print_options(0);
        std::cin >> user_input;
        std::cin.ignore();
        try {
            parsed_user_input = stoi(user_input);
            if(parsed_user_input == 0){
                running = false;
//            break;
            }
            else if(parsed_user_input > 0 && parsed_user_input <= menu_count){
                running = (this->*bool_ui_functions[parsed_user_input])();

            }
        }
        catch (std::invalid_argument &input_e) {
            std::cout << "Invalid option!\n";
        }
    }
}


bool MenuUI::ui_admin_menu() {
    std::string user_input;
    int parsed_user_input;

    while (true) {
        ui_print_options(1);
        std::cin >> user_input;
        std::cin.ignore();
        try {
            parsed_user_input = std::stoi(user_input);
            if(parsed_user_input == 0) {
                return false;
            }
            else if(parsed_user_input > 0 && parsed_user_input <= options_count[1]){
                (this->*void_ui_functions[1][parsed_user_input])();
            }
            else if(parsed_user_input == options_count[1] + 1){
                return true;
            }
        }
        catch (std::invalid_argument &input_e){
            std::cout << "Invalid option!\n";
        }
    }
}


void MenuUI::ui_admin_add() {
    std::string string_size, colour, string_price, string_quantity, photograph;
    int size, price, quantity;
    while (true) {
        std::cout << "Enter size: "; getline(std::cin, string_size);
        try {
            size = std::stoi(string_size);
            break;
        }
        catch (std::invalid_argument &invalid_argument) {
            std::cout << "Invalid type for size!\n";
        }
    }
    std::cout << "Enter colour: "; getline(std::cin, colour);
    while (true) {
        std::cout << "Enter price: "; getline(std::cin, string_price);
        try {
            price = std::stoi(string_price);
            break;
        }
        catch (std::invalid_argument &invalid_argument) {
            std::cout << "Invalid type for price!\n";
        }
    }
    while (true) {
        std::cout << "Enter quantity: "; getline(std::cin, string_quantity);
        try {
            quantity = std::stoi(string_quantity);
            break;
        }
        catch (std::invalid_argument &invalid_argument) {
            std::cout << "Invalid type for quantity!\n";
        }
    }
    std::cout << "Enter photograph: "; getline(std::cin, photograph);
    try {
        admin.add_service(size, colour, price, quantity, photograph);
        std::cout << "Success!\n";
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }
}


void MenuUI::ui_admin_update() {
    std::string old_photo, string_new_size, new_colour, string_new_price, string_new_quantity, new_photograph;
    int new_size, new_price, new_quantity;
    std::cout << "Enter old photo: ";
    getline(std::cin, old_photo);
    while (true) {
        std::cout << "Enter new size: "; getline(std::cin, string_new_size);
        try {
            new_size = stoi(string_new_size);
            break;
        }
        catch (std::invalid_argument &invalid_argument) {
            std::cout << "Invalid type for size!\n";
        }
    }
    std::cout << "Enter new colour: "; getline(std::cin, new_colour);
    while (true) {
        std::cout << "Enter new price: "; getline(std::cin, string_new_price);
        try {
            new_price = std::stoi(string_new_price);
            break;
        }
        catch (std::invalid_argument &invalid_argument) {
            std::cout << "Invalid type for price!\n";
        }
    }
    while (true) {
        std::cout << "Enter new quantity: "; getline(std::cin, string_new_quantity);
        try {
            new_quantity = std::stoi(string_new_quantity);
            break;
        }
        catch (std::invalid_argument &invalid_argument) {
            std::cout << "Invalid type for quantity!\n";
        }
    }
    std::cout << "Enter new photograph: "; getline(std::cin, new_photograph);
    try {
        admin.update_service(old_photo, new_size, new_colour, new_price, new_quantity, new_photograph);
        std::cout << "Success!\n";
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }
}


void MenuUI::ui_admin_remove() {
    std::string photograph;
    std::cout << "Enter photograph: ";
    getline(std::cin, photograph);
    try {
        admin.remove_service(photograph);
        std::cout << "Success!\n";
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }
}


void MenuUI::ui_admin_list() {
    std::string result = admin.list_service();
    std::cout << result;
}


bool MenuUI::ui_user_menu() {
    int file_type;
    std::string file_types[3][2];
    file_types[0][0] = "0. No extra file\n";
    file_types[1][0] = "1. HTML\n";
    file_types[2][0] = "2. CSV\n";
    file_types[0][1] = "none";
    file_types[1][1] = "html";
    file_types[2][1] = "csv";
    //std::cout << "1. HTML\n2.CSV\n\tEnter file type: "; std::cin >> file_type;
    std::string message = file_types[0][0].append(file_types[1][0]).append(file_types[2][0]).append("\tEnter file type: ");
    std::cout << message;
    while (!(std::cin >> file_type)) {
        std::cout << "Please enter a valid option!\n";
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }
    if (file_type == 0) {
        this->options_count[2] = 2; // hide the option to open the file using a program
        print_options[2][3] = "     3. Go back to mode selection.\n";
    }
    else {
        this->options_count[2] = 3; // show the option to open the file using a program
        print_options[2][3] = "     3. Display (open file in default application).\n";
        print_options[2][4] = "     4. Go back to mode selection.\n";
    }
    this->user.setShoppingCartSaveFileType(file_types[file_type][1]);

    std::string user_input;
    int parsed_user_input;
    while (true) {
        ui_print_options(2);
        std::cin >> user_input;
        std::cin.ignore();
        try {
            parsed_user_input = stoi(user_input);
            if(parsed_user_input == 0){
                return false;
            }
            else if(parsed_user_input > 0 && parsed_user_input <= options_count[2]){
                (this->*void_ui_functions[2][parsed_user_input])();
            }
            else if(parsed_user_input == options_count[2] + 1){
                return true;
            }
        }
        catch (std::invalid_argument &input_e) {
            std::cout << "Invalid option!\n";
        }
    }
}


void MenuUI::ui_user_browse() {
    std::string string_size;
    int size;
//        std::cin.clear();
//        while (std::cin.get() != '\n')
//        {
//            continue;
//        }
    while (true) {
      std::cout << "Enter desired size: ";
      std::cin.sync();
      getline(std::cin, string_size);
      if (string_size.empty()) {
          size = -1;
          user.browse_prepare(size);
          break;
      }
      try {
          size = stoi(string_size);
          if(user.browse_prepare(size) == false){
              std::cout << "Invalid size value!\n";
          }
          else {
              break;
          }
      }
      catch (std::invalid_argument &invalid_argument) {
          std::cout << "Invalid size format!\n";
      }
    }

    //      ->  result = repo.filter(elem.get_size() == size);
    // TODO: iterator or WHAT???
    //  no idea of other alternatives, so iterator methods were implemented in UserMode and are used in ui
    if(user.get_elements_size() == 0){
        std::cout << "No match for browsing!";
        return;
    }
    while (true){
        std::string result = user.browse_get_current();
        std::cout << result;
        std::cout << "0. Quit browsing!\n" << "1. Add.\n" << "2. Don't add\n";
        std::string user_input;
        int parsed_user_input;
        std::cin.sync();
        getline(std::cin, user_input);
        try {
          parsed_user_input = stoi(user_input);
          if (parsed_user_input == 0) {
              //browsing = false;
              return;
          }
          else if(parsed_user_input == 1){
              user.browse_add();
//              std::cout << ">>>Total price: " << user.getShoppingCartSum() << "<<<\n" << std::endl;
              user.browse_next();
          }
          else if(parsed_user_input == 2){
              user.browse_next();
          }
        }
        catch (std::invalid_argument &invalid_argument){
          std::cout << "Invalid option\n";
        }
    }
}


void MenuUI::ui_list_shopping_cart() {
    std::cout << this->user.printableShoppingCart() << std::endl;
}

void MenuUI::ui_display_shopping_cart() {
    // TODO:
    this->user.displayShoppingCart();
}

