#ifndef BOOK_H
#define BOOK_H

#include "author.h"
#include "utilityclass.h"

#include <QDate>
#include <QMap>
#include <QVector>

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
    Book(Book* book);

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
    SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, AuthorName& author);
    SingleAuthorBook(Book* book, AuthorName& author);

    AuthorName getAuthor() const;

    //  Generate random
    static SingleAuthorBook* generate(int ID);
private:
    AuthorName author;
};

class MultiAuthorBook : public Book {
public:
    MultiAuthorBook() = default;
    MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, QMap<AuthorName, int> authors);
    MultiAuthorBook(Book* book, QMap<AuthorName, int> authors);

    QMap<AuthorName, int> getAuthors() const;

    //  Generate random
    static MultiAuthorBook* generate(QVector<int> IDs);
private:
    //  Author - to coeff
    QMap<AuthorName, int> authors;
};

class AuthorByChapterBook : public Book {
public:
    AuthorByChapterBook() = default;
    AuthorByChapterBook(QString name, Genre::Name genre, QDate* date, int pages, QMap<int, AuthorName> authors);
    AuthorByChapterBook(Book* book, QMap<int, AuthorName> authors);

    QMap<int, AuthorName> getAuthors() const;

    //  Generate random
    static AuthorByChapterBook* generate(QVector<int> IDs);
private:
    //  Chapter - to Author
    QMap<int, AuthorName> authors;
};

#endif // BOOK_H
