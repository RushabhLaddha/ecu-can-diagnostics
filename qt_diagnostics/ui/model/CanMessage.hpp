#pragma once

#include <QString>
#include <QDateTime>
#include <cstdint>
#include <QMetaType>

struct CanMessage {
    uint32_t id;
    int dlc;
    QString data;
    QByteArray rawData;
    QDateTime timestamp;
};

Q_DECLARE_METATYPE(CanMessage)