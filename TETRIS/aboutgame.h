#ifndef ABOUTGAME_H
#define ABOUTGAME_H

#include <QPainter>
#include <QWidget>
#include <QPixmap>
#include <QKeyEvent>
#include <QIcon>

class about_game : public QWidget
{
    Q_OBJECT

public:
    explicit about_game()
    {
        setFixedSize(930, 600);
        setStyleSheet("background-color:white;");
        setWindowIcon(QIcon(":/pics/Icon2.jpg"));
        setWindowTitle("CosmoHelp");
        page_1 = new QPixmap(":/pics/Capture1.JPG");
        page_2 = new QPixmap(":/pics/Capture2.JPG");
        page_3 = new QPixmap(":/pics/Capture3.JPG");
        page_4 = new QPixmap(":/pics/Capture4.JPG");
        right = new QPixmap(":/pics/AjSlaq.PNG");
        left = new QPixmap(":/pics/DzaxSlaq.PNG");
        page = 1;
    }
protected:
    void paintEvent(QPaintEvent*){
        QPainter painter2;
        painter2.begin(this);
        painter2.setPen(Qt::black);
        QFont font=painter2.font() ;
        font.setPointSize(12);
        painter2.setFont(font);
        painter2.drawPixmap(450,550,50,30,*right);
        painter2.drawPixmap(300,550,50,30,*left);
        if(page == 1){
           painter2.drawPixmap(0,0,*page_1);
        }
        if(page == 2){
           painter2.drawPixmap(0,0,*page_2);
        }
        if(page == 3){
           painter2.drawPixmap(0,0,*page_3);
        }
        if(page == 4){
           painter2.drawPixmap(0,0,*page_4);
        }

        QRect rec(380,550,50,20);
        painter2.drawRect(rec);
        if(page == 1) temp = "  1 / 4";
        if(page == 2) temp = "  2 / 4";
        if(page == 3) temp = "  3 / 4";
        if(page == 4) temp = "  4 / 4";
        painter2.drawText(rec,temp);
        painter2.drawText(385,545,"Page");
        painter2.end();
    }


    void mousePressEvent(QMouseEvent *event){
        if(event->x() > 450 && event->x() < 500 && event->y() > 550 && event->y() < 570 && page < 4){
            page++;
            repaint();
        }
        if(event->x() > 300 && event->x() < 350 && event->y() > 550 && event->y() < 570 && page >1){
            page--;
            repaint();
        }
    }
private:
    int page;
    QPixmap* page_1;
    QPixmap* page_2;
    QPixmap* page_3;
    QPixmap* page_4;
    QPixmap* right;
    QPixmap* left;
    QString temp;

};




#endif // ABOUTGAME_H
