#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>

namespace Ui {
class CameraWidget;
}

class CBoxForm : public QWidget;
{
public:
    explicit CBoxForm(QWidget *parent = nullptr);

    CameraWidget();
};

#endif // CAMERAWIDGET_H
