#include <ui_mainwindow.h>
#include <MainWindow.h>
#include <fstream>

#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScreen>
#include <exception>

#include <QDebug>

#include <SourceOfCurrent.hpp>
#include <SourceOfElectricity.hpp>
#include <Switcher.hpp>
#include <Resistor.hpp>
#include <Bulb.hpp>
#include <Inductor.hpp>
#include <Capacitor.hpp>
#include <Voltmeter.hpp>
#include <Ammeter.hpp>
#include <Line.hpp>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mCreateObject(),
	mCurFile(0),
	mFullNum(0),
	mWasChanged(false),
	cFileName("undoredo"),
	cDirectory("")
{
	ui->setupUi(this);
	setWindowIcon( QIcon(":/icons/icons/eLogo.png") );
	mScene = new QGraphicsScene(this);

	initGraphics();


	//init load/save to file
	//init undo/redo
	//slots will contain mWasChange and mFullNum++
	//i'm praying it will work with normal time

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

	// File menu: an overlay opened by the settings button
	ui->menu->hide();

	connect(ui->setings, &QPushButton::pressed,
			ui->menu, &QWidget::show);
	connect(ui->cancel, &QPushButton::pressed,
			ui->menu, &QWidget::hide);
	connect(ui->newFile, &QPushButton::pressed,
			this, &MainWindow::newFile);
	connect(ui->save, &QPushButton::pressed,
			this, &MainWindow::saveFile);
	connect(ui->saveTo, &QPushButton::pressed,
			this, &MainWindow::saveToFile);
	connect(ui->load, &QPushButton::pressed,
			this, &MainWindow::loadFromFile);
	connect(ui->pushButton_2, &QPushButton::pressed,
			this, &MainWindow::close);

	connect(ui->play, &QPushButton::toggled,
			[this](bool checked)
			{
				if (checked)
					this->startSimulation();
				else
					this->stopSimulation();
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
			ui->play->toggle();
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

void MainWindow::startSimulation()
{
	mSolver.reset( new Solver() );

	try
	{
		mSolver->run(mScene);
	}
	catch(std::exception& e)
	{
		QMessageBox::warning(this, "Electricity", e.what());
		ui->play->setChecked(false);
	}
}

void MainWindow::stopSimulation()
{
	// ~Solver resets the currents it has shown
	mSolver.reset();
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

void MainWindow::newFile()
{
	clearScene();
	mFileName.clear();
	ui->menu->hide();
}

void MainWindow::saveFile()
{
	if ( mFileName.isEmpty() )
	{
		saveToFile();
		return;
	}

	save(mFileName);
	ui->menu->hide();
}

void MainWindow::saveToFile()
{
	QString fileName = QFileDialog::getSaveFileName(
		this,
		"Save File",
		QString(),
		"File ( *.scheme )"
	);

	if (fileName.size() == 0)
		return;

	save(fileName);
	mFileName = fileName;
	ui->menu->hide();
}

void MainWindow::loadFromFile()
{

	QString fileName = QFileDialog::getOpenFileName(
		this,
		"Open File",
		QString(),
		"File ( *.scheme )"
	);

	if (fileName.size() == 0)
		return;

	load(fileName);
	mFileName = fileName;
	ui->menu->hide();
}

void MainWindow::load(QString filename)
{
	std::ifstream in( filename.toStdString() );
	load(in);
}

void MainWindow::save(QString filename)
{
	std::ofstream out( filename.toStdString() );
	save(out);
}

void MainWindow::clearScene()
{
	// The solver points to the items: stop it first
	ui->play->setChecked(false);
	ui->graphicsView->setDrag(false);
	mScene->clear();
}

void MainWindow::load(std::istream& in)
{
	clearScene();

	std::string str;

		while( in >> str )
		{
			if (str == "Line")
			{
				int x1, x2, y1, y2;
				int px, py;
					in >> px >> py;
					in >> x1 >> y1 >> x2 >> y2;

				Line* l = new Line( QPoint(x1, y1), QPoint(x2, y2) );
				l->setPos(px, py);
				mScene->addItem(l);
			}
			else
			{
				GObject* gObj = nullptr;
				qreal rotation;
				int px, py;
				std::string dim;
				std::string val;

					in >> val;
					in >> dim;
					in >> px >> py;
					in >> rotation;

				if (str == "Ammeter")
					gObj = new Ammeter();
				if (str == "Bulb")
					gObj = new Bulb();
				if (str == "Capacitor")
					gObj = new Capacitor();
				if (str == "Inductor")
					gObj = new Inductor();
				if (str == "Resistor")
					gObj = new Resistor();
				if (str == "SourceOfElectricity")
					gObj = new SourceOfElectricity();
				if (str == "Switch")
					gObj = new Switch();
				if (str == "Voltmetr")
					gObj = new Voltmeter();

				// No sprite for e.g. `SourceOfCurrent`: skip it
				if (gObj == nullptr)
					continue;

				gObj->setAngle(rotation);
				gObj->setPos(px, py);

				EObject* eObj = dynamic_cast<EObject*>(gObj);
				eObj->setValue(val);
				eObj->setDimension(dim);

				if (str == "Switch")
					static_cast<Switch*>(gObj)->setState(
						eObj->getValue() == Switch::ON );

				mScene->addItem(gObj);
			}
		}
}

void MainWindow::save(std::ostream& out)
{
	auto list = mScene->items();

		for (auto& i : list)
			if ( i->type() == static_cast<int>(GObjectType::Item) )
			{
				auto obj = dynamic_cast<EObject*>(i);

					switch( obj->getType() )
					{
						case EObjectType::Ammeter:
						{
							out << "Ammeter\n";
							break;
						}

						case EObjectType::Bulb:
						{
							out << "Bulb\n";
							break;
						}

						case EObjectType::Capacitor:
						{
							out << "Capacitor\n";
							break;
						}

						case EObjectType::Inductor:
						{
							out <<"Inductor\n";
							break;
						}

						case EObjectType::Resistor:
						{
							out << "Resistor\n";
							break;
						}

						case EObjectType::SourceOfCurrent:
						{
							out << "SourceOfCurrent\n";
							break;
						}

						case EObjectType::SourceOfElectricity:
						{
							out << "SourceOfElectricity\n";
							break;
						}

						case EObjectType::Switch:
						{
							out << "Switch\n";
							break;
						}

						case EObjectType::Voltmeter:
						{
							out << "Voltmetr\n";
							break;
						}
					}

				out << obj->getString() << "\n";
				out << obj->getDimension() << "\n";
				out << i->pos().toPoint().x() << " "
					<< i->pos().toPoint().y() << "\n";
				out << i->rotation() << "\n";
			}

			else if( i->type() == static_cast<int>(GObjectType::Line) )
			{
				auto p = dynamic_cast<Line*>(i);
				out << "Line\n";
				out << p->pos().toPoint().x() << "\n"
					<<  p->pos().toPoint().y() << "\n";
				out << p->line().p1().toPoint().x() << "\n"
					<< p->line().p1().toPoint().y() << "\n"
					<< p->line().p2().toPoint().x() << "\n"
					<< p->line().p2().toPoint().y() << "\n";
			}
}

void MainWindow::undo()
{
	if (mCurFile == 0)
		return;

	QString num = QString::number( --mCurFile );
	load(cDirectory + cFileName + num + ".scheme");
}

void MainWindow::redo()
{
	if (mCurFile == mFullNum)
		return;

	if (mCurFile < mFullNum && !mWasChanged)
	{
		QString num = QString::number( ++mCurFile );
		load(cDirectory + cFileName + num + ".scheme");
		return;
	}

	if (mCurFile < mFullNum && mWasChanged)
	{
		mFullNum = mCurFile;
		return;
	}
}
