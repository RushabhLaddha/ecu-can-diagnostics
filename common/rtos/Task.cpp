#include "Task.hpp"
#include <iostream>

Task::Task(const std::string& taskName) : m_taskName(taskName) {

}

Task::~Task(){
    stop();
}

void Task::start() {
    if(m_running) {
        return;
    }
    m_running.store(true);
    m_thread = std::thread(&Task::threadEntry, this);
}

void Task::stop() {
    if(!m_running) {
        return;
    }
    m_running.store(false);
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

bool Task::isRunning() const {
    return m_running.load();
}

void Task::threadEntry() {
    std::cout<<"Task "<<m_taskName<<" started"<<std::endl;
    run();
    std::cout<<"Task "<<m_taskName<<" ended"<<std::endl;
}
