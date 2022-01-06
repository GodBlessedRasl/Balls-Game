#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QLayout>
#include <QMainWindow>
#include<QPushButton>
#include<QGridLayout>
#include<QLabel>
#include<QFont>
#include<QVBoxLayout>
#include<QDebug>
#include<QPair>
#include<QVariant>
#include<QString>
#include<QIcon>
#include<QPalette>
#include <time.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <QTimer>

class Button : public QPushButton
{
    Q_OBJECT
public:
    int x,y,type;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGridLayout *menu;
    QWidget *menuWidg;
    QVBoxLayout *exit;
    QVBoxLayout *restart;

    QVBoxLayout *buff;
    QGridLayout *mainLay;
    QWidget *mainWidg;
    QGridLayout *pole;
    QHBoxLayout *predict, *hvatit;
    QLabel *score, *score_name, *col_hod, *name_hod, *bomb;
    Button* buttons[10][10];
    Button* butt, *ball_1, *ball_2, *ball_3, *von, *snova;
    QVBoxLayout *pravo;
    void random_ball();
    std ::vector<std ::pair<int,int>>path;
    void build();
    int grid[10][10];
    int pathx[100];
    int pathy[100];
    int blya = 0;
    int gg = 0;
    int curr = 1;
    int scor = 0;
    bool kon = 0;
    int x1, y1, x2, y2, x3, y3, f, s, t;
    int ax,ay,bx,by,tx,ty;
    int bomb_type = 0, col_balls = 0, ready = 0;
    int res = 0, fig = 0, hod = 0, exp =0;
    bool lee(int ax, int ay, int bx, int by);
    bool vanish(int bx, int by);
    void future();
    void ff();
    void ratata();
    QTimer *timer;
public slots:
    void pos_restart();
    void proverka();
    void quit();
    void showw();
    void start_rand();
    //void pos_square();
};
#endif // MAINWINDOW_H
