// Takes a maze (in vector form) and populates an adjacency list with the
// connections between nodes. Takes an obstacle argument, to indicate when the
// connection mustn't take place.
#include <vector>
using namespace std;
template <typename T>
void graph_from_maze(int cols, int rows, std::vector<T> &maze, T obstacle, std::vector<int> adjacency_list[]) {
    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x) {
            int pos = x + y*cols, up = pos - cols, down = pos + cols, left = pos -1, right = pos + 1;
            if(x != 0 && (maze[left] != obstacle) && (maze[pos] != obstacle))
                adjacency_list[pos].push_back(left);
            if( y != 0 && (maze[up] != obstacle) && (maze[pos] != obstacle))
                adjacency_list[pos].push_back(up);
            if( x < (cols-1) && (maze[right] != obstacle) && (maze[pos] != obstacle))
                adjacency_list[pos].push_back(right);
            if(y < (rows-1) && (maze[down] != obstacle) && (maze[pos] != obstacle))
                adjacency_list[pos].push_back(down);
        }
}
