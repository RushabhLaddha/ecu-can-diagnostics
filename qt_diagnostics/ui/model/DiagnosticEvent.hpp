#pragma once

#include <QString>
#include <QDateTime>

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