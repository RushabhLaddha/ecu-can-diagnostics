#pragma once

#include <QWidget>
#include "qt_types/FaultTypeQt.hpp"

class QPushButton;

class FaultInjectionTab : public QWidget {
    Q_OBJECT
public:
    explicit FaultInjectionTab(QWidget *parent = nullptr);

signals:
    void faultRequested(FaultType fault);

private:
    QPushButton* m_stopAllBtn;
    QPushButton* m_wrongValueBtn;
    QPushButton* m_wrongDlcBtn;
};