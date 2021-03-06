#include <randomnumbergenerator.h>

RandomNumberGenerator::RandomNumberGenerator(QObject *parent) : QObject(parent), m_maxValue(100)
{
    QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(updateProperty()));
    m_timer.start(500);
}

int RandomNumberGenerator::maxValue() const
{
    return m_maxValue;
}

void RandomNumberGenerator::setMaxValue(int maxValue)
{
    m_maxValue = maxValue;
}
