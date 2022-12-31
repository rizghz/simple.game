#pragma once

#include <string>
#include <functional>

#include "Model.hpp"

class Buffer {

    public:

        std::string content[256][256];
        Vector<int> dimension;

    public:

        Buffer() = default;

        Buffer(const int& height, const int& width) {
            dimension = {width * 5 + 1, height * 2 + 1};
        }

        void Set(std::function<void (int, int, Vector<int>)> rule) {
            for (int y = 0; y < dimension.y; y++) {
                for (int x = 0; x < dimension.x; x++) {
                    rule(x, y, dimension);
                }
            }
        }

        void Fill(std::string image, Vector<int> coord) {
            content[coord.y][coord.x] = image;
        }

        std::string Get(Vector<int> coord) {
            return content[coord.y][coord.x];
        }

};

std::ostream& operator << (std::ostream& out, const Buffer& buffer) {
    out << "\x1b[H";
    for (int y = 0; y < buffer.dimension.y; y++) {
        for (int x = 0; x < buffer.dimension.x; x++) {
            out << buffer.content[y][x];
        }
        out << '\n';
    }
    return out;
}
