#include "DiagnosticsTab.hpp"
#include "model/DiagnosticModel.hpp"

#include <QListView>
#include <QVBoxLayout>

DiagnosticsTab::DiagnosticsTab(QWidget *parent) : QWidget(parent) {
    m_model = new DiagnosticModel(this);
    m_listView = new QListView(this);

    m_listView->setModel(m_model);

    m_listView->setSelectionMode(QAbstractItemView::NoSelection);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_listView);

    DiagnosticEvent e1 {
        QDateTime::currentDateTime(),
        DiagnosticSeverity::INFO,
        "Heartbeat receved"
    };
    DiagnosticEvent e2 {
        QDateTime::currentDateTime(),
        DiagnosticSeverity::WARN,
        "Temperature approaching limit"
    };
    DiagnosticEvent e3 {
        QDateTime::currentDateTime(),
        DiagnosticSeverity::ERROR,
        "Engine Speed message Timeout"
    };

    m_model->addEvent(e1);
    m_model->addEvent(e2);
    m_model->addEvent(e3);
}