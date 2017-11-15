#include <ui_mainwindow.h>
#include <MainWindow.h>
#include <fstream>

#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QKeyEvent>
#include <QScreen>
#include <exception>

#include <QDebug>

#include <SourceOfElectricity.hpp>
#include <Switcher.hpp>
#include <Resistor.hpp>
#include <Bulb.hpp>
#include <Inductor.hpp>
#include <Capacitor.hpp>
#include <Voltmeter.hpp>
#include <Ammeter.hpp>

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

	connect(ui->bulb, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Bulb;
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

	connect(ui->capacitor, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Capacitor;
				this->createElement();
			}
	);

    connect(ui->voltmeter, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Voltmeter;
				this->createElement();
			}
	);

	connect(ui->ammeter, &QPushButton::pressed,
			[this]() mutable
			{
				this->mCreateObject =
					EObjectType::Ammeter;
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

    ui->undoRedo->move(ui->centralWidget->width()
                       - ui->undoRedo->width() - 10, 10);

    ui->buttons->move((ui->centralWidget->width()
                       + ui->sideMenu->width())/2
                      - ui->buttons->width()/2, 10);

	ui->menu->resize( this->width(),
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

			case EObjectType::Bulb:
			{
				newObject = new Bulb();
				break;
			}

			case EObjectType::Switch:
			{
				newObject = new Switch();
				break;
			}

			case EObjectType::Inductor:
			{
				newObject = new Inductor();
				break;
			}

			case EObjectType::Capacitor:
			{
				newObject = new Capacitor();
				break;
			}

			case EObjectType::Voltmeter:
			{
				newObject = new Voltmeter();
				break;
			}

			case EObjectType::Ammeter:
			{
				newObject = new Ammeter();
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
		connect( ui->graphicsView, SIGNAL( cursorChangePos(QPointF) ),
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
}

/*void MainWindow::saveToFile()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr);
}*/
