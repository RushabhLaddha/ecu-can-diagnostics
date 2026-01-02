#pragma once

#include <QObject>
#include <QTimer>
#include <unordered_map>
#include "ui/model/CanMessage.hpp"
#include "ui/model/DiagnosticEvent.hpp"
#include "can/CanIds.hpp"

class QDiagnostics : public QObject {
    Q_OBJECT

public:
    explicit QDiagnostics(QObject* parent = nullptr);

public slots:
    void onCanMessageReceived(const CanMessage &msg);
    
signals:
    void diagEventRaised(const DiagnosticEvent &event);

private slots:
    void checkTimeout();

private:
    std::unordered_map<uint32_t, QDateTime> m_lastSeen;
    QTimer m_timer;

    void checkRanges(const CanMessage &msg);
};