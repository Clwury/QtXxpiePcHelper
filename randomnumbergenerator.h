#include <QObject>
#include <QQmlPropertyValueSource>
#include <QQmlProperty>
#include <QTimer>
#include <QRandomGenerator>
#include <qqml.h>

class RandomNumberGenerator : public QObject, public QQmlPropertyValueSource
{
    Q_OBJECT
    Q_INTERFACES(QQmlPropertyValueSource)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    QML_ELEMENT
public:
    RandomNumberGenerator(QObject *parent);

    int maxValue() const;

    void setMaxValue(int maxValue);

    virtual void setTarget(const QQmlProperty &prop) { m_targetProperty = prop; }

signals:
    void maxValueChanged();

private slots:
    void updateProperty() {
        m_targetProperty.write(QRandomGenerator::global()->bounded(m_maxValue));
    }

private:
    QQmlProperty m_targetProperty;
    QTimer m_timer;
    int m_maxValue;
};
