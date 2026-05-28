#include "win.h"
#include <new>

Win::Win(QWidget *parent) : QWidget(parent)
{
    codec = QTextCodec::codecForName("UTF-8");
    setWindowTitle(codec->toUnicode("Счётчик"));

    label1 = new (std::nothrow) QLabel(codec->toUnicode("Счёт по 1"), this);
    if (!label1)
    {
        setWindowTitle("Ошибка: QLabel label1");
        return;
    }

    label2 = new (std::nothrow) QLabel(codec->toUnicode("Счёт по 5"), this);
    if (!label2)
    {
        setWindowTitle("Ошибка: QLabel label2");
        return;
    }

    // Оба счётчика стартуют с "0" - пустая строка здесь не подойдёт,
    // потому что toInt() вернёт 0 и логика первого нажатия могла бы дать ложный сигнал.
    edit1 = new (std::nothrow) Counter("0", this);
    if (!edit1)
    {
        setWindowTitle("Ошибка: Counter edit1");
        return;
    }

    edit2 = new (std::nothrow) Counter("0", this);
    if (!edit2)
    {
        setWindowTitle("Ошибка: Counter edit2");
        return;
    }

    calcbutton = new (std::nothrow) QPushButton("+1", this);
    if (!calcbutton)
    {
        setWindowTitle("Ошибка: QPushButton calcbutton");
        return;
    }

    exitbutton = new (std::nothrow) QPushButton(codec->toUnicode("Выход"), this);
    if (!exitbutton)
    {
        setWindowTitle("Ошибка: QPushButton exitbutton");
        return;
    }

    // Три горизонтальных ряда, собранных в один вертикальный layout.
    QHBoxLayout *layout1 = new(std::nothrow) QHBoxLayout();
    if (!layout1) { setWindowTitle("Ошибка: QHBoxLayout layout1"); return; }
    layout1->addWidget(label1);
    layout1->addWidget(label2);

    QHBoxLayout *layout2 = new(std::nothrow) QHBoxLayout();
    if (!layout2) { setWindowTitle("Ошибка: QHBoxLayout layout2"); return; }
    layout2->addWidget(edit1);
    layout2->addWidget(edit2);

    QHBoxLayout *layout3 = new(std::nothrow) QHBoxLayout();
    if (!layout3) { setWindowTitle("Ошибка: QHBoxLayout layout3"); return; }
    layout3->addWidget(calcbutton);
    layout3->addWidget(exitbutton);

    QVBoxLayout *layout4 = new(std::nothrow) QVBoxLayout(this);
    if (!layout4) { setWindowTitle("Ошибка: QVBoxLayout layout4"); return; }
    layout4->addLayout(layout1);
    layout4->addLayout(layout2);
    layout4->addLayout(layout3);

    // Нажатие "+1" - edit1 считает одиночные нажатия
    connect(calcbutton, &QPushButton::clicked, edit1, &Counter::add_one);

    // Когда edit1 достигает кратного пяти - tick_signal попадает в edit2,
    // который считает завершённые серии.
    connect(edit1, &Counter::tick_signal, edit2, &Counter::add_one);

    connect(exitbutton, &QPushButton::clicked, this, &Win::close);
}
