//
// Created by kamui on 23.03.2021.
//

#include <test_all.h>
#include <QDebug>
#include <gui.h>
#include <QApplication>
#include "ui/menu_ui.h"
#include "service/admin.h"
#include "service/user.h"
#include "storage/repo_using_stl.h"


void add_entries(Admin<TrenchCoat, std::string>& admin){
    admin.add_service(121, "grey", 1000, 100, "https://assets.burberry.com/is/image/Burberryltd/DF7F4770-A238-43DE-9D0B-A3064C679585.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251");
    admin.add_service(122, "navy", 1500, 14, "https://assets.burberry.com/is/image/Burberryltd/ED5887AD-A52D-4CE9-B568-C40EEF4C1B9A.jpg?$BBY_V2_ML_1x1$&wid=1500&hei=1500");
    admin.add_service(125, "camel", 2400, 2, "https://assets.burberry.com/is/image/Burberryltd/FF35AFF4-C9D2-4EB4-8C7B-3FDD5F3EFCFF.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251");
    admin.add_service(124, "beige", 700, 60, "https://assets.burberry.com/is/image/Burberryltd/f35fd125df8b310c08833d4167e5c110f25baf19.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251");
    admin.add_service(125, "black", 1800, 11, "https://assets.burberry.com/is/image/Burberryltd/94287DBF-BA0B-478E-B077-B62023F63D66.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251");
    admin.add_service(126, "khaki", 900, 40, "https://assets.burberry.com/is/image/Burberryltd/E4F5FCB5-554A-4B13-8605-A09EEB2DA7C0.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251   ");
    admin.add_service(127, "burberry", 1342, 23, "https://assets.burberry.com/is/image/Burberryltd/63DC7E01-DDDC-4A46-8511-60C6FED19AAB.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251");
    admin.add_service(125, "dark blue", 1045, 17, "https://assets.burberry.com/is/image/Burberryltd/96A6D830-9E06-41E9-B9EE-0D12AA117D5F.jpg?$BBY_V2_ML_1x1$&wid=1251&hei=1251");
    admin.add_service(129, "white", 2000, 10, "https://images-na.ssl-images-amazon.com/images/I/51YAUJCBOqL._AC_UY500_.jpg");
    admin.add_service(130, "brown", 1750, 33, "https://images-na.ssl-images-amazon.com/images/I/81H1sKZH7vL._AC_UY500_.jpg");
}

// TODO:
/// \attention MAYBE remove REDUNDANT Repository operator=... what was it used for anyways?
/// \attention IDEA - in validator throw just 1 exception containing a string composed of all the messages
/// \attention !!!! - implemented Repository copy constructor gives COMPILE ERROR in TestAdmin or TestService
/// \attention - MAYBE store a repo reference in UserMode
int main(int argc, char *argv[]){
//    qDebug() << QT_VERSION_STR;
    /// ADMIN SERVICE COVERAGE ISN'T 100%: last return statement is skipped by exceptions
    Tests tests;
    tests.test_run_all();

    TrenchCoatValidator trench_coat_validator;
//    std::shared_ptr<Repository<TrenchCoat, std::string>> repository(new Repository<TrenchCoat, std::string>); // 1st repo - implemented DynArray
//    std::shared_ptr<RepoSTL<TrenchCoat, std::string>> repository(new RepoSTL<TrenchCoat, std::string>); // 2nd repo - using std::vector, without polymorphism
//    std::shared_ptr<Repository<TrenchCoat, std::string>> repository(new RepoSTL<TrenchCoat, std::string>); // 2nd repo - using std::vector, with polymorphism
    std::shared_ptr<Repository<TrenchCoat, std::string>> repository(new FileRepository<TrenchCoat, std::string>("../data/repoData.txt")); // 3rd repo - FileRepository, using polymorphism

    Admin<TrenchCoat, std::string> admin(repository, trench_coat_validator);
//    add_entries(admin); // MUST RUN ONLY ONCE, in case ../data/repoData.txt is empty
    UserMode user(repository);

//    MenuUI ui(admin, user);
//    ui.run_ui();
//    return 0;
    QApplication application(argc, argv);
    GUI gui{admin, user};
    gui.show();
    return QApplication::exec();
}








/*
/// some references
REPAIR STREAM BUFFER:
    http://www.cplusplus.com/forum/beginner/48568/

shared_ptr
    https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=msvc-160
    https://www.geeksforgeeks.org/auto_ptr-unique_ptr-shared_ptr-weak_ptr-2/

'explicit' keyword
    http://www.cplusplus.com/forum/general/168292/
    https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean

partial application &  currlying functions:
    https://www.walletfox.com/course/fp_partialapplication.php

string to integer stoi() execption
    https://stackoverflow.com/questions/41070101/terminate-called-after-throwing-an-instance-of-stdinvalid-argument-what-s
    https://www.cplusplus.com/reference/stdexcept/invalid_argument/


//    void (*void_ui_functions[3][5])();
    https://stackoverflow.com/questions/2898316/using-a-member-function-pointer-within-a-class
    https://stackoverflow.com/questions/46527961/storing-functions-from-class-in-array-and-invoke-them-c

 copy constr + dynamicARRAY
    https://www.cplusplus.com/articles/y8hv0pDG/
    https://www.cs.fsu.edu/~myers/cop3330/notes/dma.html
    https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
    https://en.cppreference.com/w/cpp/language/rule_of_three
 */