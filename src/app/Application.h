//
// Created by Steve Wagner on 9/20/20.
//

#ifndef TIDAL_APPLICATION_H
#define TIDAL_APPLICATION_H

#include <lunar.h>

class Application {
public:
    Application();
    ~Application();
    void Run();

private:
    Lunar* lunar;
};


#endif //TIDAL_APPLICATION_H
