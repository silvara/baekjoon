#include <cstdio>
#include <map>

using namespace std;

int main() {
	int N, M;
	map<int, int> count_map; // <A, A_count>

	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		int A;
		scanf("%d", &A);

		if(count_map.find(A) == count_map.end())
			count_map.insert({A, 1});
	}

	scanf("%d", &M);
	for(int i = 0; i < M; ++i) {
		int B;
		scanf("%d", &B);

		printf("%d\n", count_map.find(B) == count_map.end() ? 0 : 1);
	}
}
