#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int T[15], P[15];

int get_payment(int index) {
  if(index >= N)
    return 0;

  if(index + T[index] > N)
    return get_payment(index + 1);

  int payment = P[index] + get_payment(index + T[index]);
  int next_payment = get_payment(index + 1);
  return max(payment, next_payment);
}



int main() {
  scanf("%d", &N);
  for(int i = 0; i < N; ++i)
    scanf("%d %d", &T[i], &P[i]);

  printf("%d\n", get_payment(0));
}
