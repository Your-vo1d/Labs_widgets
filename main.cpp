#include "window.h"

// QApplication инициализирует всю Qt-инфраструктуру — создаём первым делом.
int main(int argc, char *argv[])
{
    QApplication appl(argc, argv);
    Window win;
    win.show();
    return appl.exec();
}
