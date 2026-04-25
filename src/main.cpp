#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <string>

#include "utils.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
  net::io_context ioc;
  tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

  std::cout << "Listening on http://localhost:8080\n";

  while (true) {
    try {
      tcp::socket socket(ioc);
      acceptor.accept(socket);

      beast::flat_buffer buf;
      http::request<http::string_body> req;
      http::read(socket, buf, req);

      auto res = handle_request(req);
      http::write(socket, res);

      socket.shutdown(tcp::socket::shutdown_send);
    } catch (const beast::system_error& e) {
      std::cerr << "Error: " << e.what() << '\n';
    }
  }
}
