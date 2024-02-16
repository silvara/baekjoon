#include <cstdio>
#include <map>

using namespace std;

int main() {
  int N;
	map<int, int> myMap; // <A, A_count>

	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		int A;
		scanf("%d", &A);

    myMap[A] = 1;
	}

  for(const auto &myPair : myMap) {
    printf("%d\n", myPair.first);
  }
}
