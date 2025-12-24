#include "MainWindow.hpp"
#include "ui/CanMonitorTab.hpp"
#include "ui/DiagnosticsTab.hpp"
#include "ui/FaultInjectionTab.hpp"

#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ECU Diagnostics Tool");
    resize(900, 600);

    m_tabWidget = new QTabWidget(this);

    m_tabWidget->addTab(new CanMonitorTab(this), "CAN Monitor");
    m_tabWidget->addTab(new DiagnosticsTab(this), "Diagnostics");
    m_tabWidget->addTab(new FaultInjectionTab(this), "Fault Injection");

    setCentralWidget(m_tabWidget);

}
