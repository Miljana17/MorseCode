#include "ColorFillButton.h"
#include <QDebug>

// Konstruktor koji prima tekst za dugme
ColorFillButton::ColorFillButton(const QString &buttonText, QWidget *parent)
    : QPushButton(buttonText, parent), filledParts(0) {
    this->setFixedSize(100, 100);  // Fiksna veličina dugmeta
    //connect(this, &QPushButton::clicked, this, &ColorFillButton::toggleFill);
    //qDebug() << "Novi ColorFillButton napravljen, filledParts je postavljen na:" << filledParts;
}

// Funkcija za ažuriranje popunjenosti
void ColorFillButton::updateFill(bool increase) {

    qDebug() << "usao u updateFill button";
    qDebug() << "FILLEDPARTS" << filledParts;

    if (increase) {
        if (filledParts < totalParts) {

            filledParts = filledParts + 1;  // Povećaj popunjenost
            qDebug() << "UVECAO GA" << filledParts;
            //update();
        }
    } else {
        if (filledParts > 0) {
            filledParts--;  // Smanji popunjenost
            qDebug() << "SMANJIO GA" << filledParts;
            //update();
        }
    }
    update();  // Ponovo iscrtaj dugme
}

// Funkcija za prilagođeno crtanje
void ColorFillButton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);  // Nasledi ponašanje QPushButton

    QPainter painter(this);
    qDebug() << "da li je usao barem u PAINTEVENT";

    // Ukupan broj delova koje popunjavamo (9 delova)
    int heightPerPart = this->height() / totalParts;

    // Ispunimo deo dugmeta plavom bojom
    qDebug() << "VREDNOST filledParts pre for petlje" << filledParts;
    for (int i = 0; i < filledParts; i++) {
        painter.fillRect(0, this->height() - (i + 1) * heightPerPart, this->width(), heightPerPart, Qt::gray);
        qDebug() << "da li je usao u paint event pa paint for petlju";
    }
}

// Funkcija koja poveća popunjenost kada se klikne na dugme
void ColorFillButton::toggleFill() {
    updateFill(true);  // Povećaj popunjenost na klik
}

void ColorFillButton::setFilledParts(int parts)
{
    filledParts = parts;
}
