#include "SimpleRequestHandler.hpp"

Softadastra::SimpleRequestHandler::SimpleRequestHandler(std::function<void(const http::request<http::string_body> &, http::response<http::string_body> &)> handler)
    : handler_(std::move(handler)) {}

void Softadastra::SimpleRequestHandler::handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res)
{
    handler_(req, res);
}
