#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "author.h"
#include "book.h"
#include <vector>

using std::vector;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonGenerateAuthor_clicked();
    void on_buttonGenerateBook_clicked();

private:

    //  Updates all views
    void update();
    void putBooks();
    void putAuthors();
    vector<Book*> selectedBooks; //    Vector for selecting books

    //  Selected author
    Author* filter;

    //  Generates data
    void generateBooks();
    void generateAuthors();

    //  Generates random author
    Author *generateAuthor();

    //  Generates random number and nickname book
    //  with given authors
    SingleAuthorBook *generateSingleAuthorBook();
    MultiAuthorBook *generateMultiAuthorBook();
    AuthorByChapterBook *generateAuthorByChapterBook();

    //  Data
    vector<Author*> authors;
    vector<SingleAuthorBook*> singleAuthorBooks;
    vector<MultiAuthorBook*> multiAuthorBooks;
    vector<AuthorByChapterBook*> authorByChapterBooks;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

/*

SingleAuthorBook* SingleAuthorBook::generate(int ID) {
    Author* newAuthor = Author::generate(ID);
    AuthorName newAuthorName(newAuthor, rand() % (newAuthor->getNicknamesCount() + 1));
    SingleAuthorBook* newBook = new SingleAuthorBook(Book::generate(), newAuthorName);
    return newBook;
}


MultiAuthorBook* MultiAuthorBook::generate(vector<int> IDs) {
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


AuthorByChapterBook* AuthorByChapterBook::generate(vector<int> IDs) {
    QMap<int, AuthorName> newAuthors;
    vector<Author*> authorsList;
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


 * */
