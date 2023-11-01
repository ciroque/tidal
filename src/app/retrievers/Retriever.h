//
// Created by Steve Wagner on 9/23/20.
//

#ifndef TIDAL_RETRIEVER_H
#define TIDAL_RETRIEVER_H

#include <cstdint>
#include <string>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/dynamic_body.hpp>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>

class Retriever {
protected:
    std::string Retrieve(std::string host, std::string port, std::string target);
};


#endif //TIDAL_RETRIEVER_H
