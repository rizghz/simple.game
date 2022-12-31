#pragma once

#include <iostream>

#include "Model.hpp"
#include "Buffer.hpp"
#include "Character.hpp"

class Board {

    public:

        Buffer frame;
        Vector<int> coord[250][256];

    public:

        Board(const int& row, const int& col) {
            frame = Buffer(row, col);
            SetCoord(row, col);
        }

        Board& Create() {
            frame.Set([&](int x, int y, Vector<int> edge){
                if (y == 0)
                    // frame.content[y][x] = (x == 0) ? "┌" : (x == edge.x - 1) ? "┐" : (x % 5 == 0) ? "┬" : "─";
                    frame.content[y][x] = (x == 0) ? "┌" : (x == edge.x - 1) ? "┐" : "─";
                if (y > 0 and y % 2 == 1)
                    // frame.content[y][x] = (x == 0 or x == edge.x - 1 or x % 5 == 0) ? "│" : " ";
                    // frame.content[y][x] = (x == 0 or x == edge.x - 1) ? "│" : " ";
                    // frame.content[y][x] = (x == 0 or x == edge.x - 1) ? "│" : (x % 5 == 0) ? "" : " ";
                    // frame.content[y][x] = (x == 0 or x == edge.x - 1) ? "│" : (x % 5 == 0) ? "\x1b[38;2;255;255;85m·\x1b[0m" : " ";
                    frame.content[y][x] = (x == 0 or x == edge.x - 1) ? "│" : (x % 5 == 0) ? "\e[90m·\e[0m" : " ";
                if (y > 0 and y % 2 == 0)
                    // frame.content[y][x] = (x == 0) ? "├" : (x == edge.x - 1) ? "┤" : (x % 5 == 0) ? "┼" : "─";
                    frame.content[y][x] = (x == 0) ? "├" : (x == edge.x - 1) ? "┤" : "─";
                if (y == edge.y - 1)
                    // frame.content[y][x] = (x == 0) ? "└" : (x == edge.x - 1) ? "┘" : (x % 5 == 0) ? "┴" : "─";
                    frame.content[y][x] = (x == 0) ? "└" : (x == edge.x - 1) ? "┘" : "─";
            });
            return *this;
        }

        void SetCoord(const int& row, const int& col) {
            for (int y = 0, r = 1; y < row; y++) {
                for (int x = 0, c = 2; x < col; x++) {
                    coord[y][x] = Vector<int>{c, r};
                    c += 5;
                }
                r += 2;
            }
        }

        Vector<int> TransformCoord(const Vector<int>& c) {
            return coord[c.y][c.x];
        }

        void AddObject(const Character& chara) {
            frame.Fill(chara.image, TransformCoord(chara.coord));
        }

        void FlushObject(Character& chara, std::string image) {
            frame.Fill(image, TransformCoord(chara.coord));
        }

        void MoveObject(Character& chara, Vector<int> step) {
            if (frame.Get(Board::TransformCoord(chara.coord)) == chara.image) {
                Board::FlushObject(chara, " ");
            }
            frame.Fill(chara.image, Board::TransformCoord(step));
            chara.SetPosition(step);
        }

        bool TileEmpty(Vector<int> c) {
            if (frame.Get(Board::TransformCoord(c)) == " ") {
                return true;
            }
            return false;
        }

        Buffer& GetFrame() {
            return Board::frame;
        }

};
