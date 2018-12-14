#ifndef SINGLEAUTHORBOOK_H
#define SINGLEAUTHORBOOK_H

#include "basebook.h"
#include "singlebook.h"

class SingleAuthorBook : public BaseBook {
public:
    SingleAuthorBook() = default;
    SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages, AuthorName& author);
    SingleAuthorBook(SingleBook* book, AuthorName const &author);

    QVector<AuthorName> getAuthors() const;
    bool hasAuthor(Author* author);

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();
    QVector<AuthorWithPercentage> getAuthorsWithNick();

    //  Generate random
    static SingleAuthorBook *generate(AuthorName const &authorName);

    int getType();
    int countPages(Author* author);
private:
    AuthorName author;
};

#endif // SINGLEAUTHORBOOK_H
