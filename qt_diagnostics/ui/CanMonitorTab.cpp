#include "CanMonitorTab.hpp"
#include "model/CanTableModel.hpp"

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>

CanMonitorTab::CanMonitorTab(QWidget *parent) : QWidget(parent) {

    m_model = new CanTableModel(this); // Backend - Gives answers to the QTableView without letting it know how the data is stored
    m_tableView = new QTableView(this); // UI - Asks questions to the model to print the data

    m_tableView->setModel(m_model); // Connects model and view. View internally calls the functions which we defined in the CanTableModel class known as inversion of control

    m_tableView->horizontalHeader()->setStretchLastSection(true); // Last column expands to fill remaining space

    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Clicking any cell selects the entire row

    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disables in-place editing preventing accidental modification of the data presented on the screen

    auto *layout = new QVBoxLayout(this); // Creates a vertical layout and becomes child of CanMonitorTab
    layout->addWidget(m_tableView); // TableView becomes the child of the vertical layout

    // Dummy data (for now)
    CanMessage msg;
    msg.id = 0x101;
    msg.dlc = 2;
    msg.data = "DC 05";
    msg.timestamp = QDateTime::currentDateTime();

    m_model->addMessage(msg);
}