#include <InputWindow.h>

InputWindow::InputWindow(QString name, QString mu, QWidget* parent) :
	QDialog(parent)
{
	this->setWindowFlag(Qt::FramelessWindowHint);

    valueName = new QLabel(name);

	line = new QLineEdit();
    line->setFocus();

		dimention = new QComboBox();
		dimention->addItem("Femto");
		dimention->addItem("Pico");
		dimention->addItem("Nano");
		dimention->addItem("Micro");
		dimention->addItem("Milli");
		dimention->addItem(" ");
		dimention->addItem("Kilo");
		dimention->addItem("Mega");
		dimention->addItem("Giga");
		dimention->addItem("Tera");
		dimention->addItem("Peta");

	muName = new QLabel(mu);

		hLayout = new QHBoxLayout();
		hLayout->addWidget(valueName);
		hLayout->addWidget(line);
		hLayout->addWidget(dimention);
		hLayout->addWidget(muName);

	ok = new QPushButton("OK");
		cancel = new QPushButton("Cancel");
		buttons = new QHBoxLayout();
		buttons->addWidget(ok);
		buttons->addWidget(cancel);

		vLayout = new QVBoxLayout();
		vLayout->addLayout(hLayout);
		vLayout->addLayout(buttons);

    this->setLayout(vLayout);

	connect(cancel, &QPushButton::pressed,
			[this]()
			{
				this->hide();
			}
	);

	connect(ok, &QPushButton::pressed,
			[this]()
			{
				emit getVal( line->text().toStdString() );
				emit getDimension( dimFromStr( dimention->currentText() ) );
				this->hide();
			}
	);
}

InputWindow::~InputWindow()
{

}

Dimension InputWindow::dimFromStr(QString s)
{
	if (s == "Femto")
		return Dimension::Femto;
	if (s == "Pico")
		return Dimension::Pico;
	if (s == "Nano")
		return Dimension::Nano;
	if (s == "Micro")
		return Dimension::Micro;
	if (s == "Milli")
		return Dimension::Milli;
	if (s == " ")
		return Dimension::Normal;
	if (s == "Kilo")
		return Dimension::Kilo;
	if (s == "Mega")
		return Dimension::Mega;
	if (s == "Giga")
		return Dimension::Giga;
	if (s == "Tera")
		return Dimension::Tera;
	if (s == "Petta")
		return Dimension::Peta;
}
