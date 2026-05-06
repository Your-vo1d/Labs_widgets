#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QTextCodec>
#include "area.h"


class Window : public QWidget
{
protected:
    QTextCodec *codec;
    Area       *area;  // холст с вращающимися фигурами
    QPushButton *btn;  // кнопка завершения

public:
    Window();
};

#endif // WINDOW_H
