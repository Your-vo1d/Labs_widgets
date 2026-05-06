#include "figura.h"

// Вычисляем проекции вектора длиной halflen на оси X и Y по текущему углу.
void Figura::move(float alpha, QPainter *painter)
{
    dx = static_cast<int>(halflen * cos(alpha));
    dy = static_cast<int>(halflen * sin(alpha));
    draw(painter);  // вызываем переопределённый метод - ключевое место полиморфизма
}

// Линия: один отрезок между двумя симметричными точками вокруг центра.
void MyLine::draw(QPainter *painter)
{
    painter->drawLine(x + dx, y + dy, x - dx, y - dy);
}

// Квадрат строится из 4 рёбер между соседними вершинами.
void MyRect::draw(QPainter *painter)
{
    painter->drawLine(x + dx, y + dy,  x + dy, y - dx);
    painter->drawLine(x + dy, y - dx,  x - dx, y - dy);
    painter->drawLine(x - dx, y - dy,  x - dy, y + dx);
    painter->drawLine(x - dy, y + dx,  x + dx, y + dy);
}
