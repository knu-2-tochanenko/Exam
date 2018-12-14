#include "bookwidget.h"
#include "ui_bookwidget.h"

#include <QPainter>
#include <QStyleOption>

BookWidget::BookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWidget) {
    ui->setupUi(this);

}

BookWidget::~BookWidget() {
    delete ui;
}

void BookWidget::getInformation(BaseBook *book, QVector<AuthorWithPercentage> authors, int type) {
    this->book = book;
    this->authors = authors;
    this->type = type;
    update();
}

void BookWidget::update() {
    ui->bookISBN->setText(this->book->getISBN());
    ui->bookPublishDate->setText(this->book->getDate()->toString(Qt::TextDate));
    ui->bookGenre->setText(Genre::toString(this->book->getGenre()));
    ui->bookTitle->setText(this->book->getName());
    ui->bookPages->setNum(this->book->getPages());

    //  Put all authors and their
    int numberOfAuthors = this->authors.size();

    QFontMetrics fontMetrics(ui->bookAuthors->font());
    int fontHeight = fontMetrics.height();
    int height = fontHeight * numberOfAuthors;

    ui->bookAuthors->setMinimumHeight(height + 20);
    ui->bookAuthors->setMaximumHeight(height + 20);

    QString authorsString = "";

    for (int i = 0; i < numberOfAuthors; i++) {
        if (type == 1)
            authorsString += QString::number(i) + " : ";
        else if (type == 2)
            authorsString += QString::number(
                        static_cast<int>(this->book->getPages() * this->authors[i].percentage / 100)) + " : ";
        authorsString += this->authors[i].author->getNickName(this->authors[i].name);
        if (this->authors[i].name > 0)
            authorsString += " (" + this->authors[i].author->getNickName(0) + ")";
        authorsString += "\n";
    }

    ui->bookAuthors->setText(authorsString);

    this->height = 140 + height;

    this->setMinimumHeight(140 + height);
    this->setMaximumHeight(140 + height);
}

int BookWidget::getHeight() {
    return this->height;
}

void BookWidget::paintEvent(QPaintEvent *) {
    QStyleOption opt;
        opt.init(this);
        QPainter *p = new QPainter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, p, this);
}
