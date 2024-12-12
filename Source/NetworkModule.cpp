#include "../Headers/NetworkModule.h"

void NetworkModule::start_server(int port)
{
    try
    {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), static_cast<unsigned short>(port));
        acceptor.open(endpoint.protocol());
        acceptor.bind(endpoint);
        acceptor.listen();

        std::cout << "Server started on port" << port << std::endl;

        accept_client_connections();

        io_context.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void NetworkModule::accept_client_connections()
{
    std::shared_ptr<boost::asio::ip::tcp::socket> socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
    acceptor.async_accept(
        *socket, 
        [this, socket](boost::system::error_code ec)
        {
            if(!ec)
            {
                handle_new_connection(socket);
            }
            else
            {
                std::cerr << "Error connecting client: " << ec.message() << std::endl;
            }
            accept_client_connections();
        }
    );
}

void NetworkModule::handle_new_connection(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    try
    {
        std::cout << "new connection from " 
                  << socket->remote_endpoint().address().to_string() 
                  << ":" << socket->remote_endpoint().port() << std::endl;

        std::vector<char> buffer(1024);
        boost::system::error_code read_ec;
        size_t bytes_transferred = socket->read_some(boost::asio::buffer(buffer), read_ec);
        if(!read_ec)
        {
            std::string received_data(buffer.begin(), buffer.begin() + bytes_transferred);
            std::cout << "Received data: " << received_data << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}