#pragma once
#ifndef QMLENGINE_H
#define QMLENGINE_H
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>


/*
 * EngineHelper manages the engine run by the QMLApplication that hosts the QMLComponent(s)
 */
class EngineHelper : public QQmlEngine
{
    Q_OBJECT
public:
    EngineHelper();
    void addComponent(QQmlComponent *component);
    void scheduleDelete();

public slots:
    void onComponentRemoved();

private:

    bool mDeleteScheduled;
    QList<QQmlComponent *> mComponents;
};

EngineHelper::EngineHelper() : QQmlEngine(), mDeleteScheduled(false)
{

}

/* Add a QQmlComponenet to the engine */
void EngineHelper::addComponent(QQmlComponent *component)
{
    mComponents.append(component);
    connect(component, SIGNAL(destroyed(QObject*)), this, SLOT(onComponentRemoved()));
}

/* Delete when the engine no longer has any QQmlComponents */
void EngineHelper::scheduleDelete() {
    if (mComponents.isEmpty()) {
        delete this;
    }
    mDeleteScheduled = true;
}

/* Remove component from the engine, if empty, we're safe to exit the engine */
void EngineHelper::onComponentRemoved()
{
    mComponents.removeAll(qobject_cast<QQmlComponent*>(sender()));
    if (mComponents.isEmpty()) {
        delete this;
    }
}

#endif //QMLENGINE_H