#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_agregar1_clicked();

    void on_quitar1_clicked();

    void on_guardar_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
