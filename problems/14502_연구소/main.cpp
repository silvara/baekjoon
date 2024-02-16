#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

enum map_type {
  MAP_EMPTY,
  MAP_WALL,
  MAP_VIRUS,
};

struct Position {
  int r;
  int c;
};

void spread_virus_one(int map[][8], int rows, int columns, int virus_r, int virus_c) {
  map[virus_r][virus_c] = MAP_VIRUS;

  // north
  if(virus_r - 1 >= 0 && map[virus_r - 1][virus_c] == MAP_EMPTY)
    spread_virus_one(map, rows, columns, virus_r - 1, virus_c);

  // east
  if(virus_c + 1 < columns && map[virus_r][virus_c + 1] == MAP_EMPTY)
    spread_virus_one(map, rows, columns, virus_r, virus_c + 1);

  // south
  if(virus_r + 1 < rows && map[virus_r + 1][virus_c] == MAP_EMPTY)
    spread_virus_one(map, rows, columns, virus_r + 1, virus_c);

  // west
  if(virus_c - 1 >= 0 && map[virus_r][virus_c - 1] == MAP_EMPTY)
    spread_virus_one(map, rows, columns, virus_r, virus_c - 1);
}

void spread_virus(int map[][8], int rows, int columns) {
  vector<struct Position> positions;
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < columns; ++c) {
      if(map[r][c] == MAP_VIRUS) {
        positions.push_back({r, c});
      }
    }
  }

  for(auto it = positions.begin(); it != positions.end(); it++)
    spread_virus_one(map, rows, columns, it->r, it->c);
}

int get_safe_area(int map[][8], int rows, int columns) {
  int safe_area = 0;
  for(int r = 0; r < rows; ++r) {
    for(int c = 0; c < columns; ++c) {
      if(map[r][c] == MAP_EMPTY)
        ++safe_area;
    }
  }

  return safe_area;
}

int simulate_wall(int map[][8], int rows, int columns,
    int wall1_r, int wall1_c, int wall2_r, int wall2_c, int wall3_r, int wall3_c, bool printmap) {
  int simulation_map[8][8];
  copy(&map[0][0], &map[0][0] + 8 * 8, &simulation_map[0][0]);

  simulation_map[wall1_r][wall1_c] = MAP_WALL;
  simulation_map[wall2_r][wall2_c] = MAP_WALL;
  simulation_map[wall3_r][wall3_c] = MAP_WALL;

  spread_virus(simulation_map, rows, columns);
  return get_safe_area(simulation_map, rows, columns);
}

int main() {
  int N, M;
  int map[8][8];

  scanf("%d %d", &N, &M);
  for(int r = 0; r < N; ++r) {
    for(int c = 0; c < M; ++c)
      scanf("%d", &map[r][c]);
  }

  int max_safe_area = 0;
  for(int wall1_r = 0; wall1_r < N; ++wall1_r) {
    for(int wall1_c = 0; wall1_c < M; ++wall1_c) {
      if(map[wall1_r][wall1_c] != MAP_EMPTY)
        continue;

      for(int wall2_r = 0; wall2_r < N; ++wall2_r) {
        for(int wall2_c = 0; wall2_c < M; ++wall2_c) {
          if(map[wall2_r][wall2_c] != MAP_EMPTY) {
            continue;
          } else if(wall1_r == wall2_r && wall1_c == wall2_c) {
            continue;
          }

          for(int wall3_r = 0; wall3_r < N; ++wall3_r) {
            for(int wall3_c = 0; wall3_c < M; ++wall3_c) {
              if(map[wall3_r][wall3_c] != MAP_EMPTY) {
                continue;
              } else if((wall1_r == wall3_r && wall1_c == wall3_c) || (wall2_r == wall3_r && wall2_c == wall3_c)) {
                continue;
              }

              int safe_area = simulate_wall(map, N, M, wall1_r, wall1_c, wall2_r, wall2_c, wall3_r, wall3_c, true);
              max_safe_area = max(max_safe_area, safe_area);
            }
          }
        }
      }
    }
  }

  printf("%d\n", max_safe_area);
}
