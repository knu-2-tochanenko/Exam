#include "bookwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilityclass.h"
#include "time.h"

#include <QListWidgetItem>
#include <QVector>
#include <memory>
#include <algorithm>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //srand();

    //  Add strings to ComboBox
    ui->filerMode->addItem("Date");
    ui->filerMode->addItem("Pages");
    ui->filerMode->addItem("Author's pages");

    //  Initialize author filter
    this->filter = NULL;

    //  Generate 5 random authors
     
    this->authors.reserve(5);
    for (int i = 0; i < 5; i++) {
        Author* newAuthor = Author::generate(i);
        newAuthor->generateValues();
        this->authors.emplace_back(newAuthor);
    }

    update();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_buttonGenerateAuthor_clicked() {
    int newNumber = this->authors.size();
    Author* newAuthor = Author::generate(newNumber);
    newAuthor->generateValues();
    this->authors.emplace_back(newAuthor);
    update();
}

void MainWindow::on_buttonGenerateBook_clicked() {
    int bookType = rand() % 3;
    if (bookType == 0)
        this->singleAuthorBooks.push_back(
            SingleAuthorBook::generate(AuthorName(this->authors[rand() % this->authors.size()], rand() % 3)));
    if (bookType == 1) {
        QVector<AuthorWithPercentage> authorsMap;
        int randomNumberOfAuthors = rand() % this->authors.size() / 2 + 1;
        int percentage = 100;
        for (int i = 0; i < randomNumberOfAuthors; i++) {
            Author* author = this->authors[rand() % this->authors.size()];
            int currentPercentage = rand() % percentage;
            percentage -= currentPercentage;
            authorsMap.push_back(AuthorWithPercentage(author, rand() % 3, currentPercentage));
        }
        this->multiAuthorBooks.push_back(
            MultiAuthorBook::generate(authorsMap));
    }
    else {
        QMap<int, AuthorName> authorsMap;
        int numberOfChapters = rand() % 8;
        for (int i = 0; i < numberOfChapters; i++) {
            Author* author = this->authors[rand() % this->authors.size()];
            authorsMap.insert(i, AuthorName(author, rand() % 3));
        }
        this->authorByChapterBooks.push_back(
            AuthorByChapterBook::generate(authorsMap));
    }
    update();
}

void MainWindow::update() {
    QString currentMode = ui->filerMode->currentText();

    //  Push all books to single list
    selectedBooks.clear();
    if (this->filter == NULL) {
        for (int i = 0; i < this->singleAuthorBooks.size(); i++)
            selectedBooks.push_back(this->singleAuthorBooks[i]);
        for (int i = 0; i < this->multiAuthorBooks.size(); i++)
            selectedBooks.push_back(this->multiAuthorBooks[i]);
        for (int i = 0; i < this->authorByChapterBooks.size(); i++)
            selectedBooks.push_back(this->authorByChapterBooks[i]);
    }
    else {
        for (int i = 0; i < this->singleAuthorBooks.size(); i++)
            if (this->singleAuthorBooks[i]->hasAuthor(this->filter))
                selectedBooks.push_back(this->singleAuthorBooks[i]);
        for (int i = 0; i < this->multiAuthorBooks.size(); i++)
            if (this->multiAuthorBooks[i]->hasAuthor(this->filter))
                selectedBooks.push_back(this->multiAuthorBooks[i]);
        for (int i = 0; i < this->authorByChapterBooks.size(); i++)
            if (this->authorByChapterBooks[i]->hasAuthor(this->filter))
                selectedBooks.push_back(this->authorByChapterBooks[i]);
    }

    if (currentMode == "Date") {
        //  Bubble sort by date
        int booksSize = selectedBooks.size();
        for (int i = 0; i < booksSize - 1; i++)
            for (int j = 0; j < booksSize; j++)
                if (selectedBooks[i]->getDate() > selectedBooks[i + 1]->getDate()) {
                    Book* sub = selectedBooks[i];
                    selectedBooks[i] = selectedBooks[i + 1];
                    selectedBooks[i + 1] = sub;
                }
    }
    if (currentMode == "Pages") {
        //  Bubble sort by pages
        int booksSize = selectedBooks.size();
        for (int i = 0; i < booksSize - 1; i++)
            for (int j = 0; j < booksSize; j++)
                if (selectedBooks[i]->getPages() > selectedBooks[i + 1]->getPages()) {
                    Book* sub = selectedBooks[i];
                    selectedBooks[i] = selectedBooks[i + 1];
                    selectedBooks[i + 1] = sub;
                }
    }
    if (currentMode == "Author's pages") {
        if (this->filter == NULL) {
            Utility.errorMSG("Please, select author!");
            ui->filerMode->setCurrentIndex(0);
        }
        else  {
            int booksSize = selectedBooks.size();
            //  Todo write method
        }
    }
    putBooks();
    putAuthors();
}

//  Puts books to the books list
void MainWindow::putBooks() {
    int booksSize = this->selectedBooks.size();
    QVector<AuthorName> bookAuthors;
    ui->booksList->clear();
    for (int i = 0; i < booksSize; i++) {

        //  Create vector of authors
        bookAuthors.clear();
        bookAuthors = selectedBooks[i]->getAuthorsWithNick();

        QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->booksList);
        ui->booksList->addItem(listWidgetItem);
        BookWidget *snv = new BookWidget;
        snv->setStyleSheet("singleNoteView {border-bottom: 1px solid #BDBDBD}");
        snv->getInformation(selectedBooks[i], bookAuthors);
        listWidgetItem->setSizeHint(QSize(snv->sizeHint().width(), 170));
        ui->booksList->setItemWidget(listWidgetItem, snv);
    }
}


//  Puts authors to the authors list
void MainWindow::putAuthors() {
    int authorsSize = this->authors.size();
    vector<AuthorName> bookAuthors;
    ui->authorsList->clear();
    for (int i = 0; i < authorsSize; i++) {
        ui->authorsList->addItem(this->authors[i]->getName());
    }
}
