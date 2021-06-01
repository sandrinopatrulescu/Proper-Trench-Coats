//
// Created by kamui on 24.03.2021.
//

#ifndef A45_915_PATRULESCU_SANDRINO_TEST_REPOSITORY_H
#define A45_915_PATRULESCU_SANDRINO_TEST_REPOSITORY_H

#include <memory>
#include "../domain/trench_coat.h"
#include "../storage/repository.h"
#include "../storage/repo_using_stl.h"
#include "../storage/file_repo.h"
#include <cassert>
#include <utils.h>

class CustomInt{
private:
    int value;
    int doubleValue;
public:
    CustomInt(): value(0), doubleValue(0){
    };

    explicit CustomInt(int value_): value{value_}{
        doubleValue = 2 * value_;
    }

    CustomInt(const CustomInt& i){
        value = i.value;
        doubleValue = i.doubleValue;
    }

    CustomInt& operator=(const CustomInt& i)= default;

    void set_value(int value_){
        value = value_;
    }

    void set_double_value(int doubleValue_){
        doubleValue = doubleValue_;
    }

    int get_id() const{
        return value;
    }

    bool operator==(const CustomInt &rhs) const {
        return value == rhs.value;
    }

    bool operator!=(const CustomInt &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream& operator<<(std::ostream& os, const CustomInt& ci){
        os << ci.value << "," << ci.doubleValue << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, CustomInt& ci){
//        is >> ci.value >> ci.doubleValue;
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = tokenize(line, ',');
        if (tokens.size() != 2){
            return is;
        }
        ci.value = std::stoi(tokens[0]);
        ci.doubleValue = std::stoi(tokens[1]);
        return is;
    }

    static std::vector<CustomInt> create_entries(int number){
        if (number < 0){
            std::string message = "Invalid number of entries for creating CustomInts!\n";
            throw message.c_str();
        }
        else {
            std::vector<CustomInt> elements;
            elements.reserve(number);
            for (int i = 0; i < number; ++i) {
                elements.emplace_back(CustomInt{i});
            }
            return elements;
        }
    }
};


template<typename  TElem, typename ID>
class TestRepository{
private:
//    Repository<TElem, ID> repo;
    std::shared_ptr<Repository<TElem, ID>> repo_shared_ptr{new Repository<TElem, ID>};    void test_size();
    void test_add();
    void test_get();
    void test_remove();
    void test_update();
    void test_get_all();
    void test_filter();
    void test_iterate();
    void test_repo_stl();
    void test_repo_file();
public:
    void run_all_repository();
};


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::run_all_repository() {
    test_size();
    test_add();
    test_get();
    test_remove();
    test_update();
    test_get_all();
    test_filter();
    test_iterate();

    test_repo_stl();
    test_repo_file();
}

/*
template<typename  TElem, typename ID>
TestRepository<TElem, ID>:
 */
template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_size() {
    assert(repo_shared_ptr->size() == 0);
}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_add() {
    assert(repo_shared_ptr.get()->size() == 0);
    TrenchCoat tc1(112, "red", 50, 2, "link 1");
    repo_shared_ptr.get()->add_to_repo(tc1);
    assert(repo_shared_ptr.get()->size() == 1);
    assert(repo_shared_ptr.get()->search_by_id("link 1") == true);
    assert(repo_shared_ptr.get()->search_by_id("link  ") == false);
    TrenchCoat tc2(129, "black", 100, 7, "link 2");
    repo_shared_ptr.get()->add_to_repo(tc2);
    assert(true == repo_shared_ptr.get()->search_by_id("link 2"));

    TrenchCoat tc3{1, "gray", 17, 4, "link 2"};
    try{
        repo_shared_ptr.get()->add_to_repo(tc3);
    }
    catch (RepositoryException& re){
        assert(std::string(re.what()) == std::string("Repo cannot add: Element with given ID already exists!\n"));
    }
}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_get() {
    assert(repo_shared_ptr->get_element("link 2") == TrenchCoat(129, "black", 100, 7, "link 2"));
    try{
        repo_shared_ptr->get_element("no link");
    }
    catch (RepositoryException& re){
        assert(std::string(re.what()) == std::string("Repo cannot get: Given ID belongs to NO element!\n"));
    }
}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_remove() {
    assert(repo_shared_ptr.get()->size() == 2);
    try{
        repo_shared_ptr->remove_from_repo("link 99");
    }
    catch (RepositoryException& re){
        assert(std::string(re.what()) == std::string("Repo cannot remove: Element with given ID doesn't exist!\n"));
    }
    assert(repo_shared_ptr->size() == 2);
    repo_shared_ptr->remove_from_repo("link 2");
    assert(repo_shared_ptr->size() == 1);
    assert(repo_shared_ptr->search_by_id("link 2") == false);
}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_update() {
    TrenchCoat tc1(129, "black", 100, 7, "link 2");
    assert(repo_shared_ptr.get()->search_by_id("link 2") == false);
    repo_shared_ptr->add_to_repo(tc1);
    assert(repo_shared_ptr.get()->search_by_id("link 2") == true);
    TrenchCoat tc2{1, "blue", 200, 12, "link 11"};
    try{

        repo_shared_ptr->update_in_repo("no link", tc2);
    }
    catch (RepositoryException& re){
        assert(std::string(re.what()) == std::string("Repo cannot update: No element with given ID!\n"));
    }
    TrenchCoat tc3{1, "blue", 200, 12, "link 2"};
    try{
        repo_shared_ptr->update_in_repo("link 1", tc3);
    }
    catch (RepositoryException& re){
        assert(std::string(re.what()) == std::string("Repo cannot update: ID of given element belongs to an existing object!\n"));
    }
    TrenchCoat tc4{121, "cyan", 2000, 15, "link 2"};
    TrenchCoat tc5{130, "purple", 666, 69, "link 12"};
    assert(repo_shared_ptr->update_in_repo("link 2", tc4) == true);
    assert(repo_shared_ptr->update_in_repo("link 1", tc5) == true);
    assert(repo_shared_ptr.get()->search_by_id("link 2") == true);
    assert(repo_shared_ptr.get()->search_by_id("link 1") == false);
    assert(repo_shared_ptr.get()->search_by_id("link 12") == true);

}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_get_all() {
    repo_shared_ptr->add_to_repo(TrenchCoat{123, "pink", 4200, 42, "link 96"});
    TrenchCoat result[repo_shared_ptr->size()];
    repo_shared_ptr->get_all(result);
    int index;
    for(index = 0; index < repo_shared_ptr->size(); index = index + 1){
        assert(result[index] == repo_shared_ptr->get_element(result[index].get_id()));
//        std::cout << result[index].printable();
    }
}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_filter() {
    void* argv[1];
    int size = 120;
    argv[0] =  &size;
    TElem array[repo_shared_ptr->size()];
    int array_size = repo_shared_ptr->filter(array, size_is, argv);
    assert(array_size == 0);
    TrenchCoat tc1(123, "blue", 1000, 100, "link 7");
    repo_shared_ptr->add_to_repo(tc1);
    size = 123;
    TElem array1[repo_shared_ptr->size()];
    array_size = repo_shared_ptr->filter(array1, size_is, argv);
    assert(array_size == 2);
}


template<typename TElem, typename ID>
void TestRepository<TElem, ID>::test_iterate() {
    TrenchCoat tc1 = repo_shared_ptr->iterate();
    assert(tc1 == repo_shared_ptr->get_element("link 12"));
    assert(repo_shared_ptr->iterate() == repo_shared_ptr->get_element("link 2"));
    assert(repo_shared_ptr->iterate() == repo_shared_ptr->get_element("link 96"));
//    std::cout << repo_shared_ptr->iterate().printable();
    assert(repo_shared_ptr->iterate() == repo_shared_ptr->get_element("link 7"));
    assert(repo_shared_ptr->iterate() == repo_shared_ptr->get_element("link 12"));
}


template<typename  TElem, typename ID>
void TestRepository<TElem, ID>::test_repo_stl() {

    RepoSTL<CustomInt, int> repo;
    assert(repo.size() == 0);
    // TODO: this, after: implementation

    // testing add
    CustomInt i1{2};
    CustomInt array[10];
    for(int index = 0 ; index < 10; index = index + 1){
        array[index] = CustomInt{index};
    }
    repo.add_to_repo(array[2]);
    assert(repo.size() == 1);
    assert(repo.search_by_id(2) == true);
    i1 = repo.get_element(2);
    assert(i1 == array[2]);
    repo.add_to_repo(array[5]);
    assert(repo.size() == 2);
    assert(repo.search_by_id(5) == true);
    assert(repo.get_element(5) == array[5]);
    repo.add_to_repo(array[3]);
    assert(repo.size() == 3);
    try {
        repo.add_to_repo(array[2]);
        assert(false);
    }
    catch (RepositoryException& repositoryException) {
        assert(std::string(repositoryException.what()) == "Repo cannot add: Element with given ID already exists!\n");
    }

    // test update
    repo.update_in_repo(5, array[7]);
    assert(repo.size() == 3);
    assert(repo.search_by_id(5) == false);
    assert(repo.search_by_id(7) == true);
    assert(repo.get_element(7) == array[7]);
    try {
        repo.update_in_repo(10, array[9]);
        assert(false);
    }
    catch (RepositoryException& repositoryException) {
        assert(std::string(repositoryException.what()) == "Repo cannot update: No element with given ID!\n");
    }
    try {
        repo.update_in_repo(2, array[7]);
    }
    catch (RepositoryException& repositoryException) {
        assert(std::string(repositoryException.what()) == "Repo cannot update: ID of given element belongs to an existing object!\n");
    }

    // test remove
    repo.remove_from_repo(2);
    assert(repo.size() == 2);
    assert(repo.search_by_id(2) == false);
    try {
        CustomInt a = repo.get_element(2);
        assert(false);
    }
    catch (RepositoryException& repositoryException) {
        assert(std::string(repositoryException.what()) == "Repo cannot get: Given ID belongs to NO element!\n");
    }
    try {
        repo.remove_from_repo(66);
    }
    catch (RepositoryException& repositoryException) {
        assert(std::string(repositoryException.what()) == "Repo cannot remove: Element with given ID doesn't exist!\n");
    }
    assert(repo.size() == 2);

    // test get_all
    repo.add_to_repo(array[8]);
    repo.add_to_repo(array[4]);
    CustomInt elements[repo.size()];
    repo.get_all(elements);
    assert(elements[0] == array[7]);
    assert(elements[1] == array[3]);
    assert(elements[2] == array[8]);
    assert(elements[3] == array[4]);

    std::vector<class CustomInt> test_data = {CustomInt{7}, CustomInt{3}, CustomInt{8}, CustomInt{4}};
    assert(test_data == repo.get_all());

    repo.remove_all();
    assert(repo.size() == 0);
    assert(repo.search_by_id(7) == false);
    assert(repo.search_by_id(3) == false);
    assert(repo.search_by_id(8) == false);
    assert(repo.search_by_id(4) == false);
}

template<typename TElem, typename ID>
void TestRepository<TElem, ID>::test_repo_file() {
    // test reading
    std::string file_name = "../data/repoDataTestOnCustomInt.txt";
    std::ofstream fileTestRead(file_name);
    fileTestRead << CustomInt{10};
    fileTestRead << CustomInt{17};
    fileTestRead << CustomInt{13};
    fileTestRead.close();
    FileRepository<CustomInt, int> repo(file_name);
    // now the repo should contain 3 elements
    assert(repo.size() == 3);
    assert(repo.search_by_id(10) == true);
    assert(repo.search_by_id(17) == true);
    assert(repo.search_by_id(13) == true);
    assert(repo.get_element(13) == CustomInt{13});
    assert(repo.get_element(17) == CustomInt{17});

    repo.remove_all();
    assert(repo.size() == 0);


    // TODO: -tests
    //       -test main application
    // test add
    std::vector<CustomInt> my_data = CustomInt::create_entries(10);
    assert(repo.size() == 0);
    repo.add_to_repo(*my_data.begin());
    assert(repo.size() == 1);
    assert(repo.search_by_id(0) == true);
    assert(repo.get_element(0) == *my_data.begin());

    // pre test write
    std::ifstream repoOutputFile{file_name};
    std::stringstream repoDataStream;
    repoDataStream << *my_data.begin();
    std::string repoDataString = repoDataStream.str();
    // test write
    std::string line;
    std::getline(repoOutputFile, line);
    long int pos = repoOutputFile.tellg();
    line.append("\n");
    assert(line == repoDataString);
    auto it = my_data.begin();
    for (auto const& elem: my_data) {
        if (elem == *my_data.begin()){
            continue;
        }
        else {
            repo.add_to_repo(elem);
            std::stringstream writingStream;
            writingStream << elem;
            std::string writtenString = writingStream.str();
            repoOutputFile.seekg(pos);
            getline(repoOutputFile, line);
            pos = repoOutputFile.tellg();
            line.append("\n");
            assert(line == writtenString);
        }
    }
    repoOutputFile.close();
    // test update
    repo.update_in_repo(6, CustomInt{66});
    std::ifstream repoDataFile(file_name);
    CustomInt elem;
    int found_updated = 0;
    while (repoDataFile >> elem) {
        assert(elem != CustomInt{6});
        if (elem == CustomInt{66}) {
            found_updated = found_updated + 1;
        }
    }
    assert(found_updated == 1);
    repoDataFile.close();

    // test remove
    repo.remove_from_repo(4);
    repo.remove_from_repo(8);
    repoDataFile.open(file_name, std::ios::in);
    int found_elements = 0;
    while (repoDataFile >> elem){
        assert(elem != CustomInt{4});
        assert(elem != CustomInt{8});
        found_elements = found_elements + 1;
    }
    assert(found_elements == 8);
    assert(repo.size() == 8);
}

#endif //A45_915_PATRULESCU_SANDRINO_TEST_REPOSITORY_H
