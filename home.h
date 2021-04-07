#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

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
