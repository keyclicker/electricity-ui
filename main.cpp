#include <QApplication>
#include <MainWindow.h>
#include <Debug.hpp>

const std::string FILENAME = "main";
const std::ios_base::openmode OPENMODE =
	std::ios_base::out;

int main(int argc, char* argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	return a.exec();
}
