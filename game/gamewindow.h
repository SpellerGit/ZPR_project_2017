#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include "game/gamedata.h"
#include "network/connection.h"

namespace Ui {
class GameWindow;
}
namespace game {
/*Class with window where the game is playing*/
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    QGraphicsScene * getScenePointer() const;
    void setData(std::shared_ptr<GameData> gdata);

public slots:
   void updateDisplay();

signals:
   void sendUserAction(game::user_action a);

private slots:
   void handleExit();

private:
    void checkCollisions();
    void shoot(QGraphicsSceneMouseEvent* event,
               int playerNumber);
    bool eventFilter(QObject *target, QEvent *event);

    std::shared_ptr<network::Connection> connection;
    std::shared_ptr<GameData> gdata;
    QGraphicsScene * scene;
    Ui::GameWindow *ui;
};
} // namespace game
#endif // GAMEWINDOW_H
