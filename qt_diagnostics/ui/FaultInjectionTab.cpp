#include "FaultInjectionTab.hpp"
#include <QPushButton>
#include <QVBoxLayout>

FaultInjectionTab::FaultInjectionTab(QWidget *parent) : QWidget(parent) {
    m_stopAllBtn = new QPushButton("Stop All CAN frames");
    m_wrongValueBtn = new QPushButton("Send Incorrect Values");
    m_wrongDlcBtn = new QPushButton("Send Incorrect DLCs");

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(m_stopAllBtn);
    layout->addWidget(m_wrongValueBtn);
    layout->addWidget(m_wrongDlcBtn);
    layout->addStretch();

    connect(m_stopAllBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::StopAll);});
    connect(m_wrongValueBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::WrongValues);});
    connect(m_wrongDlcBtn, &QPushButton::clicked, this, [=](){emit faultRequested(FaultType::WrongDLC);});
    
}