

#include "Engine/Systems/Server.system.hpp"
#include "r-type.hpp"

using boost::asio::ip::udp;
using namespace Engine::System;

void Server::configure([[maybe_unused]] ECS::World &world)
{
    this->StartReceive();
    try {
        this->io_context_.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return;
}

void Server::StartReceive()
{
    this->socket_.async_receive_from(boost::asio::buffer(this->recvbuffer), remote_endpoint_,
                                     boost::bind(&Server::handle_receive, this, boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
}

void Server::handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::cout << "Client: " << std::string(this->recvbuffer.data(), bytes_transferred) << std::endl;
        std::string msg = "Hello to you too!!!\n";
        socket_.async_send_to(boost::asio::buffer(msg), remote_endpoint_,
                              boost::bind(&Server::handle_send, this, msg, boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred));
        this->StartReceive();
    }
}

void Server::handle_send(std::string /*message*/, const boost::system::error_code & /*error*/,
                         std::size_t /*bytes_transferred*/)
{
}

void Server::run(std::string message)
{
    std::cout << "server receive" << std::endl;
    std::cout << message << std::endl;
    return;
}

void Server::unconfigure()
{
    close(this->socket_.native_handle());
    return;
}

void Server::tick()
{
    std::cout << "server receive" << std::endl;
}

Server::~Server()
{
    this->unconfigure();
}