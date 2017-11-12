#include "mainwindow.h"
#include "ui_mainwindow.h"

#define sc ui->graphicsView->scene()

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	//Ініціалізація
	ui->setupUi(this);

    canvas = new QGraphicsScene(this);
    ui->graphicsView->setScene(canvas);

	//Конектим кнопки до слотів
	connect(ui->resistor, SIGNAL(clicked(bool)),
			this, SLOT(createResistor(bool)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    ui->sideMenu->resize(ui->sideMenu->width(), this->height());
    ui->graphicsView->resize(this->width(), this->height());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	//Фулскрін
    if (event->key() == Qt::Key_F11)
    {
            setWindowState(windowState() ^
                (Qt::WindowFullScreen | Qt::WindowActive));
    }

	//Для узгодження з івентами айтемів
    QMainWindow::keyPressEvent(event);
}

//Сигнал створення резистора
void MainWindow::createResistor(bool val)
{
	if (!ui->graphicsView->isDrag())
	{
		//Створюємо айтем
		GObject *resistor = new GObject();

		canvas->addItem(resistor);

		//Пирив'язуємо новостворений айтем до курсора
		connect(ui->graphicsView, SIGNAL(cursorChangePos(QPointF)),
									resistor, SLOT(moveTo(QPointF)));

		resistor->setVisible(false); //Невеликий костиль
		resistor->setFocus();
		ui->graphicsView->setDrag(true);
	}
}
