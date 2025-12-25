#include "DiagnosticModel.hpp"

DiagnosticModel::DiagnosticModel(QObject *parent) : QAbstractListModel(parent) {

}

int DiagnosticModel::rowCount(const QModelIndex &) const {
    return m_events.size();
}

QVariant DiagnosticModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return {};
    }

    if(role == Qt::DisplayRole) {
        const auto &event = m_events.at(index.row());

        QString severity {};
        switch(event.severity) {
            case DiagnosticSeverity::ERROR : severity = "[ERROR]"; break;
            case DiagnosticSeverity::INFO : severity  = "[INFO ]"; break;
            case DiagnosticSeverity::WARN : severity  = "[WARN ]"; break;
        }
        return QString("%1 %2 %3")
                .arg(event.timestamp.toString("hh:mm:ss"))
                .arg(severity)
                .arg(event.message);
    }

    return {};
}

void DiagnosticModel::addEvent(const DiagnosticEvent& event) {
    beginInsertRows(QModelIndex(), m_events.size(), m_events.size());
    m_events.append(event);
    endInsertRows();
} 

