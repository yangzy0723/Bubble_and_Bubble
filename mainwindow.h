#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "gamescene.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QSoundEffect>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameScene *gameScene;

    QSoundEffect* background;
};
#endif  // MAINWINDOW_H_
