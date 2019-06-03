#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



//    setWindowIcon(QIcon(":/../resources/appicon.ico"));
    winTaskbarButton = new QWinTaskbarButton(this);
    winTaskbarButton->setWindow(windowHandle());
//    winTaskbarButton->setOverlayIcon(QIcon(":/../resources/overlay.ico"));

    winTaskbarProgress = winTaskbarButton->progress();
    winTaskbarProgress->setVisible(true);



    maximumCount = 3600;

    winTaskbarProgress->setMinimum(0);
    winTaskbarProgress->setMaximum(maximumCount);



    //https://forum.qt.io/topic/9470/timer-stop-from-slot/2
    timer = new QTimer(this);
    showInitialTime();



    player = new QMediaPlayer(this);

    //create a path realtive to sound file
    QString link = QApplication::applicationDirPath() + "/alarm.mp3";
    player->setMedia(QUrl::fromLocalFile(link));



    player->setVolume(50);



    connect(timer, SIGNAL(timeout()), this, SLOT(actionSlotCronometru()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBarTimer()));



    ui->timeEdit->hide();

    counter = 0;

}




MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}





void MainWindow::showInitialTime()
{

    time.setHMS(00,00,00,0);
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






void MainWindow::updateProgressBar()
{
    if (ui->radioButtonCronometru->isChecked()){

        winTaskbarProgress->show();

        if(counter <= maximumCount)
        {
            counter++;
            winTaskbarProgress ->setValue(counter);
        }
        else
        {
            counter = 1;
            player->play();
        }
    }
    else if(ui->radioButtonTimer->isChecked()){

        winTaskbarProgress->show();

        if(counter<timeOnTimerStart)
        {
            counter++;
            winTaskbarProgress ->setValue(counter);
        }
        else
        {
            counter = 1;
            player->play();
        }
    }
}



void MainWindow::updateProgressBarTimer()
{
    winTaskbarProgress->show();
    if (counter < QTime(0,0).secsTo(time))
    {
        counter++;
        winTaskbarProgress ->setValue(counter);
    }
    else
    {
        counter = 1;
        player->play();
    }
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

    //linia asta este foarte importanta
    winTaskbarButton->setWindow(windowHandle());




    if (ui->radioButtonCronometru->isChecked())
    {

        timer->start(1000);
    }

    if (ui->radioButtonTimer->isChecked())
    {
        timer->start(1000);

        //https://stackoverflow.com/questions/31428987/how-to-read-current-time-in-qtimeedit-in-qt
        time = ui->timeEdit->time();
        QString text = time.toString ("hh:mm:ss");
        ui->lcdNumber->display (text);

        timeOnTimerStart = QTime(0,0,0).secsTo(time);
        winTaskbarProgress->setMaximum(timeOnTimerStart);
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
