#include "display/game_window.hpp"

int main() {
    // Create the game window with the specified size and title
    GameWindow gw = GameWindow { 1600,1000, "opengl samples" };

    return gw.Run();
}