/*
 * License: GPLv3
 * BUPT DS homework: Maze
 * Tested with G++ under standard C++98
 * Author: Yinuo Deng <i@dyn.im>
*/

#include <iostream>
#include <vector>
#include <utility>

typedef std::vector<std::vector<bool> > Matrix;
typedef std::vector<std::pair<size_t, size_t> > Path;

Path findPath(size_t i, size_t j, Matrix &maze) {
    static Path path, finalPath;
    static size_t m = maze.size(), n = maze[0].size();
    maze[i][j] = 1;
    path.push_back(std::make_pair(i, j));
    if (i == m - 1 && j == n - 1) finalPath = path;
    if (i >= 1 && !maze[i - 1][j]) (void) findPath(i - 1, j, maze);
    if (i + 1 < m && !maze[i + 1][j]) (void) findPath(i + 1, j, maze);
    if (j >= 1 && !maze[i][j - 1]) (void) findPath(i, j - 1, maze);
    if (j + 1 < n && !maze[i][j + 1]) (void) findPath(i, j + 1, maze);
    maze[i][j] = 0;
    path.pop_back();
    return finalPath;
}

int main(void) {
    size_t m, n;
    std::cin >> m >> n;
    Matrix maze;
    for (size_t i = 0; i < m; i++) {
        std::vector<bool> temp;
        bool input;
        for (size_t j = 0; j < n; j++) {
            std::cin >> input;
            temp.push_back(input);
        }
        maze.push_back(temp);
    }
    Path path = findPath(0, 0, maze);
    for (Path::iterator iter = path.begin(); iter != path.end(); iter++)
        std::cout << "(" << iter->first << ", " << iter->second << ")\n";
    return 0;
}
