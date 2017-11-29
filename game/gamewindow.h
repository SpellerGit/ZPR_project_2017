#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsPixmapItem>


namespace Ui {
class GameWindow;
}
namespace game {
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
   void handleExit();

private:
    QGraphicsPixmapItem * item;
    Ui::GameWindow *ui;
};
} // namespace game
#endif // GAMEWINDOW_H
