#include <ui_mainwindow.h>
#include <MainWindow.h>

#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QScreen>
#include <exception>

#include <QDebug>

#include <SourceOfElectricity.hpp>
#include <Switcher.hpp>
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

	connect(ui->battery, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::SourceOfElectricity;
				this->createElement();
			}
	);

	connect(ui->Switch, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Switch;
				this->createElement();
			}
	);
/*
	connect(ui->capacitor, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Capacitor;
				this->createElement();
			}
	);

	connect(ui->inductor, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Inductor;
				this->createElement();
			}
	);

	connect(ui-> , &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::SourceOfElectricity;
				this->createElement();
			}
	);

	connect(ui-> , &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::SourceOfElectricity;
				this->createElement();
			}
	);
*/

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
			auto* solver = new Solver();
			try
			{
				solver->run(mScene);
			}
			catch(std::exception& e)
			{
				qDebug() << e.what();
			}

			delete solver;

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

			case EObjectType::SourceOfElectricity:
			{
				newObject = new SourceOfElectricity();
				break;
			}

			case EObjectType::Switch:
			{
				newObject = new Switch();
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
//	ui->sideMenu->setGraphicsEffect(effect);
}
