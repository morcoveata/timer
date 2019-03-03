#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //https://forum.qt.io/topic/9470/timer-stop-from-slot/2
    timer = new QTimer(this);
    showInitialTime();



    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("g:/programare/timer_repo/timer/alarm.mp4"));
//    player->setMedia(QUrl::fromLocalFile(QFileInfo("alarm.mp4").absoluteFilePath()));
    player->setVolume(50);


    connect(timer, SIGNAL(timeout()), this, SLOT(actionSlotCronometru()));

    ui->timeEdit->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::showInitialTime()
{

    time.setHMS(00,00,00,0);
//    QString text = time.toString ("hh:mm:ss");
    QString text = time.toString (Qt::TextDate);

    ui->lcdNumber->display(text);

}



void MainWindow::actionSlotCronometru()
{


    if (ui->radioButtonCronometru->isChecked())
    {
        t = time.addSecs(1);
    }
    else
    {
        t = time.addSecs(-1);

        QTime timeCompare;

        //why set s to 1 ?
        timeCompare.setHMS(00,00,01,0);

        if (time == timeCompare)

        {

            timer->stop();
            player->play();

        }

    }
    time = t;

    QString text = t.toString ("hh:mm:ss");
    ui->lcdNumber->display (text);
}



void MainWindow::on_pushButtonStop_clicked()
{

    //https://forum.qt.io/topic/9470/timer-stop-from-slot/2
    timer->stop();

    ui->radioButtonCronometru->setEnabled(true);
    ui->radioButtonTimer->setEnabled(true);
    ui->timeEdit->setEnabled(true);
    ui->pushButtonRestart->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    player->stop();

    // resetare time settings la cronometru
    QTime time(0, 0, 0);
    ui->timeEdit->setTime(time);
}







void MainWindow::on_pushButtonStart_clicked()
{

    if (ui->radioButtonCronometru->isChecked())
    {
//        connect(timer, SIGNAL(timeout()), this, SLOT(actionSlot()));
        timer->start(1000);
    }

    if (ui->radioButtonTimer->isChecked())
    {
//        ui->timeEdit->hide();

        timer->start(1000);

        //https://stackoverflow.com/questions/31428987/how-to-read-current-time-in-qtimeedit-in-qt
        time = ui->timeEdit->time();
        QString text = time.toString ("hh:mm:ss");
        ui->lcdNumber->display (text);
    }


    ui->timeEdit->setEnabled(false);
    ui->radioButtonCronometru->setEnabled(false);
    ui->radioButtonTimer->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonRestart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
}






void MainWindow::on_pushButtonRestart_clicked()
{

    timer->stop();

    showInitialTime();
    ui->pushButtonRestart->setEnabled(false);
}






void MainWindow::on_radioButtonTimer_clicked()
{
    ui->timeEdit->show();
}





void MainWindow::on_radioButtonCronometru_clicked()
{
    ui->timeEdit->hide();
}
