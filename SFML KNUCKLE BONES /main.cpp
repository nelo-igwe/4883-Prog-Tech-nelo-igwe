#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <optional>

class Dice {
public:
    Dice() : engine(std::random_device{}()), distribution(1, 6) {}

    int roll() {
        return distribution(engine);
    }

private:
    std::mt19937 engine;
    std::uniform_int_distribution<int> distribution;
};

class Grid {
public:
    Grid(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<std::optional<int>>(cols)) {}

    bool place_value(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col].has_value()) {
            return false;
        }
        grid[row][col] = value;
        return true;
    }

    bool is_full() const {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                if (!cell.has_value()) {
                    return false;
                }
            }
        }
        return true;
    }

    void display() const {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                if (cell.has_value()) {
                    std::cout << cell.value() << " ";
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    int rows;
    int cols;
    std::vector<std::vector<std::optional<int>>> grid;
};

class Player {
public:
    Player(const std::string& name) : name(name) {}

    const std::string& get_name() const {
        return name;
    }

private:
    std::string name;
};

class Game {
public:
    Game() : dice(), grid(3, 3), current_player_index(0) {}

    void initialize_players(const std::string& player1_name, const std::string& player2_name) {
        players.emplace_back(player1_name);
        players.emplace_back(player2_name);
    }

    void start() {
        std::cout << "Game started!\n";

        while (!grid.is_full()) {
            take_turn();
            switch_turn();
        }

        std::cout << "Game over! The grid is full.\n";
    }

private:
    Dice dice;
    Grid grid;
    std::vector<Player> players;
    size_t current_player_index;

    void take_turn() {
        const Player& current_player = players[current_player_index];
        std::cout << current_player.get_name() << "'s turn.\n";

        int dice_roll = dice.roll();
        std::cout << "Rolled a " << dice_roll << ".\n";

        int row, col;
        while (true) {
            std::cout << "Enter row and column to place the dice roll: ";
            std::cin >> row >> col;

            if (std::cin.fail() || !grid.place_value(row, col, dice_roll)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input or position taken. Try again.\n";
            } else {
                break;
            }
        }

        grid.display();
    }

    void switch_turn() {
        current_player_index = (current_player_index + 1) % players.size();
    }
};

int main() {
    Game game;
    std::string player1, player2;

    std::cout << "Enter name for Player 1: ";
    std::cin >> player1;
    std::cout << "Enter name for Player 2: ";
    std::cin >> player2;

    game.initialize_players(player1, player2);
    game.start();

    return 0;
}
