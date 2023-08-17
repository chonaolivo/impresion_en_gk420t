#include "dialog.h"
#include "ui_dialog.h"
#include <fstream>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    std::string nombre;
    QString nombre1;
    std::ifstream arch;
    arch.open("flores.txt");
    while (std::getline(arch, nombre)) {
        nombre1 = QString::fromStdString(nombre);
        ui->lista1->addItem(nombre1);
    }
    arch.close();
}
Dialog::~Dialog(){delete ui;}
void Dialog::on_agregar1_clicked()
{
    QString nombre;
    nombre= ui->Nombre->text();
    ui->lista1->addItem(nombre);
    std::ofstream arch;
    std::string nuevaflor=nombre.toStdString();
    arch.open("flores.txt", std::ios::app);  // Abre el archivo en modo append
    if (arch.is_open()) {
        arch <<nuevaflor<<std::endl;    // Escribe el nuevo nombre en el archivo
        arch.close();   // Cierra el archivo
    } else {}    
}
void Dialog::on_quitar1_clicked()
{
    QListWidgetItem* aux1= ui->lista1->currentItem();   //tomamos el item marcado en la lista
    QString temp=aux1->text();  //tomamos el texto en una variable QString
    std::string Aeliminar = temp.QString::toStdString();    //transformo el QString en std::string
    int aux=0;
    std::string nombres[99];
    std::ifstream arch;
    arch.open("flores.txt");    //abro el archivo flores.txt
    while (std::getline(arch, nombres[aux])) {aux++;}   //Guardo todo en nombres[]
    std::ofstream archi;    //creo una variable ofstream para enviar los nombres que no quiero borrar al archivo
    archi.open("flores.txt");   //abro nuevamente el archivo flores.txt
    if(archi.is_open()){    //verifico que se halla abierto
        for(int i=0;i<aux;i++){
            if(nombres[i]!=Aeliminar){  //guardo todos los otros items menos el que no corresponde
                archi<<nombres[i]<<std::endl;
            }
            else{}
        }
    }
    arch.close();
    delete aux1;
}
void Dialog::on_guardar_clicked(){accept();}
