#include "config.h"

const QUuid UID = QUuid::createUuid();
const QString MACHINE_ID = UID.toString();


QString md5(const QString &str)
{
    QString md5;
    md5 = QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5).toHex();
    return md5;
}
