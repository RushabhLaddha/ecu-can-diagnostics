#include "CanBackendWorker.hpp"
#include <QThread>
#include <QDateTime>

CanBackendWorker::CanBackendWorker(QObject *parent) : QObject(parent) {

}

void CanBackendWorker::start() {
    m_running = true;

    while(m_running) {
        CanMessage msg {0x101, 2, "DC 05", QDateTime::currentDateTime()};

        emit canMessageReceived(msg);

        DiagnosticEvent event {QDateTime::currentDateTime(), DiagnosticSeverity::ERROR, "Engine Speed above limit"};

        emit diagEventRaised(event);

        QThread::msleep(100);
    }
}

void CanBackendWorker::stop() {
    m_running = false;
}