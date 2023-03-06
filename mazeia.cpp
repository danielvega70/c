#include <iostream>
#include <SDL.h> 
#include <vector>
#include <map>

// Set up window dimensions and colors 
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 600;
const int FPS = 30;
const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color GREEN = { 0, 255, 0, 255 };
const SDL_Color BLUE = { 0, 0, 255, 255 };
const SDL_Color YELLOW = { 255, 255, 0, 255 };

// Set up maze variables
int x = 0;
int y = 0;
int w = 20;
std::vector<std::pair<int, int>> grid;
std::vector<std::pair<int, int>> visited;
std::vector<std::pair<int, int>> stack;
std::map<std::pair<int, int>, std::pair<int, int>> solution;

struct cell {
    int x;
    int y;
    bool visited;
    bool up;
    bool down;
    bool left;
    bool right;
};

// Set up SDL window
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Build the grid
void build_grid() {
    for (int i = 1; i <= 20; i++) {
        x = 20;
        y = y + 20;
        for (int j = 1; j <= 20; j++) {
            SDL_Rect cell = { x, y, w, w };
            SDL_SetRenderDrawColor(gRenderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
            SDL_RenderDrawLine(gRenderer, x, y, x + w, y);           // top of cell
            SDL_RenderDrawLine(gRenderer, x + w, y, x + w, y + w);   // right of cell
            SDL_RenderDrawLine(gRenderer, x + w, y + w, x, y + w);   // bottom of cell
            SDL_RenderDrawLine(gRenderer, x, y + w, x, y);           // left of cell
            grid.push_back(std::make_pair(x, y));
            x = x + 20;
        }
    }
    SDL_RenderPresent(gRenderer);
}

// Draw the walls of each cell
void draw_wall(int x, int y, std::string dir) {
    SDL_Rect wall;
    if (dir == "up") {
        wall = { x + 1, y - w + 1, 19, 39 };
    }
    else if (dir == "down") {
        wall = { x + 1, y + 1, 19, 39 };
    }
    else if (dir == "left") {
        wall = { x - w + 1, y + 1, 39, 19 };
    }
    else if (dir == "right") {
        wall = { x + 1, y + 1, 39, 19 };
    }
    SDL_SetRenderDrawColor(gRenderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
    SDL_RenderFillRect(gRenderer, &wall);
    SDL_RenderPresent(gRenderer);
}

// Create a new cell 
void new_cell(int x, int y) {
    SDL_Rect cell = { x + 1, y + 1, 19, 19 };
    SDL_SetRenderDrawColor(gRenderer, GREEN.r,
