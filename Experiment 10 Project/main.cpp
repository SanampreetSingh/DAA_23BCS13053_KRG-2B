#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <numeric>
#include <string>
#include <algorithm>

const int size = 10;

bool visited[size * size];
bool walls[size * size][2] = { 0 };

const int start = 0;
const int goal = size * size - 1;

int path[size * size] = { 0 };

int mazeBlocks[size * size][5];

int pos = start;
int rot = 0;
int pathIndex = 0;

int emptyWalls[4] = { 0 };
int emptyWallsCount = 0;

/**
 * @brief Finds the delta to an unvisited neighbor for DFS maze generation.
 * @param currentPos The index of the current cell.
 * @param size The size of the maze grid (side length).
 * @return The delta (+/- 1 or +/- size) to the next cell, or 0 if no unvisited neighbors exist.
 */
int nextCell(int currentPos, int size) {
    std::vector<int> options;

    if (currentPos >= size && !visited[currentPos - size]) { options.push_back(-size); }
    if ((currentPos + 1) % size != 0 && !visited[currentPos + 1]) { options.push_back(1); }
    if (currentPos < size * (size - 1) && !visited[currentPos + size]) { options.push_back(size); }
    if (currentPos % size != 0 && !visited[currentPos - 1]) { options.push_back(-1); }

    if (options.empty()) { return 0; }

    return options[rand() % options.size()];
}

/**
 * @brief Breaks the wall between two adjacent cells.
 * @param pos1 Index of the first cell.
 * @param pos2 Index of the second cell.
 */
void connect(int pos1, int pos2) {
    if (pos2 > pos1) {
        if (pos2 == pos1 + 1) {
            walls[pos2][0] = 1;
        } else {
            walls[pos2][1] = 1;
        }
    } else {
        if (pos1 == pos2 + 1) {
            walls[pos1][0] = 1;
        } else {
            walls[pos1][1] = 1;
        }
    }
}

/**
 * @brief Generates the maze using Randomized Depth-First Search (DFS).
 * @param currentPos The index of the current cell.
 * @param size The size of the maze grid.
 */
void randomdfs(int currentPos, int size) {
    visited[currentPos] = true;
    int nextDelta;

    while ((nextDelta = nextCell(currentPos, size)) != 0) {
        int nextPos = currentPos + nextDelta;
        connect(currentPos, nextPos);
        randomdfs(nextPos, size);
    }
}

/**
 * @brief Initializes and runs the DFS maze generation.
 */
void createMazeDFS() {
    std::cout << "Starting DFS maze generation..." << std::endl;
    for (int i = 0; i < size * size; ++i) {
        visited[i] = false;
        walls[i][0] = 0;
        walls[i][1] = 0;
        path[i] = 0;
    }

    randomdfs(start, size);
    std::cout << "Maze generation complete." << std::endl;
}

/**
 * @brief Finds open walls from the current position. Used for A*.
 */
void getEmptyWalls() {
    emptyWallsCount = 0;

    if (pos >= size && walls[pos][1]) {
        emptyWalls[emptyWallsCount++] = -size;
    }
    if ((pos + 1) % size != 0 && walls[pos + 1][0]) {
        emptyWalls[emptyWallsCount++] = 1;
    }
    if (pos < size * (size - 1) && walls[pos + size][1]) {
        emptyWalls[emptyWallsCount++] = size;
    }
    if (pos % size != 0 && walls[pos][0]) {
        emptyWalls[emptyWallsCount++] = -1;
    }
}

/**
 * @brief Updates G, H, F, and Parent values for a neighbor in A* search.
 */
void aStarCalculate(int neighborPos) {
    int g = mazeBlocks[pos][0] + 1;

    int dx = std::abs(neighborPos % size - goal % size);
    int dy = std::abs((neighborPos / size) - (goal / size));
    int h = dx + dy;

    int f = g + h;

    if (mazeBlocks[neighborPos][2] == 0 || f < mazeBlocks[neighborPos][2]) {
        mazeBlocks[neighborPos][0] = g;
        mazeBlocks[neighborPos][1] = h;
        mazeBlocks[neighborPos][2] = f;
        mazeBlocks[neighborPos][4] = pos;
    }
}

/**
 * @brief Solves the maze using the A* search algorithm (guaranteed shortest path).
 * @return The length of the shortest path found.
 */
int solveMazeAstar() {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < 5; j++) {
            mazeBlocks[i][j] = 0;
        }
        path[i] = 0;
    }

    pos = start;
    mazeBlocks[pos][0] = 0;
    mazeBlocks[pos][1] = std::abs(pos % size - goal % size) + std::abs((pos / size) - (goal / size));
    mazeBlocks[pos][2] = mazeBlocks[pos][1];

    while (pos != goal) {
        mazeBlocks[pos][3] = 1;

        getEmptyWalls();

        for (int i = 0; i < emptyWallsCount; i++) {
            int neighborPos = pos + emptyWalls[i];
            if (mazeBlocks[neighborPos][3] == 0) {
                aStarCalculate(neighborPos);
            }
        }

        int minf = size * size * 2;
        int minh = size * size;
        int nextCell = -1;

        for (int i = 0; i < size * size; i++) {
            if (mazeBlocks[i][3] == 0 && mazeBlocks[i][2] != 0) {
                if (mazeBlocks[i][2] < minf) {
                    minf = mazeBlocks[i][2];
                    minh = mazeBlocks[i][1];
                    nextCell = i;
                } else if (mazeBlocks[i][2] == minf && mazeBlocks[i][1] < minh) {
                    minh = mazeBlocks[i][1];
                    nextCell = i;
                }
            }
        }

        if (nextCell == -1) {
            return -1;
        }

        pos = nextCell;
    }

    int currentCell = goal;
    std::vector<int> shortestPathCells;

    while (currentCell != -1) {
        shortestPathCells.push_back(currentCell);
        if (currentCell == start) break;
        currentCell = mazeBlocks[currentCell][4];
    }

    int pathLength = shortestPathCells.size() - 1;
    for (size_t i = 0; i < shortestPathCells.size(); ++i) {
        int cellIndex = shortestPathCells[shortestPathCells.size() - 1 - i];
        path[cellIndex] = i + 1;
    }

    return pathLength;
}

/**
 * @brief Prints the maze representation with the corresponding solution path markers.
 * @param title The title for the maze output.
 */
void printMaze(const std::string& title) {
    std::cout << "\n=================================================" << std::endl;
    std::cout << "--- " << title << " (" << size << "x" << size << ") ---" << std::endl;
    std::cout << "=================================================" << std::endl;

    bool is_unsolved = title.find("Unsolved") != std::string::npos;
    bool is_astar_solved = title.find("A* Shortest Path") != std::string::npos;

    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            int currentPos = j * size + i;

            std::cout << "+";

            bool wallOpen = false;
            if (j > 0) {
                wallOpen = walls[currentPos][1] == 1;
            } else {
                if (currentPos == start) {
                    wallOpen = true;
                }
            }

            if (wallOpen) {
                std::cout << "   ";
            } else {
                std::cout << "---";
            }
        }
        std::cout << "+\n";

        for (int i = 0; i < size; ++i) {
            int currentPos = j * size + i;

            bool wallOpen = false;
            if (i == 0) {
                if (currentPos == start) {
                    wallOpen = true;
                } else {
                    wallOpen = false;
                }
            } else {
                wallOpen = walls[currentPos][0] == 1;
            }

            if (wallOpen) {
                std::cout << " ";
            } else {
                std::cout << "|";
            }

            if (is_unsolved) {
                if (currentPos == start) std::cout << " S ";
                else if (currentPos == goal) std::cout << " G ";
                else std::cout << "   ";
            }
            else if (is_astar_solved && path[currentPos] > 0) {
                int step = path[currentPos];
                std::string s = std::to_string(step);

                if (s.length() == 1) std::cout << "  " << s;
                else if (s.length() == 2) std::cout << " " << s;
                else if (s.length() >= 3) std::cout << s.substr(0, 3);
            }
            else {
                std::cout << "   ";
            }
        }

        if (j == size - 1) {
            if (goal % size == size - 1) {
                bool pathExists = (is_astar_solved && path[goal] > 0);

                if (pathExists || is_unsolved) {
                    std::cout << " \n";
                } else {
                    std::cout << "|\n";
                }
            } else {
                 std::cout << "|\n";
            }
        } else {
            std::cout << "|\n";
        }
    }

    for (int i = 0; i < size; ++i) {
        std::cout << "+";
        if (i == size - 1) {
            bool pathExists = (is_astar_solved && path[goal] > 0);

            if (pathExists || is_unsolved) {
                 std::cout << " ";
            } else {
                std::cout << "---";
            }
        } else {
            std::cout << "---";
        }
    }
    std::cout << "+\n";

    if (is_unsolved) {
        std::cout << "Legend: S=Start, G=Goal\n";
    } else if (is_astar_solved) {
        std::cout << "Legend: 1,2,3...=A* Shortest Path Steps\n";
    }
}

int main()
{
    srand(time(NULL));

    createMazeDFS();

    for (int i = 0; i < size * size; i++) {
        path[i] = 0;
    }
    printMaze("Unsolved Maze");

    std::cout << "\nStarting A* search solution..." << std::endl;
    int aStarLength = solveMazeAstar();

    if (aStarLength != -1) {
        std::cout << "A* solution complete. Shortest path length: " << aStarLength << " steps." << std::endl;
        printMaze("A* Shortest Path");
    } else {
        std::cout << "A* FAILED: No path found." << std::endl;
    }

    std::cout << "\nExecution finished. Maze size reduced to " << size << "x" << size << " for console visualization." << std::endl;

    return 0;
}