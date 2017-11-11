#ifndef INFOTAB_H
#define INFOTAB_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <string>
#include <QVBoxLayout>

class InfoTab : public QLabel
{
	Q_OBJECT

public:
	explicit InfoTab(QWidget *parent = nullptr);

	void appendInfo(QString name, qreal value, QString mu);
};

#endif // INFOTAB_H
