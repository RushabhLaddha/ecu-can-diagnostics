#include "CanBackendWorker.hpp"
#include <QThread>
#include <QDateTime>

CanBackendWorker::CanBackendWorker(QObject *parent) : QObject(parent) {

}

void CanBackendWorker::start() {
    m_driver = std::make_unique<SocketCanDriver>("vcan0");

    if(!m_driver->init()) {
        DiagnosticEvent event {QDateTime::currentDateTime(), DiagnosticSeverity::ERROR, "Failed to initialize CAN interface"};

        emit diagEventRaised(event);
        return;
    }

    m_running = true;

    while(m_running) {
        CanFrame frame;
        if(m_driver->receive(frame)) {
            processFrame(frame);
        } else {
            QThread::msleep(5);
        }
    }
}

void CanBackendWorker::stop() {
    m_running = false;
}

void CanBackendWorker::processFrame(const CanFrame &frame) {
    CanMessage msg {};
    msg.id = frame.id;
    msg.dlc = frame.dlc;
    msg.rawData.clear();
    msg.rawData.reserve(msg.dlc);
    for(int i = 0; i < msg.dlc; ++i) {
        msg.rawData.append(static_cast<char>(frame.data[i]));
    }
    QString dataStr;
    for (int i = 0; i < frame.dlc; ++i) {
        dataStr += QString("%1 ").arg(frame.data[i], 2, 16, QLatin1Char('0')).toUpper();
    }
    msg.data = dataStr.trimmed();
    msg.timestamp = QDateTime::currentDateTime();

    emit canMessageReceived(msg);
}