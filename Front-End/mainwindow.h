#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include <QTimeLine>
#include <QKeyEvent>
#include <QtCore>
#include <QtGui>

#include "GObject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
    Ui::MainWindow *ui;
    QGraphicsScene *canvas;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*) override;
    void keyPressEvent(QKeyEvent*) override;	

public slots:
    void createResistor(bool val);

};

#endif // MAINWINDOW_H
