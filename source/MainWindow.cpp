#include <ui_mainwindow.h>
#include <MainWindow.h>

#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QScreen>

#include <QDebug>

#include <Resistor.hpp>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mCreateObject()
{
	ui->setupUi(this);
	setWindowIcon( QIcon(":/icons/icons/eLogo.png") );
	mScene = new QGraphicsScene(this);
	mSolver = new Solver(this);

	initGraphics();

	connect(ui->resistor, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Resistor;
				this->createElement();
			}
	);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	ui->sideMenu->resize( ui->sideMenu->width(),
						  this->height() );

	QMainWindow::resizeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	switch(event->key())
	{
		case Qt::Key_Escape:
		{
			ui->sideMenu->setVisible(
				!ui->sideMenu->isVisible() );
			break;
		}

		case Qt::Key_F11:
		{
			setWindowState(windowState() ^
				(Qt::WindowFullScreen | Qt::WindowActive) );
			break;
		}

		case Qt::Key_R:
		{
			mSolver->run(mScene);
			break;
		}

		default:
			QMainWindow::keyPressEvent(event);
	}
}

void MainWindow::createElement()
{
	GObject* newObject;

	if ( !ui->graphicsView->isDrag() )
	{
		switch (mCreateObject)
		{
			case EObjectType::Resistor:
			{
				newObject = new Resistor();
				break;
			}

			default:
			{
				break;
			}
		}

		mScene->addItem( newObject );
		newObject->setVisible(false);
		ui->graphicsView->setDrag(true);
		connect( ui->graphicsView, SIGNAL(cursorChangePos(QPointF)),
				 newObject, SLOT( moveTo(QPointF) ) );
	}
}

void MainWindow::initGraphics()
{
	QRect screen = QGuiApplication::primaryScreen()->geometry();
	qint32 height = screen.height(),
		   width = screen.width();

	mScene->setSceneRect( 0, 0, width, height );
	ui->graphicsView->resize( width, height );
	ui->graphicsView->setScene( mScene );
	ui->graphicsView->setTransformationAnchor( QGraphicsView::AnchorViewCenter );
	ui->graphicsView->setRenderHint( QPainter::Antialiasing );

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(ui->sideMenu);
	effect->setBlurRadius(5);
	ui->sideMenu->setGraphicsEffect(effect);
}
