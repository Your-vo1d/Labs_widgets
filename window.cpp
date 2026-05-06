#include "window.h"

Window::Window()
{
    codec = QTextCodec::codecForName("UTF-8");
    setWindowTitle(codec->toUnicode("Обработка событий"));

    area = new Area(this);
    btn  = new QPushButton(codec->toUnicode("Завершить"), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(area);
    layout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(close()));
}
