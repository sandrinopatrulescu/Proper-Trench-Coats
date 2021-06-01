//
// Created by kamui on 12.04.2021.
//

#ifndef A67_915_PATRULESCU_SANDRINO_FILE_REPO_H
#define A67_915_PATRULESCU_SANDRINO_FILE_REPO_H

#include <fstream>
#include "repo_using_stl.h"

template<class TElem, class ID>
class FileRepository: public RepoSTL<TElem, ID>{
private:
    std::string file_name;
protected:
    virtual void write_to_file();
    virtual void read_from_file();
public:
    explicit FileRepository(const std::string& file_name_): file_name(file_name_) {
        read_from_file();
    };
    virtual bool add_to_repo(const TElem& element) override;
    virtual bool remove_from_repo(const ID& id) override;
    virtual bool update_in_repo(const ID& id, const TElem& new_element) override;
    virtual void remove_all() override;
};


template<class TElem, class ID>
void FileRepository<TElem, ID>::write_to_file() {
    std::ofstream file(file_name, std::ios::out | std::ios::trunc);
    if(!file.is_open()){
        throw RepositoryException("Repo could not open file at writing!\n");
    }
    std::vector<TElem> elements = RepoSTL<TElem, ID>::get_all();
    // TODO: check if I can put the get_all() function in the for loop
    for (const auto& elem: elements) {
        file << elem;
    }
    file.close();
}


template<class TElem, class ID>
void FileRepository<TElem, ID>::read_from_file() {
//    std::fstream file(file_name, std::ios::out | std::ios::in);
//    std::fstream file(file_name, std::ios::app | std::ios::out);
    std::ifstream file(file_name, std::ios::in);
    if(!file.is_open()){
        std::fstream file_new(file_name, std::ios::app);
        if (!file_new.is_open()){
            throw RepositoryException("Repo could not open file at reading!\n");
        }
        else {
            file_new.close();
            return;;
        }
    }
    else{
        RepoSTL<TElem, ID>::remove_all();
        TElem element;
        while(file >> element){
            RepoSTL<TElem, ID>::add_to_repo(element);
        }
        file.close();
    }
}


template<class TElem, class ID>
bool FileRepository<TElem, ID>::add_to_repo(const TElem &element) {
    RepoSTL<TElem, ID>::add_to_repo(element);
    this->write_to_file();
    return true;
}


template<class TElem, class ID>
bool FileRepository<TElem, ID>::remove_from_repo(const ID &id) {
    RepoSTL<TElem, ID>::remove_from_repo(id);
    this->write_to_file();
    return true;
}


template<class TElem, class ID>
bool FileRepository<TElem, ID>::update_in_repo(const ID &id, const TElem &new_element) {
    RepoSTL<TElem, ID>::update_in_repo(id, new_element);
    this->write_to_file();
    return true;
}

template<class TElem, class ID>
void FileRepository<TElem, ID>::remove_all() {
    RepoSTL<TElem, ID>::remove_all();
    write_to_file();
}


#endif //A67_915_PATRULESCU_SANDRINO_FILE_REPO_H
