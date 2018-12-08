#ifndef BOOK_H
#define BOOK_H

#include "author.h"

#include <QDate>
#include <QMap>

class Book {
public:
    Book(QString name, Genre::Name genre, QDate date, int pages);

    //  Getters
    Genre::Name getGenre() const;
    QString getName() const;
    QDate getDate() const;
    int getPages() const;
    int getISGN() const;

    //  Generate random
    static Book generate();
private:
    int ISBN;       //  It'll be generated randomly
    QString name;
    Genre::Name genre;
    QDate date;
    int pages;
};

class SingleAuthorBook : public Book {
public:
    SingleAuthorBook(QString name, Genre::Name genre, QDate date, int pages, Author* author);
    SingleAuthorBook(Book book, Author author);

    Author* getAuthor() const;

    //  Generate random
    static SingleAuthorBook generate();
private:
    Author* author;
};

class MultiAuthorBook : public Book {
public:
    MultiAuthorBook(QString name, Genre::Name genre, QDate date, int pages, QMap<Author*, double> authors);
    MultiAuthorBook(Book book, QMap<Author*, double> authors);

    QMap<Author*, double> getAuthors() const;

    //  Generate random
    static MultiAuthorBook generate();
private:
    //  Author - to coeff
    QMap<Author*, double> authors;
};

class AuthorByChapterBook : public Book {
public:
    AuthorByChapterBook(QString name, Genre::Name genre, QDate date, int pages, QMap<int, Author*> authors);
    AuthorByChapterBook(Book book, QMap<int, Author*> authors);

    QMap<int, Author*> getAuthors() const;

    //  Generate random
    static AuthorByChapterBook generate();
private:
    //  Chapter - to Author
    QMap<int, Author*> authors;
};

#endif // BOOK_H
