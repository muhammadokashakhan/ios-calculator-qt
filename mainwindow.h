#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void buttonClicked();

private:
    QWidget *centralWidget;
    QLineEdit *display;
    QGridLayout *grid;

    QPushButton* createButton(const QString &text, const QString &type);

    double firstNumber;
    QString currentOperator;
    bool waitingForSecondNumber;
};

#endif // MAINWINDOW_H


