#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>
#include "basebook.h"
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

    void getInformation(BaseBook* book, QVector<AuthorWithPercentage> authors, int type);

    //  Draws information
    void update();

    //  Get height
    int getHeight();

private:
    Ui::BookWidget *ui;

    //  Data
    BaseBook* book;
    QVector<AuthorWithPercentage> authors;
    int height = 0;
    /* type:
     *  0 : SingleAuthorBook
     *  1 : AuthorByChapterBook
     *  2 : MultiAuthorBook         */
    int type;

    //  To draw bottom line
    void paintEvent(QPaintEvent *);
};

#endif // BOOKWIDGET_H
