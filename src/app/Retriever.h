//
// Created by Steve Wagner on 9/23/20.
//

#ifndef TIDAL_RETRIEVER_H
#define TIDAL_RETRIEVER_H

#include <string>

class Retriever {
protected:
    unsigned int Retrieve(std::string host, std::string port, std::string target);
};


#endif //TIDAL_RETRIEVER_H
