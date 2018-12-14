#ifndef SINGLEBOOK_H
#define SINGLEBOOK_H

#include "basebook.h"

class SingleBook : public BaseBook {
public:
    QVector<Author*> getAuthorsList();
    QVector<AuthorWithPercentage> getAuthorsWithNick();
    bool hasAuthor(Author* author);

    static SingleBook* generate();

    int getType();
};

#endif // SINGLEBOOK_H
