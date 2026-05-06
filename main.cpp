#include "win.h"

// QApplication обязан быть создан первым — он инициализирует всю Qt-инфраструктуру.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Win win(nullptr);
    win.show();
    return app.exec();  // запускаем цикл событий; выйдем, когда закроется окно
}
