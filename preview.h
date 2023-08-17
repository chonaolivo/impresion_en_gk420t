#ifndef PREVIEW_H
#define PREVIEW_H

#include <QMainWindow>

namespace Ui {
class preview;
}

class preview : public QMainWindow
{
    Q_OBJECT

public:
    explicit preview(QWidget *parent = nullptr);
    ~preview();

private:
    Ui::preview *ui;
};

#endif // PREVIEW_H
