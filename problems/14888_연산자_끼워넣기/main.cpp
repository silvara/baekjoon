#include <algorithm>
#include <cstdio>
#include <climits>

using namespace std;

struct Result {
  int max;
  int min;
};

struct Result get_result(struct Result result, int n, int a[], int n_add, int n_sub, int n_mul, int n_div) {
  if(n == 0)
    return result;

  int max_result = INT_MIN;
  int min_result = INT_MAX;

  if(n_add > 0) {
    struct Result result_add = get_result({result.max + a[0], result.min + a[0]}, n - 1, &a[1], n_add - 1, n_sub, n_mul, n_div);
    max_result = max(max_result, result_add.max);
    min_result = min(min_result, result_add.min);
  }

  if(n_sub > 0) {
    struct Result result_sub = get_result({result.max - a[0], result.min - a[0]}, n - 1, &a[1], n_add, n_sub - 1, n_mul, n_div);
    max_result = max(max_result, result_sub.max);
    min_result = min(min_result, result_sub.min);
  }

  if(n_mul > 0) {
    struct Result result_mul = get_result({result.max * a[0], result.min * a[0]}, n - 1, &a[1], n_add, n_sub, n_mul - 1, n_div);
    max_result = max(max_result, result_mul.max);
    min_result = min(min_result, result_mul.min);
  }

  if(n_div > 0) {
    struct Result result_div = get_result({result.max / a[0], result.min / a[0]}, n - 1, &a[1], n_add, n_sub, n_mul, n_div - 1);
    max_result = max(max_result, result_div.max);
    min_result = min(min_result, result_div.min);
  }

  return { max_result, min_result };
}

int main() {
  int N;
  int A[100];
  int n_add, n_sub, n_mul, n_div;

  scanf("%d", &N);
  for(int i = 0; i < N; ++i)
    scanf("%d", &A[i]);
  scanf("%d %d %d %d", &n_add, &n_sub, &n_mul, &n_div);

  struct Result result = get_result({A[0], A[0]}, N - 1, &A[1], n_add, n_sub, n_mul, n_div);
  printf("%d\n", result.max);
  printf("%d\n", result.min);
}
