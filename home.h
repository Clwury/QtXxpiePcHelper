#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QScreen>
#include <QHBoxLayout>
#include "networkrequest.h"

class home : public QMainWindow
{
    Q_OBJECT
public:
    explicit home(QWidget *parent = nullptr);

signals:

private:


    void initUI();
    void initSignalSlots();
};

#endif // HOME_H
