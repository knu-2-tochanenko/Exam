#include "author.h"
#include "time.h"

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
    if (number == 0)
        return this->name;
    if (number > this->nickNames.size() || number <= 0)
        return this->name;
    else
        return this->nickNames[number - 1];
}

Genre::Name Author::getGenre() const {
    return this->genre;
}

int Author::getID() const {
    return this->ID;
}

int Author::getNicknamesCount() const {
    return this->nickNames.size();
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

void Author::generateValues() {
    this->name = Utility.getRandomName();
    int numberOfNickNames = rand() % 4;
    this->nickNames.clear();
    for (int i = 0; i < numberOfNickNames; i++)
        this->nickNames.push_back(Utility.getRandomName());
    this->genre = Genre::getRandom();
}
