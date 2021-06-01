cmake_minimum_required(VERSION 3.19)
project(a89_915_Patrulescu_Sandrino)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)


include_directories(domain)
include_directories(exceptions)
include_directories(service)
include_directories(storage)
include_directories(tests)
include_directories(ui)
include_directories(validators)

add_executable(a89_915_Patrulescu_Sandrino
        domain/dynamic_vector.h
        domain/trench_coat.cpp
        domain/trench_coat.h
        exceptions/dynamic_vector_exceptions.h
        exceptions/repository_exceptions.h
        exceptions/trench_coat_exceptions.h
        service/admin.cpp
        service/admin.h
        service/user.cpp
        service/user.h
        service/utils.cpp
        service/utils.h
        storage/csvAndhtml_repo.h
        storage/file_repo.cpp
        storage/file_repo.h
        storage/repo_using_stl.cpp
        storage/repo_using_stl.h
        storage/repository.cpp
        storage/repository.h
        tests/test_all.cpp
        tests/test_all.h
        tests/test_domain.cpp
        tests/test_domain.h
        tests/test_repository.cpp
        tests/test_repository.h
        tests/test_service.cpp
        tests/test_service.h
        tests/test_validators.cpp
        tests/test_validators.h
        ui/menu_ui.cpp
        ui/menu_ui.h
        "validators/trench_coat validator.cpp"
        "validators/trench_coat validator.h"
        main.cpp ui/gui.cpp ui/gui.h)

file(COPY data/repoData.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})