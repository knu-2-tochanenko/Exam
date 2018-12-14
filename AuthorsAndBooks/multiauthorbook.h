#ifndef MULTIAUTHORBOOK_H
#define MULTIAUTHORBOOK_H

#include "basebook.h"
#include "singlebook.h"

class MultiAuthorBook : public BaseBook {
public:
    MultiAuthorBook() = default;
    MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, QVector<AuthorWithPercentage> authors);
    MultiAuthorBook(SingleBook* book, QVector<AuthorWithPercentage> const authors);

    QVector<AuthorWithPercentage> getAuthorsWithNick();
    QVector<AuthorWithPercentage> getAuthors() const;
    bool hasAuthor(Author* author);

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();

    //  Generate random
    static MultiAuthorBook *generate(QVector<AuthorWithPercentage> const &authorsMap);

    int getType();
private:
    //  Author - to coeff
    QVector<AuthorWithPercentage> authors;
};

#endif // MULTIAUTHORBOOK_H
