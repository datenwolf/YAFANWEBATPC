#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QtGui/QWidget>

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = 0);
    ~ClientWidget();
};

#endif // CLIENTWIDGET_H
