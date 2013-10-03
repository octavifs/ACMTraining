#define PB push_back
#define SZ size()

#include <vector>
#include <iostream>
#include <utility>

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
using namespace std;

int N;                  // numero de nodos
vector<int> A[10001];   // listas de adyacencia

int BFS(int s, int t) { // distancia entre s y t
  if (s == t) return 0;
  int l[10001], k = 0;  // inicializar cola
  vector<int> v(N, -1); // inicializar distancias
  l[k++] = s;           // agregar s a la cola
  v[s] = 0;             // distancia hasta s es 0
  for (int i = 0; i < k; i++)
    // para todos los nodos adyacentes de l[i]
    for (int j = 0; j < (int)A[l[i]].SZ; j++)
      // si el vecino no se ha visitado
      if (v[A[l[i]][j]] < 0) {
        // actualizar su distancia
    v[A[l[i]][j]] = v[l[i]] + 1;
        // si encontramos t, devolver resultado
    if (A[l[i]][j] == t) return v[t];
        // agregar a la cola
    l[k++] = A[l[i]][j];
      }
  return -1;
}

int main() {
  int runs;
  cin >> runs;
  for(int run = 0; run < runs; run++) {
    int col, row;
    vector<int> map;
    cin >> col >> row;
    N = col*row;
    for (int y = 0; y < row; ++y)
    {
      for (int x = 0; x < col; ++x)
      {
        int cell;
        cin >> cell;
        map.PB(cell);
      }
    }
    int start, end;
    int coordX, coordY;
    cin >> coordX >> coordY;
    start = coordX + coordY * col;
    cin >> coordX >> coordY;
    end = coordX + coordY * col;
    graph_from_maze<int>(col, row, map, 1, A);
    cout << BFS(start, end) + 1 << endl;
    for (int i = 0; i < 10001; ++i)
    {
      A[i].clear();
    }

  }
}