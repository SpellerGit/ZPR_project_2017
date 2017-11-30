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
    bool eventFilter(QObject *target, QEvent *event);
    QGraphicsScene * scene;
    QImage image;
    QImage image2;
    QGraphicsPixmapItem * item;
    QGraphicsPixmapItem * item2;
    Ui::GameWindow *ui;
};
} // namespace game
#endif // GAMEWINDOW_H
