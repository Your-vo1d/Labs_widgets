#ifndef FIGURA_H
#define FIGURA_H

#include <QPainter>
#include <cmath>  // cos, sin

// Абстрактный базовый класс фигуры.
// Хранит геометрический центр (x, y) и полуразмер фигуры (halflen)
class Figura
{
protected:
    int x, y, halflen, dx, dy, r;

    // Чисто виртуальный метод — каждый наследник рисует себя по-своему.
    virtual void draw(QPainter *painter) = 0;

public:
    Figura(int X, int Y, int Halflen)
        : x(X), y(Y), halflen(Halflen), dx(0), dy(0), r(0) {}

    virtual ~Figura() = default;

    void move(float alpha, QPainter *painter);
};

class MyLine : public Figura
{
protected:
    void draw(QPainter *painter) override;
public:
    MyLine(int x, int y, int halflen) : Figura(x, y, halflen) {}
};

class MyRect : public Figura
{
protected:
    void draw(QPainter *painter) override;
public:
    MyRect(int x, int y, int halflen) : Figura(x, y, halflen) {}
};

#endif // FIGURA_H
