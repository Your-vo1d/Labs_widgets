#include "area.h"

Area::Area(QWidget *parent) : QWidget(parent)
{
    // Фиксируем размер холста - фигуры нарисованы под конкретные координаты,
    // при изменении размера они могут вылезти за пределы
    setFixedSize(QSize(300, 200));

    myline = new MyLine(80,  100, 50);
    myrect = new MyRect(220, 100, 50);
    alpha  = 0;
}

// showEvent вызывается Qt автоматически при первом show() и при любом повторном показе.
// Именно здесь запускаем таймер 
void Area::showEvent(QShowEvent *)
{
    myTimer = startTimer(50);
}

// Qt вызывает paintEvent всякий раз, когда нужно перерисовать виджет
void Area::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::red);  // все линии красным

    myline->move(alpha, &painter); // линия вращается со скоростью 1×
    myrect->move(alpha * (-0.5f), &painter); // квадрат - в обратную сторону, вдвое медленнее
}

void Area::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == myTimer)
    {

        alpha += 0.2f;
        update(); 
    }
    else
    {
        QWidget::timerEvent(event);
    }
}

// hideEvent симметричен showEvent: виджет скрывается - таймер останавливаем.
void Area::hideEvent(QHideEvent *)
{
    killTimer(myTimer);
}

Area::~Area()
{
    delete myline;
    delete myrect;
}
