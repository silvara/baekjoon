#include <cstdio>

enum map_info {
  MAP_DIRTY,
  MAP_WALL,
  MAP_CLEAN,
  MAP_ERROR,
};

enum direction_type {
  NORTH,
  EAST,
  SOUTH,
  WEST,
};

class RobotCleaner {
  // Map info
  int rows, columns;
  int** map;

  // Current position
  int pos_r, pos_c;
  int direction;

  int clean_count;

public:
  RobotCleaner() {
    clean_count = 0;
  }

  ~RobotCleaner() {
    for(int r = 0; r < rows; ++r)
      delete map[r];
    delete map;
  }

  void parse() {
    scanf("%d %d", &rows, &columns);
    scanf("%d %d %d", &pos_r, &pos_c, &direction);

    map = new int*[rows];
    for(int r = 0; r < rows; ++r) {
      map[r] = new int[columns];
      for(int c = 0; c < columns; ++c)
        scanf("%d", &map[r][c]);
    }
  }

  bool check_dirty() {
    return map[pos_r][pos_c] == MAP_DIRTY;
  }

  void move_front() {
    if(direction == NORTH) {
      pos_r -= 1;
    } else if(direction == EAST) {
      pos_c += 1;
    } else if(direction == SOUTH) {
      pos_r += 1;
    } else if(direction == WEST) {
      pos_c -= 1;
    }
  }

  void move_back() {
    if(direction == NORTH) {
      pos_r += 1;
    } else if(direction == EAST) {
      pos_c -= 1;
    } else if(direction == SOUTH) {
      pos_r -= 1;
    } else if(direction == WEST) {
      pos_c += 1;
    }
  }

  void clean() {
    map[pos_r][pos_c] = MAP_CLEAN;
    ++clean_count;
  }

  int get_clean_count() {
    return clean_count;
  }

  int check_position(int r, int c) {
    if(r < 0 || r >= rows)
      return MAP_ERROR;

    if(c < 0 || c >= columns)
      return MAP_ERROR;

    return map[r][c];
  }

  int check_direction(int d) {
    int r, c;
    if(d == NORTH) {
      r = pos_r - 1;
      c = pos_c;
    } else if(d == EAST) {
      r = pos_r;
      c = pos_c + 1;
    } else if(d == SOUTH) {
      r = pos_r + 1;
      c = pos_c;
    } else if(d == WEST) {
      r = pos_r;
      c = pos_c - 1;
    }

    return check_position(r, c);
  }

  bool check_left() {
    int left_direction = direction - 1;
    if(left_direction < 0)
      left_direction += 4;

    return check_direction(left_direction);
  }

  int check_back() {
    int back_direction = (direction + 2) % 4;
    return check_direction(back_direction);
  }

  void turn_left() {
    direction = (direction + 3) % 4;
  }
};

int main() {
  RobotCleaner robot;
  robot.parse();

  if(robot.check_dirty())
    robot.clean();

  int rotate_count = 0;
  while(true) {
    if(robot.check_left() == MAP_DIRTY) {
      rotate_count = 0;
      robot.turn_left();
      robot.move_front();
      robot.clean();
    } else if(rotate_count < 3) {
      robot.turn_left();
      ++rotate_count;
    } else {
      rotate_count = 0;
      robot.turn_left();
      int check = robot.check_back();
      if(check == MAP_ERROR || check == MAP_WALL)
        break;

      robot.move_back();
      if(robot.check_dirty())
        robot.clean();
    }
  }

  printf("%d\n", robot.get_clean_count());
}
