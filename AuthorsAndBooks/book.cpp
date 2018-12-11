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

void Book::generateNumbers() {
    srand(clock_t());
    int year = rand() % 519 + 1500;
    int month = rand() % 12;
    int day = rand() % 31;
    Utility.normalize(year, month, day);
    this->date = new QDate(year, month, day);
    this->name = Utility.getRandomTitle();
    this->genre = Genre::getRandom();
    this->pages = rand() % MAX_PAGES;
}

SingleAuthorBook::SingleAuthorBook(QString name, Genre::Name genre, QDate* date, int pages,
    AuthorName& author) : Book(name, genre, date, pages), author(author) {
}

SingleAuthorBook::SingleAuthorBook(Book* book, AuthorName const &author)
    : Book(book), author(author) {
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

QVector<AuthorName> SingleAuthorBook::getAuthorsWithNick() const {
    QVector<AuthorName> res;
    res.push_back(this->author);
    return res;
}

SingleAuthorBook *SingleAuthorBook::generate(AuthorName const &authorName) {
    SingleAuthorBook* newBook = new SingleAuthorBook(Book::generate(), authorName);
    return newBook;
}

MultiAuthorBook::MultiAuthorBook(QString name, Genre::Name genre, QDate* date, int pages,
    QVector<AuthorWithPercentage> authors) : Book(name, genre, date, pages) {
    this->authors = authors;
}

MultiAuthorBook::MultiAuthorBook(Book* book, QVector<AuthorWithPercentage> authors)
    : Book(book) {
    this->authors = authors;
}

QVector<AuthorName> MultiAuthorBook::getAuthorsWithNick() {
    int authorsSize = this->authors.size();
    QVector<AuthorName> res;
    for (int i = 0; i < authorsSize; i++)
        res.push_back(AuthorName(this->authors[i].author, this->authors[i].name));
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

vector<Author *> MultiAuthorBook::getAuthorsList() {
    vector<Author*> res;
    for (int i = 0; i < this->authors.size(); i++)
        res.push_back(this->authors[i].author);
    return res;
}

MultiAuthorBook *MultiAuthorBook::generate(QVector<AuthorWithPercentage> const &authorsMap) {
    MultiAuthorBook* newBook = new MultiAuthorBook(Book::generate(), authorsMap);
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
    AuthorByChapterBook* newBook = new AuthorByChapterBook(Book::generate(), authorsMap);
    return newBook;
}

AuthorName::AuthorName(Author *author, int name) {
    this->name = name;
    this->author = author;
}

AuthorName AuthorName::getAuthor() {
    AuthorName res(this->author, this->name);
    return res;
}

AuthorWithPercentage::AuthorWithPercentage(Author *author, int name, int percentage) {
    this->author = author;
    this->name = name;
    this->percentage = percentage;
}

AuthorName AuthorWithPercentage::getAuthor() {
    AuthorName res(this->author, this->name);
    return res;
}
