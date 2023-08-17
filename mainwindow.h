#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fstream>
#include <string>
#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString nombre;


private slots:
    void on_seleccionados_itemClicked(QListWidgetItem *item);

    void on_lista_itemClicked(QListWidgetItem *item);

    void on_quitar_clicked();

    void on_imprimir_clicked();


    void on_filtro_textChanged(const QString &arg1);

    void on_cantidad_flor_currentTextChanged(const QString &arg1);

    void on_Nuevo_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
