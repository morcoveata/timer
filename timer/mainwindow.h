#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void showInitialTime();
    void OnStartButton();
    QTimer *timer;
    QTime time;
    QTime t;
    int i;



    QMediaPlayer *player;


public slots:
    void actionSlotCronometru();





private slots:
    void on_pushButtonStop_clicked();
    void on_pushButtonStart_clicked();

    void on_pushButtonRestart_clicked();

    void on_radioButtonTimer_clicked();

    void on_radioButtonCronometru_clicked();

private:
    Ui::MainWindow *ui;
    int timerId;
};

#endif // MAINWINDOW_H
