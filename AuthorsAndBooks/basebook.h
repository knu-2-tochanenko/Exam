#ifndef BOOK_H
#define BOOK_H

#include "author.h"
#include "utilityclass.h"

#include <QDate>
#include <QMap>
#include <QVector>
#include <vector>

using std::vector;

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

class BaseBook {
public:
    BaseBook() = default;
    BaseBook(QString name, Genre::Name genre, QDate* date, int pages);
    BaseBook(BaseBook& book);
    BaseBook(BaseBook* book);

    //  Getters
    Genre::Name getGenre() const;
    QString getName() const;
    QDate* getDate() const;
    int getPages() const;
    QString getISBN() const;

    //  Setters
    void setGenre(Genre::Name const &genre);
    void setName(QString const &name);
    void setDate(QDate *date);
    void setPages(int const &pages);
    void setISBN(QString const &ISBN);

    //  Get authors list for displaying the book
    virtual QVector<Author*> getAuthorsList() = 0;
    virtual QVector<AuthorName> getAuthorsWithNick() = 0;
    virtual bool hasAuthor(Author* author) = 0;
protected:
    QString ISBN;       //  It'll be generated randomly
    QString name;
    Genre::Name genre;
    QDate* date;
    int pages;

    void generateNumbers();
};

void normalize(int& year, int& month, int& day);

#endif // BOOK_H
