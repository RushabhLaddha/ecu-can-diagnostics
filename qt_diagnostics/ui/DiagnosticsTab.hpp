#pragma once

#include <QWidget>

class QListView;
class DiagnosticModel;

class DiagnosticsTab : public QWidget {
    Q_OBJECT
public:
    explicit DiagnosticsTab(QWidget *parent = nullptr);

    DiagnosticModel* getModel();
private slots:
    void scrollToBottom();
private:
    QListView* m_listView;
    DiagnosticModel* m_model;
};