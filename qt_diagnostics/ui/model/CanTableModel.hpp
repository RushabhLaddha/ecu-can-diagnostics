#pragma once

#include <QAbstractTableModel>
#include "CanMessage.hpp"

class CanTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit CanTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // QVariant - A box that can hold one value of many possible types, and remembers what type it holds
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addMessage(const CanMessage &msg);

private:
    QVector<CanMessage>m_messages;
};