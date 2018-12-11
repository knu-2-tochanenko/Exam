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
    AuthorName() = default;
    AuthorName(Author *author, int name);
    AuthorName getAuthor();
};

struct AuthorWithPercentage {
    Author* author;
    int name;
    int percentage;
    AuthorWithPercentage() = default;
    AuthorWithPercentage(Author *author, int name, int percentage);
    AuthorName getAuthor();
};

//////////////////////////////////////////////////

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

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList(){ return QVector<Author*>(); }
    QVector<AuthorName> getAuthorsWithNick(){ return QVector<AuthorName>(); }
    bool hasAuthor(Author* author) { return false; };

    //  Generate random
    static Book *generate();
private:
    QString ISBN;       //  It'll be generated randomly
    QString name;
    Genre::Name genre;
    QDate* date;
    int pages;
};

void normalize(int& year, int& month, int& day);

//////////////////////////////////////////////////

class SingleAuthorBook : public Book {
public:
    SingleAuthorBook() = default;
    SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, AuthorName& author);
    SingleAuthorBook(Book* book, AuthorName const &author);

    QVector<AuthorName> getAuthors() const;
    bool hasAuthor(Author* author);

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();
    QVector<AuthorName> getAuthorsWithNick() const;

    //  Generate random
    static SingleAuthorBook *generate(AuthorName const &authorName);
private:
    AuthorName author;
};

//////////////////////////////////////////////////

class MultiAuthorBook : public Book {
public:
    MultiAuthorBook() = default;
    MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, QVector<AuthorWithPercentage> authors);
    MultiAuthorBook(Book* book, QVector<AuthorWithPercentage> const authors);

    QVector<AuthorName> getAuthorsWithNick();
    QVector<AuthorWithPercentage> getAuthors() const;
    bool hasAuthor(Author* author);

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();

    //  Generate random
    static MultiAuthorBook *generate(QVector<AuthorWithPercentage> const &authorsMap);
private:
    //  Author - to coeff
    QVector<AuthorWithPercentage> authors;
};

//////////////////////////////////////////////////

class AuthorByChapterBook : public Book {
public:
    AuthorByChapterBook() = default;
    AuthorByChapterBook(QString name, Genre::Name genre, QDate* date, int pages, QMap<int, AuthorName> authors);
    AuthorByChapterBook(Book* book, QMap<int, AuthorName> const authors);

    QMap<int, AuthorName> getAuthors() const;
    bool hasAuthor(Author* author);

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();
    QVector<AuthorName> getAuthorsWithNick();

    //  Generate random
    static AuthorByChapterBook *generate(QMap<int, AuthorName> const &authorsMap);
private:
    //  Chapter - to Author
    QMap<int, AuthorName> authors;
};

#endif // BOOK_H
