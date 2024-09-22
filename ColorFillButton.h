#ifndef COLORFILLBUTTON_H
#define COLORFILLBUTTON_H

#include <QPushButton>
#include <QPainter>

// Definicija klase ColorFillButton
class ColorFillButton : public QPushButton {
    Q_OBJECT

public:
    // Konstruktor koji prima tekst za dugme
    ColorFillButton(const QString &buttonText, QWidget *parent = nullptr);

    // Funkcija koja menja popunjavanje dugmeta
    void updateFill(bool increase);

    void setFilledParts(int parts);

protected:
    // Override paintEvent za prilagođeno crtanje
    void paintEvent(QPaintEvent *event) override;

private slots:
    void toggleFill();  // Slot za reakciju na klik

private:

    const int totalParts = 5;  // Ukupan broj delova za punjenje

public:
    int filledParts;  // Trenutno popunjenih delova

};

#endif // COLORFILLBUTTON_H
