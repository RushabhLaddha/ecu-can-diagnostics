#include "QDiagnostics.hpp"

QDiagnostics::QDiagnostics(QObject *parent) : QObject(parent) {
    m_timer.setInterval(100);

    connect(&m_timer, &QTimer::timeout, this, &QDiagnostics::checkTimeout);

    m_timer.start();
}

void QDiagnostics::onCanMessageReceived(CanMessage msg) {
    m_lastSeen[msg.id] = msg.timestamp;

    checkRanges(msg);

    emit eventProcessed(msg);
}

void QDiagnostics::checkRanges(CanMessage &msg) {
    const QDateTime now = QDateTime::currentDateTime();
    msg.valid = true;
    if(msg.id == CanId::EngineSpeed) {
        if(msg.dlc != DLC::EngineSpeedDLC) {
            emit diagEventRaised({now, DiagnosticSeverity::ERROR, QString("EngineSpeed DLC mismatch : Expected 2, Got %1").arg(msg.dlc)});
            msg.valid = false;
            return;
        }

        uint16_t rpm = static_cast<uint8_t>(msg.rawData[0]) | (static_cast<uint8_t>(msg.rawData[1]) << 8);

        if(rpm > 4000) {
            emit diagEventRaised({now, DiagnosticSeverity::WARN, QString("EngineSpeed too high : %1 rpm").arg(rpm)});
            msg.valid = false;
        }
        
    } else if(msg.id == CanId::Temperature) {
        if(msg.dlc != DLC::TemperatureDLC) {
            emit diagEventRaised({now, DiagnosticSeverity::ERROR, QString("Temperature DLC mismatch : Expected 1, Got %1").arg(msg.dlc)});
            msg.valid = false;
            return;
        }

        uint8_t temperature = static_cast<uint8_t>(msg.rawData[0]);

        if(temperature > 150) {
            emit diagEventRaised({now, DiagnosticSeverity::WARN, QString("Temperature too high : %1").arg(temperature)});
            msg.valid = false;
        }
    } else if(msg.id == CanId::Heartbeat) {
        if(msg.dlc != DLC::HeartbeatDLC) {
            emit diagEventRaised({now, DiagnosticSeverity::ERROR, QString("Heartbeat DLC mismatch : Expected 1, Got %1").arg(msg.dlc)});
            msg.valid = false;
            return;
        }

        uint8_t heartbeat = static_cast<uint8_t>(msg.rawData[0]);

        if(heartbeat != 0xAA) {
            emit diagEventRaised({now, DiagnosticSeverity::ERROR, QString("ECU is dead, Expected 0xAA, Got %1").arg(heartbeat)});
            msg.valid = false;
        }
    }
}

void QDiagnostics::checkTimeout() {
    const QDateTime now = QDateTime::currentDateTime();

    auto check = [&] (uint32_t id, int timeout, const QString name) {
        if(m_lastSeen.find(id) == m_lastSeen.end()) {
            return;
        }

        if(m_lastSeen[id].msecsTo(now) > timeout) {
            emit diagEventRaised({now, DiagnosticSeverity::ERROR, QString("%1 message timeout").arg(name)});

            m_lastSeen.erase(id);
        }
    };

    check(CanId::EngineSpeed, 300, "EngineSpeed");
    check(CanId::Temperature, 500, "Temperature");
    check(CanId::Heartbeat, 1500, "Heartbeat");
}

