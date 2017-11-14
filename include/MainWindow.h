#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <Solver.hpp>
#include <EObjectType.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected:
		void resizeEvent(QResizeEvent*) override;
		void keyPressEvent(QKeyEvent*) override;

	private:
		void initGraphics();
		void createElement();

	private:
		Ui::MainWindow* ui;
		QGraphicsScene* mScene;
		Solver* mSolver;
		EObjectType mCreateObject;
};

#endif // MAINWINDOW_H
