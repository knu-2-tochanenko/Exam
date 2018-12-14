#include "multiauthorbook.h"

MultiAuthorBook::MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages,
    QVector<AuthorWithPercentage> authors) : BaseBook(name, genre, date, pages) {
    this->authors = authors;
}

MultiAuthorBook::MultiAuthorBook(SingleBook* book, QVector<AuthorWithPercentage> authors)
    : BaseBook(book) {
    this->authors = authors;
}

QVector<AuthorWithPercentage> MultiAuthorBook::getAuthorsWithNick() {
    int authorsSize = this->authors.size();
    QVector<AuthorWithPercentage> res;
    for (int i = 0; i < authorsSize; i++)
        res.push_back(AuthorWithPercentage(
                          this->authors[i].author, this->authors[i].name, this->authors[i].percentage));
    return res;
}

QVector<AuthorWithPercentage> MultiAuthorBook::getAuthors() const {
    return this->authors;
}

bool MultiAuthorBook::hasAuthor(Author *author) {
    int authorsSize = this->authors.size();
    for (int i = 0; i < authorsSize; i++)
        if (this->authors[i].author->getID() == author->getID())
            return true;
    return false;
}

QVector<Author *> MultiAuthorBook::getAuthorsList() {
    QVector<Author*> res;
    for (int i = 0; i < this->authors.size(); i++)
        res.push_back(this->authors[i].author);
    return res;
}

MultiAuthorBook *MultiAuthorBook::generate(QVector<AuthorWithPercentage> const &authorsMap) {
    MultiAuthorBook* newBook = new MultiAuthorBook(SingleBook::generate(), authorsMap);
    return newBook;
}

int MultiAuthorBook::getType() {
    return 2;
}
