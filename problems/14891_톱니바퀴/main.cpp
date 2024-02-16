#include <iostream>
#include <vector>

using namespace std;

enum Pole {
  POLE_N,
  POLE_S,
};

enum Direction {
  CLOCKWISE = 1,
  NONE = 0,
  COUNTER_CLOCKWISE = -1,
};

void rotate_wheel(vector<int>& wheel, int direction) {
  if(direction == CLOCKWISE) {
    vector<int>::iterator it;
    it = wheel.begin();

    int tmp = wheel[7];
    wheel.insert(it, tmp);
    wheel.pop_back();
  } else if(direction == COUNTER_CLOCKWISE) {
    vector<int>::iterator it;
    it = wheel.begin();

    int tmp = wheel[0];
    wheel.erase(it);
    wheel.push_back(tmp);
  }
}

void rotate_wheels(vector<int> wheels[], int wheel_idx, int direction) {
  int directions[4] = { 0 };
  directions[wheel_idx] = direction;

  // Left side
  for(int i = wheel_idx; i >= 1; --i) {
    if(wheels[i][6] == wheels[i - 1][2])
      break;

    directions[i - 1] = directions[i] * (-1);
  }

  // Right side
  for(int i = wheel_idx; i < 3; ++i) {
    if(wheels[i][2] == wheels[i + 1][6])
      break;

    directions[i + 1] = directions[i] * (-1);
  }

  for(int i = 0; i < 4; ++i)
    rotate_wheel(wheels[i], directions[i]);
}

int get_score(vector<int> wheels[]) {
  return wheels[0][0] + wheels[1][0] * 2 + wheels[2][0] * 4 + wheels[3][0] * 8;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  vector<int> wheels[4];
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 8; ++j) {
      char pole;
      cin >> pole;
      wheels[i].push_back(pole - '0');
    }
  }

  int K;
  cin >> K;
  for(int i = 0; i < K; ++i) {
    int wheel_idx, direction;
    cin >> wheel_idx >> direction;
    rotate_wheels(wheels, wheel_idx - 1, direction);
  }

  cout << get_score(wheels) << endl;
}
