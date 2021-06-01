//
// Created by kamui on 29.04.2021.
//

#include "gui.h"

GUI::GUI(Admin<TrenchCoat, std::string> &admin_, UserMode &userMode_) : admin{admin_}, userMode{userMode_} {
    this->initializeGUI();
    this->connectSignalsAndSlots();
}


void GUI::initializeGUI() {
    // main window
    //QVBoxLayout* mainLayout = new QVBoxLayout{this};
    QVBoxLayout* mainLayout = new QVBoxLayout{this};
    mainLayout->setSpacing(1);

    this->setWindowTitle("Trench Coats Main Menu");
    this->mainAdminButton = new QPushButton{"&Admin"};
    mainAdminButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->mainUserButton = new QPushButton{"&User"};
    mainUserButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->mainExitButton = new QPushButton{"&Exit"};
    mainExitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(this->mainAdminButton);
    mainLayout->addWidget(this->mainUserButton);
    mainLayout->addWidget(this->mainExitButton);

    // admin window
    this->adminWidget = new QWidget{};
    this->adminWidget->setWindowTitle("Admin Menu");
    this->adminWidget->setVisible(false);
    QVBoxLayout* adminLayout =  new QVBoxLayout{this->adminWidget};
    this->adminListWidget = new QListWidget{};
    this->adminListWidget->setFont(QFont("Times New Roman", 12));
    this->adminAddButton = new QPushButton{"&Add"};
    this->adminUpdateButton = new QPushButton{"&Update"};
    this->adminRemoveButton = new QPushButton{"&Remove"};
    this->adminBackButton = new QPushButton{"&Back"};
    this->adminExitButton = new QPushButton{"&Exit"};

    adminLayout->addWidget(this->adminListWidget);
    adminLayout->addWidget(this->adminAddButton);
    adminLayout->addWidget(this->adminUpdateButton);
    adminLayout->addWidget(this->adminRemoveButton);
    adminLayout->addWidget(this->adminBackButton);
    adminLayout->addWidget(this->adminExitButton);


    // pre-user window
    this->preUserWidget = new QWidget{};
    this->preUserWidget->setWindowTitle("Pre-User Menu");
    this->preUserWidget->setVisible(false);
    QVBoxLayout* preUserLayout =  new QVBoxLayout{this->preUserWidget};
    this->preUserNoFileButton = new QPushButton{"No file"};
    this->preUserCsvButton = new QPushButton{"CSV"};
    this->preUserHtmlButton = new QPushButton{"HTML"};
    this->preUserBackButton = new QPushButton{"&Back"};
    this->preUserExitButton = new QPushButton{"&Exit"};

    preUserLayout->addWidget(this->preUserNoFileButton);
    preUserLayout->addWidget(this->preUserCsvButton);
    preUserLayout->addWidget(this->preUserHtmlButton);
    preUserLayout->addWidget(this->preUserBackButton);
    preUserLayout->addWidget(this->preUserExitButton);


    // user window
    this->userWidget = new QWidget{};
    this->userWidget->setWindowTitle("User Menu");
    this->userWidget->setVisible(false);
    QVBoxLayout* userLayout =  new QVBoxLayout{this->userWidget};
    this->userList = new QListWidget{};
    this->userBrowseButton = new QPushButton{"&Browse"};
    this->userShowButton = new QPushButton{"&Show"};
    this->userOpenButton = new QPushButton{"&Open"};
    this->userBackButton = new QPushButton{"&Back"};
    this->userExitButton = new QPushButton{"&Exit"};

    userLayout->addWidget(this->userList);
    userLayout->addWidget(this->userBrowseButton);
    userLayout->addWidget(this->userShowButton);
    userLayout->addWidget(this->userOpenButton);
    userLayout->addWidget(this->userBackButton);
    userLayout->addWidget(this->userExitButton);

    // admin -> add
    this->adminAddWidget = new QWidget{};
    QVBoxLayout *adminAddLayout = new QVBoxLayout{this->adminAddWidget};

    QFormLayout *adminAddInputLayout = new QFormLayout{};
    adminAddLayout->addLayout(adminAddInputLayout);

    this->addSizeLineEdit = new QLineEdit{};
    this->addColourLineEdit = new QLineEdit{};
    this->addPriceLineEdit = new QLineEdit{};
    this->addQuantityLineEdit = new QLineEdit{};
    this->addPhotographLineEdit = new QLineEdit{};

    adminAddInputLayout->addRow("&Size", this->addSizeLineEdit);
    adminAddInputLayout->addRow("&Colour", this->addColourLineEdit);
    adminAddInputLayout->addRow("&Price", this->addPriceLineEdit);
    adminAddInputLayout->addRow("&Quantity", this->addQuantityLineEdit);
    adminAddInputLayout->addRow("&Photograph", this->addPhotographLineEdit);

    QHBoxLayout *adminAddButtonsLayout = new QHBoxLayout{};
    adminAddLayout->addLayout(adminAddButtonsLayout);

    this->addSaveButton = new QPushButton{"&Save"};
    this->addCancelButton = new QPushButton{"&Cancel"};

    adminAddButtonsLayout->addWidget(this->addSaveButton);
    adminAddButtonsLayout->addWidget(this->addCancelButton);


    // admin -> update
    this->adminUpdateWidget = new QWidget{};
    QVBoxLayout *adminUpdateLayout = new QVBoxLayout{this->adminUpdateWidget};

    QFormLayout *adminUpdateInputLayout =  new QFormLayout{};
    adminUpdateLayout->addLayout(adminUpdateInputLayout);

    this->updateOldPhotographLineEdit = new QLineEdit{};
    this->updateNewSizeLineEdit = new QLineEdit{};
    this->updateNewColourLineEdit = new QLineEdit{};
    this->updateNewPriceLineEdit = new QLineEdit{};
    this->updateNewQuantityLineEdit = new QLineEdit{};
    this->updateNewPhotographLineEdit = new QLineEdit{};

    adminUpdateInputLayout->addRow("&OldPhotograph", this->updateOldPhotographLineEdit);
    adminUpdateInputLayout->addRow("&NewSize", this->updateNewSizeLineEdit);
    adminUpdateInputLayout->addRow("&NewColour", this->updateNewColourLineEdit);
    adminUpdateInputLayout->addRow("&NewPrice", this->updateNewPriceLineEdit);
    adminUpdateInputLayout->addRow("&NewQuantity", this->updateNewQuantityLineEdit);
    adminUpdateInputLayout->addRow("&NewPhotograph", this->updateNewPhotographLineEdit);

    QHBoxLayout *adminUpdateButtonsLayout = new QHBoxLayout{};
    adminUpdateLayout->addLayout(adminUpdateButtonsLayout);

    this->updateSaveButton = new QPushButton{"&Save"};
    this->updateCancelButton = new QPushButton{"&Cancel"};

    adminUpdateButtonsLayout->addWidget(this->updateSaveButton);
    adminUpdateButtonsLayout->addWidget(this->updateCancelButton);


    // admin -> remove
    this->adminRemoveWidget = new QWidget{};
    QVBoxLayout *adminRemoveLayout = new QVBoxLayout{this->adminRemoveWidget};

    QFormLayout *adminRemoveInputLayout = new QFormLayout{};
    adminRemoveLayout->addLayout(adminRemoveInputLayout);

    this->removePhotographLineEdit = new QLineEdit{};

    adminRemoveInputLayout->addRow("&Photograph", this->removePhotographLineEdit);

    QHBoxLayout *adminRemoveButtonsLayout = new QHBoxLayout{};
    adminRemoveLayout->addLayout(adminRemoveButtonsLayout);

    this->removeSaveButton = new QPushButton{"&Save"};
    this->removeCancelButton = new QPushButton{"&Cancel"};

    adminRemoveButtonsLayout->addWidget(this->removeSaveButton);
    adminRemoveButtonsLayout->addWidget(this->removeCancelButton);

    // user -> browse

    this->quitBrowsingButton = new QPushButton{"&Quit Browsing"};
    this->addButton = new QPushButton{"&Add"};
    this->nextButton = new QPushButton{"&Next"};

    userLayout->addWidget(this->quitBrowsingButton);
    userLayout->addWidget(this->addButton);
    userLayout->addWidget(this->nextButton);

    this->quitBrowsingButton->hide();
    this->addButton->hide();
    this->nextButton->hide();

    // user -> show


    // user -> open

//    this->connectSignalsAndSlots();
}

void GUI::connectSignalsAndSlots() {
    // main window
    QObject::connect(this->mainAdminButton, &QAbstractButton::clicked, this,  &GUI::mainAdminButtonHandler);
    QObject::connect(this->mainUserButton, &QAbstractButton::clicked, this,  &GUI::mainUserButtonHandler);
    QObject::connect(this->mainExitButton, &QAbstractButton::clicked, this,  &QWidget::close);


    // admin window
    QObject::connect(this->adminAddButton, &QAbstractButton::clicked, this,  &GUI::adminAddButtonHandler);
    QObject::connect(this->adminUpdateButton, &QAbstractButton::clicked, this,  &GUI::adminUpdateButtonHandler);
    QObject::connect(this->adminRemoveButton, &QAbstractButton::clicked, this,  &GUI::adminRemoveButtonHandler);
    QObject::connect(this->adminBackButton, &QAbstractButton::clicked, this,  &GUI::adminBackButtonHandler);
    QObject::connect(this->adminExitButton, &QAbstractButton::clicked, this,  &GUI::adminExitButtonHandler);
//    QObject::connect(this->adminListWidget, &QListWidget::clicked, this, [this]() {
////       this->adminListWidget->NoSelection;
////       this->adminListWidget->setCurrentRow(-1);
////       if (this->adminListWidget)
//        QModelIndexList selected = this->adminListWidget->selectionModel()->;
//       if (this->adminListWidget->mouse)
//       if (this->adminListWidget->selectedItems().isEmpty()) {
//           this->adminListWidget->setCurrentItem(nullptr);
//       }
//
//    });

    // admin -> add
    QObject::connect(this->addSaveButton, &QAbstractButton::clicked, this, &GUI::addSaveButtonHandler);
    QObject::connect(this->addCancelButton, &QAbstractButton::clicked, this, &GUI::addCancelButtonHandler);


    // admin -> update
    QObject::connect(this->updateSaveButton, &QAbstractButton::clicked, this, &GUI::updateSaveButtonHandler);
    QObject::connect(this->updateCancelButton, &QAbstractButton::clicked, this, &GUI::updateCancelButtonHandler);

    // admin -> remove
    QObject::connect(this->removeSaveButton, &QAbstractButton::clicked, this, &GUI::removeSaveButtonHandler);
    QObject::connect(this->removeCancelButton, &QAbstractButton::clicked, this, &GUI::removeCancelButtonHandler);


    // pre-user window
    QObject::connect(this->preUserNoFileButton, &QAbstractButton::clicked, this, &GUI::preUserNoFileButtonHandler);
    QObject::connect(this->preUserCsvButton, &QAbstractButton::clicked, this, &GUI::preUserCsvButtonHandler);
    QObject::connect(this->preUserHtmlButton, &QAbstractButton::clicked, this, &GUI::preUserHtmlButtonHandler);
    QObject::connect(this->preUserBackButton, &QAbstractButton::clicked, this, &GUI::preUserBackButtonHandler);
    QObject::connect(this->preUserExitButton, &QAbstractButton::clicked, this, &GUI::preUserExitButtonHandler);

    // user window
    QObject::connect(this->userBrowseButton, &QAbstractButton::clicked, this, &GUI::userBrowseButtonHandler);
    QObject::connect(this->userShowButton, &QAbstractButton::clicked, this, &GUI::userShowButtonHandler);
    QObject::connect(this->userOpenButton, &QAbstractButton::clicked, this, &GUI::userOpenButtonHandler);
    QObject::connect(this->userBackButton, &QAbstractButton::clicked, this, &GUI::userBackButtonHandler);
    QObject::connect(this->userExitButton, &QAbstractButton::clicked, this, &GUI::userExitButtonHandler);

    // user -> browse
    QObject::connect(this->quitBrowsingButton, &QAbstractButton::clicked, this, &GUI::quitBrowsingButtonHandler);
    QObject::connect(this->addButton, &QAbstractButton::clicked, this, &GUI::addButtonHandler);
    QObject::connect(this->nextButton, &QAbstractButton::clicked, this, &GUI::nextButtonHandler);

    // user -> show

}


// main window
void GUI::mainAdminButtonHandler() {
//    this->setVisible(false);
//    this->fillAdminList();
//    this->adminWidget->setVisible(true);
    this->fillAdminList();
    this->adminWidget->show();
    this->close();
}

void GUI::mainUserButtonHandler() {
    this->setVisible(false);
    this->preUserWidget->setVisible(true);
}


// admin window
void GUI::fillAdminList() {
    this->adminListWidget->clear();
    /// next 2 lines not checked
//    this->adminListWidget->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
//    this->adminListWidget->setMinimumSize(QSize(1111, 111));
     //    this->adminListWidget->setStyleSheet("QListView {background: gray}");
    this->adminListWidget->setAlternatingRowColors(true);
    for (const auto &elem: this->admin.getAll()) {
//        QListWidgetItem item{QString::fromStdString(elem.printable())};
//        item.setBackgroundColor(QColor::fromRgb(190, 190, 190));
        this->adminListWidget->addItem(QString::fromStdString(elem.printable()));
//        this->adminListWidget->addItem(&item);
//        this->adminListWidget->count();
//        this->adminListWidget->setItem
    }
}

void GUI::adminAddButtonHandler() {
    ;
    // TODO:
    this->adminAddWidget->show();
    QListWidgetItem *currentItem = this->adminListWidget->currentItem();
    if (currentItem != nullptr) {
        QString currentText = this->adminListWidget->currentItem()->text();
        int position = 0;
        int currentHeaderIndex = 0;
        QVector<QString> preText = {"Size: ", "Colour: ", "Price: ", "Quantity: ", "Photograph: "};
        QVector<QLineEdit *> lineEdits{this->addSizeLineEdit, this->addColourLineEdit, this->addPriceLineEdit,
                                       this->addQuantityLineEdit, this->addPhotographLineEdit};
        while (position != -1) {
            // headerStart => starting position of Colour: inside the text
            int headerStart = currentText.indexOf(preText[currentHeaderIndex], position);
            // headerEnd => ending position of Colour: inside the text
            int firstAfterHeaderEnd = headerStart + preText[currentHeaderIndex].size();
            int indexOfComma = currentText.indexOf(",", firstAfterHeaderEnd);
            if (indexOfComma == -1) {
                lineEdits[currentHeaderIndex]->setText(currentText.mid(firstAfterHeaderEnd).simplified());
                break;
            } else {
                lineEdits[currentHeaderIndex]->setText(
                        currentText.mid(firstAfterHeaderEnd, indexOfComma - firstAfterHeaderEnd));
            }
            position = indexOfComma;
            currentHeaderIndex++;
        }
    }
    else {
        this->addSizeLineEdit->clear();
        this->addColourLineEdit->clear();
        this->addPriceLineEdit->clear();
        this->addQuantityLineEdit->clear();
        this->addPhotographLineEdit->clear();
    }

//        std::cout << attributes;
//        QTextStream out(stdout);
//        out << currentText << endl;
//        QRegExp rx("(, )*([a-zA-z]+: )");
//        rx.setMinimal(true);
//        int pos = 0;
//        while ((pos = rx.indexIn(currentText, pos)) != -1) {
//            out << rx.cap(1) << " ";
//            pos += rx.matchedLength();
//        }
//        out << endl;
//        QStringList::const_iterator it;
//        out << "Const STL it\n";
//        for(it = attributes.begin(); it != attributes.end(); ++it) {
//            out << "---" << (*it) << "---" << (*it).toLocal8Bit().constData() << "---" << endl;
//        }
////        out << attributes;
//        QStringListIterator attributesIterator(attributes);
//
//        for(auto lineEditIterator = lineEdits.begin(); lineEditIterator != lineEdits.end(); lineEditIterator++) {
//            out << attributes.at(lineEditIterator - lineEdits.begin()) << endl;
//            (*lineEditIterator)->setText(attributes.at(lineEditIterator - lineEdits.begin()));
//        }
        //        attributesIterator;
//    }


    //this->adminWidget->close();
}

void GUI::adminUpdateButtonHandler() {
    QListWidgetItem *currentItem = this->adminListWidget->currentItem();
    if (currentItem != nullptr) {
        QString currentText = this->adminListWidget->currentItem()->text();
        int position = 0;
        int currentHeaderIndex = 0;
        QVector<QString> preText = {"Size: ", "Colour: ", "Price: ", "Quantity: ", "Photograph: "};
        QVector<QLineEdit *> lineEdits{this->updateNewSizeLineEdit, this->updateNewColourLineEdit, this->updateNewPriceLineEdit,
                                       this->updateNewQuantityLineEdit, this->updateNewPhotographLineEdit};
        while (position != -1) {
            // headerStart => starting position of Colour: inside the text
            int headerStart = currentText.indexOf(preText[currentHeaderIndex], position);
            // headerEnd => ending position of Colour: inside the text
            int firstAfterHeaderEnd = headerStart + preText[currentHeaderIndex].size();
            int indexOfComma = currentText.indexOf(",", firstAfterHeaderEnd);
            if (indexOfComma == -1) {
                lineEdits[currentHeaderIndex]->setText(currentText.mid(firstAfterHeaderEnd).simplified());
                break;
            } else {
                lineEdits[currentHeaderIndex]->setText(
                        currentText.mid(firstAfterHeaderEnd, indexOfComma - firstAfterHeaderEnd));
            }
            position = indexOfComma;
            currentHeaderIndex++;
        }
        this->updateOldPhotographLineEdit->setText(this->updateNewPhotographLineEdit->text().simplified());
    }
    else {
        this->updateOldPhotographLineEdit->clear();
        this->updateNewSizeLineEdit->clear();
        this->updateNewColourLineEdit->clear();
        this->updateNewPriceLineEdit->clear();
        this->updateNewQuantityLineEdit->clear();
        this->updateNewPhotographLineEdit->clear();
    }
    this->adminUpdateWidget->show();
//    this->adminWidget->close();
}

void GUI::adminRemoveButtonHandler() {

    QListWidgetItem *currentItem = this->adminListWidget->currentItem();
    if (currentItem != nullptr) {
        QString currentText = this->adminListWidget->currentItem()->text();
        QString header = "Photograph: ";
        int firstAfterHeaderEnd = currentText.indexOf(header, 0) + header.size();
        this->removePhotographLineEdit->setText(currentText.mid(firstAfterHeaderEnd).simplified());
    }
    else {
        this->removePhotographLineEdit->clear();
    }
    this->adminRemoveWidget->show();
//    this->adminWidget->close();
}

void GUI::adminBackButtonHandler() {
//    this->setVisible(true);
//    this->adminWidget->setVisible(false);
    this->show();
    this->adminWidget->close();
}

void GUI::adminExitButtonHandler() {
//    this->close(); optional
    this->adminWidget->close();
}


// admin -> add
void GUI::addSaveButtonHandler() {
    ;
    // TODO:
    try {
        this->admin.add_service(this->addSizeLineEdit->text().toInt(), this->addColourLineEdit->text().toStdString(), this->addPriceLineEdit->text().toInt(), this->addQuantityLineEdit->text().toInt(), this->addPhotographLineEdit->text().toStdString());
        this->fillAdminList();
    }
    catch (std::exception &e) {
        // TODO: dialog with error
        QMessageBox::information(this->adminAddWidget, "Error!", QString(e.what()));
    }
}

void GUI::addCancelButtonHandler() {
    this->fillAdminList();
    this->adminWidget->show();
    this->adminAddWidget->close();
}


// admin -> update
void GUI::updateSaveButtonHandler() {
    ;
    // TODO:
    try {
        this->admin.update_service(this->updateOldPhotographLineEdit->text().simplified().toStdString(), this->updateNewSizeLineEdit->text().toInt(), this->updateNewColourLineEdit->text().toStdString(), this->updateNewPriceLineEdit->text().toInt(), this->updateNewQuantityLineEdit->text().toInt(), this->updateNewPhotographLineEdit->text().toStdString());
        this->fillAdminList();
    }
    catch (std::exception &e) {
        // TODO: dialog with error
        QMessageBox::information(this->adminAddWidget, "Error!", QString(e.what()));
    }
}

void GUI::updateCancelButtonHandler() {
    this->fillAdminList();
    this->adminWidget->show();
    this->adminUpdateWidget->close();
}

// admin -> remove
void GUI::removeSaveButtonHandler() {
    ;
    // TODO:
    try {
        this->admin.remove_service(this->removePhotographLineEdit->text().simplified().toStdString());
        this->fillAdminList();
    }
    catch (std::exception &e) {
        // TODO: dialog with error
        QMessageBox::information(this->adminAddWidget, "Error!", QString(e.what()));
    }
}
void GUI::removeCancelButtonHandler() {
    this->fillAdminList();
    this->adminWidget->show();
    this->adminRemoveWidget->close();
}


// pre-user window
void GUI::preUserNoFileButtonHandler() {
    // TODO:
    this->userMode.setShoppingCartSaveFileType("none");
    this->userOpenButton->hide();
    this->quitBrowsingButton->hide();
    this->addButton->hide();
    this->nextButton->hide();
    this->userList->clear();
    this->userList->addItem("Shopping cart is emtpy!");
    this->userWidget->setVisible(true);
    this->preUserWidget->setVisible(false);
}

void GUI::preUserCsvButtonHandler() {
    // TODO:
    this->userMode.setShoppingCartSaveFileType("csv");
    this->userOpenButton->show();
    this->quitBrowsingButton->hide();
    this->addButton->hide();
    this->nextButton->hide();
    this->userList->clear();
    this->userList->addItem("Shopping cart is emtpy!");
    this->userWidget->setVisible(true);
    this->preUserWidget->setVisible(false);
}

void GUI::preUserHtmlButtonHandler(){
    // TODO:
    this->userMode.setShoppingCartSaveFileType("html");
    this->userOpenButton->show();
    this->quitBrowsingButton->hide();
    this->addButton->hide();
    this->nextButton->hide();
    this->userList->clear();
    this->userList->addItem("Shopping cart is emtpy!");
    this->userWidget->setVisible(true);
    this->preUserWidget->setVisible(false);
}

void GUI::preUserBackButtonHandler() {
    this->setVisible(true);
    this->preUserWidget->setVisible(false);
}

void GUI::preUserExitButtonHandler() {
    this->close();
    this->preUserWidget->close();
}


// user window
void GUI::userBrowseButtonHandler() {
    ;
    // TODO:
//    QInputDialog *inputDialog = new QInputDialog{this->mainUserButton};
//    inputDialog->setWindowTitle("Browsing filtering");
//    inputDialog->set
    QString enteredSize = QInputDialog::getText(this->userBrowseButton, "Browse filtering", "Enter filter size: ", QLineEdit::Normal);
    if (enteredSize.isEmpty()) {
        if (this->userMode.browse_prepare(-1)) {
            int fetched = this->userMode.get_elements_size();
            QMessageBox::information(this->userBrowseButton, "Success!", QString("Browsing updated! Fetched %1 items.").arg(fetched));
            this->userList->clear();
            this->userBrowseButton->hide();
            this->userShowButton->hide();
            this->userBackButton->hide();
            this->userExitButton->hide();
            this->userOpenButton->hide();
            this->quitBrowsingButton->show();
            this->addButton->show();
            this->nextButton->show();
            this->userList->clear();
            this->userList->addItem(QString::fromStdString(this->userMode.browse_get_current()));
        }
    }
    else {
        bool ok;
        int size = enteredSize.toInt(&ok);
        if (!ok) {
            QMessageBox::information(this->userBrowseButton, "Error!", QString("Invalid format for size!"));
        }
        else {
            if (this->userMode.browse_prepare(size) == false) {
                QMessageBox::information(this->userBrowseButton, "Error!", QString("Invalid size number!"));
            }
            else {
                int fetched = this->userMode.get_elements_size();
                QMessageBox::information(this->userBrowseButton, "Success!", QString("Browsing updated! Fetched %1 items.").arg(fetched));
                this->userList->clear();
                this->userBrowseButton->hide();
                this->userShowButton->hide();
                this->userBackButton->hide();
                this->userExitButton->hide();
                this->userOpenButton->hide();
                this->quitBrowsingButton->show();
                this->addButton->show();
                this->nextButton->show();
                this->userList->clear();
                this->userList->addItem(QString::fromStdString(this->userMode.browse_get_current()));
            }
        }
    }
}

void GUI::quitBrowsingButtonHandler() {
    this->userBrowseButton->show();
    this->userShowButton->show();
    this->userOpenButton->show();
    this->userBackButton->show();
    this->userExitButton->show();
    this->quitBrowsingButton->hide();
    this->addButton->hide();
    this->nextButton->hide();
}

void GUI::addButtonHandler() {
    this->userMode.browse_add();
    this->nextButtonHandler();
}

void GUI::nextButtonHandler() {
    this->userList->clear();
    this->userMode.browse_next();
    this->userList->addItem(QString::fromStdString(this->userMode.browse_get_current()));
}

void GUI::userShowButtonHandler() {
    // TODO:
    this->userList->clear();
    this->userBrowseButton->show();
    this->userShowButton->show();
    this->userOpenButton->show();
    this->quitBrowsingButton->hide();
    this->addButton->hide();
    this->nextButton->hide();
    QString itemsPrintable = QString::fromStdString(this->userMode.printableShoppingCart());
    QStringList stringList = itemsPrintable.split("\n", QString::SkipEmptyParts);
    this->userList->clear();
    for(int i = 0; i < stringList.size(); i++) {
        this->userList->addItem(stringList.at(i).toLocal8Bit().constData());
    }
}

void GUI::userOpenButtonHandler(){
    ;
    // TODO:
    this->userMode.displayShoppingCart();
}

void GUI::userBackButtonHandler() {
    this->setVisible(true);
    this->userWidget->setVisible(false);
}

void GUI::userExitButtonHandler() {
    this->close();
    this->userWidget->close();
}

