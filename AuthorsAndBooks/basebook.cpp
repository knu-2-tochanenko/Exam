#include "basebook.h"
#include "time.h"

BaseBook::BaseBook(QString name, Genre::Name genre, QDate* date, int pages) {
    this->name = name;
    this->genre = genre;
    this->date = date;
    this->pages = pages;
}

BaseBook::BaseBook(BaseBook &book) {
    this->ISBN = book.ISBN;
    this->name = book.name;
    this->date = book.date;
    this->genre = book.genre;
    this->pages = book.pages;
}

BaseBook::BaseBook(BaseBook *book) {
    this->ISBN = book->ISBN;
    this->name = book->name;
    this->date = book->date;
    this->genre = book->genre;
    this->pages = book->pages;
}

Genre::Name BaseBook::getGenre() const {
    return this->genre;
}

QString BaseBook::getName() const {
    return this->name;
}

QDate* BaseBook::getDate() const {
    return this->date;
}

int BaseBook::getPages() const {
    return this->pages;
}

QString BaseBook::getISBN() const {
    return this->ISBN;
}

void BaseBook::setGenre(Genre::Name const &genre) {
    this->genre = genre;
}

void BaseBook::setName(QString const &name) {
    this->name = name;
}

void BaseBook::setDate(QDate *date) {
    this->date = date;
}

void BaseBook::setPages(int const &pages) {
    this->pages = pages;
}

void BaseBook::setISBN(QString const &ISBN) {
    this->ISBN = ISBN;
}

void BaseBook::generateNumbers() {
     
    int year = rand() % 300 + 1753;
    int month = rand() % 12;
    int day = rand() % 31;
    Utility.normalize(year, month, day);
    this->date = new QDate(year, month, day);
    this->name = Utility.getRandomTitle();
    this->genre = Genre::getRandom();
    this->pages = rand() % MAX_PAGES;
}

AuthorName::AuthorName(Author *author, int name) {
    this->name = name;
    this->author = author;
}

AuthorName AuthorName::getAuthor() {
    AuthorName res(this->author, this->name);
    return res;
}

AuthorWithPercentage::AuthorWithPercentage(Author *author, int name, int percentage) {
    this->author = author;
    this->name = name;
    this->percentage = percentage;
}

AuthorName AuthorWithPercentage::getAuthor() {
    AuthorName res(this->author, this->name);
    return res;
}
