#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>
#include "book.h"
#include "author.h"
#include <vector>
#include <QVector>

using std::vector;

namespace Ui {
    class BookWidget;
}

class BookWidget : public QWidget {
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = nullptr);
    ~BookWidget();

    void getInformation(Book* book, QVector<AuthorName> authors);

    //  Draws information
    void update();

private:
    Ui::BookWidget *ui;

    //  Data
    Book* book;
    QVector<AuthorName> authors;

    //  To draw bottom line
    void paintEvent(QPaintEvent *);
};

#endif // BOOKWIDGET_H
