#include "rtos/Task.hpp"
#include "can/ICanDriver.hpp"
#include "rtos/MessageQueue.hpp"

#include <memory>

class CanRx : public Task{
public:
    explicit CanRx(std::shared_ptr<ICanDriver> driver, MessageQueue<CanFrame>&rxQueue);
    void run() override;

private:
    std::shared_ptr<ICanDriver>m_driver;
    MessageQueue<CanFrame>& m_rxQueue;
};