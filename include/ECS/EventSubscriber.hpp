#include <string>

namespace ECS {
class BaseEventSubscriber
{
    public:
        virtual ~BaseEventSubscriber() = 0;
};

template <typename T> class EventSubscriber : public BaseEventSubscriber
{
        virtual ~EventSubscriber()                                     = 0;
        virtual void receiveEvent(const std::string &name, void *data) = 0;
};
} // namespace ECS
