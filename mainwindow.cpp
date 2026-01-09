#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    firstNumber(0),
    waitingForSecondNumber(false)
{
    setWindowTitle("Calculator");
    setFixedSize(320, 520);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background:#020617;");

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    display = new QLineEdit("0");
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);
    display->setFixedHeight(90);
    display->setStyleSheet(
        "QLineEdit {"
        "background:#0f172a;"
        "color:#e5e7eb;"
        "font-size:36px;"
        "border-radius:16px;"
        "padding:16px;"
        "}"
        );
    mainLayout->addWidget(display);

    grid = new QGridLayout();
    grid->setSpacing(10);

    QString buttons[5][4] = {
        {"AC", "%", "+/-", "÷"},
        {"7", "8", "9", "×"},
        {"4", "5", "6", "−"},
        {"1", "2", "3", "+"},
        {"0", ".", "=", ""}
    };

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 4; c++) {

            if (buttons[r][c].isEmpty()) continue;

            QString text = buttons[r][c];
            QPushButton *btn;

            if (text == "+" || text == "−" || text == "×" || text == "÷" || text == "=")
                btn = createButton(text, "operator");
            else if (text == "AC" || text == "%" || text == "+/-")
                btn = createButton(text, "function");
            else
                btn = createButton(text, "number");

            if (text == "0") {
                btn->setFixedSize(150, 70);
                grid->addWidget(btn, r, c, 1, 2);
                c++;
            } else {
                btn->setFixedSize(70, 70);
                grid->addWidget(btn, r, c);
            }
        }
    }

    mainLayout->addLayout(grid);
}

MainWindow::~MainWindow() {}

QPushButton* MainWindow::createButton(const QString &text, const QString &type)
{
    QPushButton *btn = new QPushButton(text);

    if (type == "operator") {
        btn->setStyleSheet(
            "QPushButton { background:#f97316; color:white; font-size:22px; border-radius:35px; }"
            "QPushButton:pressed { background:#ea580c; }"
            );
    }
    else if (type == "function") {
        btn->setStyleSheet(
            "QPushButton { background:#475569; color:white; font-size:20px; border-radius:35px; }"
            "QPushButton:pressed { background:#334155; }"
            );
    }
    else {
        btn->setStyleSheet(
            "QPushButton { background:#1e293b; color:#e5e7eb; font-size:20px; border-radius:35px; }"
            "QPushButton:pressed { background:#0f172a; }"
            );
    }

    connect(btn, &QPushButton::clicked, this, &MainWindow::buttonClicked);
    return btn;
}

void MainWindow::buttonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString text = btn->text();

    if (text == "AC") {
        display->setText("0");
        firstNumber = 0;
        currentOperator.clear();
        waitingForSecondNumber = false;
        return;
    }

    if (text == "+" || text == "−" || text == "×" || text == "÷") {
        firstNumber = display->text().toDouble();
        currentOperator = text;
        waitingForSecondNumber = true;
        return;
    }

    if (text == "=") {
        double secondNumber = display->text().toDouble();
        double result = 0;

        if (currentOperator == "+") result = firstNumber + secondNumber;
        else if (currentOperator == "−") result = firstNumber - secondNumber;
        else if (currentOperator == "×") result = firstNumber * secondNumber;
        else if (currentOperator == "÷") result = secondNumber != 0 ? firstNumber / secondNumber : 0;

        display->setText(QString::number(result));
        waitingForSecondNumber = false;
        return;
    }

    // Numbers & dot
    if (display->text() == "0" || waitingForSecondNumber) {
        display->setText(text);
        waitingForSecondNumber = false;
    } else {
        display->setText(display->text() + text);
    }
}

