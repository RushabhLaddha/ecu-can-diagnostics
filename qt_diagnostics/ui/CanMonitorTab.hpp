#pragma once

#include <QWidget>

class QTableView;
class CanTableModel;

class CanMonitorTab : public QWidget {
    Q_OBJECT
public:
    explicit CanMonitorTab(QWidget *parent = nullptr);

    CanTableModel* getModel();
private slots:
    void scrollToBottom();
private:
    QTableView* m_tableView;
    CanTableModel* m_model;
};