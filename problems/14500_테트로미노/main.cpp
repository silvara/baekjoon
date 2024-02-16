#include <cstdio>


class Tetromino {
  struct Coordinate {
    int x;
    int y;
  } coordinates[4];
  int min_x, min_y, max_x, max_y;

public:
  Tetromino(
      Coordinate coordinate1,
      Coordinate coordinate2,
      Coordinate coordinate3,
      Coordinate coordinate4
      ) {
    coordinates[0] = coordinate1;
    coordinates[1] = coordinate2;
    coordinates[2] = coordinate3;
    coordinates[3] = coordinate4;
    this->update_minmax();
  }

  void update_minmax() {
    min_x = 999;
    max_x = 0;
    min_y = 999;
    max_y = 0;
    for(int i = 0; i < 4; ++i) {
      if(coordinates[i].x > max_x)
        max_x = coordinates[i].x;
      if(coordinates[i].x < min_x)
        min_x = coordinates[i].x;
      if(coordinates[i].y > max_y)
        max_y = coordinates[i].y;
      if(coordinates[i].y < min_y)
        min_y = coordinates[i].y;
    }

    if(min_x < 0) {
      for(int i = 0; i < 4; ++i)
        coordinates[i].x -= min_x;
      min_x = 0;
    }

    if(min_y < 0) {
      for(int i = 0; i < 4; ++i)
        coordinates[i].y -= min_y;
      min_y = 0;
    }
  }

  Tetromino operator=(Tetromino const &obj) {
    for(int i = 0; i < 4; i++) {
      coordinates[i].x = obj.coordinates[i].x;
      coordinates[i].y = obj.coordinates[i].y;
    }
    return *this;
  }

  Tetromino& rotate90() {
    // min_x, max_y -> zero
    for(int i = 0; i < 4; ++i) {
      int new_x = max_y - coordinates[i].y;
      int new_y = coordinates[i].x - min_x;
      coordinates[i] = {new_x, new_y};
    }
    this->update_minmax();
    return *this;
  }

  int size_x() {
    return max_x - min_x + 1;
  }

  int size_y() {
    return max_y - min_y + 1;
  }

  int sum_paper(int** paper, int x, int y) {
    int sum = 0;
    for(int i = 0; i < 4; ++i)
      sum += paper[coordinates[i].y + y][coordinates[i].x + x];
    return sum;
  }
};

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  int** paper;
  paper = new int*[N];
  for(int i = 0; i < N; ++i) {
    paper[i] = new int[M];
    for(int j = 0; j < M; ++j)
      scanf("%d", &paper[i][j]);
  }

  Tetromino i_mino({0, 0}, {0, 1}, {0, 2}, {0, 3});
  Tetromino o_mino({0, 0}, {0, 1}, {1, 0}, {1, 1});
  Tetromino z_mino({0, 0}, {0, 1}, {1, 1}, {1, 2});
  Tetromino s_mino({0, 1}, {0, 2}, {1, 0}, {1, 1});
  Tetromino j_mino({0, 1}, {1, 1}, {2, 0}, {2, 1});
  Tetromino l_mino({0, 0}, {1, 0}, {2, 0}, {2, 1});
  Tetromino t_mino({0, 0}, {0, 1}, {0, 2}, {1, 1});
  Tetromino minos[7] = {
    i_mino,
    o_mino,
    z_mino,
    s_mino,
    j_mino,
    l_mino,
    t_mino,
  };

  int max = 0;
  for(int mino_idx = 0; mino_idx < 7; ++mino_idx) {
    int mino_size_x = minos[mino_idx].size_x();
    int mino_size_y = minos[mino_idx].size_y();
    for(int y = 0; y < N - mino_size_y + 1; ++y) {
      for(int x = 0; x < M - mino_size_x + 1; ++x) {
        int sum = minos[mino_idx].sum_paper(paper, x, y);
        if(sum > max)
          max = sum;
      }
    }

    Tetromino rot_mino = minos[mino_idx];
    for(int rot = 0; rot < 3; ++rot) {
      rot_mino.rotate90();

      int mino_size_x = rot_mino.size_x();
      int mino_size_y = rot_mino.size_y();
      for(int y = 0; y < N - mino_size_y + 1; ++y) {
        for(int x = 0; x < M - mino_size_x + 1; ++x) {
          int sum = rot_mino.sum_paper(paper, x, y);
          if(sum > max)
            max = sum;
        }
      }
    }
  }

  printf("%d\n", max);
}
