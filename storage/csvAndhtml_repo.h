//
// Created by kamui on 20.04.2021.
//

#ifndef A67_915_PATRULESCU_SANDRINO_CSVANDHTML_REPO_H
#define A67_915_PATRULESCU_SANDRINO_CSVANDHTML_REPO_H

#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include "file_repo.h"


template<class TElem, class ID>
class WriteToFileRepository: public RepoSTL<TElem, ID>{
public:
    WriteToFileRepository<TElem, ID>(): RepoSTL<TElem, ID>() {

    };
    virtual void save() {

    };
    virtual void open() {

    };
    virtual std::string list() {
        return this->printable();
    };
};


template<class TElem, class ID>
class CSVRepo: public WriteToFileRepository<TElem, ID>{
public:
    CSVRepo(): WriteToFileRepository<TElem, ID>() {

    };
    bool add_to_repo(const TElem& element) override;
    bool remove_from_repo(const ID& id) override;
    bool update_in_repo(const ID& id, const TElem& new_element) override;
    void remove_all() override;

    // returns string in the required format for writing to the file
    std::string list() override;
    // saves to file.extension
    void save() override;
    // opens using default program
    void open() override;
};

template<class TElem, class ID>
bool CSVRepo<TElem, ID>::add_to_repo(const TElem &element) {
    auto result = RepoSTL<TElem, ID>::add_to_repo(element);
    if (result) {
        this->save();
    }
    return result;
}

template<class TElem, class ID>
bool CSVRepo<TElem, ID>::remove_from_repo(const ID &id) {
    auto result = RepoSTL<TElem, ID>::remove_from_repo(id);
    if (result) {
        this->save();
    }
    return result;
}

template<class TElem, class ID>
bool CSVRepo<TElem, ID>::update_in_repo(const ID &id, const TElem &new_element) {
    auto result = RepoSTL<TElem, ID>::update_in_repo(id, new_element);
    if (result) {
        this->save();
    }
    return result;
}

template<class TElem, class ID>
void CSVRepo<TElem, ID>::remove_all() {
    RepoSTL<TElem, ID>::remove_all();
    this->save();
}

template<class TElem, class ID>
std::string CSVRepo<TElem, ID>::list() {
    std::stringstream buffer;
    for (const auto& elem: this->get_all()) {
        buffer << elem;
    }
    return buffer.str();
}

template<class TElem, class ID>
void CSVRepo<TElem, ID>::save() {
    std::ofstream file("../data/shoppingCartData.csv");
    if(!file.is_open()){
        throw RepositoryException("Repo could not open .csv file at writing!\n");
    }
    file << this->list();

}

template<class TElem, class ID>
void CSVRepo<TElem, ID>::open() {
    this->save();
    pid_t childPid = fork();
    if (childPid == -1) {
        throw RepositoryException("Failed to create child process for opening .csv\n");
    }
    else if (childPid == 0) {
        int result = execlp("mousepad", "mousepad", "../data/shoppingCartData.csv", NULL);
        exit(result);
    }
    int result;
    wait(&result);
//    std::cout << "CSVRepo::open() result:" << result;
//    return result;
}


template<class TElem, class ID>
class HTMLRepo: public WriteToFileRepository<TElem, ID>{
public:
    HTMLRepo(): WriteToFileRepository<TElem, ID>(){

    };
    bool add_to_repo(const TElem& element) override;
    bool remove_from_repo(const ID& id) override;
    bool update_in_repo(const ID& id, const TElem& new_element) override;
    void remove_all() override;

    std::string list() override;
    void save() override;
    void open() override;
};

template<class TElem, class ID>
bool HTMLRepo<TElem, ID>::add_to_repo(const TElem &element) {
    auto result = RepoSTL<TElem, ID>::add_to_repo(element);
    if (result) {
        this->save();
    }
    return result;
}

template<class TElem, class ID>
bool HTMLRepo<TElem, ID>::remove_from_repo(const ID &id) {
    auto result = RepoSTL<TElem, ID>::remove_from_repo(id);
    if (result) {
        this->save();
    }
    return result;
}

template<class TElem, class ID>
bool HTMLRepo<TElem, ID>::update_in_repo(const ID &id, const TElem &new_element) {
    auto result = RepoSTL<TElem, ID>::update_in_repo(id, new_element);
    if (result) {
        this->save();
    }
    return result;
}

template<class TElem, class ID>
void HTMLRepo<TElem, ID>::remove_all() {
    RepoSTL<TElem, ID>::remove_all();
    this->save();
}

template<class TElem, class ID>
std::string HTMLRepo<TElem, ID>::list() {
    std::string result;
    result.append("<!DOCTYPE html>    <!-- write this exactly as it is here -->\n"
                  "<html> <!-- write this exactly as it is here -->\n"
                  "<head> <!--  write this exactly as it is here -->\n"
                  "    <title>Playlist</title> <!-- replace “Playlist” with the title for your HTML -->\n"
                  "</head> <!-- write this exactly as it is here (close head tag) -->\n"
                  "<body> <!-- write this exactly as it is here -->\n"
                  "<table border=\"1\"> <!-- write this exactly as it is here -->\n"
                  "    <tr> <!-- tr = table row; 1 row for each entity -->\n");
    result.append("        <td>Size</td> <!-- td = table data; 1 td for each attribute of the entity -->\n");
    result.append("        <td>Colour</td>\n");
    result.append("        <td>Price</td>\n");
    result.append("        <td>Quantity</td>\n");
    result.append("        <td>Photograph</td>\n");
    result.append("    </tr>\n");
    for (const auto& elem: this->get_all()) {
        result.append("    <tr>\n");

        std::vector<std::string> string;
        std::string begin = "        <td>", end = "</td>\n";
        result.append(begin + std::to_string(elem.get_size()) + end);
        result.append(begin + elem.get_colour() + end);
        result.append(begin + std::to_string(elem.get_price()) + end);
        result.append(begin + std::to_string(elem.get_quantity()) + end);

        result.append(begin + "<a href=\"" + elem.get_photograph() + "\">Link</a>" + end);
        result.append("    </tr>\n");
    }

    result.append("</table>\n"
                  "</body>\n"
                  "</html>");
    return result;
}

template<class TElem, class ID>
void HTMLRepo<TElem, ID>::save() {
    std::ofstream file("../data/shoppingCartData.html");
    if(!file.is_open()){
        throw RepositoryException("Repo could not open .html file at writing!\n");
    }
    file << this->list();
}

template<class TElem, class ID>
void HTMLRepo<TElem, ID>::open() {
    this->save();
    pid_t childPid = fork();
    if (childPid == -1) {
        throw RepositoryException("Failed to create child process for opening .html\n");
    }
    else if (childPid == 0) {
        int result = execlp("firefox", "firefox", "../data/shoppingCartData.html", NULL);
        exit(result);
    }
    int result;
    wait(&result);
//    std::cout << "CSVRepo::open() result:" << result;
//    return result;
}


template<class TElem, class ID>
WriteToFileRepository<TElem, ID> *createWriteToFileRepository(const std::string& type){
//    if (type == "none") {
//        return new WriteToFileRepository<TElem, ID>;
//    }
//    else if (type == "csv") {
    if (type == "csv") {
        return new CSVRepo<TElem, ID>;
    }
    else if (type == "html") {
        return new HTMLRepo<TElem, ID>;
    }
//    else if (type == "none") {
    else {
        return new WriteToFileRepository<TElem, ID>;
    }
}

#endif //A67_915_PATRULESCU_SANDRINO_CSVANDHTML_REPO_H
