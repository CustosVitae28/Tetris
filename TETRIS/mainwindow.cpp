#include "mainwindow.h"
#include "logic.h"

#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include "piece.h"
#include "logic.h"
#include <QMessageBox>
#include <QFont>
#include <QString>
#include <QColor>
#include <QColorDialog>
#include <QDialog>



QTimer *timer;
Logic* boardlogic;
  int  score=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{
    setWindowIcon(QIcon(":/pics/Icon1.png"));
    this->setWindowTitle("CosmoTetris");
    resize(900,600);
    speed = 500;
    first = new QPushButton(this);
    first->setText("Start  Game");
    first->setGeometry(600,100,150,35);
    first->setStyleSheet("color: green");
    second = new QPushButton(this);
    second->setText("Pause Game");
    second->setGeometry(600,150,150,35);
    second->setStyleSheet("color: green");
    third = new QPushButton(this);
    third->setText("Stop Game");
    third->setGeometry(600,200,150,35);
    third->setStyleSheet("color: green");
    QFont key_font("Arial", 15);
    scoreLbl = new QLabel("<H1><font color='#0f0f00'>""</H1>",this);
    scoreLbl->setFont(key_font);
    scoreLbl->setGeometry(705,55,50,30);
    scoreLbl->setText("0");
    scoreLbl->setStyleSheet("color: white");
    QFont text_font("Arial",15);
    lbl=new QLabel("Score:",this);
    lbl->setStyleSheet("color: white");
    lbl->setFont(text_font);
    lbl->setGeometry(600,50,80,35);
    lbl1=new QLabel("Preview:", this);
    lbl1->setStyleSheet("color: white");
    lbl1->setFont(text_font);
    lbl1->setGeometry(600, 250, 80, 35);
    this->grabKeyboard();
    speed = 500;
    boardlogic = new Logic(this);
    timer  = new QTimer(this);
    color1 = Qt::white;
    QObject::connect(first, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    QObject::connect(second, SIGNAL(clicked()), this, SLOT(on_pauseButton_clicked()));
    QObject::connect(third, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tmr_game()));
    start=false;
    stop=false;
}

void MainWindow::paintEvent(QPaintEvent *)
{  
    QPainter painter(this);
    painter.drawPixmap(0,0,1900,600,QPixmap(":/pics/Wall2"));

    painter.drawRect(690,55,50,31);

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
        {
            painter.setPen(color2);
            switch(boardlogic->Board[i][j])
            {
                case 0:
                    painter.setBrush(color1);
                    break;
                case 1:
                    painter.setBrush(QBrush("#DF013A"));
                    break;
                case 2:
                    painter.setBrush(QBrush("#04B404"));
                    break;
                case 3:
                    painter.setBrush(QBrush("#5858FA"));
                    break;
                case 4:
                    painter.setBrush(QBrush("#FE642E"));
                    break;
                case 5:
                    painter.setBrush(QBrush("#D7DF01"));
                    break;
                case 6:
                    painter.setBrush(QBrush("#ACFA58"));
                    break;
                case 7:
                    painter.setBrush(QBrush("#F781D8"));
                    break;
            }

            painter.drawRect(j * 25 + 200, i * 25 + 30, 25, 25);

        }
    if (timer->isActive())
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                painter.setPen(QPen("#000000"));
                switch(boardlogic->CurrentPiece.PieceColor)
                {
                case 0:
                    painter.setBrush(QBrush("#9A2EFE"));
                    break;
                case 1:
                    painter.setBrush(QBrush("#DF013A"));
                    break;
                case 2:
                    painter.setBrush(QBrush("#04B404"));
                    break;
                case 3:
                    painter.setBrush(QBrush("#5858FA"));
                    break;
                case 4:
                    painter.setBrush(QBrush("#FE642E"));
                    break;
                case 5:
                    painter.setBrush(QBrush("#D7DF01"));
                    break;
                case 6:
                    painter.setBrush(QBrush("#ACFA58"));
                    break;
                case 7:
                    painter.setBrush(QBrush("#F781D8"));
                    break;
                }
                if (boardlogic->CurrentPiece.PieceArray[i][j])
                    painter.drawRect(200 + (boardlogic->CurrentPiece.X + j) * 25, 30 + (boardlogic->CurrentPiece.Y + i) * 25, 25, 25);

            }
    if(start)
        {
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                {
                    switch(boardlogic->NextPiece.PieceColor)
                    {
                        case 0:
                            painter.setBrush(color1);
                            break;
                        case 1:
                            painter.setBrush(QBrush("#DF013A"));
                            break;
                        case 2:
                            painter.setBrush(QBrush("#04B404"));
                            break;
                        case 3:
                            painter.setBrush(QBrush("#5858FA"));
                            break;
                        case 4:
                            painter.setBrush(QBrush("#FE642E"));
                            break;
                        case 5:
                            painter.setBrush(QBrush("#D7DF01"));
                            break;
                        case 6:
                            painter.setBrush(QBrush("#ACFA58"));
                            break;
                        case 7:
                            painter.setBrush(QBrush("#F781D8"));
                            break;
                    }
                    if(boardlogic->NextPiece.PieceArray[i][j])
                        painter.drawRect(650 + 20 * j, 300 + 20 * i, 20, 20);

                }
        }
    else if(stop)
        this->repaint();
    }


void MainWindow::on_startButton_clicked()
{
    start = true;
    if (!timer->isActive()) {
        if (boardlogic->dropping)
            timer->start(5);
        else
            timer->start(speed);
    }
}

void MainWindow::on_pauseButton_clicked()
{
    timer->stop();
}

void MainWindow::on_stopButton_clicked()
{
    stop=true;
    timer->stop();
    boardlogic = new Logic(this);
    scoreLbl->setText("0");
    score=0;
    speed = 500;
    this->repaint();
}

void MainWindow::board_color()
{

    QColor temp1;
    temp1=QColorDialog::getColor (Qt::white);
    if(temp1.isValid()){
        color1 = temp1;
    }
}

void MainWindow::line_color()
{

    QColor temp2;
    temp2=QColorDialog::getColor (Qt::black);
    if(temp2.isValid()){
        color2 = temp2;
    }
}

void MainWindow::tmr_game()
{
    boardlogic->DropPiece();
    //scoreLbl->setText("0"+QString::number(score));

    this->repaint();

}

void MainWindow::reset_speed()
{
    timer->setInterval(speed);
}

void MainWindow::increase_speed()
{
    speed *= 0.95;
    timer->setInterval(speed);
}

void MainWindow::game_over()
{
    timer->stop();
    QMessageBox * msg = new QMessageBox();
    msg->setWindowIcon(QIcon(":/pics/Icon1.png"));
    msg->setStyleSheet("background-color: white");
    msg->setText("Game over!\nScore: " + QString::number(score));
    msg->show();
    on_stopButton_clicked();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (timer->isActive()) {
        switch(e->key())
        {
        case Qt::Key_Left:
            if (!boardlogic->dropping)
                if (boardlogic->PieceCanGoLeft()) boardlogic->CurrentPiece.X--;
            break;
        case Qt::Key_Right:
            if (!boardlogic->dropping)
                if (boardlogic->PieceCanGoRight()) boardlogic->CurrentPiece.X++;
            break;
        case Qt::Key_Up:
            if (!boardlogic->dropping)
                if (boardlogic->PieceCanRotate(boardlogic->rot < 3 ? boardlogic->rot + 1 : 0))
                {
                    if (boardlogic->rot < 3)
                        boardlogic->rot++;
                    else boardlogic->rot = 0;
                    boardlogic->ReloadPiece();
                }

            break;
        case Qt::Key_Space:
            if (!boardlogic->dropping)
            {
                boardlogic->dropping = true;
                timer->setInterval(50);
            }
            break;
        }
        this->repaint();
    }
}
