#include "Event.hpp"
#include "Game.hpp"

enum Action {
    Up    = 65,
    Down  = 66,
    Right = 67,
    Left  = 68,
    Close = 99,
    Auto  = 97,
};

int main(int argc, char const *argv[]) {
    Game game = Game(4, 13);
    game.Init();
    bool AutoMode = false;
    while (true) {
        game.Render();
        if (not AutoMode) {
            switch (Event().OnKeyPress()) {
                case Action::Auto: {
                    AutoMode = true;
                    goto pindah;
                };
                case Action::Close: {
                    std::cout << "\e[?25h";
                    return 0;
                };
                case Action::Right: {
                    if (game.GetPlayerCoord().y != 3)
                        game.MovePlayer(1);
                    game.Check();
                    game.DeleteObstacle(3);
                    continue;
                }
                case Action::Left: {
                    if (game.GetPlayerCoord().y != 0)
                        game.MovePlayer(-1);
                    game.Check();
                    game.DeleteObstacle(3);
                    continue;
                }
                case Action::Up: {
                    game.MoveObstacle();
                    break;
                }
                default: continue;
            }
        } else {
            pindah:
            game.Automatic();
        }
        game.Check();
        game.CreateObstacle(3);
        game.DeleteObstacle(3);
    }
    return 0;
}
