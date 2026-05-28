#include "window.h"
#include <new>

Window::Window()
{
    codec = QTextCodec::codecForName("UTF-8");
    setWindowTitle(codec->toUnicode("Обработка событий"));

    area = new (std::nothrow) Area(this);
    if (!area)
    {
        setWindowTitle("Ошибка: Area");
        return;
    }

    btn = new (std::nothrow) QPushButton(codec->toUnicode("Завершить"), this);
    if (!btn)
    {
        setWindowTitle("Ошибка: QPushButton btn");
        return;
    }

    QVBoxLayout *layout = new (std::nothrow) QVBoxLayout(this);
    if (!layout)
    {
        setWindowTitle("Ошибка: QVBoxLayout layout");
        return;
    }
    layout->addWidget(area);
    layout->addWidget(btn);

    connect(btn, &QPushButton::clicked, this, &Window::close);
}
