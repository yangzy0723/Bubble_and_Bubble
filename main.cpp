#include <QApplication>
#include <QIcon>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("Q版泡泡堂");
  w.setWindowIcon(QIcon(":/image/image/icon.png"));
  w.show();
  return a.exec();
}
