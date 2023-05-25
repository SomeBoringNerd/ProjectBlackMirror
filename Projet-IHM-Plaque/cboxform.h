//#ifndef CBOXFORM_H
#define CBOXFORM_H

#include <QWidget>

namespace Ui {
class CBoxForm;
}

class CBoxForm : public QWidget
{
    Q_OBJECT

public:
    explicit CBoxForm(QWidget *parent = nullptr);
    ~CBoxForm();

private:
    Ui::CBoxForm *ui;
};
