#pragma once

#include <QString>
#include <QDateTime>
#include<QMetaType>

enum class DiagnosticSeverity {
    INFO,
    WARN,
    ERROR
};

struct DiagnosticEvent {
    QDateTime timestamp;
    DiagnosticSeverity severity;
    QString message;
};

Q_DECLARE_METATYPE(DiagnosticEvent)