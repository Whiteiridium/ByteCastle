#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <memory>

class NetworkModule
{
public:
    NetworkModule() : acceptor(io_context)
    {}

    void start_server(int port);

private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;

    void accept_client_connections();
    void handle_new_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
};