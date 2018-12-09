#include "book.h"
#include "time.h"

Book::Book(QString name, Genre::Name genre, QDate* date, int pages) {
    this->name = name;
    this->genre = genre;
    this->date = date;
    this->pages = pages;
}

Book::Book(Book &book) {
    this->ISBN = book.ISBN;
    this->name = book.name;
    this->date = book.date;
    this->genre = book.genre;
    this->pages = book.pages;
}

Book::Book(Book *book) {
    this->ISBN = book->ISBN;
    this->name = book->name;
    this->date = book->date;
    this->genre = book->genre;
    this->pages = book->pages;
}

Genre::Name Book::getGenre() const {
    return this->genre;
}

QString Book::getName() const {
    return this->name;
}

QDate* Book::getDate() const {
    return this->date;
}

int Book::getPages() const {
    return this->pages;
}

QString Book::getISBN() const {
    return this->ISBN;
}

Book* Book::generate() {
    srand(clock_t());
    Book* book = new Book();
    book->ISBN = "";
    for (int i = 0; i < 13; i++)
        book->ISBN += static_cast<char>(rand() % 10 + '0');
    int year = rand() % 519 + 1500;
    int month = rand() % 12;
    int day = rand() % 31;
    Utility.normalize(year, month, day);
    book->date = new QDate(year, month, day);
    book->name = Utility.getRandomTitle();
    book->genre = Genre::getRandom();
    book->pages = rand() % MAX_PAGES;
    return book;
}

SingleAuthorBook::SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages,
    AuthorName& author) : Book(name, genre, date, pages), author(author) {
}

SingleAuthorBook::SingleAuthorBook(Book* book, AuthorName& author)
    : Book(book), author(author) {
}

AuthorName SingleAuthorBook::getAuthor() const {
    return this->author;
}

SingleAuthorBook* SingleAuthorBook::generate(int ID) {
    Author* newAuthor = Author::generate(ID);
    AuthorName newAuthorName(newAuthor, rand() % (newAuthor->getNicknamesCount() + 1));
    SingleAuthorBook* newBook = new SingleAuthorBook(Book::generate(), newAuthorName);
    return newBook;
}

MultiAuthorBook::MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages,
    QMap<AuthorName, int> authors) : Book(name, genre, date, pages) {
    this->authors = authors;
}

MultiAuthorBook::MultiAuthorBook(Book* book, QMap<AuthorName, int> authors)
    : Book(book) {
    this->authors = authors;
}

QMap<AuthorName, int> MultiAuthorBook::getAuthors() const {
    return this->authors;
}

MultiAuthorBook* MultiAuthorBook::generate(QVector<int> IDs) {
    QMap<AuthorName, int> newAuthors;
    int activityCount = 100, activity;
    for (int i = 0; i < IDs.size(); i++) {
        Author* author = Author::generate(IDs[i]);
        AuthorName newAuthorName(author, rand() % (author->getNicknamesCount() + 1));
        activity = rand() % (activityCount - (IDs.size() - i));
        activityCount -= activity;
        newAuthors.insert(newAuthorName, activity);
    }
    MultiAuthorBook* newBook = new MultiAuthorBook(Book::generate(), newAuthors);
    return newBook;
}

AuthorByChapterBook::AuthorByChapterBook(QString name, Genre::Name genre, QDate* date, int pages,
    QMap<int, AuthorName> authors) : Book(name, genre, date, pages) {
    this->authors = authors;
}

AuthorByChapterBook::AuthorByChapterBook(Book* book, QMap<int, AuthorName> authors)
    : Book(book) {
    this->authors = authors;
}

QMap<int, AuthorName> AuthorByChapterBook::getAuthors() const {
    return this->authors;
}

//  Some authors might be lost
AuthorByChapterBook* AuthorByChapterBook::generate(QVector<int> IDs) {
    QMap<int, AuthorName> newAuthors;
    QVector<Author*> authorsList;
    int randomAuthor;

    for (int i = 0; i < IDs.size(); i++) {
        Author* author = Author::generate(IDs[i]);
        authorsList.push_back(author);
    }

    int chapters = rand() % MAX_CHAPTERS;
    for (int i = 0; i < chapters; i++) {
        randomAuthor = rand() % IDs.size();
        AuthorName newAuthorName(authorsList[randomAuthor], rand() %
                                 (authorsList[randomAuthor]->getNicknamesCount() + 1));
        newAuthors.insert(i, newAuthorName);
    }
    AuthorByChapterBook* newBook = new AuthorByChapterBook(Book::generate(), newAuthors);
    return newBook;
}

AuthorName::AuthorName(Author *author, int name) {
    this->name = name;
    this->author = author;
}
