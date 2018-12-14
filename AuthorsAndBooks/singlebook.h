#ifndef SINGLEBOOK_H
#define SINGLEBOOK_H

#include "basebook.h"

class SingleBook : public BaseBook {
public:
    QVector<Author*> getAuthorsList();
    QVector<AuthorName> getAuthorsWithNick();
    bool hasAuthor(Author* author);

    static SingleBook* generate();
};

#endif // SINGLEBOOK_H
