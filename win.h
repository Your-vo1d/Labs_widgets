#ifndef WIN_H
#define WIN_H


#include <QtWidgets>
#include <QTextCodec>


class Counter : public QLineEdit
{
    Q_OBJECT  // без этого макроса signals/slots не будут работать

public:
    // Передаём начальное значение ("0") и родителя прямо в QLineEdit.
    Counter(const QString &contents, QWidget *parent = nullptr)
        : QLineEdit(contents, parent) {}

signals:
    // Сигнал генерируется каждый раз, когда счётчик достигает кратного пяти значения.
    // Тело метода не нужно — MOC сгенерирует его сам.
    void tick_signal();

public slots:
    void add_one()
    {
        QString str = text();
        int r = str.toInt();  // читаем текущее число из поля

        // Проверяем ДО инкремента: если текущее значение кратно 5 (и не ноль),
        // испускаем сигнал — значит завершилась очередная серия из пяти нажатий.
        // r == 0 исключаем, чтобы не стрелять сигналом при самом первом нажатии.
        if (r != 0 && r % 5 == 0)
            emit tick_signal();

        r++;
        str.setNum(r);
        setText(str);
    }
};


// Класс главного окна. Содержит два счётчика, кнопку "+1" и кнопку "Выход".
class Win : public QWidget
{
    Q_OBJECT

protected:
    QTextCodec  *codec;
    QLabel      *label1, *label2; // подписи над счётчиками
    Counter     *edit1,  *edit2;  // edit1 — по 1, edit2 — по 5
    QPushButton *calcbutton; // кнопка "+1"
    QPushButton *exitbutton; // кнопка "Выход"

public:
    Win(QWidget *parent = nullptr);
};

#endif // WIN_H
