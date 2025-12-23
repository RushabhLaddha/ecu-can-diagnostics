#pragma once

#include<queue>
#include<mutex>
#include<condition_variable>

template<typename T>

class MessageQueue {
public:
    void push(const T& item) {
        {
            std::lock_guard<std::mutex>lock(m_mutex);
            m_queue.push(item);
        }
        m_cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex>lock(m_mutex);
        m_cv.wait(lock, [this] { return !m_queue.empty(); });
        T item = m_queue.front();
        m_queue.pop();
        return item;
    }

    bool pop_for(T& item, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex>lock(m_mutex);
        if(!m_cv.wait_for(lock, timeout, [this] { return !m_queue.empty(); })) {
            return false;
        }
        item = m_queue.front();
        m_queue.pop();
        return true;
    }

private:
    std::queue<T>m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};