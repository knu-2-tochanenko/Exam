#include "singleauthorbook.h"

SingleAuthorBook::SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages,
    AuthorName& author) : BaseBook(name, genre, date, pages), author(author) {
}

SingleAuthorBook::SingleAuthorBook(SingleBook* book, AuthorName const &author)
    : BaseBook(book), author(author) {
}

QVector<AuthorName> SingleAuthorBook::getAuthors() const {
    QVector<AuthorName> res;
    res.push_back(this->author);
    return res;
}

bool SingleAuthorBook::hasAuthor(Author *author) {
    return (this->author.author->getID() == author->getID());
}

QVector<Author *> SingleAuthorBook::getAuthorsList() {
    QVector<Author*> res;
    res.push_back(this->author.author);
    return res;
}

QVector<AuthorName> SingleAuthorBook::getAuthorsWithNick() {
    QVector<AuthorName> res;
    res.push_back(this->author);
    return res;
}

SingleAuthorBook *SingleAuthorBook::generate(AuthorName const &authorName) {
    SingleAuthorBook* newBook = new SingleAuthorBook(SingleBook::generate(), authorName);
    return newBook;
}
