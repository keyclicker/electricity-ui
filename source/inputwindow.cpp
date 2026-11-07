#include <inputwindow.h>

#include <QCursor>
#include <QRegularExpressionValidator>

InputWindow::InputWindow(QString name, QString mu, QWidget* parent) :
	QDialog(parent)
{
    this->setStyleSheet("background: #3e4c8a;"
                        "color: #DDD;"
                        "border-radius: 5px;");

	this->setWindowFlag(Qt::FramelessWindowHint);

    valueName = new QLabel(name);

	line = new QLineEdit();
    line->setFocus();

	// A plain positive number: the solver parses it as `cpp_float`
	line->setValidator( new QRegularExpressionValidator(
		QRegularExpression("\\d*\\.?\\d+"), line) );

		dimention = new QComboBox();
		dimention->addItem("Femto", static_cast<int>(Dimension::Femto));
		dimention->addItem("Pico", static_cast<int>(Dimension::Pico));
		dimention->addItem("Nano", static_cast<int>(Dimension::Nano));
		dimention->addItem("Micro", static_cast<int>(Dimension::Micro));
		dimention->addItem("Milli", static_cast<int>(Dimension::Milli));
		dimention->addItem(" ", static_cast<int>(Dimension::Normal));
		dimention->addItem("Kilo", static_cast<int>(Dimension::Kilo));
		dimention->addItem("Mega", static_cast<int>(Dimension::Mega));
		dimention->addItem("Giga", static_cast<int>(Dimension::Giga));
		dimention->addItem("Tera", static_cast<int>(Dimension::Tera));
		dimention->addItem("Peta", static_cast<int>(Dimension::Peta));

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
				this->reject();
			}
	);

    connect(ok, &QPushButton::pressed,
			[this]()
			{
				if ( !line->hasAcceptableInput() )
					return;

				emit getVal( line->text().toStdString() );
				emit getDimension( static_cast<Dimension>(
					dimention->currentData().toInt() ) );
				this->accept();
			}
	);
}

InputWindow::~InputWindow()
{

}

void InputWindow::setInput(const std::string& value, Dimension dimension)
{
	// Start from the element's current value, next to the cursor
	line->setText( QString::fromStdString(value) );
	dimention->setCurrentIndex(
		dimention->findData( static_cast<int>(dimension) ) );

	this->move( QCursor::pos() );
}
