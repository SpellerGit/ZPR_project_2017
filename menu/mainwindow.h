#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game/gamemanager.h"
#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleButton();
    void handleSelectMap();

private:
    std::unique_ptr<game::GameManager> mngr;
    std::shared_ptr<game::GameData> gamedata;
    Ui::MainWindow *ui;
    QPushButton *button1;
};

#endif // MAINWINDOW_H
