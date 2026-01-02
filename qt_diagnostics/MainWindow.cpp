#include "MainWindow.hpp"
#include "ui/CanMonitorTab.hpp"
#include "ui/DiagnosticsTab.hpp"
#include "ui/FaultInjectionTab.hpp"
#include "ui/model/CanTableModel.hpp"
#include "ui/model/DiagnosticModel.hpp"

#include "backend/CanBackendWorker.hpp"
#include "diagnostic/QDiagnostics.hpp"

#include <QTabWidget>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ECU Diagnostics Tool");
    resize(900, 600);

    // MainWindow is a QMainWindow that owns a QTabWidget as its central widget, and each tab is a child QWidget managed by Qt’s parent–child ownership system.
    m_tabWidget = new QTabWidget(this);
    m_CanMonitorTab = new CanMonitorTab(this);
    m_DiagnosticsTab = new DiagnosticsTab(this);

    m_tabWidget->addTab(m_CanMonitorTab, "CAN Monitor");
    m_tabWidget->addTab(m_DiagnosticsTab, "Diagnostics");
    m_tabWidget->addTab(new FaultInjectionTab(this), "Fault Injection");

    m_workerThread = new QThread(this);
    m_worker = new CanBackendWorker();
    m_diag = new QDiagnostics(this);

    m_worker->moveToThread(m_workerThread);

    // connect(sender, signal, receiver, slot) : establishes a type-safe, thread-aware communication channel between objects, allowing Qt to deliver events safely across threads using signals and slots.

    connect(m_workerThread, &QThread::started, m_worker, &CanBackendWorker::start);

    connect(this, &QObject::destroyed, m_worker, &CanBackendWorker::stop);

    auto *canMonitorModel = m_CanMonitorTab->getModel();
    connect(m_worker, &CanBackendWorker::canMessageReceived, canMonitorModel, &CanTableModel::addMessage);

    auto *diagModel = m_DiagnosticsTab->getModel();
    connect(m_worker, &CanBackendWorker::diagEventRaised, diagModel, &DiagnosticModel::addEvent);

    connect(m_diag, &QDiagnostics::diagEventRaised, diagModel, &DiagnosticModel::addEvent);

    connect(m_worker, &CanBackendWorker::canMessageReceived, m_diag, &QDiagnostics::onCanMessageReceived);

    m_workerThread->start();

    setCentralWidget(m_tabWidget); // Only one central widget is allowed

}

MainWindow::~MainWindow() {
    if(m_worker) {
        m_worker->stop();
    }

    if(m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait();
    }
}
