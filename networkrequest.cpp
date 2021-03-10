#include "networkrequest.h"

networkrequest::networkrequest(QObject *parent) : QObject(parent)
{
    networkAccessManager = new QNetworkAccessManager;
    networkAccessManager
}
