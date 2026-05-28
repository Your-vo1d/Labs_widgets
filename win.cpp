#include "win.h"
#include <new>

// Конструктор - создаёт все виджеты, выстраивает компоновку, подключает сигналы
Win::Win(QWidget *parent) : QWidget(parent)
{
    // codecForName ищет конвертер по имени кодировки - объект живёт статически,
    codec = QTextCodec::codecForName("UTF-8");
    setWindowTitle(codec->toUnicode("Возведение в квадрат"));

    // QFrame даёт нам рамку вокруг полей ввода/вывода.
    // Panel + Raised - "выпуклый" стиль
    frame = new (std::nothrow) QFrame(this);
    if (!frame)
    {
        setWindowTitle("Ошибка: QFrame");
        return;
    }
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);

    // Метки и поля ввода создаём с this в качестве родителя -
    // Qt сам освободит память при уничтожении окна (дерево объектов).
    inputLabel = new (std::nothrow) QLabel(codec->toUnicode("Введите число:"), this);
    if (!inputLabel)
    {
        setWindowTitle("Ошибка: QLabel inputLabel");
        return;
    }

    outputLabel = new (std::nothrow) QLabel(codec->toUnicode("Результат:"), this);
    if (!outputLabel)
    {
        setWindowTitle("Ошибка: QLabel outputLabel");
        return;
    }

    nextButton = new (std::nothrow) QPushButton(codec->toUnicode("Следующее"), this);
    if (!nextButton)
    {
        setWindowTitle("Ошибка: QPushButton nextButton");
        return;
    }

    exitButton = new (std::nothrow) QPushButton(codec->toUnicode("Выход"), this);
    if (!exitButton)
    {
        setWindowTitle("Ошибка: QPushButton exitButton");
        return;
    }

    inputEdit = new (std::nothrow) QLineEdit("", this);
    if (!inputEdit)
    {
        setWindowTitle("Ошибка: QLineEdit inputEdit");
        return;
    }

    outputEdit = new (std::nothrow) QLineEdit("", this);
    if (!outputEdit)
    {
        setWindowTitle("Ошибка: QLineEdit outputEdit");
        return;
    }

    // Без валидатора сигнал returnPressed() не пошлётся при нажатии Enter -
    // Qt считает ввод незавершённым. Наш StrValidator всегда говорит "Acceptable",
    // поэтому сигнал всегда проходит, а реальная проверка будет в calc().
    StrValidator *v = new (std::nothrow) StrValidator(inputEdit);
    if (!v)
    {
        setWindowTitle("Ошибка: StrValidator");
        return;
    }
    inputEdit->setValidator(v);

    // Левая колонка: рамка с метками и полями один под другим.
    // Layout сам вычислит размеры
    QVBoxLayout *vLayout1 = new (std::nothrow) QVBoxLayout(frame);
    if (!vLayout1)
    {
        setWindowTitle("Ошибка: QVBoxLayout vLayout1");
        return;
    }
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch(); // пустое пространство снизу, чтобы элементы прижались к верху

    // Правая колонка: две кнопки
    QVBoxLayout *vLayout2 = new (std::nothrow) QVBoxLayout();
    if (!vLayout2)
    {
        setWindowTitle("Ошибка: QVBoxLayout vLayout2");
        return;
    }
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch();

    // Горизонтальный layout объединяет рамку и колонку с кнопками
    QHBoxLayout *hLayout = new (std::nothrow) QHBoxLayout(this);
    if (!hLayout)
    {
        setWindowTitle("Ошибка: QHBoxLayout hLayout");
        return;
    }
    hLayout->addWidget(frame);
    hLayout->addLayout(vLayout2);

    // Вызываем begin() прямо в конструкторе - это инициализирует состояние виджетов
    begin();

    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    connect(nextButton, &QPushButton::clicked, this, &Win::begin);
    connect(inputEdit, &QLineEdit::returnPressed, this, &Win::calc);
}

// begin() - сброс интерфейса в "режим ввода"
void Win::begin()
{
    inputEdit->clear();

    // Кнопка "Следующее" не должна быть активна до получения результата -
    nextButton->setEnabled(false);

    // setDefault(false) важно: если кнопка "default", она получает нажатие Enter,
    // перехватывая его у поля ввода.
    nextButton->setDefault(false);

    inputEdit->setEnabled(true);

    // Скрываем строку результата полностью - setVisible(false) убирает виджет из layout,
    // в отличие от setEnabled, который просто делает виджет серым.
    // Скрытый элемент не занимает место, окно выглядит чище.
    outputLabel->setVisible(false);
    outputEdit->setVisible(false);
    outputEdit->setEnabled(false);

    inputEdit->setFocus(); // фокус сразу на поле ввода, пользователь может печатать без клика
}

// calc() - вычисляет квадрат числа или показывает ошибку
void Win::calc()
{
    bool Ok = true;
    float r, a; // float, как в оригинале - для учебного примера точности достаточно

    QString str = inputEdit->text();

    // toDouble пытается распарсить строку
    a = static_cast<float>(str.toDouble(&Ok));

    if (Ok)
    {
        r = a * a;
        str.setNum(r);
        outputEdit->setText(str);

        // Блокируем поле ввода - нельзя менять данные после расчёта.
        inputEdit->setEnabled(false);

        outputLabel->setVisible(true);
        outputEdit->setVisible(true);

        // setDefault(true) перенаправляет Enter на эту кнопку -
        // после расчёта Enter = "Следующее"
        nextButton->setDefault(true);
        nextButton->setEnabled(true);
        nextButton->setFocus();
    }
    else if (!str.isEmpty())
    {
        // Проверка isEmpty() нужна: при первом запуске поле пустое,
        // не нужно ругаться на пользователя, который ещё ничего не вводил.
        // Ошибку показываем только если что-то ввели, но это что-то - не число.
        QMessageBox msgBox(
            QMessageBox::Information,
            codec->toUnicode("Возведение в квадрат."),
            codec->toUnicode("Введено неверное значение."),
            QMessageBox::Ok);
        // exec() - блокирующий вызов: ждём, пока пользователь закроет диалог,
        // и только потом продолжаем выполнение. В отличие от show(), который неблокирующий.
        msgBox.exec();
    }
}
