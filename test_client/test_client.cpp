#include <iostream>
#include <boost/asio.hpp>

class NetworkClient {
public:
    NetworkClient(const std::string& host, int port)
        : endpoint(boost::asio::ip::address::from_string(host), port),
          socket(io_context)
    {}

    void connect() {
        try {
            socket.connect(endpoint);
            std::cout << "Connected to server " << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;

            communicate();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;

    void communicate() {
        try {
            while (true) {
                std::string message;
                std::cout << "Enter message to send (type 'quit' to exit): ";
                std::getline(std::cin, message);

                if (message == "quit") break;

                boost::asio::write(socket, boost::asio::buffer(message + "\n"));

                std::vector<char> buffer(1024);
                boost::system::error_code error;
                size_t bytes_received = socket.read_some(boost::asio::buffer(buffer), error);

                if (error == boost::asio::error::eof) {
                    std::cout << "Connection closed by server." << std::endl;
                    break;
                } else if (error) {
                    throw boost::system::system_error(error);
                }

                std::string response(buffer.begin(), buffer.begin() + bytes_received);
                std::cout << "Server response: " << response << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Communication error: " << e.what() << std::endl;
        }
    }
};

int main() 
{
    const std::string host = "127.0.0.1"; // Локальный сервер
    const int port = 12345; // Задайте порт сервера

    NetworkClient client(host, port);
    client.connect();

    return 0;
}
