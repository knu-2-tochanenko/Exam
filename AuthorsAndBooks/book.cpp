#include "book.h"

Book::Book(QString name, Genre::Name genre, QDate date, int pages) {

}

Genre::Name Book::getGenre() const {

}

QString Book::getName() const {

}

QDate Book::getDate() const {

}

int Book::getPages() const {

}

int Book::getISGN() const {

}

Book Book::generate() {

}

SingleAuthorBook::SingleAuthorBook(QString name, Genre::Name genre, QDate date, int pages,
    Author *author) : Book(name, genre, date, pages) {

}

SingleAuthorBook::SingleAuthorBook(Book book, Author author) {

}

Author *SingleAuthorBook::getAuthor() const {

}

SingleAuthorBook SingleAuthorBook::generate() {

}

MultiAuthorBook::MultiAuthorBook(QString name, Genre::Name genre, QDate date, int pages,
    QMap<Author *, double> authors) : Book(name, genre, date, pages) {

}

MultiAuthorBook::MultiAuthorBook(Book book, QMap<Author *, double> authors) {

}

QMap<Author *, double> MultiAuthorBook::getAuthors() const {

}

MultiAuthorBook MultiAuthorBook::generate() {

}

AuthorByChapterBook::AuthorByChapterBook(QString name, Genre::Name genre, QDate date, int pages,
    QMap<int, Author *> authors) : Book(name, genre, date, pages) {

}

AuthorByChapterBook::AuthorByChapterBook(Book book, QMap<int, Author *> authors) {

}

QMap<int, Author *> AuthorByChapterBook::getAuthors() const {

}

AuthorByChapterBook AuthorByChapterBook::generate() {

}
