#pragma once

#include <QString>
#include <QDateTime>
#include <cstdint>

struct CanMessage {
    uint32_t id;
    int dlc;
    QString data;
    QDateTime timestamp;
};