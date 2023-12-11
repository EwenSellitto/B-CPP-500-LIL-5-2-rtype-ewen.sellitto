/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** EventSubscriber.hpp
*/

#include <string>

namespace ECS {

/**
 * @class BaseEventSubscriber
 * @brief Abstract base class for event subscribers in an ECS framework.
 *
 * This class provides the interface for any event subscriber that can
 * listen to and respond to events within the ECS.
 */
class BaseEventSubscriber
{
    public:
        /**
         * @brief Virtual destructor for BaseEventSubscriber, defined as pure virtual (0).
         */
        virtual ~BaseEventSubscriber() = 0;

        /**
         * @brief Receive and process an event.
         *
         * @param name The name of the event.
         * @param data A pointer to the event data.
         */
        virtual void receiveEvent(const std::string &name, void *data) = 0;
};

/**
 * @class EventSubscriber
 * @brief Template class for event subscribers specialized to certain event types.
 *
 * @tparam T The type of the event data that this subscriber is interested in.
 */
template <typename T> class EventSubscriber : public BaseEventSubscriber
{
    public:
        /**
         * @brief Virtual destructor for EventSubscriber, defined as pure virtual (0).
         */
        virtual ~EventSubscriber() = 0;

        /**
         * @brief Receive and process an event.
         *
         * @param name The name of the event.
         * @param data A pointer to the event data, expected to be of type T.
         *
         * @warning This method can cause infinite recursion if its broadcasting an event of type T or
         * it broadcast an event of type T and another subscriber is also subscribed to that event.
         */
        virtual void receiveEvent(const std::string &name, void *data) = 0;
};

} // namespace ECS
