#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, L;
  cin >> N >> L;

  int** map = new int*[N];
  for(int r = 0; r < N; ++r) {
    map[r] = new int[N];
    for(int c = 0; c < N; ++c)
      cin >> map[r][c];
  }

  int count = 0;

  // Check horizontal
  for(int r = 0; r < N; ++r) {
    bool valid = true;
    int slope[N] = { 0 };
    for(int c = 0; c < N - 1; ++c) {
      int next_diff = map[r][c + 1] - map[r][c];
      if(next_diff == 0) {
        continue;
      } else if(next_diff == 1) {
        if(c + 1 < L) {
          valid = false;
          break;
        }

        for(int i = c; i > c - L; --i) {
          if(slope[i] || map[r][c] != map[r][i]) {
            valid = false;
            break;
          }
          slope[i] = true;
        }

        if(!valid)
          break;
      } else if(next_diff == -1) {
        if(c >= N - L) {
          valid = false;
          break;
        }

        for(int i = c + 1; i <= c + L; ++i) {
          if(slope[i] || map[r][c + 1] != map[r][i]) {
            valid = false;
            break;
          }
          slope[i] = true;
        }

        if(!valid)
          break;
      } else {
        valid = false;
        break;
      }
    }

    if(valid)
      ++count;
  }

  // Check vertical
  for(int c = 0; c < N; ++c) {
    bool valid = true;
    int slope[N] = { 0 };
    for(int r = 0; r < N - 1; ++r) {
      int next_diff = map[r + 1][c] - map[r][c];
      if(next_diff == 0) {
        continue;
      } else if(next_diff == 1) {
        if(r + 1 < L) {
          valid = false;
          break;
        }

        for(int i = r; i > r - L; --i) {
          if(slope[i] || map[r][c] != map[i][c]) {
            valid = false;
            break;
          }
          slope[i] = true;
        }

        if(!valid)
          break;
      } else if(next_diff == -1) {
        if(r >= N - L) {
          valid = false;
          break;
        }

        for(int i = r + 1; i <= r + L; ++i) {
          if(slope[i] || map[r + 1][c] != map[i][c]) {
            valid = false;
            break;
          }
          slope[i] = true;
        }

        if(!valid)
          break;
      } else {
        valid = false;
        break;
      }
    }

    if(valid)
      ++count;
  }

  cout << count << endl;
}
