#include "preview.h"
#include "ui_preview.h"
#include <fstream>
preview::preview(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::preview)
{
    ui->setupUi(this);
    std::string nombre;
    QString nombre1;
    std::ifstream archivo;
    archivo.open("flores.txt");
    while (std::getline(archivo, nombre)) {
        nombre1 = QString::fromStdString(nombre);
        ui->lista1->addItem(nombre1);
    }
}

preview::~preview()
{
    delete ui;
}
