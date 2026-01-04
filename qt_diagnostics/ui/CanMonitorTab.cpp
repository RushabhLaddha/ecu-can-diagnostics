#include "CanMonitorTab.hpp"
#include "model/CanTableModel.hpp"

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QScrollBar>

CanMonitorTab::CanMonitorTab(QWidget *parent) : QWidget(parent) {

    m_model = new CanTableModel(this); // Backend - Gives answers to the QTableView without letting it know how the data is stored
    m_tableView = new QTableView(this); // UI - Asks questions to the model to print the data

    m_tableView->setModel(m_model); // Connects model and view. View internally calls the functions which we defined in the CanTableModel class known as inversion of control

    connect(m_model, &QAbstractItemModel::rowsInserted, this, &CanMonitorTab::scrollToBottom);

    m_tableView->horizontalHeader()->setStretchLastSection(true); // Last column expands to fill remaining space

    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Clicking any cell selects the entire row

    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disables in-place editing preventing accidental modification of the data presented on the screen

    auto *layout = new QVBoxLayout(this); // Creates a vertical layout and becomes child of CanMonitorTab
    layout->addWidget(m_tableView); // TableView becomes the child of the vertical layout
}

CanTableModel* CanMonitorTab::getModel() {
    return m_model;
}

void CanMonitorTab::scrollToBottom() {
    auto *bar = m_tableView->verticalScrollBar();
    if(bar->value() == bar->maximum()) {
        m_tableView->scrollToBottom();
    }
}