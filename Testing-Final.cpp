#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace sf;
using namespace sfp;


const int N = 20; // size of the grid

// Grid to store the current state of the game
std::vector<std::vector<bool>> grid(N, std::vector<bool>(N));

// Grid to store the next state of the game
std::vector<std::vector<bool>> next_grid(N, std::vector<bool>(N));

// Function to count the number of alive neighbors for a given cell
int count_neighbors(int x, int y) {
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            }
            if (i >= 0 && i < N && j >= 0 && j < N && grid[i][j]) {
                count++;
            }
        }
    }
    return count;
}

// Function to update the state of the game
void update() {
    // Count the number of alive neighbors for each cell
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            int neighbors = count_neighbors(x, y);
            // Apply the rules of the game
            if (grid[x][y]) {
                next_grid[x][y] = (neighbors == 2 || neighbors == 3);
            }
            else {
                next_grid[x][y] = (neighbors == 3);
            }
        }
    }
    // Update the grid with the new state
    grid = next_grid;
}

// Function to print the current state of the game
void print() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            std::cout << (grid[x][y] ? "X" : "O");
        }
        std::cout << std::endl;
    }
}

int main() {
    // Black and white tiles
    PhysicsRectangle black;
    black.setSize(Vector2f(10, 10));
    black.setFillColor(Color(0, 0, 0));

    PhysicsRectangle white;
    white.setSize(Vector2f(10, 10));
    white.setFillColor(Color(255, 255, 255));

    // Initialize the grid with a pattern
    grid[10][10] = true;
    grid[10][11] = true;
    grid[10][12] = true;
    grid[11][12] = true;
    grid[12][11] = true;

    // Run the game until the user quits
    std::string input;
    while (true) {

        update();
        print();
        std::cout << std::endl;
        std::cout << "Press Enter to continue, or 'q' to quit: ";
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }
    }

    return 0;
}
