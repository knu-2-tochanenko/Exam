#include "author.h"

Author::Author(QString name, QStringList nickNames, Genre::Name genre, int ID) {
    this->name = name;
    this->nickNames = nickNames;
    this->genre = genre;
    this->ID = ID;
}

QString Author::getName() const {
    return this->name;
}

QStringList Author::getNickNames() const {
    return this->nickNames;
}

QString Author::getNickName(int number) const {
    if (number >= this->nickNames.size())
        return "";
    else
        return this->nickNames[number];
}

Genre::Name Author::getGenre() const {
    return this->genre;
}

int Author::getID() const {
    return this->ID;
}

Author *Author::generate(int ID) {
    Author* newAuthor = new Author();
    newAuthor->ID = ID;
    newAuthor->name = Utility.getRandomName();

    //  Generate up to 3 [possibly] different nicknames
    int numberOfNickNames = rand() % 4;
    for (int i = 0; i < numberOfNickNames; i++)
        newAuthor->nickNames.push_back(Utility.getRandomName());
    newAuthor->genre = Genre::getRandom();
    return newAuthor;
}
