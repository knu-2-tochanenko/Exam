#include "utilityclass.h"
#include <time.h>
#include <random>
#include <QMessageBox>

UtilityClass::UtilityClass() {
    this->namesSize = this->names.size();
    this->lastNamesSize = this->lastNames.size();
    this->bookTitleSize = this->bookTitles.size();
}

QString UtilityClass::getRandomName() {
     
    int name = rand() % this->namesSize;
    int lastName = rand() % this->lastNamesSize;
    return this->names[name] + " " + this->lastNames[lastName];
}

QString UtilityClass::getRandomTitle() {
     
    int title = rand() % this->bookTitleSize;
    return this->bookTitles[title];
}

//  Check if generated date is valid. If not, correct it
void UtilityClass::normalize(int &year, int &month, int &day) {
    switch (month) {
    case 2:
        if ((year % 400 == 0) ||
                ((year % 400 != 0) && (year % 4 == 0) && (year % 100 != 0)))
        day %= 29;
        else day %= 28;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        day %= 31;
        break;
    default:
        day %= 30;
        break;
    }
}

void UtilityClass::errorMSG(QString message) {
    QMessageBox messageBox;
    messageBox.setText(message);
    messageBox.setIcon(QMessageBox::Warning);
    messageBox.exec();
}

QString Genre::to_string(Genre::Name name) {
    switch (name) {
        case SCIENCE_FICTION:
            return "Science fictoin";
        case SATIRE:
            return "Satire";
        case DRAMA:
            return "Drama";
        case ADVENTURE:
            return "Adventure";
        case ROMANCE:
            return "Romance";
        case MYSTERY:
            return "Mystery";
        case HORROR:
            return "Horror";
        case GUIDE:
            return "Guide";
        case SCIENCE:
            return "Science";
        case MATH:
            return "Math";
        case HISTORY:
            return "History";
        case POETRY:
            return "Poetry";
        case COMICS:
            return "Comics";
        case DICTIONARY:
            return "Dictionary";
        case ART:
            return "Art";
        case BIOGRAPHY:
            return "Biography";
        case DIARY:
            return "Diary";
        case FANTASY:
            return "Fantasy";
        default:
            return "UNRECOGNIZED";
    }
}

Genre::Name Genre::getRandom() {
    return static_cast<Genre::Name>(rand() % 19);
}
