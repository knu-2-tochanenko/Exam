#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QStringList>

class Genre {
public:
    enum Name { SCIENCE_FICTION, SATIRE, DRAMA, ADVENTURE, ROMANCE, MYSTERY, HORROR,
               GUIDE, SCIENCE, MATH, HISTORY, POETRY, COMICS, DICTIONARY, ART, BIOGRAPHY,
               DIARY, FANTASY, UNRECOGNIZED };
    static QString to_string();
};

class Author {
public:
    Author(QString name, QStringList nickNames, Genre::Name genre, int ID);

    QString getName() const;
    QStringList getNickNames() const;
    QString getNickName(int number) const;
    Genre::Name getGenre() const;
    int getID() const;

private:
    int ID;
    QString name;
    QStringList nickNames;
    Genre::Name genre;
};

#endif // AUTHOR_H
