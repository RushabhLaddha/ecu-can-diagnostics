#pragma once

#include <QMainWindow>

class QTabWidget;
class CanMonitorTab;
class DiagnosticsTab;
class CanBackendWorker;
class QDiagnostics;
class FaultInjectionTab;

class MainWindow : public QMainWindow {
    Q_OBJECT // Must needed macro for all the classes derived from QObject class to enable Signal/Slots etc.
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    QTabWidget *m_tabWidget;
    CanMonitorTab *m_CanMonitorTab;
    DiagnosticsTab *m_DiagnosticsTab;
    FaultInjectionTab *m_FaultInjectionTab;
    QThread *m_workerThread;
    CanBackendWorker *m_worker;
    QDiagnostics *m_diag;
};