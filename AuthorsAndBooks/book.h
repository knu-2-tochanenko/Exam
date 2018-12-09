#ifndef BOOK_H
#define BOOK_H

#include "author.h"
#include "utilityclass.h"

#include <QDate>
#include <QMap>

struct AuthorName {
    Author* author;
    int name;
    AuthorName(Author *author, int name);
};

class Book {
public:
    Book() = default;
    Book(QString name, Genre::Name genre, QDate* date, int pages);
    Book(Book& book);

    //  Getters
    Genre::Name getGenre() const;
    QString getName() const;
    QDate* getDate() const;
    int getPages() const;
    QString getISBN() const;

    //  Generate random
    static Book* generate();
private:
    QString ISBN;       //  It'll be generated randomly
    QString name;
    Genre::Name genre;
    QDate* date;
    int pages;
};

void normalize(int& year, int& month, int& day);

class SingleAuthorBook : public Book {
public:
    SingleAuthorBook() = default;
    SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, Author* author);
    SingleAuthorBook(Book book, Author* author);

    Author* getAuthor() const;

    //  Generate random
    static SingleAuthorBook* generate();
private:
    Author* author;
};

class MultiAuthorBook : public Book {
public:
    MultiAuthorBook() = default;
    MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, QMap<AuthorName, double> authors);
    MultiAuthorBook(Book book, QMap<AuthorName, double> authors);

    QMap<AuthorName, double> getAuthors() const;

    //  Generate random
    static MultiAuthorBook* generate();
private:
    //  Author - to coeff
    QMap<AuthorName, double> authors;
};

class AuthorByChapterBook : public Book {
public:
    AuthorByChapterBook() = default;
    AuthorByChapterBook(QString name, Genre::Name genre, QDate* date, int pages, QMap<int, AuthorName> authors);
    AuthorByChapterBook(Book book, QMap<int, AuthorName> authors);

    QMap<int, AuthorName> getAuthors() const;

    //  Generate random
    static AuthorByChapterBook* generate();
private:
    //  Chapter - to Author
    QMap<int, AuthorName> authors;
};

#endif // BOOK_H
