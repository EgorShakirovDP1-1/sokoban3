#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Define the dimensions of the level matrix
const int width = 12;
const int height = 12;

// Create an empty matrix with walls around the edge
char matrix[48][48];
void initialize_matrix() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
                matrix[i][j] = '1';
            }
            else {
                matrix[i][j] = '0';
            }
        }
    }
}

// Randomly place boxes and target spots on the matrix
void place_boxes_and_targets(int num_boxes) {
    std::vector<std::pair<int, int>> available_spaces;
    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            if (matrix[i][j] == '0' && matrix[i-1][j] == '0' && matrix[i+1][j] == '0' && matrix[i][j - 1] == '0' && matrix[i][j + 1] == '0') {
                available_spaces.push_back(std::make_pair(i, j));
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_spaces.begin(), available_spaces.end(), gen);
    for (int i = 0; i < num_boxes; i++) {
        int x = available_spaces.back().first;
        int y = available_spaces.back().second;
        available_spaces.pop_back();
        matrix[x][y] = '$';
        matrix[width - x - 1][height - y - 1] = '.';
    }
}

// Place the player character randomly on the matrix
void place_player() {
    std::vector<std::pair<int, int>> available_spaces;
    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            if (matrix[i][j] == '0') {
                available_spaces.push_back(std::make_pair(i, j));
            }
        }
    }
    std::random_device rd;
    std::mt19937  gen(rd());
    std::uniform_int_distribution<> dis(0, available_spaces.size() - 1);
    int index = dis(gen);
    int x = available_spaces[index].first; // ошибка здесь
    int y = available_spaces[index].second;
    matrix[x][y] = '@';
}

// Generate a path for the player character to follow
bool can_reach_all_targets(int x, int y, std::vector<std::pair<int, int>> targets) {
    std::vector<std::pair<int, int>> visited;
    std::vector<std::pair<int, int>> frontier;
    frontier.push_back(std::make_pair(x, y));
    while (!frontier.empty()) {
        std::pair<int, int> current = frontier.back();
        frontier.pop_back();
        visited.push_back(current);
        for (std::pair<int, int> target : targets) {
            if (current == target) {
                //targets.erase(std::remove(targets.begin(), targets.end(), target), targets.end());
                std::remove(targets.begin(), targets.end(),target);
            }
        }
        if (targets.empty()) {
            return true;
        }
        if ( matrix[current.first - 1][current.second] != '1' && matrix[current.first + 1][current.second] != '1' && matrix[current.first][current.second - 1] != '1' && matrix[current.first][current.second + 1] != '1'
            && std::find(visited.begin(), visited.end(), std::make_pair(current.first - 1, current.second)) == visited.end()) {
            frontier.push_back(std::make_pair(current.first - 1, current.second));
        }
        //
    }

}
void place_walls(int num_walls) {
    std::vector<std::pair<int, int>> available_spaces;
    for (int i = 1; i < width - 1; i++) {
        for (int j = 1; j < height - 1; j++) {
            if (matrix[i][j] == '0') {
                available_spaces.push_back(std::make_pair(i, j));
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_spaces.begin(), available_spaces.end(), gen);
    for (int i = 0; i < num_walls; i++) {
        int x = available_spaces.back().first;
        int y = available_spaces.back().second;
        available_spaces.pop_back();
        matrix[x][y] = '1';

    }
}