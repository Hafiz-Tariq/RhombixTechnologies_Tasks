#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    const int rows = 60;
    const int cols = 80;
    const int cellSize = 10;
    const int windowWidth = cols * cellSize;
    const int windowHeight = rows * cellSize;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Conway's Game of Life");
    window.setFramerateLimit(30);

    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> next = grid;

    bool running = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                running = !running;

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
                grid.assign(rows, std::vector<int>(cols, 0));

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
			    for (int i = 0; i < rows; ++i)
			        for (int j = 0; j < cols; ++j)
			            grid[i][j] = rand() % 2;
			}

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                auto pos = sf::Mouse::getPosition(window);
                int x = pos.x / cellSize;
                int y = pos.y / cellSize;
                if (x >= 0 && x < cols && y >= 0 && y < rows)
                    grid[y][x] = 1;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                auto pos = sf::Mouse::getPosition(window);
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

        window.clear(sf::Color::Black);
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
        cell.setFillColor(sf::Color::Green);

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
