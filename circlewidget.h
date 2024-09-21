#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>

class CircleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CircleWidget(QWidget *parent = nullptr);

    // Funkcija za punjenje kruga
    void setFilled(bool filled);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_filled;  // Da li je krug popunjen
    //CircleWidget circle;
};

#endif // CIRCLEWIDGET_H
