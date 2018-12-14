#include "authorbychapterbook.h"

AuthorByChapterBook::AuthorByChapterBook(QString name, Genre::Name genre, QDate* date, int pages,
    QMap<int, AuthorName> authors) : BaseBook(name, genre, date, pages) {
    this->authors = authors;
}

AuthorByChapterBook::AuthorByChapterBook(SingleBook* book, QMap<int, AuthorName> authors)
    : BaseBook(book) {
    this->authors = authors;
}

QMap<int, AuthorName> AuthorByChapterBook::getAuthors() const {
    return this->authors;
}

bool AuthorByChapterBook::hasAuthor(Author *author) {
    for (int i = 0; i < this->authors.size(); i++)
        if (this->authors[i].author->getID() == author->getID())
            return true;
    return false;
}

QVector<Author *> AuthorByChapterBook::getAuthorsList() {
    QVector<Author*> res;
    for (int i = 0; i < this->authors.size(); i++)
        res.push_back(this->authors[i].author);
    return res;
}

QVector<AuthorName> AuthorByChapterBook::getAuthorsWithNick() {
    int authorsSize = this->authors.size();
    QVector<AuthorName> res;
    for (int i = 0; i < authorsSize; i++)
        res.push_back(AuthorName(this->authors[i].author, this->authors[i].name));
    return res;
}

AuthorByChapterBook *AuthorByChapterBook::generate(QMap<int, AuthorName> const &authorsMap) {
    AuthorByChapterBook* newBook = new AuthorByChapterBook(SingleBook::generate(), authorsMap);
    return newBook;
}
