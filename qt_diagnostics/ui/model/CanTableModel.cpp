#include "CanTableModel.hpp"
#include <QBrush>

CanTableModel::CanTableModel(QObject *parent) : QAbstractTableModel(parent) {

}

int CanTableModel::rowCount(const QModelIndex &) const {
    return m_messages.size();
}

int CanTableModel::columnCount(const QModelIndex &) const {
    return 4;
}

QVariant CanTableModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return {};
    }

    const auto &msg = m_messages.at(index.row());  
    if(role == Qt::DisplayRole) {
        switch(index.column()) {
            case 0: return QString("0x%1").arg(msg.id, 0, 16);
            case 1: return msg.dlc;
            case 2: return msg.data;
            case 3: return msg.timestamp.toString("hh:mm:ss.zzz");
            default: return {};
        }
    }

    if(role == Qt::BackgroundRole) {
        if(!msg.valid) {
            return QBrush(Qt::red);
        }
    }

    return {};
}

QVariant CanTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
            case 0: return "CAN ID";
            case 1: return "DLC";
            case 2: return "Data";
            case 3: return "TimeStamp";
        }
    }
    return {};
}

void CanTableModel::addMessage(const CanMessage &msg) {
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size()); // Tells the QT/UI that the layout is about to change
    m_messages.append(msg);
    endInsertRows();
}