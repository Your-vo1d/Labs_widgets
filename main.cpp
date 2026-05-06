#include "win.h"

// Точка входа: создаём QApplication, окно Win и запускаем цикл обработки событий.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Win win(nullptr);  // nullptr означает: окно верхнего уровня, без родителя
    win.show();

    // app.exec() — бесконечный цикл обработки событий
    // Возвращает 0, когда последнее окно закрыто (или вызван app.quit()).
    return app.exec();
}
