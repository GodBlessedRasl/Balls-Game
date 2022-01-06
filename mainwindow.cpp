#include "mainwindow.h"
#include<vector>
#include<utility>
#include<queue>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(800, 550);
    pole = new QGridLayout(this);
    for(int i=0;i<10;++i){
        for(int j=0;j<10;++j){
            buttons[i][j] = new Button;
            buttons[i][j]->setFixedSize(50, 50);
            buttons[i][j]->setIconSize(QSize(50,50));
            buttons[i][j]->x = i;
            buttons[i][j]->y = j;
            buttons[i][j]->type = 0;
            pole->addWidget(buttons[i][j], i, j, 1, 1);
            connect(buttons[i][j], SIGNAL(clicked(bool)), this, SLOT(proverka()));
        }
    }
    menu = new QGridLayout(this);
    menuWidg = new QWidget;
    menuWidg->setLayout(menu);
    menuWidg->setStyleSheet("background-color: purple");
    restart = new QVBoxLayout(this);
    von = new Button;
    von->setFixedSize(200, 50);
    von->setStyleSheet("background-color: white");
    von->setText("QUIT");
    restart->addWidget(von);
    menu->addLayout(restart,1,1);
    connect(von, SIGNAL(clicked(bool)), this, SLOT(pos_restart()));



    mainLay = new QGridLayout(this);
    mainLay->addLayout(pole, 0, 0, 1, 1);
    score_name = new QLabel(this);
    score = new QLabel(this);
    score->setStyleSheet("background-color: white;");
    score_name->setStyleSheet("background-color: white;");
    score_name->setText("              CURRENT SCORE");
    score->setText(QString ::number(res));
    pravo = new QVBoxLayout(this);
    mainLay->addLayout(pravo, 0, 1, 1, 1);

    snova = new Button;
    snova->setFixedSize(200, 50);
    snova->setText("RESTART");
    snova->setStyleSheet("background-color: yellow");
    pravo->addWidget(snova);
    connect(snova, SIGNAL(clicked(bool)), this, SLOT(pos_restart()));

    butt = new Button;
    butt->setFixedSize(200,50);
    butt->setText("BACK TO MENU");
    exit = new QVBoxLayout(this);
    exit->addWidget(butt);
    predict = new QHBoxLayout(this);
    ball_1 = new Button;
    ball_2 = new Button;
    ball_3 = new Button;
    ball_1->setFixedSize(50,50);
    ball_2->setFixedSize(50,50);
    ball_3->setFixedSize(50,50);
    predict->addWidget(ball_1);
    predict->addWidget(ball_2);
    predict->addWidget(ball_3);
    pravo->addWidget(score_name);
    pravo->addWidget(score);
    score_name->setFixedSize(200,50);
    score->setFixedSize(200,50);

    hvatit = new QHBoxLayout(this);
    name_hod = new QLabel(this);
    name_hod->setText("        TURNS :");
    col_hod = new QLabel(this);
    col_hod->setText(QString ::number(hod));
    hvatit->addWidget(name_hod);
    hvatit->addWidget(col_hod);
    pravo->addLayout(hvatit);
    name_hod->setFixedSize(100, 50);
    col_hod->setFixedSize(100, 50);
    name_hod->setStyleSheet("background-color: white");
    col_hod->setStyleSheet("background-color: white");

    bomb = new QLabel(this);
    bomb->setStyleSheet("background-color: green");
    bomb->setText("BOMB IS NOT READY YET");
    bomb_type = 0;
    bomb->setFixedSize(200,30);
    pravo->addWidget(bomb);

    pravo->addLayout(predict);
    pravo->addLayout(exit);
    //mainLay->addLayout(score_tab, 1, 1, 1, 1);
    //mainLay->addLayout(ss, 0, 1, 1, 1);


    connect(butt, SIGNAL(clicked(bool)), this, SLOT(quit()) );
    mainWidg = new QWidget;
    mainWidg->setLayout(mainLay);
    mainWidg->setStyleSheet("background-color: purple");
    setCentralWidget(mainWidg);
    start_rand();
    random_ball();
}

MainWindow::~MainWindow()
{

}

void MainWindow :: quit(){
    setCentralWidget(menuWidg);
    setFixedSize(800, 550);
}

void MainWindow ::showw(){
    if(curr < path.size()){
        if(buttons[path[0].first][path[0].second]->type == 1){
            buttons[path[curr].first][path[curr].second]->setIcon(QIcon("/home/rasull/game/Red.png1"));
        } else if(buttons[path[0].first][path[0].second]->type == 2){
            buttons[path[curr].first][path[curr].second]->setIcon(QIcon("/home/rasull/game/Blue.png2"));
        } else if(buttons[path[0].first][path[0].second]->type == 3){
            buttons[path[curr].first][path[curr].second]->setIcon(QIcon("/home/rasull/game/Purple.png3"));
        } else if(buttons[path[0].first][path[0].second]->type == 4){
            buttons[path[curr].first][path[curr].second]->setIcon(QIcon("/home/rasull/game/Green.png4"));
        } else if(buttons[path[0].first][path[0].second]->type == 5){
            buttons[path[curr].first][path[curr].second]->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
        } else if(buttons[path[0].first][path[0].second]->type == 6){
            buttons[path[curr].first][path[curr].second]->setIcon(QIcon("/home/rasull/game/Orange.png6"));
        }
        buttons[path[curr - 1].first][path[curr - 1].second]->setIcon(QIcon());
        if(curr == path.size() - 1){
            buttons[path[curr].first][path[curr].second]->type = buttons[path[0].first][path[0].second]->type;
            buttons[path[0].first][path[0].second]->type = 0;
        }
        ++curr;
    } else{
        kon = 1;
        ratata();
    }
    return;
}

void MainWindow :: ratata(){
    if(kon){
        timer->stop();
    }
    if((kon) && !vanish(bx, by)){
        random_ball();
    }
    ++hod;
    if(hod % 20 == 0 && hod!= 0){
        bomb->setText("BOMB IS READY TO USE");
        bomb->setStyleSheet("background-color : yellow");
        bomb_type = 1;
    }
    if(bomb_type == 2){
        if(exp == 0){
            ++exp;
        } else if(exp == 1){
            ++exp;
        } else{
            scor = 0;
            for(int i =0;i<10;++i){
                if(buttons[i][ty]->type >=1 && buttons[i][ty]->type<=6){
                    ++scor;
                }
                buttons[i][ty]->setIcon(QIcon());
                buttons[i][ty]->type = 0;
            }
            for(int j = 0;j < 10; ++j){
                if(buttons[tx][j]->type >=1 && buttons[tx][j]->type<=6){
                    ++scor;
                }
                buttons[tx][j]->setIcon(QIcon());
                buttons[tx][j]->type = 0;
            }
            res+=scor*10;
            col_balls-=scor;
            bomb_type = 0;
            score->setText(QString ::number(res));
            bomb->setText("BOMB IS NOT READY YET");
            bomb->setStyleSheet("background-color : green");
            exp = 0;
        }
    }
    col_hod->setText(QString ::number(hod));
    return;

if(col_balls >= 100){
          bomb->setText("GAME OVER");
   butt->setStyleSheet("background-color: yellow");
}
}

void MainWindow ::start_rand(){
    std ::srand(unsigned(std::time(0)));
    f = std ::rand() % 6 + 1;
    s = std ::rand() % 6 + 1;
    t = std ::rand() % 6 + 1;
    ball_1->type = f;
    ball_2->type = s;
    ball_3->type = t;
}

void MainWindow ::future(){
    if(col_balls >= 100){
           bomb->setText("GAME OVER");
           butt->setStyleSheet("background-color: yellow");
       }
     std ::srand(unsigned(std::time(0)));
     int a = std ::rand() % 6;
     int b = std ::rand() % 6;
     int c = std ::rand() % 6;
     ++a,++b,++c;
     if(a == 1){
         ball_1->type = 1;
         ball_1->setIcon(QIcon("/home/rasull/game/Red.png1"));
         ball_1->setIconSize(QSize(50,50));
     } else if(a == 2){
         ball_1->type = 2;
         ball_1->setIcon(QIcon("/home/rasull/game/Blue.png2"));
         ball_1->setIconSize(QSize(50,50));
     } else if(a == 3){
         ball_1->type = 3;
         ball_1->setIcon(QIcon("/home/rasull/game/Purple.png3"));
         ball_1->setIconSize(QSize(50,50));
     } else if(a == 4){
         ball_1->type = 4;
         ball_1->setIcon(QIcon("/home/rasull/game/Green.png4"));
         ball_1->setIconSize(QSize(50,50));
     } else if(a == 5){
         ball_1->type = 5;
         ball_1->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
         ball_1->setIconSize(QSize(50,50));
     } else {
         ball_1->type = 6;
         ball_1->setIcon(QIcon("/home/rasull/game/Orange.png6"));
         ball_1->setIconSize(QSize(50,50));
     }

     if(b == 1){
         ball_2->type = 1;
         ball_2->setIcon(QIcon("/home/rasull/game/Red.png1"));
         ball_2->setIconSize(QSize(50,50));
     } else if(b == 2){
         ball_2->type = 2;
         ball_2->setIcon(QIcon("/home/rasull/game/Blue.png2"));
         ball_2->setIconSize(QSize(50,50));
     } else if(b == 3){
         ball_2->type = 3;
         ball_2->setIcon(QIcon("/home/rasull/game/Purple.png3"));
         ball_2->setIconSize(QSize(50,50));
     } else if(b == 4){
         ball_2->type = 4;
         ball_2->setIcon(QIcon("/home/rasull/game/Green.png4"));
         ball_2->setIconSize(QSize(50,50));
     } else if(b == 5){
         ball_2->type = 5;
         ball_2->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
         ball_2->setIconSize(QSize(50,50));
     } else {
         ball_2->type = 6;
         ball_2->setIcon(QIcon("/home/rasull/game/Orange.png6"));
         ball_2->setIconSize(QSize(50,50));
     }

     if(c == 1){
         ball_3->type = 1;
         ball_3->setIcon(QIcon("/home/rasull/game/Red.png1"));
         ball_3->setIconSize(QSize(50,50));
     } else if(c == 2){
         ball_3->type = 2;
         ball_3->setIcon(QIcon("/home/rasull/game/Blue.png2"));
         ball_3->setIconSize(QSize(50,50));
     } else if(c == 3){
         ball_3->type = 3;
         ball_3->setIcon(QIcon("/home/rasull/game/Purple.png3"));
         ball_3->setIconSize(QSize(50,50));
     } else if(c == 4){
         ball_3->type = 4;
         ball_3->setIcon(QIcon("/home/rasull/game/Green.png4"));
         ball_3->setIconSize(QSize(50,50));
     } else if(c == 5){
         ball_3->type = 5;
         ball_3->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
         ball_3->setIconSize(QSize(50,50));
     } else {
         ball_3->type = 6;
         ball_3->setIcon(QIcon("/home/rasull/game/Orange.png6"));
         ball_3->setIconSize(QSize(50,50));
     }
}

void MainWindow::random_ball(){
    if(col_balls >= 100){
           bomb->setText("GAME OVER");
           butt->setStyleSheet("background-color: yellow");
       }
    std ::srand(unsigned(std::time(0)));
    ready = 0;
    x1 = std ::rand() % 10;
    y1 = std ::rand() % 10;
    if(col_balls <= 99){
        while(buttons[x1][y1]->type != 0){
            x1 = std ::rand() % 10;
            y1 = std ::rand() % 10;
        }
        if(ball_1->type == 1 && buttons[x1][y1]->type == 0){
            buttons[x1][y1]->setIcon(QIcon("/home/rasull/game/Red.png1"));
            buttons[x1][y1]->setIconSize(QSize(50,50));
            buttons[x1][y1]->type = 1;
        } else if(ball_1->type == 2 && buttons[x1][y1]->type == 0){
            buttons[x1][y1]->setIcon(QIcon("/home/rasull/game/Blue.png2"));
            buttons[x1][y1]->setIconSize(QSize(50,50));
            buttons[x1][y1]->type = 2;
        } else if(ball_1->type == 3 && buttons[x1][y1]->type == 0){
            buttons[x1][y1]->setIcon(QIcon("/home/rasull/game/Purple.png3"));
            buttons[x1][y1]->setIconSize(QSize(50,50));
            buttons[x1][y1]->type = 3;
        } else if(ball_1->type == 4 && buttons[x1][y1]->type == 0){
            buttons[x1][y1]->setIcon(QIcon("/home/rasull/game/Green.png4"));
            buttons[x1][y1]->setIconSize(QSize(50,50));
            buttons[x1][y1]->type = 4;
        } else if(ball_1->type == 5 && buttons[x1][y1]->type == 0){
            buttons[x1][y1]->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
            buttons[x1][y1]->setIconSize(QSize(50,50));
            buttons[x1][y1]->type = 5;
        } else if(buttons[x1][y1]->type == 0){
            buttons[x1][y1]->setIcon(QIcon("/home/rasull/game/Orange.png6"));
            buttons[x1][y1]->setIconSize(QSize(50,50));
            buttons[x1][y1]->type = 6;
        }
        ++col_balls;
        ++ready;
    }
    if(col_balls <=99){
    x2 = std ::rand() % 10;
    y2 = std ::rand() % 10;
    while(buttons[x2][y2]->type != 0){
        x2 = std ::rand() % 10;
        y2 = std ::rand() % 10;
    }
    if(ball_2->type == 1 && buttons[x2][y2]->type == 0){
        buttons[x2][y2]->setIcon(QIcon("/home/rasull/game/Red.png1"));
        buttons[x2][y2]->setIconSize(QSize(50,50));
        buttons[x2][y2]->type = 1;
    } else if(ball_2->type == 2 && buttons[x2][y2]->type == 0){
        buttons[x2][y2]->setIcon(QIcon("/home/rasull/game/Blue.png2"));
        buttons[x2][y2]->setIconSize(QSize(50,50));
        buttons[x2][y2]->type = 2;
    } else if(ball_2->type == 3 && buttons[x2][y2]->type == 0){
        buttons[x2][y2]->setIcon(QIcon("/home/rasull/game/Purple.png3"));
        buttons[x2][y2]->setIconSize(QSize(50,50));
        buttons[x2][y2]->type = 3;
    } else if(ball_2->type == 4 && buttons[x2][y2]->type == 0){
        buttons[x2][y2]->setIcon(QIcon("/home/rasull/game/Green.png4"));
        buttons[x2][y2]->setIconSize(QSize(50,50));
        buttons[x2][y2]->type = 4;
    } else if(ball_2->type == 5 && buttons[x2][y2]->type == 0){
        buttons[x2][y2]->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
        buttons[x2][y2]->setIconSize(QSize(50,50));
        buttons[x2][y2]->type = 5;
    } else if (buttons[x2][y2]->type == 0){
        buttons[x2][y2]->setIcon(QIcon("/home/rasull/game/Orange.png6"));
        buttons[x2][y2]->setIconSize(QSize(50,50));
        buttons[x2][y2]->type = 6;
    }
    ++col_balls;
    ++ready;
    }
    if(col_balls <= 99){
    x3 = std ::rand() % 10;
    y3 = std ::rand() % 10;
    while( buttons[x3][y3]->type != 0){
        x3 = std ::rand() % 10;
        y3 = std ::rand() % 10;
    }
    if(ball_3->type == 1 && buttons[x3][y3]->type == 0){
        buttons[x3][y3]->setIcon(QIcon("/home/rasull/game/Red.png1"));
        buttons[x3][y3]->setIconSize(QSize(50,50));
        buttons[x3][y3]->type = 1;
    } else if(ball_3->type == 2 && buttons[x3][y3]->type == 0){
        buttons[x3][y3]->setIcon(QIcon("/home/rasull/game/Blue.png2"));
        buttons[x3][y3]->setIconSize(QSize(50,50));
        buttons[x3][y3]->type = 2;
    } else if(ball_3->type == 3 && buttons[x3][y3]->type == 0){
        buttons[x3][y3]->setIcon(QIcon("/home/rasull/game/Purple.png3"));
        buttons[x3][y3]->setIconSize(QSize(50,50));
        buttons[x3][y3]->type = 3;
    } else if(ball_3->type == 4 && buttons[x3][y3]->type == 0){
        buttons[x3][y3]->setIcon(QIcon("/home/rasull/game/Green.png4"));
        buttons[x3][y3]->setIconSize(QSize(50,50));
        buttons[x3][y3]->type = 4;
    } else if(ball_3->type == 5 && buttons[x3][y3]->type == 0){
        buttons[x3][y3]->setIcon(QIcon("/home/rasull/game/Yellow.png5"));
        buttons[x3][y3]->setIconSize(QSize(50,50));
        buttons[x3][y3]->type = 5;
    } else if (buttons[x3][y3]->type == 0){
        buttons[x3][y3]->setIcon(QIcon("/home/rasull/game/Orange.png6"));
        buttons[x3][y3]->setIconSize(QSize(50,50));
        buttons[x3][y3]->type = 6;
    }
    ++col_balls;
    ++ready;
    }
    if(ready == 3){
        vanish(x1, y1);
        vanish(x2, y2);
        vanish(x3, y3);
    } else if(ready == 2){
        vanish(x1, y1);
        vanish(x2, y2);
    } else if(ready == 1){
        vanish(x1, y1);
    }
    future();
}

//void MainWindow ::sraka(){

//}

void MainWindow::pos_restart(){
    setCentralWidget(mainWidg);
    for(int i=0;i<10;++i){
        for(int j=0; j< 10;++j){
            buttons[i][j]->setIcon(QIcon());
            buttons[i][j]->type = 0;
        }
    }
    random_ball();
    res = 0;
    fig = 0;
    hod = 0;
    score->setText(QString ::number(res));
    col_hod->setText(QString ::number(hod));
}

bool MainWindow::lee(int ax, int ay, int bx, int by){
    path.clear();
    int grid[10][10];
    for(int i=0;i<10;++i){
        for(int j=0;j<10;++j){
            if(i == ax && j == ay){
                grid[i][j] = 0;
            } else if(buttons[i][j]->type != 0){
                grid[i][j] = -1;
            } else {
                grid[i][j] = -2;
            }
        }
    }
    bool pos = true, ans = false;
    int d = 0;
    bool shag_sdelan = true;
    while(pos && shag_sdelan){
        shag_sdelan = false;
        pos = false;
        bool cur = true;
        for(int i=0;i<10;++i){
            if(!cur){
                pos = 0;
                break;
            }
            for(int j =0;j<10;++j){
                if(grid[i][j] == d){
                    if((i+1<10) && grid[i+1][j]==-2){
                        grid[i+1][j] = d + 1;
                        pos = true;
                        shag_sdelan = true;
                        if(i+1 == bx && j == by){
                            cur = 0;
                            ans = 1;
                            break;
                        }
                    }
                    if((i - 1 >= 0) && grid[i - 1][j] == -2){
                        grid[i - 1][j] = d + 1;
                        pos = true;
                        shag_sdelan = true;
                        if(i-1 == bx && j == by){
                            cur = 0;
                            ans = 1;
                            break;
                        }
                    }
                    if((j+1<10) && grid[i][j+1] == -2){
                        grid[i][j+1] = d + 1;
                        pos = true;
                        shag_sdelan = true;
                        if(i == bx && j+1 == by){
                            cur = 0;
                            ans = 1;
                            break;
                        }
                    }
                    if((j - 1 >= 0) && grid[i][j-1]==-2){
                        grid[i][j-1] = d + 1;
                        pos = true;
                        shag_sdelan = true;
                        if(i == bx && j-1 == by){
                            cur = 0;
                            ans = 1;
                            break;
                        }
                    }
                }
            }
        }
        ++d;
    }

    if(!ans){
        return false;
    } else{
        int cur_i = bx, cur_j = by;
        path.push_back(std ::make_pair(bx, by));
        while(d != 0){
            if((cur_i+1 <10) && grid[cur_i+1][cur_j] == d - 1){
                ++cur_i;
                --d;
            } else if((cur_i-1 >=0) && grid[cur_i-1][cur_j] == d - 1){
                --cur_i;
                --d;
            } else if((cur_j + 1 <10) && grid[cur_i][cur_j + 1] == d - 1){
                ++cur_j;
                --d;
            } else{
                --cur_j;
                --d;
            }
            path.push_back(std ::make_pair(cur_i, cur_j));
        }
       // path.push_back(std ::make_pair(ax, ay));
    }
    std ::reverse(path.begin(), path.end());
    return true;
}

bool MainWindow ::vanish(int bx, int by){
    int colx = 0, coly = 0, diagl =0, diagr = 0;
    int cur = buttons[bx][by]->type;
    // if-аем строки, столбцы и диагонали
    for(int i = bx; i < 10; ++i){
        if(buttons[i][by]->type != cur){
            break;
        } else {
           ++colx;
        }
    }

    for(int i = bx - 1; i >= 0; --i){
        if(buttons[i][by]->type != cur){
            break;
        } else {
           ++colx;
        }
    }

    for(int i = by; i < 10; ++i){
        if(buttons[bx][i]->type != cur){
            break;
        } else {
           ++coly;
        }
    }

    for(int i = by - 1; i >= 0; --i){
        if(buttons[bx][i]->type != cur){
            break;
        } else {
           ++coly;
        }
    }

    for(int i = 0; i < 10; ++i){
        if(bx + i == 10 || by - i == -1){
            break;
        } else if(buttons[bx + i][by - i]->type != cur){
            break;
        } else {
           ++diagr;
        }
    }

    for(int i = 1; i < 10; ++i){
        if(bx - i == -1 || by + i == 10){
            break;
        } else if(buttons[bx - i][by + i]->type != cur){
            break;
        } else {
           ++diagr;
        }
    }

    for(int i = 0; i < 10; ++i){
        if(bx - i == -1 || by - i == -1){
            break;
        } else if(buttons[bx - i][by - i]->type != cur){
            break;
        } else {
           ++diagl;
        }
    }

    for(int i = 1; i < 10; ++i){
        if(bx + i == 10 || by + i == 10){
            break;
        } else if(buttons[bx + i][by + i]->type != cur){
            break;
        } else {
           ++diagl;
        }
    }
    bool ans =false;

    if(colx >=5){
        ans = 1;
        for(int i = bx + 1; i < 10; ++i){
            if(buttons[i][by]->type != cur){
                break;
            } else {
               buttons[i][by]->setIcon(QIcon());
               ++scor;
               buttons[i][by]->type = 0;
            }
        }

        for(int i = bx - 1; i >= 0; --i){
            if(buttons[i][by]->type != cur){
                break;
            } else {
                buttons[i][by]->setIcon(QIcon());
                ++scor;
                buttons[i][by]->type = 0;
            }
        }
    }

    if(coly >= 5){
        ans = 1;
        for(int i = by + 1; i < 10; ++i){
            if(buttons[bx][i]->type != cur){
                break;
            } else {
                buttons[bx][i]->setIcon(QIcon());
                ++scor;
                buttons[bx][i]->type = 0;
            }
        }

        for(int i = by - 1; i >= 0; --i){
            if(buttons[bx][i]->type != cur){
                break;
            } else {
                buttons[bx][i]->setIcon(QIcon());
                ++scor;
                buttons[bx][i]->type = 0;
            }
        }
    }

    if(diagr >= 5){
        ans = 1;
        for(int i = 1; i < 10; ++i){
            if(bx + i == 10 || by - i == -1){
                break;
            } else if(buttons[bx + i][by - i]->type != cur){
                break;
            } else {
                buttons[bx + i][by - i]->setIcon(QIcon());
                ++scor;
                buttons[bx + i][by - i]->type = 0;
            }
        }

        for(int i = 1; i < 10; ++i){
            if(bx - i == -1 || by + i == 10){
                break;
            } else if(buttons[bx - i][by + i]->type != cur){
                break;
            } else {
                buttons[bx - i][by + i]->setIcon(QIcon());
                ++scor;
                buttons[bx - i][by + i]->type = 0;
            }
        }
    }

    if(diagl >= 5){
        ans = 1;
        for(int i = 1; i < 10; ++i){
            if(bx - i == -1 || by - i == -1){
                break;
            } else if(buttons[bx - i][by - i]->type != cur){
                break;
            } else {
                buttons[bx - i][by - i]->setIcon(QIcon());
                ++scor;
                buttons[bx - i][by - i]->type = 0;
            }
        }

        for(int i = 1; i < 10; ++i){
            if(bx + i == 10 || by + i == 10){
                break;
            } else if(buttons[bx + i][by + i]->type != cur){
                break;
            } else {
                buttons[bx + i][by + i]->setIcon(QIcon());
                ++scor;
                buttons[bx + i][by + i]->type = 0;
            }
        }
    }

    if(ans){
        buttons[bx][by]->setIcon(QIcon());
        ++scor;
        col_balls-=scor;
        buttons[bx][by]->type = 0;
        res+= scor * 10;
        score->setText(QString ::number(res));
        qDebug() << "d" << colx << coly << diagr << diagl;
        return 1;

    } else {
        return 0;
    }
}

void MainWindow ::proverka(){
    auto now = (Button*) sender();
    if(now->type == 7){
        return;
    }
    if(bomb_type == 1){
        tx = now->x;
        ty = now->y;
        buttons[tx][ty]->setIcon(QIcon("/home/rasull/game/BOMB.png"));
        bomb->setText("WAITING FOR EXPLODE");
        bomb->setStyleSheet("background-color : red");
        buttons[tx][ty]->type = 7;
        exp = 0;
        bomb_type = 2;
    }

    if (fig == 0){
        if (now->type == 0 && now->type !=7) {
            return;
        }
        fig = 1;
        ax = now->x;
        ay = now->y;
        return;
    } else if (fig == 1 && now->type !=7){
        if(now->type >=1){
            fig = 0;
            return;
        }
        fig = 0;
        bx = now->x;
        by = now->y;
        if(lee(ax,ay,bx,by)){
            curr = 1;
            kon = 0;
            timer = new QTimer;
            connect(timer, SIGNAL(timeout()), this, SLOT(showw()));
            timer->start(100);
            if(kon){
                timer->stop();
            }
            if((kon) && !vanish(bx, by)){
                random_ball();
            }
            ++hod;
            if(hod % 20 == 0 && hod!= 0){
                bomb->setText("BOMB IS READY TO USE");
                bomb->setStyleSheet("background-color : yellow");
                bomb_type = 1;
            }
            if(bomb_type == 2){
                if(exp == 0){
                    ++exp;
                } else if(exp == 1){
                    ++exp;
                } else{
                    scor = 0;
                    for(int i =0;i<10;++i){
                        if(buttons[i][ty]->type >=1 && buttons[i][ty]->type<=6){
                            ++scor;
                        }
                        buttons[i][ty]->setIcon(QIcon());
                        buttons[i][ty]->type = 0;
                    }
                    for(int j = 0;j < 10; ++j){
                        if(buttons[tx][j]->type >=1 && buttons[tx][j]->type<=6){
                            ++scor;
                        }
                        buttons[tx][j]->setIcon(QIcon());
                        buttons[tx][j]->type = 0;
                    }
                    res+=scor*10;
                    col_balls-=scor;
                    bomb_type = 0;
                    score->setText(QString ::number(res));
                    bomb->setText("BOMB IS NOT READY YET");
                    bomb->setStyleSheet("background-color : green");
                    exp = 0;
                }
            }
            col_hod->setText(QString ::number(hod));
        } else {
            return;
        }

    }
    if(col_balls >= 100){
                  bomb->setText("GAME OVER");
           butt->setStyleSheet("background-color: yellow");
    }
        }
