#include "circlewidget.h"
#include <QPainter>
#include <QDebug>

CircleWidget::CircleWidget(QWidget *parent)
    : QWidget(parent), m_filled(false)
{
    setFixedSize(26, 26);  // Postavljanje fiksne veličine
}

void CircleWidget::setFilled(bool filled)
{
    qDebug() << "Da li je usao u setFilled:" << filled;
    m_filled = filled;
     qDebug() << "Pozivam update()";
    update();  // Osvježavanje widgeta
}

void CircleWidget::paintEvent(QPaintEvent *event)
{

    qDebug() << "Da li je usao u paintevent:";
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

     QColor wetGrassColor("#228B22");
     QColor red("#FF4646");


    // Boja za ivice
    QPen pen(wetGrassColor, 0.8);  // Zelena ivica sa debljinom 5
    painter.setPen(pen);
   // painter.setBrush(wetGrassColor);


    // Ako je krug popunjen
    if (m_filled)
    {
        painter.setBrush(red);  // Popunjava se zelenom bojom
    }
    else
    {
       painter.setBrush(wetGrassColor);  // Nema popunjavanja
    }

    // Crtanje kruga
    painter.drawEllipse(0, 0, 26, 26);
}
