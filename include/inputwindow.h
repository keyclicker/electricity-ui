#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#endif // INPUTWINDOW_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <string>

#include <Dimension.hpp>


class InputWindow : public QDialog
{
	Q_OBJECT
	public:
		InputWindow(QString, QString, QWidget* = nullptr);
		virtual ~InputWindow();
		Dimension dimFromStr(QString);

	signals:
		void getDimension(Dimension);
		void getVal(std::string);

	private:
		QHBoxLayout *hLayout, *buttons;
		QVBoxLayout *vLayout;

		QLabel *valueName, *muName;
		QLineEdit *line;
		QComboBox *dimention;
		QPushButton *ok, *cancel;
};
