#include "InputWindow.h"

InputWindow::InputWindow(QString name, QString mu)
{
    this->setWindowFlag(Qt::Tool);

    valueName = new QLabel(name);

    line = new QLineEdit();
    line->setFocus();

    dimention = new QComboBox();
    dimention->addItem("Feto");
    dimention->addItem("Pico");
    dimention->addItem("Nano");
    dimention->addItem("Micro");
    dimention->addItem("Milli");
    dimention->addItem(" ");
    dimention->addItem("Kilo");
    dimention->addItem("Mega");
    dimention->addItem("Giga");
    dimention->addItem("Tera");
    dimention->addItem("Petta");

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



    this->show();
}
