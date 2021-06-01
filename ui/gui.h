//
// Created by kamui on 29.04.2021.
//

#ifndef A89_915_PATRULESCU_SANDRINO_GUI_H
#define A89_915_PATRULESCU_SANDRINO_GUI_H


#include "../service/admin.h"
#include "../service/user.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>


class GUI: public QWidget {
private:
    Admin<TrenchCoat, std::string> &admin;
    UserMode& userMode;


    // main window
    QPushButton *mainAdminButton;
    QPushButton *mainUserButton;
    QPushButton *mainExitButton;

    void mainAdminButtonHandler();
    void mainUserButtonHandler();
//    void mainExitButtonHandler();


    // admin window
    QWidget* adminWidget;
    QListWidget *adminListWidget;
    QPushButton *adminAddButton;
    QPushButton *adminUpdateButton;
    QPushButton *adminRemoveButton;
    QPushButton *adminBackButton;
    QPushButton *adminExitButton;
    void fillAdminList();
    void adminAddButtonHandler();
    void adminUpdateButtonHandler();
    void adminRemoveButtonHandler();
    void adminBackButtonHandler();
    void adminExitButtonHandler();


    // admin -> add
    // TO DO:
//    QFormLayout* adminAddInputLayout;
    QWidget *adminAddWidget;
    QLineEdit *addSizeLineEdit, *addColourLineEdit, *addPriceLineEdit, *addQuantityLineEdit, *addPhotographLineEdit;
    QPushButton *addSaveButton;
    QPushButton *addCancelButton;
    void addSaveButtonHandler();
    void addCancelButtonHandler();

    // admin -> update
    // TO DO:
    QWidget *adminUpdateWidget;
    QLineEdit *updateOldPhotographLineEdit;
    QLineEdit *updateNewSizeLineEdit;
    QLineEdit *updateNewColourLineEdit;
    QLineEdit *updateNewPriceLineEdit;
    QLineEdit *updateNewQuantityLineEdit;
    QLineEdit *updateNewPhotographLineEdit;
    QPushButton *updateSaveButton;
    QPushButton *updateCancelButton;
    void updateSaveButtonHandler();
    void updateCancelButtonHandler();

    // admin -> remove
    // TO DO:
    QWidget *adminRemoveWidget;
    QLineEdit *removePhotographLineEdit;
    QPushButton *removeSaveButton;
    QPushButton *removeCancelButton;
    void removeSaveButtonHandler();
    void removeCancelButtonHandler();


    // pre-user window
    QWidget* preUserWidget;
    QPushButton *preUserNoFileButton;
    QPushButton *preUserCsvButton;
    QPushButton *preUserHtmlButton;
    QPushButton *preUserBackButton;
    QPushButton *preUserExitButton;

    void preUserNoFileButtonHandler();
    void preUserCsvButtonHandler();
    void preUserHtmlButtonHandler();
    void preUserBackButtonHandler();
    void preUserExitButtonHandler();

    // pre-user -> nofile
    // TO DO:

    // pre-user -> csv
    // TO DO:

    // pre-user -> html
    // TO DO:


    // user window
    QWidget* userWidget;
    QListWidget *userList;
    QPushButton *userBrowseButton;
    QPushButton *userShowButton;
    QPushButton *userOpenButton;
    QPushButton *userBackButton;
    QPushButton *userExitButton;

    void userBrowseButtonHandler();
    void userShowButtonHandler();
    void userOpenButtonHandler();
    void userBackButtonHandler();
    void userExitButtonHandler();

    // user -> browse
    QPushButton *quitBrowsingButton;
    QPushButton *addButton;
    QPushButton *nextButton;

    void quitBrowsingButtonHandler();
    void addButtonHandler();
    void nextButtonHandler();

    // user -> show
    // TO DO:

    // user -> open
    // TO DO:



    //QLabel *adminLabel, *userLabel;
    //QPushButton *adminAddButton, *adminUpdateButton, *adminRemoveButton, *adminListButton;
    //QPushButton *userBrowseButton, *userListButton, *userOpenButton, *userChartButton;
public:
//    GUI();
    GUI(Admin<TrenchCoat, std::string>&, UserMode&);

private:
    void initializeGUI();
    void connectSignalsAndSlots();
};

#endif //A89_915_PATRULESCU_SANDRINO_GUI_H
