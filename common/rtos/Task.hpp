#pragma once
#include<atomic>
#include<thread>
#include<string>

class Task {
public:
    explicit Task(const std::string& taskName);
    virtual ~Task();
    void start();
    void stop();

    Task(const Task&) = delete;
    Task& operator= (const Task&) = delete;

protected:
    virtual void run() = 0;
    bool isRunning() const;

private:
    void threadEntry();

    std::string m_taskName;
    std::thread m_thread;
    std::atomic<bool>m_running{false};
};