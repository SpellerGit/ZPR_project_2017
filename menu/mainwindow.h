#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game/gamemanager.h"
#include "menu/gamelobby.h"
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
    void handleNetwork();

private:
    std::unique_ptr<game::GameManager> mngr;
    std::shared_ptr<game::GameData> gamedata;
    std::unique_ptr<GameLobby> lobby;
    std::shared_ptr<network::Connection> connection;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
