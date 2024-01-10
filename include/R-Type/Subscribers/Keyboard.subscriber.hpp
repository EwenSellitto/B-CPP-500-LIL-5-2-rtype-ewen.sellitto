#include <SFML/Window/Event.hpp>

#include "ECS/EventSubscriber.hpp"
#include "Engine/Events/KeyPressed.event.hpp"
#include "Engine/Events/KeyReleased.event.hpp"
#include "Engine/Systems/Inputs.system.hpp"

namespace Rtype::Subscriber
{
    class KeyboardPressedSubscriber : public virtual ECS::EventSubscriber<KeyPressedEvent>
    {
        public:
            KeyboardPressedSubscriber()           = default;
            ~KeyboardPressedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyPressedEvent &data) override {}

        private:
            std::vector<sf::Keyboard::Key> _keys = {sf::Keyboard::Num0,    sf::Keyboard::Num1,    sf::Keyboard::Num2,
                                                    sf::Keyboard::Num3,    sf::Keyboard::Num4,    sf::Keyboard::Num5,
                                                    sf::Keyboard::Num6,    sf::Keyboard::Num7,    sf::Keyboard::Num8,
                                                    sf::Keyboard::Num9,    sf::Keyboard::Numpad0, sf::Keyboard::Numpad1,
                                                    sf::Keyboard::Numpad2, sf::Keyboard::Numpad3, sf::Keyboard::Numpad4,
                                                    sf::Keyboard::Numpad5, sf::Keyboard::Numpad6, sf::Keyboard::Numpad7,
                                                    sf::Keyboard::Numpad8, sf::Keyboard::Numpad9, sf::Keyboard::Period};
    };

    class KeyboardReleasedSubscriber : public virtual ECS::EventSubscriber<KeyReleasedEvent>
    {
        public:
            KeyboardReleasedSubscriber()           = default;
            ~KeyboardReleasedSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const KeyReleasedEvent &data) override
            {
                std::string                   keyPressed = "";
                Engine::System::InputsSystem *inputSystem =
                    dynamic_cast<Engine::System::InputsSystem *>(WORLD.getSystems()["InputsSystem"].get());
                for (auto key : _keys)
                    if (data.keyEvent.code == key) {
                        if (inputSystem) {
                            if (data.keyEvent.code == sf::Keyboard::Period ||
                                data.keyEvent.code == sf::Keyboard::SemiColon)
                                keyPressed += ".";
                            else if (data.keyEvent.code >= sf::Keyboard::Num0 &&
                                     data.keyEvent.code <= sf::Keyboard::Num9)
                                keyPressed += data.keyEvent.code - sf::Keyboard::Num0 + '0';
                            else if (data.keyEvent.code >= sf::Keyboard::Numpad0 &&
                                     data.keyEvent.code <= sf::Keyboard::Numpad9)
                                keyPressed += data.keyEvent.code - sf::Keyboard::Numpad0 + '0';
                            else if (data.keyEvent.code == sf::Keyboard::Dash)
                                keyPressed += "6";
                            else if (data.keyEvent.code == sf::Keyboard::Quote)
                                keyPressed += "4";

                            if (data.keyEvent.code != sf::Keyboard::BackSpace)
                                inputSystem->changeText(keyPressed);
                            else
                                inputSystem->removeText();
                        }
                    }
            }

        private:
            std::vector<sf::Keyboard::Key> _keys = {
                sf::Keyboard::Num0,     sf::Keyboard::Num1,      sf::Keyboard::Num2,    sf::Keyboard::Num3,
                sf::Keyboard::Num4,     sf::Keyboard::Num5,      sf::Keyboard::Num6,    sf::Keyboard::Num7,
                sf::Keyboard::Num8,     sf::Keyboard::Num9,      sf::Keyboard::Numpad0, sf::Keyboard::Numpad1,
                sf::Keyboard::Numpad2,  sf::Keyboard::Numpad3,   sf::Keyboard::Numpad4, sf::Keyboard::Numpad5,
                sf::Keyboard::Numpad6,  sf::Keyboard::Numpad7,   sf::Keyboard::Numpad8, sf::Keyboard::Numpad9,
                sf::Keyboard::Period,   sf::Keyboard::SemiColon, sf::Keyboard::Quote,   sf::Keyboard::Dash,
                sf::Keyboard::BackSpace};
    };
} // namespace Rtype::Subscriber
