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

void BookWidget::getInformation(Book *book, QVector<AuthorName> authors) {
    this->book = book;
    this->authors = authors;
    update();
}

void BookWidget::update() {
    ui->bookISBN->setText(this->book->getISBN());
    ui->bookPublishDate->setText(this->book->getDate()->toString(Qt::TextDate));
    ui->bookGenre->setText(Genre::to_string(this->book->getGenre()));
    ui->bookTitle->setText(this->book->getName());
    ui->bookPages->setNum(this->book->getPages());

    //  Put all authors and their
    int numberOfAuthors = this->authors.size();

    QFontMetrics fontMetrics(ui->bookAuthors->font());
    int fontHeight = fontMetrics.height();
    int height = fontHeight * numberOfAuthors;

    ui->bookAuthors->setMinimumHeight(height);
    ui->bookAuthors->setMaximumHeight(height);

    QString authorsString = "";

    for (int i = 0; i < numberOfAuthors; i++)
        authorsString += this->authors[i].author->getNickName(this->authors[i].name) + "\n";

    this->setMinimumHeight(170 + height);
    this->setMaximumHeight(170 + height);
}

void BookWidget::paintEvent(QPaintEvent *) {
    QStyleOption opt;
        opt.init(this);
        QPainter *p = new QPainter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, p, this);
}
