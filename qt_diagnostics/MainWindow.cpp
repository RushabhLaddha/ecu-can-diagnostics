#include "MainWindow.hpp"
#include "ui/CanMonitorTab.hpp"
#include "ui/DiagnosticsTab.hpp"
#include "ui/FaultInjectionTab.hpp"

#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ECU Diagnostics Tool");
    resize(900, 600);

    // MainWindow is a QMainWindow that owns a QTabWidget as its central widget, and each tab is a child QWidget managed by Qt’s parent–child ownership system.
    m_tabWidget = new QTabWidget(this);

    m_tabWidget->addTab(new CanMonitorTab(this), "CAN Monitor");
    m_tabWidget->addTab(new DiagnosticsTab(this), "Diagnostics");
    m_tabWidget->addTab(new FaultInjectionTab(this), "Fault Injection");

    setCentralWidget(m_tabWidget); // Only one central widget is allowed

}
