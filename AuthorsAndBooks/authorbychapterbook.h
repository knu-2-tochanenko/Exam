#ifndef AUTHORBYCHAPTERBOOK_H
#define AUTHORBYCHAPTERBOOK_H

#include "basebook.h"
#include "singlebook.h"

class AuthorByChapterBook : public BaseBook {
public:
    AuthorByChapterBook() = default;
    AuthorByChapterBook(QString name, Genre::Name genre, QDate* date, int pages, QMap<int, AuthorName> authors);
    AuthorByChapterBook(SingleBook* book, QMap<int, AuthorName> const authors);

    QMap<int, AuthorName> getAuthors() const;
    bool hasAuthor(Author* author);

    //  Get authors list for displaying the book
    QVector<Author*> getAuthorsList();
    QVector<AuthorWithPercentage> getAuthorsWithNick();

    //  Generate random
    static AuthorByChapterBook *generate(QMap<int, AuthorName> const &authorsMap);

    int numberOfChapters();

    int getType();
    int countPages(Author* author);
private:
    //  Chapter - to Author
    QMap<int, AuthorName> authors;
};

#endif // AUTHORBYCHAPTERBOOK_H
