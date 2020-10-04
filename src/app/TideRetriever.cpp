//
// Created by Steve Wagner on 9/23/20.
//

#include <iostream>
#include "TideRetriever.h"

void TideRetriever::Retrieve() {
    std::cout << "TideRetriever::Retrieve" << std::endl;
    std::string res = this->Retriever::Retrieve(host, port, path);
    std::cout << res << std::endl;
}
