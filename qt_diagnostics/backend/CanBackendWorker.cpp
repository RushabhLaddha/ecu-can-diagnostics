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
    QString dataStr;
    for (int i = 0; i < frame.dlc; ++i) {
        dataStr += QString("%1 ").arg(frame.data[i], 2, 16, QLatin1Char('0')).toUpper();
    }
    msg.data = dataStr.trimmed();
    msg.timestamp = QDateTime::currentDateTime();

    emit canMessageReceived(msg);

    if (frame.id == 0x101) { // Engine Speed
        uint16_t rpm = frame.data[0] | (frame.data[1] << 8);

        if (rpm > 3000) {
            DiagnosticEvent ev {
                QDateTime::currentDateTime(),
                DiagnosticSeverity::WARN,
                QString("Engine speed too high: %1 rpm").arg(rpm)
            };
            emit diagEventRaised(ev);
        }
    }
}