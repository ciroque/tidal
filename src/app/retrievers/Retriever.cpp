//
// Created by Steve Wagner on 9/23/20.
//

#include "Retriever.h"

#include <iostream>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

std::string Retriever::Retrieve(std::string host, std::string port, std::string target) {
    std::string response = "[]";
    try
    {
        int version = 11;
        beast::error_code ec;

        net::io_context ioc;
        ssl::context ctx(ssl::context::tlsv12_client);

        ctx.set_default_verify_paths();

        ctx.set_verify_mode(ssl::verify_peer);

        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        if(! SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        auto const results = resolver.resolve(host, port);

        beast::get_lowest_layer(stream).connect(results);

        stream.handshake(ssl::stream_base::client);

        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        beast::flat_buffer buffer;

        http::response<http::string_body> res;
        http::read(stream, buffer, res);
        response = res.body();

        stream.shutdown(ec);
        if(ec == net::error::eof)
        {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec = {};
        }
        if(ec) {
            throw beast::system_error{ec};
        }
    }
    catch(boost::system::system_error const &se) {
        std::cerr << host.c_str() << "; " << se.code() << "; " << se.what() << std::endl;
    } catch(std::exception const& e) {
        std::cerr << host.c_str() << "; " << "Error: " << e.what() << std::endl;
    } catch (const std::string& ex) {
        std::cerr << host.c_str() << "; " << "Error string: " << ex << std::endl;
    } catch (...) {
        std::cerr << host.c_str() << "; " << "Some other error " << std::endl;// ...
    }

    return response;
}
