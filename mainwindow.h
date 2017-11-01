#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <scene.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget* = nullptr);
		~MainWindow();

	protected:
		void resizeEvent(QResizeEvent*) override;
		void keyPressEvent(QKeyEvent*) override;
		void mouseDoubleClickEvent(QMouseEvent*) override;

	private:
		void initGraphics();

	private:
		Ui::MainWindow* ui;
		GridScene* mScene;
};

#endif // MAINWINDOW_H
