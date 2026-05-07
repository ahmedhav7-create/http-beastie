#include "utils.hpp"
#include <fstream>
#include <sstream>

namespace beast = boost::beast;
namespace http = beast::http;
using namespace std;

  string read_file(string path) {

    ifstream file(path, ios::in);

    if (!file.is_open()) {
        return "not opened";
    }

    stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

  http::response<http::string_body> handle_request(const http::request<http::string_body>& req) {
  http::response<http::string_body> res;

  res.version(req.version());
  res.keep_alive(false);

  res.set(http::field::server, "http-beastie");
  res.set(http::field::content_type, "text/html");

  if (req.method() == http::verb::get) {
    if (req.target() == "/") {
      res.result(http::status::ok);
      res.body() = "<h1 style=\"text-align: center;\">CSCE 1102</h1>";
      read_file("static/index.html");
    } else {
      res.result(http::status::not_found);
      res.body() = "<h1 style=\"text-align: center;\">404 Not Found</h1>";
    }
  } else {
    res.result(http::status::method_not_allowed);
    res.set(http::field::allow, "GET");
    res.body() = "<h1 style=\"text-align: center;\">405 Method Not Allowed</h1>";
  }

  res.prepare_payload();
  return res;
}
