#include <display/RenderWindow.h>


int main() {
    // Create the game window with the specified size and title
    //GameWindow gw = GameWindow { 1600,1000, "opengl samples" };
    RenderWindow rw = RenderWindow { 800, 600, "opengl samples" };

    return rw.Run();
}