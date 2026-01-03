#include "FaultInjectionTab.hpp"
#include <QPushButton>
#include <QVBoxLayout>

FaultInjectionTab::FaultInjectionTab(QWidget *parent) : QWidget(parent) {
    m_stopAllBtn = new QPushButton("Stop All CAN frames");
    m_wrongValueBtn = new QPushButton("Send Incorrect Values");
    m_wrongDlcBtn = new QPushButton("Send Incorrect DLCs");
    m_resetBtn = new QPushButton("Reset Faults");

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(m_stopAllBtn);
    layout->addWidget(m_wrongValueBtn);
    layout->addWidget(m_wrongDlcBtn);
    layout->addWidget(m_resetBtn);
    layout->addStretch();

    connect(m_stopAllBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::StopAll);});
    connect(m_wrongValueBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::WrongValues);});
    connect(m_wrongDlcBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::WrongDLC);});
    connect(m_resetBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::None);});
    
}