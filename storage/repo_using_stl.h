//
// Created by kamui on 09.04.2021.
//

#ifndef A67_915_PATRULESCU_SANDRINO_REPO_USING_STL_H
#define A67_915_PATRULESCU_SANDRINO_REPO_USING_STL_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "repository.h"


/// every TElem must implement the following methods
/// std::string printable()
/// ID get_id();
template<class TElem, class ID>
class RepoSTL: public Repository<TElem, ID>{
private:
    std::vector<TElem> data;
    auto getElementIterator(const ID& id) const;
public:
    RepoSTL();
    int size() const;
    bool search_by_id(const ID &id) const override;
    virtual bool add_to_repo(const TElem& element) override;
    virtual bool remove_from_repo(const ID& id) override;
    virtual bool update_in_repo(const ID& id, const TElem& new_element) override;
    TElem get_element(const ID& id) const override;
    // either override or get rid of parameters
    void get_all(TElem result[]) override;
    std::vector<TElem> get_all() const override;
    int filter(TElem result[], bool (*filter_function)(const TElem&, void **), void** argv) override;
    virtual void remove_all();
//    friend std::ostream& operator<<(std::ostream& os, const RepoSTL<TElem, ID>&);
    std::string printable();
};


template<class TElem, class ID>
RepoSTL<TElem, ID>::RepoSTL(): Repository<TElem, ID>() {

}


template<class TElem, class ID>
auto RepoSTL<TElem, ID>::getElementIterator(const ID &id) const{
    auto idIs = [&](const TElem& elem)->bool { return elem.get_id() == id;};
    auto it = std::find_if(data.begin(), data.end(), idIs);
    return it;
}


template<class TElem, class ID>
bool RepoSTL<TElem, ID>::search_by_id(const ID &id) const {
    return getElementIterator(id) != data.end();
//    auto id_filter = [=](const TElem& elem) -> bool { return elem.get_id() == id;};
//    auto it = std::find_if(data.begin(), data.end(), id_filter);
//    if (it == data.end()) {
//        return false;
//    }
//    return true;
}

template<class TElem, class ID>
bool RepoSTL<TElem, ID>::add_to_repo(const TElem &element) {
//    if (std::find(data.begin(), data.end(), element) != data.end()) {
    if (getElementIterator(element.get_id()) != data.end() && size() != 0) {
        throw RepositoryException("Repo cannot add: Element with given ID already exists!\n");
    }
    data.push_back(element);
    return true;
}


template<class TElem, class ID>
bool RepoSTL<TElem, ID>::remove_from_repo(const ID &id) {
//    auto find_by_id = [&](const TElem& element) -> bool { return element.get_id() == id;};
//    auto it = std::find_if(data.begin(), data.end(), find_by_id);
    auto it = getElementIterator(id);
    if (it == data.end()) {
        throw RepositoryException("Repo cannot remove: Element with given ID doesn't exist!\n");
    }
    else{
        data.erase(it);
        return true;
    }
}


template<class TElem, class ID>
bool RepoSTL<TElem, ID>::update_in_repo(const ID &id, const TElem &new_element) {
    auto find_by_id = [&](const TElem& element)->bool {return element.get_id() == id;};
    auto itOldElement = std::find_if(data.begin(), data.end(), find_by_id);
//    auto itOldElement = getElementIterator(id);
    /* TODO: find out why using 'auto itOldElement = get_it(id);' sets up this error for getElementIterator declared constant:
     *          /media/kamui/2454C0AC54C08252/Uni/GitHub/IE1.Semester II/a67-915-Patrulescu-Sandrino/tests/test_all.cpp:96:36:   required from here
     *          /media/kamui/2454C0AC54C08252/Uni/GitHub/IE1.Semester II/a67-915-Patrulescu-Sandrino/storage/repo_using_stl.h:98:27: error: passing ‘const CustomInt’ as ‘this’ argument discards qualifiers [-fpermissive]
     *          98 |             *itOldElement = new_element;
     *      and why for using it without constant gives an error in the search and get?
     */
    if (itOldElement == data.end()) {
        throw RepositoryException("Repo cannot update: No element with given ID!\n");
    }
    else {
//        auto find_if_duplicate = [&](const TElem& element)->bool {return element.get_id() == new_element.get_id();};
//        auto it_of_duplicate = std::find_if(data.begin(), data.end(), find_if_duplicate);
//        if (it_of_duplicate != data.end()) {
        if (getElementIterator(new_element.get_id()) != data.end() && getElementIterator(new_element.get_id()) != itOldElement) {
                throw RepositoryException("Repo cannot update: ID of given element belongs to an existing object!\n");
        }
        else {
            *itOldElement = new_element;
            return true;
        }
    }
}


template<class TElem, class ID>
TElem RepoSTL<TElem, ID>::get_element(const ID &id) const{
//    auto find_by_id = [&](const TElem& elem)->bool { return elem.get_id() == id;};
//    auto it = std::find_if(data.begin(), data.end(), find_by_id);
    auto it = getElementIterator(id);
    if (it == data.end()) {
        throw RepositoryException("Repo cannot get: Given ID belongs to NO element!\n");
    }
    else{
        return *it;
    }
}


template<class TElem, class ID>
void RepoSTL<TElem, ID>::get_all(TElem *result) {
    for(auto index = 0; index < this->size(); index = index + 1){
        result[index] = *(data.begin() + index);
    }
}


template<class TElem, class ID>
int RepoSTL<TElem, ID>::filter(TElem *result, bool (*filter_function)(const TElem &, void **), void **argv) {
    int index = 0;
    auto filter = [&](const TElem& elem) { if (filter_function(elem, argv)) result[index++] = elem;};
    std::for_each(data.begin(), data.end(), filter);
    return index;
}

template<class TElem, class ID>
int RepoSTL<TElem, ID>::size() const{
    return data.size();
}

template<class TElem, class ID>
std::vector<TElem> RepoSTL<TElem, ID>::get_all() const{
    return data;
}

template<class TElem, class ID>
void RepoSTL<TElem, ID>::remove_all() {
    data.clear();
}

//template<class TElem, class ID>
//std::ostream &operator<<(std::ostream &os, const RepoSTL<TElem, ID>& repo) {
//    for (const auto& elem: repo.data) {
//        os << elem;
//    }
//    return os;
//}

template<class TElem, class ID>
std::string RepoSTL<TElem, ID>::printable() {
    std::string result;
    for (const auto& elem: this->data) {
        result.append(elem.printable());
    }
    return result;
}


#endif //A67_915_PATRULESCU_SANDRINO_REPO_USING_STL_H
