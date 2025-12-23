#include "rtos/Task.hpp"
#include "rtos/MessageQueue.hpp"
#include "can/CanFrame.hpp"
#include "can/CanIds.hpp"
#include <unordered_map>
#include <chrono>

class Diagnostics : public Task {
public:
    explicit Diagnostics(MessageQueue<CanFrame>&rxQueue);
protected:
    void run() override;
private:
    void processFrame(const CanFrame& frame);
    void checkTimeouts();
    MessageQueue<CanFrame>& m_rxQueue;
    std::unordered_map<uint32_t, std::chrono::steady_clock::time_point> m_lastSeen;
};