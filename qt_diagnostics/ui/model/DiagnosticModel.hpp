#pragma once

#include <QAbstractListModel>

#include "DiagnosticEvent.hpp"

class DiagnosticModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit DiagnosticModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addEvent(const DiagnosticEvent &event);

private:
    QVector<DiagnosticEvent>m_events;
};