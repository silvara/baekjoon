#include <cmath>
#include <cstdint>
#include <cstdio>

int main() {
  int N;
  int* A;
  int B, C;

  scanf("%d", &N);
  A = new int[N];
  for(int i = 0; i < N; ++i)
    scanf("%d", &A[i]);
  scanf("%d %d", &B, &C);

  uint64_t result = 0;
  for(int i = 0; i < N; ++i) {
    if(A[i] < B) {
      result += 1;
    } else {
      result += ceil(((double)A[i] - B) / C) + 1;
    }
  }

  printf("%ld\n", result);

  free(A);
}
