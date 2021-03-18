#ifndef FRIST_H
#define FRIST_H

#include <QWidget>

namespace Ui {
class frist;
}

class frist : public QWidget
{
    Q_OBJECT

public:
    explicit frist(QWidget *parent = nullptr);
    ~frist();

private slots:
    void on_pushButton_clicked();

private:
    Ui::frist *ui;
};

#endif // FRIST_H
