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
}

DiagnosticModel* DiagnosticsTab::getModel() {
    return m_model;
}