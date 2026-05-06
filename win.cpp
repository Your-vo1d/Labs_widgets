#include "win.h"

Win::Win(QWidget *parent) : QWidget(parent)
{
    codec = QTextCodec::codecForName("UTF-8");
    setWindowTitle(codec->toUnicode("Счётчик"));

    label1 = new QLabel(codec->toUnicode("Счёт по 1"), this);
    label2 = new QLabel(codec->toUnicode("Счёт по 5"), this);

    // Оба счётчика стартуют с "0" - пустая строка здесь не подойдёт,
    // потому что toInt() вернёт 0 и логика первого нажатия могла бы дать ложный сигнал.
    edit1 = new Counter("0", this);
    edit2 = new Counter("0", this);

    calcbutton = new QPushButton("+1", this);
    exitbutton = new QPushButton(codec->toUnicode("Выход"), this);

    // Три горизонтальных ряда, собранных в один вертикальный layout.
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(label1);
    layout1->addWidget(label2);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(edit1);
    layout2->addWidget(edit2);

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(calcbutton);
    layout3->addWidget(exitbutton);

    QVBoxLayout *layout4 = new QVBoxLayout(this);
    layout4->addLayout(layout1);
    layout4->addLayout(layout2);
    layout4->addLayout(layout3);

    // Нажатие "+1" - edit1 считает одиночные нажатия
    connect(calcbutton, SIGNAL(clicked(bool)), edit1, SLOT(add_one()));

    // Когда edit1 достигает кратного пяти - tick_signal попадает в edit2,
    // который считает завершённые серии. Объекты не знают друг о друге напрямую -
    // только через сигнал. Это и есть слабая связность в Qt.
    connect(edit1, SIGNAL(tick_signal()), edit2, SLOT(add_one()));

    connect(exitbutton, SIGNAL(clicked(bool)), this, SLOT(close()));
}
