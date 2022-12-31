#pragma once

#include <iostream>

class Event {
    
    private:

        std::string engine;
        int key;

    public:

        Event() {
            engine = "stty";
        }

        void Init() {
            std::string cmd = engine + " raw -echo";
            system(cmd.c_str());
        }

        int OnKeyPress() {
            Init();
            key = std::getc(stdin);
            Stop();
            return key;
        }

        void Stop() {
            std::string cmd = engine + " echo cooked";
            system(cmd.c_str());
        }

};
