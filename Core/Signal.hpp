#ifndef SIGNAL_H
#define SIGNAL_H

#include <queue>

namespace SE
{
    struct Signal
    {
        typedef std::size_t SignalID;
    };

    class SignalQueue
    {
    public:
        void emit(const Signal::SignalID& id)
        {
            m_queue.push(id);
            m_queue.pop();
        }

        std::queue<Signal::SignalID>& getQueue() { return m_queue; }

    private:
        std::queue<Signal::SignalID> m_queue;
    };
}

#endif // SIGNAL_H
