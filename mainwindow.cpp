#include <mainwindow.h>
#include <ui_mainwindow.h>

#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QScreen>
#include <QtCore>

#include <box.hpp>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/images/eLogo.png"));
	mScene = new GridScene(this);
	initGraphics();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	ui->sideMenu->resize( ui->sideMenu->width(),
						  this->height() );
	qDebug() << "\n";
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	switch(event->key())
	{
		case Qt::Key_F11:
		{
			setWindowState(windowState() ^
				(Qt::WindowFullScreen | Qt::WindowActive) );
			break;
		}

		case Qt::Key_Escape:
		{
			ui->sideMenu->setVisible(
				!ui->sideMenu->isVisible() );
			break;
		}

		default:
			QMainWindow::keyPressEvent(event);
	}
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
	QGraphicsItem* box = new Box(":/images/icon.png");
	box->setPos(ui->graphicsView->mapToScene(event->pos()));
	mScene->addItem(box);
}

void MainWindow::initGraphics()
{
	QRect screen = QGuiApplication::primaryScreen()->geometry();
	qint32 height = screen.height(),
		   width = screen.width();

	mScene->setSceneRect(0, 0, width, height);
	ui->graphicsView->resize(width, height);
	ui->graphicsView->setScene(mScene);
	ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
