#include "singlebook.h"

QVector<Author *> SingleBook::getAuthorsList() {
    return QVector<Author *>();
}

QVector<AuthorWithPercentage> SingleBook::getAuthorsWithNick() {
    return QVector<AuthorWithPercentage>();
}

bool SingleBook::hasAuthor(Author *author) {
    return true;
}

SingleBook *SingleBook::generate() {
    SingleBook* book = new SingleBook();

    QString ISBN = "";
    for (int i = 0; i < 13; i++)
        ISBN += static_cast<char>(rand() % 10 + '0');
    book->setISBN(ISBN);
    int year = rand() % 300 + 1753;
    int month = rand() % 12;
    int day = rand() % 31;
    Utility.normalize(year, month, day);
    book->setDate(new QDate(year, month, day));
    book->setName(Utility.getRandomTitle());
    book->setGenre(Genre::getRandom());
    book->setPages(rand() % MAX_PAGES);
    return book;
}

int SingleBook::getType() {
    return -1;
}

int SingleBook::countPages(Author *author) {
    return this->pages;
}
