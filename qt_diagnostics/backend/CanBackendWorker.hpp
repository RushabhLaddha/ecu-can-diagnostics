#pragma once

#include <QObject>
#include <atomic>
#include <memory>
#include "ui/model/CanMessage.hpp"
#include "ui/model/DiagnosticEvent.hpp"
#include "can/CanFrame.hpp"
#include "can/SocketCanDriver.hpp"

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
    std::atomic<bool> m_running {false};
    std::unique_ptr<SocketCanDriver> m_driver;

    void processFrame(const CanFrame &frame);
};