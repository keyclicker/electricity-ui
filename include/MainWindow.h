#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <Solver.hpp>
#include <EObjectType.hpp>

#include <memory>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

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
		void startSimulation();
		void stopSimulation();
		void save(std::ostream&);
		void load(std::istream&);
		void save(QString);
		void load(QString);
		void clearScene();
		void resetHistory();

	private slots:
		void newFile();
		void loadFromFile();
		void saveFile();
		void saveToFile();
		void commit();
		void undo();
		void redo();

	private:
		Ui::MainWindow* ui;
		QGraphicsScene* mScene;
		std::unique_ptr<Solver> mSolver;
		EObjectType mCreateObject;
		QString mFileName;

	//for undo/redo: saved schemes, the shown one
		std::vector<std::string> mHistory;
		std::size_t mCurrent;
};

#endif // MAINWINDOW_H
