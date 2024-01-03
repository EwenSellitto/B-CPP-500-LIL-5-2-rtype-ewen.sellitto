#include <unordered_map>
#include <vector>
#include <SFML/Network.hpp>

struct IpAddressHash {
    std::size_t operator()(const sf::IpAddress& ip) const {
        return std::hash<std::string>()(ip.toString());
    }
};

class Server {
    public:
        Server() = default;
        Server(unsigned short port);
        void run();

    private:

        void receivePackets();
        void processPacket(const sf::IpAddress& sender, unsigned short port, const std::vector<char>& packet);
        void sendUpdates();

        sf::UdpSocket socket;
        std::unordered_map<sf::IpAddress, unsigned short, IpAddressHash> clients;
        unsigned short port;
        bool running = true;
};
