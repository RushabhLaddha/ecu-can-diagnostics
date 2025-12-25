#pragma once

#include <QObject>
#include "ui/model/CanMessage.hpp"
#include "ui/model/DiagnosticEvent.hpp"

class CanBackendWorker : public QObject {
    Q_OBJECT

public:
    explicit CanBackendWorker(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

signals:
    void canMessageReceived(const CanMessage &msg);
    void diagEventRaised(const DiagnosticEvent &event);

private:
    bool m_running {false}; 
};