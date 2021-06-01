//
// Created by kamui on 26.03.2021.
//

#include "user.h"


void ShoppingCart::cart_add(const TrenchCoat& trench_coat) {
    auto it = cart_data.begin();
    while (it != cart_data.end()){
        if ((*it).get_id() == trench_coat.get_id()){
            break;
        }
        it = it + 1;
    }
    if(it == cart_data.end()){
        cart_data.push_back(trench_coat);
        price = price + trench_coat.get_price() * trench_coat.get_quantity();
        size = size + 1;
    }
    else {
        (*it).set_quantity((*it).get_quantity() + trench_coat.get_quantity());
        price = price + trench_coat.get_price() * trench_coat.get_quantity();
    }
}


int ShoppingCart::cart_size() const {
    return size;
}


int ShoppingCart::cart_price() const {
    return price;
}


std::string ShoppingCart::cart_list() {
    std::string result;
    if (size == 0) {
        return "Shopping cart is empty!\n";
    }
    for (const auto& elem: cart_data) {
        result.append(elem.printable());
    }
    result = result + "\tTotal price: " + std::to_string(price) + "\n";
    return result;
}

void ShoppingCart::set_file(const std::string &file_type_) {
    if (file_type_ == "none" || file_type_ == "html" or file_type_ == "csv") {
        this->file_type = file_type_;
    }
}


bool UserMode::browse_prepare(int desired_size) {
    TrenchCoat result[repository->size()]; /// temporary storing for elements that will be printed for the user to see,
    if (desired_size == -1) {              /// must be updated both in repo and inside the UserMode class as they are passed by value
        repository->get_all(result); /// case 1 of browsing: no size => all elements considered
        size_of_elements = repository->size();
        //from this point to the return statement we store copies of the to be used repo elements inside the UserMode instance
        delete[] elements;
        elements = new TrenchCoat[size_of_elements];
        for(int index = 0; index < size_of_elements; index = index + 1){
            elements[index] = result[index];
        }
        current = 0; // the iterator must be reset for every browsing => set it at prepare phase, same for case 2
        return true;
    }
    else if (desired_size >= 102 && desired_size <= 137){ /// case 2 of browsing: size is given and it's valid
        void* argv[1];
        argv[0] = &desired_size; // argv will store the size for filtering
        /// from this point till the return true; we store copies of the to be used repo elements inside the UserMode instance
        size_of_elements = repository->filter(result, size_is, argv); /// size_is - a filterer for trench coats
        delete[] elements;
        elements = new TrenchCoat[size_of_elements];
        for(int index = 0; index < size_of_elements; index = index + 1){
            elements[index] = result[index];
        }
        current = 0;
        return true;
    }
    else { // case 3: user gave invalid size;
        return false;
    }
}


std::string UserMode::browse_get_current() {
    return elements[current].printable();
}


void UserMode::browse_next() {
    if(current == size_of_elements - 1){
        current = 0;
    }
    else {
        current = current + 1;
    }
}


void UserMode::browse_add() {
    TrenchCoat &element = elements[current];
    if(element.get_quantity() > 0){
        this->addToShoppingCart(element); // add to the cart
        element.set_quantity(element.get_quantity() - 1); // update the reference from the UserMode Instance
        repository->update_in_repo(element.get_id(), element); // update also in the repository from the AdminMode
    }
}


int UserMode::get_elements_size() const {
    return size_of_elements;
}

// FIXME: used only in tests
void UserMode::get_elements(TrenchCoat *result) {
    for(int index = 0; index < size_of_elements; index = index + 1){
        result[index] = elements[index];
    }
}

// FIXME: used only in tests
TrenchCoat UserMode::get_from_repo(const std::string& id) {
    return repository->get_element(id);
}


//std::string UserMode::basket_to_string() {
//    return shopping_cart.cart_list();
//}


void UserMode::setShoppingCartSaveFileType(const std::string &file_type_) {
    this->shopping_cart = createWriteToFileRepository<TrenchCoat, std::string>(file_type_);
    this->file_type = file_type_;
}


std::string UserMode::getShoppingCartSaveFileType() const {
    return this->file_type;
}


int UserMode::getShoppingCartSum() const{
    /// Method 1
//    int totalShoppingCartSum = 0;
////    std::vector<TrenchCoat> items = shopping_cart->get_all();
////    for (const auto& item: items) {
//    for (const auto& item: shopping_cart->get_all()) {
//        totalShoppingCartSum = totalShoppingCartSum + item.get_quantity() * item.get_price();
//    }
//    return totalShoppingCartSum;
    /// Method 2
    return this->price;
}

std::string UserMode::printableShoppingCart() const {
    if (this->shopping_cart->size() == 0) {
        return "Shopping cart is empty!\n";
    }
    else {
        std::string result;
        // TODO: if this doesn't work, replace with get_all and then call printable on every element
        result.append(shopping_cart->printable());
        result.append("\tTotal price: " + std::to_string(this->getShoppingCartSum()) + "\n");
        return result;
    }
}


void UserMode::displayShoppingCart() const {
    this->shopping_cart->open();

}


void UserMode::addToShoppingCart(TrenchCoat tc) {
    auto found = this->shopping_cart->search_by_id(tc.get_id());
    if(!found) {
        tc.set_quantity(1);
        this->shopping_cart->add_to_repo(tc);
    }
    else {
        auto existingTrenchCoat = this->shopping_cart->get_element(tc.get_id());
        tc.set_quantity(existingTrenchCoat.get_quantity() + 1);
        this->shopping_cart->update_in_repo(tc.get_id(), tc);
    }
    price = price + tc.get_price();
}
