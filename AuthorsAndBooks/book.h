#ifndef BOOK_H
#define BOOK_H

#include "basebook.h"
#include "author.h"
#include "utilityclass.h"

#include <QDate>
#include <QMap>
#include <QVector>
#include <vector>

class Book : public BaseBook{
public:
    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();
    QVector<AuthorName> getAuthorsWithNick();
    bool hasAuthor(Author* author);
};

#endif // BOOK_H
