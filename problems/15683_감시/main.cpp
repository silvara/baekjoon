#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int cctv_range[][4] = {
  { 0, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 0, 1, 0 },
  { 1, 1, 0, 0 },
  { 1, 1, 1, 0 },
  { 1, 1, 1, 1 },
};

enum map_elem {
  MAP_EMPTY,
  MAP_CCTV1,
  MAP_CCTV2,
  MAP_CCTV3,
  MAP_CCTV4,
  MAP_CCTV5,
  MAP_WALL,
  MAP_WATCH,
};

typedef struct _cctv_info {
  int r, c;
  int value;
  int direction;
} cctv_info;

enum DIRECTION {
  NORTH,
  EAST,
  SOUTH,
  WEST,
};

#define IS_CCTV(X) (X > MAP_EMPTY && X < MAP_WALL)

int get_blind_spot_size(int** map, int rows, int columns, vector<cctv_info>& cctv_infos) {
  for(int i = 0; i < cctv_infos.size(); ++i) {
    for(int d = 0; d < 4; ++d) {
      if(cctv_range[cctv_infos[i].value][d] == 0)
        continue;

      switch((cctv_infos[i].direction + d) % 4) {
        case 0: // NORTH
          for(int r = cctv_infos[i].r - 1; r >= 0; --r) {
            int* watch = &map[r][cctv_infos[i].c];
            if(*watch == MAP_EMPTY) {
              *watch = MAP_WATCH;
            } else if(*watch == MAP_WALL) {
              break;
            }
          }
          break;

        case 1: // EAST
          for(int c = cctv_infos[i].c + 1; c < columns; ++c) {
            int* watch = &map[cctv_infos[i].r][c];
            if(*watch == MAP_EMPTY) {
              *watch = MAP_WATCH;
            } else if(*watch == MAP_WALL) {
              break;
            }
          }
          break;

        case 2: // SOUTH
          for(int r = cctv_infos[i].r + 1; r < rows; ++r) {
            int* watch = &map[r][cctv_infos[i].c];
            if(*watch == MAP_EMPTY) {
              *watch = MAP_WATCH;
            } else if(*watch == MAP_WALL) {
              break;
            }
          }
          break;

        case 3: // WEST
          for(int c = cctv_infos[i].c - 1; c >= 0; --c) {
            int* watch = &map[cctv_infos[i].r][c];
            if(*watch == MAP_EMPTY) {
              *watch = MAP_WATCH;
            } else if(*watch == MAP_WALL) {
              break;
            }
          }
          break;
      }
    }
  }

  int blind_spot_size = 0;
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < columns; ++c) {
      if(map[r][c] == MAP_EMPTY) {
        ++blind_spot_size;
      } else if(map[r][c] == MAP_WATCH) {
        map[r][c] = MAP_EMPTY;
      }
    }
  }

  return blind_spot_size;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<cctv_info> cctv_infos;

  int** map = new int*[N];
  for(int i = 0; i < N; ++i) {
    map[i] = new int[M];
    for(int j = 0; j < M; ++j) {
      cin >> map[i][j];

      if(IS_CCTV(map[i][j]))
        cctv_infos.push_back({ i, j, map[i][j] });
    }
  }

  int min_blind_spot_size = INT_MAX;
  for(int directions = 0; directions < pow(4, cctv_infos.size()); ++directions) {
    int _directions = directions;
    for(int i = 0; i < cctv_infos.size(); ++i) {
      cctv_infos[i].direction = _directions % 4;
      _directions /= 4;
    }

    int blind_spot_size = get_blind_spot_size(map, N, M, cctv_infos);
    if(blind_spot_size < min_blind_spot_size)
      min_blind_spot_size = blind_spot_size;
  }

  cout << min_blind_spot_size << endl;
}
