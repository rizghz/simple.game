#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <thread>
#include <list>
#include <vector>
#include <map>

#include "Character.hpp"
#include "Board.hpp"

std::map<std::string, std::vector<std::string>> icons {
    {"player",   {"", "", "", "", "", ""}},
    {"obstacle", {"", "", "", "", "", "", "", "", "", "", "", "", ""}},
    {"enemy",    {"", "", ""}},
};

class Game {

    private:

        Board *board;
        std::list<Character> obstacle;
        Character *player;

        int pass = 0;
        int counter = 0;

    public:

        Game(const int& row, const int& col);
       ~Game();
        void Init();
        void Status();
        void Render();
        void CreateObstacle(const int& n);
        void DeleteObstacle(const int& n);
        void MoveObstacle();
        void MovePlayer(const int& y);
        Vector<int> GetPlayerCoord();
        bool Collision();
        int GetRandomNumber();
        void Check();
        int Algorithm(int a, int b, int pos);
        void Wait(int delay);
        void Automatic();

};

Game::Game(const int& row, const int& col) {
    board = new Board(row, col);
    player = new Character("\e[96m" + icons["player"][GetRandomNumber() % 6] + "\e[0m", {2, GetRandomNumber() % 4});
}

Game::~Game() {
    delete player;
    delete board;
}

inline void Game::Init() {
    std::cout << "\e[2J\e[?25l";
    board->Create();
    board->AddObject(*player);
    for (int i = 0; i < 4; i++) {
        board->AddObject(Character("\e[31m" + icons["enemy"][GetRandomNumber() % 3] + "\e[0m", {0, i}));
    }
}

inline void Game::Status() {
    std::cout << "   " << "\e[3m" << this->pass << " poin\e[0m" << std::endl;;
}

inline void Game::Render() {
    std::cout << board->GetFrame();
    Status();
}

inline void Game::CreateObstacle(const int& n) {
    if (counter % 5 == 0) {
        for (int i = 0; i < n; i++) {
            Vector<int> coord = {12, GetRandomNumber() % 4};
            if (board->TileEmpty(coord)) {
                obstacle.push_back(Character(icons["obstacle"][GetRandomNumber() % 13], coord));
                board->AddObject(obstacle.back());
                // Render();
            }
        }
        // Render();
    }
    counter++;
}

inline void Game::DeleteObstacle(const int& n) {
    bool isDeleted = false;
    for (int i = 0; i < n; i++) {
        if (obstacle.front().coord.x == 0) {
            isDeleted = true;
            board->FlushObject(obstacle.front(), "\e[31m" + icons["enemy"][GetRandomNumber() % 3] + "\e[0m");
            obstacle.pop_front();
        }
    }
    if (isDeleted) {
        pass++;
    }
}

inline void Game::MoveObstacle() {
    std::for_each(obstacle.begin(), obstacle.end(), [&](Character& obs){
        board->MoveObject(obs, {obs.coord.x - 1, obs.coord.y});
    });
    DeleteObstacle(3);
}

inline void Game::MovePlayer(const int& y) {
    board->MoveObject(*player, {player->coord.x, player->coord.y + y});
    MoveObstacle();
    CreateObstacle(3);
}

inline Vector<int> Game::GetPlayerCoord() {
    return player->coord;
}

inline bool Game::Collision() {
    bool isCollision = false;
    for (auto &&obs : obstacle) {
        if (player->coord == obs.coord) {
            isCollision = true;
        }
    }
    return isCollision;
}

int Game::GetRandomNumber() {
    char number;
    std::ifstream("/dev/urandom", std::ios::binary).read(&number, 1);
    return abs(int(number));
}

inline void Game::Check() {
    if (Collision()) {
        board->FlushObject(*player, "\e[5m\e[0m");
        Render();
        std::cout << "   \e[3mSelamat kamu gagal menyelesaikan permainan ini.\e[0m   ";
        std::cin.get();
        system("clear");
        std::cout << "\e[?25h";
        exit(0);
    }
    if (pass == 100) {
        board->FlushObject(*player, "\e[5m" + player->image + "\e[0m");
        Render();
        std::cout << "\r";
        std::cout << "   \e[3mSelamat anda telah menyelesaikan permainan ini.\e[0m   ";
        std::cin.get();
        system("clear");
        std::cout << "\e[?25h";
        exit(0);
    }
}

int Game::Algorithm(int a, int b, int pos) {
    int k[b + 1], sum = 0;
    int mid = (a + b) / 2;
    for (int i = a; i <= b; i++) {
        k[i] = not board->TileEmpty({pos, i});
        sum += k[i];
    }
    if (a + b == 3 and sum == 0) {
        return player->coord.y;
    }
    if (b - a == 0) {
        return b;
    }
    if (k[a] + k[mid] <= k[mid + 1] + k[b]) {
        return Game::Algorithm(a, mid, pos);
    }
    return Game::Algorithm(mid + 1, b, pos);
}

void Game::Wait(int delay) {
    std::this_thread::sleep_for(std::chrono::microseconds(delay));
}

void Game::Automatic() {
    std::cout << "   \e[3mMode otomatis aktif\e[0m";
    int path = Game::Algorithm(0, 3, 6);
    while (player->coord.y != path) {
        int step = (path > player->coord.y) ? 1 : -1;
        MovePlayer(step);
        Game::Wait(300000);
        Render();
    }
    MoveObstacle();
    Game::Wait(300000);
    Check();
}
