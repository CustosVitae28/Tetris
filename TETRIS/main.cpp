#include "mainwindow.h"
#include <QApplication>
#include <QMenu>
#include <QMenuBar>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QMenuBar* mnuBar = new QMenuBar(&w);
        QMenu* file = new QMenu("&File");
        QMenu* tools = new QMenu("&Tools");
        QMenu* help = new QMenu("&CosmoHelp");
          file->addAction("New Game", &w, SLOT(start_new_game()), Qt::Key_F2);
          file->addAction("&Exit", &a, SLOT(quit()), Qt::ALT + Qt::Key_X);
          help->addAction("&About Qt", &a,SLOT(aboutQt()),Qt::CTRL + Qt::Key_Q);
          help->addAction("&About Game",&w,SLOT(slotfunc()));
          tools->addAction("Board Color", &w,SLOT(board_color()));
          tools->addAction("Line Color", &w,SLOT(line_color()));


          mnuBar->addMenu(file);
          mnuBar->addMenu(tools);
          mnuBar->addMenu(help);
          mnuBar->adjustSize();
          w.setFixedSize(1000, 600);
    w.show();

    return a.exec();
}
