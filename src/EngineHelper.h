#pragma once
#ifndef QMLENGINE_H
#define QMLENGINE_H
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlComponent>


/*
 * QmlEngine manages the engine run by the QMLApplication that hosts the QMLComponent(s)
 */
class QmlEngine : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    QmlEngine();
    void addComponent(QQmlComponent *component);
    void scheduleDelete();

public slots:
    void onComponentRemoved();

private:

    bool mDeleteScheduled;
    QList<QQmlComponent *> mComponents;
};

QmlEngine::QmlEngine() : QQmlApplicationEngine(), mDeleteScheduled(false)
{

}

/* Add a QQmlComponenet to the engine */
void QmlEngine::addComponent(QQmlComponent *component)
{
    mComponents.append(component);
    connect(component, SIGNAL(destroyed(QObject*)), this, SLOT(onComponentRemoved()));
}

/* Delete when the engine when it no longer has any QQmlComponents */
void QmlEngine::scheduleDelete() {
    if (mComponents.isEmpty()) {
        delete this;
    }
    mDeleteScheduled = true;
}

/* Remove component from the engine, if empty, we're safe to exit the engine */
void QmlEngine::onComponentRemoved()
{
    mComponents.removeAll(qobject_cast<QQmlComponent*>(sender()));
    if (mComponents.isEmpty()) {
        delete this;
    }
}

#endif //QMLENGINE_H