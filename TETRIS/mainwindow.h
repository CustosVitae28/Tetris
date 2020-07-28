#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <aboutgame.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void reset_speed();
    void increase_speed();
    void game_over();
    void setscore(int a){
        QString temp = QString::number(a);
        scoreLbl->setText(temp);
        scoreLbl->show();
    }
private slots:
    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void board_color();
    void line_color();

    void start_new_game()
    {
        if(!start)
            this->on_startButton_clicked();
        else {
            this->on_stopButton_clicked();
        this->on_startButton_clicked();}

    }
    void slotfunc(){
        game.resize(1100,600);
        game.show();
    }

private:
    QPushButton *first;
    QPushButton *second;
    QPushButton *third;
    QPushButton *choice;
    QLabel* scoreLbl;
    QLabel *lbl;
    QLabel *lbl1;
    QColor color1;
    QColor color2;
    void paintEvent(QPaintEvent*);
    int speed;
    about_game game;

    bool start;
    bool stop;
public slots:
    void tmr_game();
protected:
    void keyPressEvent(QKeyEvent *e);
    int mode;
};

#endif // MAINWINDOW_H
