#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QListWidget>
#include "dialog.h"
#include <QProcess>
#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <vector>
#include <QDate>
#include <QDebug>
#include <QPrinter>
int cont=0;
QString cantidad;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::string nombre,L_O[99];
    int aux=0;
    QString nombre1;
    std::ifstream arch;
    arch.open("flores.txt");
    while (std::getline(arch, nombre)) {
        L_O[aux]=nombre;
        aux++;
    }
    arch.close();
    for (int i = 0; i < aux - 1; ++i) {     //ordena el vector de forma alfabetica
        for (int j = 0; j < aux - i - 1; ++j) {
            if (L_O[j] > L_O[j + 1]) {
                std::swap(L_O[j], L_O[j + 1]);
            }
        }
    }
    for(int i=0;i<aux;i++){ //agrega los items ordenados a la lista
        nombre1 = QString::fromStdString(L_O[i]);
        ui->lista->addItem(nombre1);
    }
}
MainWindow::~MainWindow(){delete ui;}
void MainWindow::on_seleccionados_itemClicked(QListWidgetItem *item) //lista derecha
{    
    item=ui->seleccionados->currentItem();  //guardamos en el puntero item la fila seleccionada
    std::string nombre,nombres[999],nombres_nuevos[999],quitar; //nombre=variable para traer las palabras del archivo
    QString Qquitar;    //QString para poder pasarlo a string
    Qquitar=item->text();   //pasamos el texto del item al QString
    quitar=Qquitar.toStdString();   //transformacion QString -- std::string
    cont--;
    delete item;
}
void MainWindow::on_lista_itemClicked(QListWidgetItem *item) //lista izquierda
{
    QListWidgetItem* aux= ui->lista->currentItem(); //marcamos el item seleccionado
    QString aux1=aux->text();   //Lo pasamos a un QString
    ui->seleccionados->addItem(aux1);   //lo añadimos a la lista de impresion
    cont++;
}

void MainWindow::on_quitar_clicked()

{
    Dialog pd(this);    //llamamos la ventana de Agregar/Quitar
    pd.exec();  //la ejecutamos
    std::string nombre;
    QString nombre1;
    std::ifstream arch;
    arch.open("flores.txt");
    while (std::getline(arch, nombre)) {
        nombre1 = QString::fromStdString(nombre);
        ui->lista->addItem(nombre1);
    }
    arch.close();
    QCoreApplication::quit();   // Cerrar la aplicación actual
    QProcess::startDetached(QCoreApplication::applicationFilePath());   // Iniciar una nueva instancia de la aplicación
    MainWindow activateWindow;  // Activar la ventana de la nueva instancia
}

void MainWindow::on_imprimir_clicked()
{    
    QImage baseImage("Rotulo.png"); // Carga la imagen base desde la ruta especificada
    QString text[8];  // Texto que se centrará en la imagen
    QString Qfecha;   //guarda la fecha en un QString para imprimirla
    int fecha=0;    //va a almacenar temporalmente la fecha
    QDate currentDate = QDate::currentDate();   //almacena la fecha de ese mismo dia
    //fecha
    Qfecha="ELAB.";fecha=currentDate.day();Qfecha+=QString::number(fecha);Qfecha+="/";fecha=currentDate.month();Qfecha+=QString::number(fecha);Qfecha+="/";fecha=currentDate.year();Qfecha+=QString::number(fecha);
    int aux=1;    
    QImage resultImage(baseImage.size(), QImage::Format_RGB32); // Crea una nueva imagen con el mismo tamaño que la imagen base
    resultImage.fill(Qt::white);  // Llena la imagen con color blanco
    QPainter painter(&resultImage);  // Crea un pintor para dibujar en la imagen
    painter.drawImage(0, 0, baseImage); // Dibuja la imagen base en las coordenadas (0, 0)
    QFont font = painter.font();  // Obtiene la fuente actual del pintor
    font.setFamily("Arial");  // Cambia "Arial" a la fuente que desees
    font.setPointSize(25);    // Cambia el tamaño de la fuente a tu preferencia
    painter.setFont(font);  // Establece la fuente actual del pintor
    QFontMetrics fm(font);  // Obtiene métricas de la fuente para el cálculo del tamaño del texto
    int textWidth; // Calcula el ancho del texto
    int textHeight = fm.height();  // Obtiene la altura de la fuente


    int x=0;    // Eje x para imprimir el texto sobre la imagen
    int y = (resultImage.height() - textHeight) / 2;    //calcula el centro de la imagen en el eje y
    // Calcula las coordenadas para colocar el texto en la esquina inferior derecha
    int x1 = resultImage.width() - textWidth - 300;  // Desplazamiento de 10 píxeles desde el borde derecho
    int y1 = resultImage.height() - textHeight - -30;    // Desplazamiento de 10 píxeles desde el borde inferior
    painter.drawText(x1,y1,Qfecha); //pintamos la fecha de elaboracion
    // Iterar sobre los elementos del QListWidget y dibujarlos
    if(cont==1){
        y-=90;  //le otorgamos -90 a y para estandarizar la pos del texto
        for(int i=0;i<cont;i++){
            QListWidgetItem *item = ui->seleccionados->item(i); //selecciona el item
            QString itemText = item->text();    //lo transforma a QString
            textWidth = fm.horizontalAdvance(itemText);  // Calcula el ancho del texto
            x = (resultImage.width() - textWidth) / 2;  //sacamos el centro del texto
            painter.drawText(x, y, itemText);   //lo dibujamos
            y+=30;  //le sumamos 30 a y para estandarizar las escrituras siguientes
            cantidad=ui->cantidad_flor->currentText();  //imprime la cantidad especificada en cantidad_flor
            textWidth = fm.horizontalAdvance(cantidad); //largo del texto
            x = (resultImage.width() - textWidth) / 2;  //medio del texto
            painter.drawText(x, y, cantidad);   //dibujamos
        }
    }
    else if (cont%2==0 && cont<10){
        y-=90;
        for(int i=0;i<cont;i++){
            QListWidgetItem *item = ui->seleccionados->item(i);
            QString itemText = item->text();
            QListWidgetItem *item1 = ui->seleccionados->item(i+1);
            QString itemText1 = item1->text();
            i++;
            textWidth = fm.horizontalAdvance(itemText);
            textWidth += fm.horizontalAdvance(itemText1);
            x = (resultImage.width() - textWidth) / 2;
            itemText += " - "+itemText1;
            painter.drawText(x, y, itemText);
            y+=30;
        }        
        cantidad=ui->cantidad_flor->currentText();
        textWidth = fm.horizontalAdvance(cantidad);
        x = (resultImage.width() - textWidth) / 2;
        painter.drawText(x, y, cantidad);
    }
    else if(cont%2!=0 && cont<10){
        y-=90;
        for(int i=0;i<cont-1;i++){
            QListWidgetItem *item = ui->seleccionados->item(i);
            QString itemText = item->text();
            QListWidgetItem *item1 = ui->seleccionados->item(i+1);
             QString itemText1 = item1->text();
            i++;
            textWidth = fm.horizontalAdvance(itemText);
            textWidth += fm.horizontalAdvance(itemText1);
            x = (resultImage.width() - textWidth) / 2;
            itemText += " - "+itemText1;
            painter.drawText(x, y, itemText);
            y+=30;
        }
        QListWidgetItem *item = ui->seleccionados->item(cont-1);
        QString itemText = item->text();
        textWidth = fm.horizontalAdvance(itemText);
        x = (resultImage.width() - textWidth) / 2;
        painter.drawText(x, y, itemText);
        y+=30;
        cantidad=ui->cantidad_flor->currentText();
        textWidth = fm.horizontalAdvance(cantidad);
        x = (resultImage.width() - textWidth) / 2;
        painter.drawText(x, y, cantidad);
    }
    else if(cont==11){
        y-=100;
        for(int i=0;i<cont-2;i++){
            QListWidgetItem *item = ui->seleccionados->item(i);
            QString itemText = item->text();
            QListWidgetItem *item1 = ui->seleccionados->item(i+1);
            QString itemText1 = item1->text();
            QListWidgetItem *item2 = ui->seleccionados->item(i+2);
            QString itemText2 = item2->text();
            i++;
            i++;
            textWidth = fm.horizontalAdvance(itemText);
            textWidth += fm.horizontalAdvance(itemText1);
            textWidth += fm.horizontalAdvance(itemText2);
            x = (resultImage.width() - textWidth) / 2;
            x+=20;
            itemText += " - "+itemText1+" - "+itemText2;
            painter.drawText(x, y, itemText);
            y+=30;
        }
        QListWidgetItem *item = ui->seleccionados->item(cont-1);
        QString itemText = item->text();
        QListWidgetItem *item1 = ui->seleccionados->item(cont-2);
        QString itemText1 = item1->text();
        textWidth = fm.horizontalAdvance(itemText);
        textWidth += fm.horizontalAdvance(itemText1);
        x = (resultImage.width() - textWidth) / 2;
        itemText += " - "+itemText1;
        painter.drawText(x, y, itemText);
        y+=30;
        cantidad=ui->cantidad_flor->currentText();
        textWidth = fm.horizontalAdvance(cantidad);
        x = (resultImage.width() - textWidth) / 2;
        painter.drawText(x, y, cantidad);
    }

    else if(cont==12){
        y-=100;
        for(int i=0;i<cont-1;i++){
            QListWidgetItem *item = ui->seleccionados->item(i);
            QString itemText = item->text();
            QListWidgetItem *item1 = ui->seleccionados->item(i+1);
            QString itemText1 = item1->text();
            QListWidgetItem *item2 = ui->seleccionados->item(i+2);
            QString itemText2 = item2->text();
            i++;
            i++;
            textWidth = fm.horizontalAdvance(itemText);
            textWidth += fm.horizontalAdvance(itemText1);
            textWidth += fm.horizontalAdvance(itemText2);
            x = (resultImage.width() - textWidth) / 2;
            x+=30;
            itemText += " - "+itemText1+" - "+itemText2;
            painter.drawText(x, y, itemText);
            y+=30;
        }
        y+=30;
        cantidad=ui->cantidad_flor->currentText();
        textWidth = fm.horizontalAdvance(cantidad);
        x = (resultImage.width() - textWidth) / 2;
        painter.drawText(x, y, cantidad);
    }
    x1 = (resultImage.width() - textWidth) /2;  //
    y1 = (resultImage.height() - textHeight) /2;    //
    cantidad="VIGENCIA DE ESTA PREPARACION 30 DIAS";
    textWidth = fm.horizontalAdvance(cantidad);
    x1 = (resultImage.width() - textWidth) / 2;
    y1=y1+105;
    painter.drawText(x1,y1,cantidad);
    cantidad="FARMACIA MOYANO";
    textWidth = fm.horizontalAdvance(cantidad);
    x1 = (resultImage.width() - textWidth) / 2;
    y1+=45;
    painter.drawText(x1,y1,cantidad);
    cantidad="Perla L G de Falcón M.P.2792 Alicia Falcón M.P.326";
    textWidth = fm.horizontalAdvance(cantidad);
    x1 = (resultImage.width() - textWidth) / 2;
    y1=y1+30;
     painter.drawText(x1,y1,cantidad);
    cantidad="Farmacéutica";
    textWidth = fm.horizontalAdvance(cantidad);
    x1 = (resultImage.width() - textWidth) / 2;
    y1=y1+35;
    painter.drawText(x1,y1,cantidad);
    painter.end();  // Finaliza el dibujo en la imagen

    QString savePath = "imagen_generada.jpg";   // Ruta donde se guardará la imagen generada
    resultImage.save(savePath);  // Guarda la imagen generada en la ruta especificada
    QPrinter printer;   // Crear una instancia de QPrinter
    printer.setPrinterName("Zebra ZD230 ZPL HOMEOPATIA");   //configuramos el nombre de la impresora
    double widthInInches = 7.62 * 0.3937;   // Convertir el tamaño de centímetros a pulgadas (1 cm ≈ 0.3937 pulgadas)
    double heightInInches = 5.08 * 0.3937;  //especifico para rotulos de 8cm x 4cm
    int widthInPoints = static_cast<int>(printer.logicalDpiX() * widthInInches);// Convertir el tamaño de pulgadas a puntos utilizando la resolución de la impresora
    int heightInPoints = static_cast<int>(printer.logicalDpiY() * heightInInches);    
    QPageSize customPageSize(QSizeF(widthInPoints, heightInPoints), QPageSize::Point, "Custom");    // Crear un tamaño de página personalizado
    printer.setPageSize(customPageSize);    
    QPainter painter1(&printer);    // Crear un QPainter para pintar en la impresora
    QImage image("imagen_generada.jpg");    // Cargar la imagen que deseas imprimir
    widthInPoints=319.725;  //tamaño promedio para encajar la imagen en el rotulo
    heightInPoints=159.355; //reitero, por defecto para rotulos 8cm x 4cm
    if (!image.isNull()) {        
        QImage scaledImage = image.scaled(QSize(widthInPoints, heightInPoints), Qt::KeepAspectRatio, Qt::SmoothTransformation); // Cambiar el tamaño de la imagen según tus necesidades
        painter1.drawImage(QPoint(35, -40), scaledImage);// Dibujar la imagen en el contexto de impresión, QPoint(x,y)
        // Finalizar la pintura en la impresora
        painter1.end(); //finalizamos la instancia QPainter
    } else {qDebug() << "No se pudo cargar la imagen.";}
}
void MainWindow::on_filtro_textChanged(const QString &filtro)
{
    std::ifstream archi;
    std::string LxL,LxL2,nombre;
    QString Alista;
    LxL2=filtro.toStdString();
    int aux=0;
    for (char caracter : LxL2) {    //verificamos cuantos caracteres tiene el texto ingresado
        if (std::isalpha(caracter)) {
            aux++;
        }
    }
    archi.open("flores.txt");   //abrimos el archivo
    if(archi.is_open()){    //verificamos que este abierto
        if(LxL2==""){   //si esta vacio, debe copiar toda la lista de flores de forma ordenada
            ui->lista->clear(); //limpiamos la lista
            std::string L_O[99];
            QString nombre1;
            while (std::getline(archi, nombre)) {L_O[aux]=nombre;aux++;}    //sacamos todos los elementos del archivo
            for (int i = 0; i < aux - 1; ++i) { //lo ordenamos
                for (int j = 0; j < aux - i - 1; ++j) {
                    if (L_O[j] > L_O[j + 1]) {
                        std::swap(L_O[j], L_O[j + 1]);
                    }
                }
            }
            for(int i=0;i<aux;i++){nombre1 = QString::fromStdString(L_O[i]);ui->lista->addItem(nombre1);}   //añadimos a la lista los items ordenados
                for(int i=0;i<aux;i++){
                    nombre1 = QString::fromStdString(L_O[i]);
                    ui->lista->addItem(nombre1);
                }
                Alista=QString::fromStdString(nombre);
                ui->lista->addItem(Alista);            
        }
        else{
            ui->lista->clear(); //limpiamos la lista
            while(std::getline(archi, nombre)){ //creamos un while que llega hasta el fin del archivo
                LxL=nombre.substr(0,aux);   //igualamos LxL a las aux letras del nombre de la flor que queremos verificar
                if(LxL2==LxL){  //verificamos que el las letras ingresadas concuerden con el nombre de la flor
                    Alista=QString::fromStdString(nombre);  //transformamos el nombre a QString para poder meterlo en la lista
                    ui->lista->addItem(Alista); //agregamos a la lista el nombre
                }
            }
        }
    }
    else{}
    archi.close();  //cerramos el archivo
}
void MainWindow::on_cantidad_flor_currentTextChanged(const QString &arg1){}
/*El boton nuevo, crea una nueva instancia del programa, esto fue creado asi porque al
  intentar limpiar la lista seleccionados surgia un error.*/
void MainWindow::on_Nuevo_clicked(){
    QCoreApplication::quit();// Cerrar la aplicación actual
    QProcess::startDetached(QCoreApplication::applicationFilePath());// Iniciar una nueva instancia de la aplicación
    MainWindow activateWindow;}// Activar la ventana de la nueva instancia

