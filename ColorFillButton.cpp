#include "ColorFillButton.h"

// Konstruktor koji prima tekst za dugme
ColorFillButton::ColorFillButton(const QString &buttonText, QWidget *parent)
    : QPushButton(buttonText, parent), filledParts(0) {
    this->setFixedSize(100, 100);  // Fiksna veličina dugmeta
    //connect(this, &QPushButton::clicked, this, &ColorFillButton::toggleFill);
}

// Funkcija za ažuriranje popunjenosti
void ColorFillButton::updateFill(bool increase) {
    if (increase) {
        if (filledParts < totalParts) {
            filledParts++;  // Povećaj popunjenost
        }
    } else {
        if (filledParts > 0) {
            filledParts--;  // Smanji popunjenost
        }
    }
    update();  // Ponovo iscrtaj dugme
}

// Funkcija za prilagođeno crtanje
void ColorFillButton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);  // Nasledi ponašanje QPushButton

    QPainter painter(this);

    // Ukupan broj delova koje popunjavamo (9 delova)
    int heightPerPart = this->height() / totalParts;

    // Ispunimo deo dugmeta plavom bojom
    for (int i = 0; i < filledParts; i++) {
        painter.fillRect(0, this->height() - (i + 1) * heightPerPart, this->width(), heightPerPart, Qt::blue);
    }
}

// Funkcija koja poveća popunjenost kada se klikne na dugme
void ColorFillButton::toggleFill() {
    updateFill(true);  // Povećaj popunjenost na klik
}
