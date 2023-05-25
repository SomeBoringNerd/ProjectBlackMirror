#include "cboxform.h"
#include "qwidget.h"
CBoxForm::CBoxForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CBoxForm)
{
    ui->setupUi(this);
}

CBoxForm::~CBoxForm()
{
    delete ui;
}
