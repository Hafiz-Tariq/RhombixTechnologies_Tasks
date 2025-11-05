#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

int main() {
    const int rows = 60;
    const int cols = 80;
    const int cellSize = 10;
    const int windowWidth = cols * cellSize;
    const int windowHeight = rows * cellSize;

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Conway's Game of Life");
    window.setFramerateLimit(30);

    vector<std::vector<int>> grid(rows, vector<int>(cols, 0));
    vector<std::vector<int>> next = grid;

    bool running = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                running = !running;

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C)
                grid.assign(rows, vector<int>(cols, 0));

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
			    for (int i = 0; i < rows; ++i)
			        for (int j = 0; j < cols; ++j)
			            grid[i][j] = rand() % 2;
			}

            if (Mouse::isButtonPressed(Mouse::Left)) {
                auto pos = Mouse::getPosition(window);
                int x = pos.x / cellSize;
                int y = pos.y / cellSize;
                if (x >= 0 && x < cols && y >= 0 && y < rows)
                    grid[y][x] = 1;
            }
            if (Mouse::isButtonPressed(Mouse::Right)) {
                auto pos = Mouse::getPosition(window);
                int x = pos.x / cellSize;
                int y = pos.y / cellSize;
                if (x >= 0 && x < cols && y >= 0 && y < rows)
                    grid[y][x] = 0;
            }
        }

        if (running) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int live = 0;
                    for (int x = -1; x <= 1; ++x)
                        for (int y = -1; y <= 1; ++y)
                            if (x || y)
                                live += grid[(i + x + rows) % rows][(j + y + cols) % cols];

                    next[i][j] = (live == 3 || (live == 2 && grid[i][j]));
                }
            }
            grid.swap(next);
        }

        window.clear(Color::Black);
        RectangleShape cell(Vector2f(cellSize - 1, cellSize - 1));
        cell.setFillColor(Color::Green);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j]) {
                    cell.setPosition(j * cellSize, i * cellSize);
                    window.draw(cell);
                }
            }
        }
        window.display();
    }
}
