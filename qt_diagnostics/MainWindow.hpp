#pragma once

#include <QMainWindow>

class QTabWidget;
class CanMonitorTab;
class DiagnosticsTab;
class CanBackendWorker;

class MainWindow : public QMainWindow {
    Q_OBJECT // Must needed macro for all the classes derived from QObject class to enable Signal/Slots etc.
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    QTabWidget *m_tabWidget;
    CanMonitorTab *m_CanMonitorTab;
    DiagnosticsTab *m_DiagnosticsTab;
    QThread *m_workerThread;
    CanBackendWorker *m_worker;
};