#pragma once

#include <string>

#include "Model.hpp"

class Character {

    public:

        std::string image;
        Vector<int> coord;

    public:

        Character(std::string image, const Vector<int>& coord) {
            this->image = image;
            this->coord = coord;
        }

        void SetPosition(const int& x, const int& y) {
            coord.x = x;
            coord.y = y;
        }

        void SetPosition(const Vector<int>& coord) {
            this->coord.x = coord.x;
            this->coord.y = coord.y;
        }

        Vector<int> GetPosition() {
            return this->coord;
        }

        void SetImage(const std::string& image) {
            this->image = image;
        }

};
