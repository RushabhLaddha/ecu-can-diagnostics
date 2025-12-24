#pragma once

#include <QMainWindow>

class QTabWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT // Must needed macro for all the classes derived from QObject class to enable Signal/Slots etc.
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    QTabWidget *m_tabWidget;
};