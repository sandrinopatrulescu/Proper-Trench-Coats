//
// Created by kamui on 23.03.2021.
//

#include <repo_using_stl.h>
#include "test_all.h"
#include "test_validators.h"
#include "test_repository.h"
#include "test_service.h"


void Tests::test_run_all() {
    TestDomain test_domain;
    test_domain.run_all_domain();

    TestValidators test_validator;
    test_validator.run_all_validators();

    TestRepository<TrenchCoat, std::string> test_repository;
    test_repository.run_all_repository();

    TestRepository<TrenchCoat, std::string> repo;
    TestService test_service;
    test_service.run_all_service();
}


