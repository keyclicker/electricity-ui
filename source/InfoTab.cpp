#include <InfoTab.h>

InfoTab::InfoTab(QWidget* parent) :
	QLabel(parent)
{
	this->setStyleSheet("padding: 5px;"
                            "border: 2px solid #78909C;"
                            "border-radius: 10px;"
                            "background: rgb(0,0,0,100);"
                            "color: #DDDDDD;"
                            "font-size: 10pt;"
                            "font-family: Roboto;");
}

void InfoTab::appendInfo(QString name, qreal value, QString mu)
{
	this->setText(this->text() + name + ": " +
			QString::fromStdString(std::to_string(value)) + ' ' + mu + '\n');
//	this->setFixedHeight(height() + 100);
}

