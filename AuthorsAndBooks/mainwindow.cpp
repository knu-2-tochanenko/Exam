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

    //  Add strings to filter mode
    ui->filerMode->addItem("Date");
    ui->filerMode->addItem("Pages");
    ui->filerMode->addItem("Author's pages");

    //  Add strings to order mode
    ui->orderMode->addItem("Increasing");
    ui->orderMode->addItem("Decreasing");

    //  Initialize author filter
    this->filter = NULL;

    //  Generate 5 random authors
     
    this->authors.reserve(5);
    for (int i = 0; i < 5; i++) {
        Author* newAuthor = Author::generate(i);
        newAuthor->generateValues();
        this->authors.push_back(newAuthor);
    }

    //  Connect with updating combobox
    connect(ui->filerMode, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(switchcall(const QString&)));
    connect(ui->orderMode, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(switchcall(const QString&)));

    //  Connect list of authors
    connect(ui->authorsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onListMailItemClicked(QListWidgetItem*)));

    //  Set smooth scroll
    ui->booksList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    update();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_buttonGenerateAuthor_clicked() {
    int newNumber = this->authors.size();
    Author* newAuthor = Author::generate(newNumber);
    newAuthor->generateValues();
    this->authors.push_back(newAuthor);
    update();
}

void MainWindow::on_buttonGenerateBook_clicked() {
    int bookType = rand() % 3, coef;
    if (bookType == 0) {
        coef = rand() % this->authors.size();
        this->singleAuthorBooks.push_back(
            SingleAuthorBook::generate(AuthorName(this->authors[coef], rand() % (this->authors[coef]->getNicknamesCount() + 1))));
    }
    else if (bookType == 1) {
        QVector<AuthorWithPercentage> authorsMap;
        int randomNumberOfAuthors = rand() % (this->authors.size() / 2) + 2;
        int percentage = 100;
        for (int i = 0; i < randomNumberOfAuthors; i++) {
            Author* author = this->authors[rand() % this->authors.size()];
            int currentPercentage = rand() % percentage;
            percentage -= currentPercentage;
            authorsMap.push_back(AuthorWithPercentage(author, rand() % (author->getNicknamesCount() + 1), currentPercentage));
        }
        this->multiAuthorBooks.push_back(
            MultiAuthorBook::generate(authorsMap));
    }
    else {
        QMap<int, AuthorName> authorsMap;
        int numberOfChapters = rand() % 8 + 2;
        for (int i = 0; i < numberOfChapters; i++) {
            Author* author = this->authors[rand() % this->authors.size()];
            authorsMap.insert(i, AuthorName(author, rand() % (author->getNicknamesCount() + 1)));
        }
        this->authorByChapterBooks.push_back(
            AuthorByChapterBook::generate(authorsMap));
    }
    update();
}

void MainWindow::switchcall(const QString &) {
    update();
}

void MainWindow::on_searchAuthor_textChanged() {
    if (ui->searchAuthor->text() == "")
        putAuthors();
    else {
        int authorsSize = this->authors.size();
        vector<AuthorName> bookAuthors;
        ui->authorsList->clear();
        for (int i = 0; i < authorsSize; i++) {
            if (this->authors[i]->getName().indexOf(ui->searchAuthor->text()) >= 0)
                ui->authorsList->addItem(this->authors[i]->getName());
        }
    }
}

void MainWindow::onListMailItemClicked(QListWidgetItem *listWidgetItem) {
    if (filter != NULL && filter->getName() == listWidgetItem->text()) {
        filter = NULL;
        listWidgetItem->setTextColor(QColor(0, 0, 0));
    }
    else
        for (int i = 0; i < this->authors.size(); i++)
            if (this->authors[i]->getName() == listWidgetItem->text()) {
                filter = this->authors[i];
                listWidgetItem->setTextColor(QColor(0, 121, 107));
                break;
            }
    displayAuthor();
    update();
}

int MainWindow::numberOfPages(QDate begin, QDate end, Author *author) {
    getPagesOrBooks(begin, end, author, true);
}

int MainWindow::numberOfBooks(QDate begin, QDate end, Author *author) {
    getPagesOrBooks(begin, end, author, false);
}

QString MainWindow::getGenres(QDate begin, QDate end, Author *author) {
    QVector<QString> res;
    if (filter == NULL)
        return "";

    for (int i = 0; i < this->singleAuthorBooks.size(); i++)
        if (this->singleAuthorBooks[i]->hasAuthor(this->filter))
            if ((!res.contains(Genre::toString(this->singleAuthorBooks[i]->getGenre())))
                && (isAfter(*this->singleAuthorBooks[i]->getDate(), begin))
                && (isAfter(end, *this->singleAuthorBooks[i]->getDate())))
                res.push_back(Genre::toString(this->singleAuthorBooks[i]->getGenre()));

    for (int i = 0; i < this->multiAuthorBooks.size(); i++)
        if (this->multiAuthorBooks[i]->hasAuthor(this->filter))
            if ((!res.contains(Genre::toString(this->multiAuthorBooks[i]->getGenre())))
                && (isAfter(*this->multiAuthorBooks[i]->getDate(), begin))
                && (isAfter(end, *this->multiAuthorBooks[i]->getDate())))
                res.push_back(Genre::toString(this->multiAuthorBooks[i]->getGenre()));

    for (int i = 0; i < this->authorByChapterBooks.size(); i++)
        if (this->authorByChapterBooks[i]->hasAuthor(this->filter))
            if ((!res.contains(Genre::toString(this->authorByChapterBooks[i]->getGenre())))
                    && (isAfter(*this->authorByChapterBooks[i]->getDate(), begin))
                    && (isAfter(end, *this->authorByChapterBooks[i]->getDate())))
                res.push_back(Genre::toString(this->authorByChapterBooks[i]->getGenre()));

    QString resString = "";
    for (int i = 0; i < res.size(); i++)
        resString += res[i] + "\n";
    return  resString;
}

int MainWindow::getPagesOrBooks(QDate begin, QDate end, Author *author, bool mode) {
    if (this->filter == NULL)
        return -1;

    int pages = 0, books = 0;

    for (int i = 0; i < this->singleAuthorBooks.size(); i++)
        if ((this->singleAuthorBooks[i]->hasAuthor(this->filter))
            && (isAfter(*this->singleAuthorBooks[i]->getDate(), begin))
            && (isAfter(end, *this->singleAuthorBooks[i]->getDate()))){
            books++;
            pages += this->singleAuthorBooks[i]->getPages();
        }

    for (int i = 0; i < this->multiAuthorBooks.size(); i++)
        if ((this->multiAuthorBooks[i]->hasAuthor(this->filter))
            && (isAfter(*this->multiAuthorBooks[i]->getDate(), begin))
            && (isAfter(end, *this->multiAuthorBooks[i]->getDate()))) {
            books++;
            QVector<AuthorWithPercentage> authorsBook = this->multiAuthorBooks[i]->getAuthors();
            for (int j = 0; j < authorsBook.size(); j++)
                if (authorsBook[j].author->getID() == filter->getID())
                    pages += this->multiAuthorBooks[i]->getPages() * authorsBook[j].percentage / 100;
        }

    for (int i = 0; i < this->authorByChapterBooks.size(); i++)
        if ((this->authorByChapterBooks[i]->hasAuthor(this->filter))
            && (isAfter(*this->authorByChapterBooks[i]->getDate(), begin))
            && (isAfter(end, *this->authorByChapterBooks[i]->getDate()))){
            books++;
            QVector<Author*> authorsBook = this->authorByChapterBooks[i]->getAuthorsList();
            for (int j = 0; j < authorsBook.size(); j++)
                if (authorsBook[j]->getID() == filter->getID())
                    pages += this->authorByChapterBooks[i]->getPages() /
                            this->authorByChapterBooks[i]->numberOfChapters();
        }
    if (mode)
        return pages;
    else
        return books;
}

void MainWindow::update() {
    QString currentMode = ui->filerMode->currentText();
    QString orderMode = ui->orderMode->currentText();

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
        for (int i = 0; i < booksSize; i++)
            for (int j = 0; j < booksSize - 1; j++)
                if ((isAfter(*selectedBooks[j]->getDate(), *selectedBooks[j + 1]->getDate())
                    && orderMode == "Increasing") ||
                    (!isAfter(*selectedBooks[j]->getDate(), *selectedBooks[j + 1]->getDate())
                    && orderMode != "Increasing")) {
                    BaseBook* sub = selectedBooks[j];
                    selectedBooks[j] = selectedBooks[j + 1];
                    selectedBooks.replace(j, selectedBooks[j + 1]);
                    selectedBooks.replace(j + 1, sub);
                }
    }
    else if (currentMode == "Pages") {
        //  Bubble sort by pages
        int booksSize = selectedBooks.size();
        for (int i = 0; i < booksSize; i++)
            for (int j = 0; j < booksSize - 1; j++)
                if (((selectedBooks[j]->getPages() > selectedBooks[j + 1]->getPages())
                    && orderMode == "Increasing") ||
                    ((!(selectedBooks[j]->getPages() > selectedBooks[j + 1]->getPages()))
                    && orderMode != "Increasing")) {
                    BaseBook* sub = selectedBooks[j];
                    selectedBooks[j] = selectedBooks[j + 1];
                    selectedBooks[j + 1] = sub;
                }
    }
    else if (currentMode == "Author's pages") {
        if (this->filter == NULL) {
            Utility.errorMSG("Please, select author!");
            ui->filerMode->setCurrentIndex(0);
        }
        else  {
            int booksSize = selectedBooks.size();
            //  TODO write method
        }
    }
    putBooks();
    putAuthors();
}

//  Puts books to the books list
void MainWindow::putBooks() {
    int booksSize = this->selectedBooks.size();
    QVector<AuthorWithPercentage> bookAuthors;
    ui->booksList->clear();
    for (int i = 0; i < booksSize; i++) {

        //  Create vector of authors
        bookAuthors.clear();
        bookAuthors = selectedBooks[i]->getAuthorsWithNick();

        QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->booksList);
        ui->booksList->addItem(listWidgetItem);
        BookWidget *snv = new BookWidget;
        snv->setStyleSheet("BookWidget {border-bottom: 1px solid #BDBDBD}");
        snv->getInformation(selectedBooks[i], bookAuthors, selectedBooks[i]->getType());
        listWidgetItem->setSizeHint(QSize(snv->sizeHint().width(), snv->getHeight()));
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

void MainWindow::displayAuthor() {
    if (this->filter == NULL) {
        ui->authorName->setText("Select Author");
        ui->authorBooksCount->setText("---");
        ui->authorPagesCount->setText("---");
        ui->authorGenres->setText("---");
    }
    else {
        ui->authorName->setText(filter->getName());
        ui->authorBooksCount->setNum(numberOfBooks(ui->dateBegin->date(), ui->dateEnd->date(), filter));
        ui->authorPagesCount->setNum(numberOfPages(ui->dateBegin->date(), ui->dateEnd->date(), filter));
        ui->authorGenres->setText(getGenres(ui->dateBegin->date(), ui->dateEnd->date(), filter));
    }
}

bool MainWindow::isAfter(QDate &date, QDate &final) {
    if (date.year() > final.year())
        return true;
    else if (date.year() == final.year())
        if (date.month() > final.month())
            return true;
        else if (date.month() == final.month())
            if (date.day() > final.day())
                return true;
    return false;
}
