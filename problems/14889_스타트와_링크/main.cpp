#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <climits>

using namespace std;

#define TEAM(T, N) ((T >> N) % 2)

int get_diff(int n, int s[][20], int teams) {
  int power0 = 0;
  int power1 = 0;

  for(int i = 0; i < n - 1; ++i) {
    for(int j = i + 1; j < n; ++j) {
      int team_i = TEAM(teams, i);
      int team_j = TEAM(teams, j);
      if(team_i != team_j)
        continue;

      if(team_i == 0) {
        power0 += s[i][j] + s[j][i];
      } else {
        power1 += s[i][j] + s[j][i];
      }
    }
  }

  return abs(power0 - power1);
}

int get_result(int n, int s[][20]) {
  int min_diff = INT_MAX;

  for(int teams = 0; teams < pow(2, n) + 1; ++teams) {
    int team_count = 0;
    for(int j = 0; j < n; ++j) {
      if(TEAM(teams, j) == 0)
        ++team_count;
    }

    if(team_count != n / 2)
      continue;

    min_diff = min(min_diff, get_diff(n, s, teams));
  }

  return min_diff;
}

int main() {
  int N;
  int S[20][20];

  scanf("%d", &N);
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j)
      scanf("%d", &S[i][j]);
  }

  printf("%d\n", get_result(N, S));
}
