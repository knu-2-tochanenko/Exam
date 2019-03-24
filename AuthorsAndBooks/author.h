#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "utilityclass.h"
#include <vector>

using std::vector;

class Author {
public:
    Author() = default;
    Author(QString name, QStringList nickNames, Genre::Name genre, int ID);

    QString getName() const;
    QStringList getNickNames() const;
    QString getNickName(int number) const;
    Genre::Name getGenre() const;
    int getID() const;
    int getNicknamesCount() const;

    //  Generate random
    static Author *generate(int ID);
    void generateValues();

private:
    int ID;
    QString name;
    QStringList nickNames;
    Genre::Name genre;
};

#endif // AUTHOR_H
