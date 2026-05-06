#ifndef AREA_H
#define AREA_H

#include <QtWidgets>
#include "figura.h"

// Холст (Area) - виджет, на котором рисуются и анимируются фигуры.
// Он же управляет таймером: запускает при показе, останавливает при скрытии.
class Area : public QWidget
{
    int   myTimer; // идентификатор таймера, возвращённый startTimer()
    float alpha; // текущий угол поворота фигур (накапливается с каждым тиком)

public:
    Area(QWidget *parent = nullptr);
    ~Area();

    MyLine *myline;
    MyRect *myrect;

protected:
    // Четыре обработчика событий
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent  *event) override;
    void hideEvent(QHideEvent  *event) override;
};

#endif // AREA_H
