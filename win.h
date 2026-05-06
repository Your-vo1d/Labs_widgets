#ifndef WIN_H
#define WIN_H

#include <QtWidgets>
#include <QTextCodec>


// Класс-валидатор нужен НЕ для проверки правильности числа, а для того,
// чтобы QLineEdit слал сигнал returnPressed() по Enter.
// Без установленного валидатора сигнал не генерируется, если ввод "неполный"
class StrValidator : public QValidator
{
public:

    StrValidator(QObject *parent) : QValidator(parent) {}

    virtual State validate(QString &str, int &pos) const override
    {
        Q_UNUSED(str)
        Q_UNUSED(pos)
        return Acceptable;
    }
};


class Win : public QWidget
{
    Q_OBJECT 

protected:
    QTextCodec  *codec;

    QFrame      *frame;        // рамка вокруг полей - чисто декоративно
    QLabel      *inputLabel;   // метка "Введите число:"
    QLineEdit   *inputEdit;    // поле для ввода числа
    QLabel      *outputLabel;  // метка "Результат:" (скрыта до вычисления)
    QLineEdit   *outputEdit;   // поле с результатом (скрыто до вычисления)
    QPushButton *nextButton;   // кнопка "Следующее"
    QPushButton *exitButton;   // кнопка "Выход"

public:
    Win(QWidget *parent = nullptr);

public slots:
    // begin() сбрасывает интерфейс в начальное состояние - вызывается и при старте,
    // и по нажатию "Следующее"
    void begin();

    // calc() читает поле ввода, возводит в квадрат или ругается на некорректный ввод
    void calc();
};

#endif // WIN_H
