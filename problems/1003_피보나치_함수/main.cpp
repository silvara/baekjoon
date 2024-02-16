#include <cstdio>
using namespace std;

class ZeroOne {
  int zeros;
  int ones;
  bool is_set;

public:
  ZeroOne() {
    zeros = 0;
    ones = 0;
    is_set = false;
  }

  ZeroOne(int _zeros, int _ones) {
    zeros = _zeros;
    ones = _ones;
    is_set = true;
  }

  ZeroOne operator+(ZeroOne const &obj) {
    ZeroOne res;
    res.zeros = zeros + obj.zeros;
    res.ones = ones + obj.ones;
    return res;
  }

  ZeroOne operator=(ZeroOne const &obj) {
    zeros = obj.zeros;
    ones = obj.ones;
    is_set = true;
    return *this;
  }

  bool isSet() {
    return is_set;
  }

  void print() {
    printf("%d %d\n", zeros, ones);
  }
};

ZeroOne zeroones[41];

ZeroOne& fibonacci(int n) {
  if (n == 0) {
    return zeroones[0];
  } else if (n == 1) {
    return zeroones[1];
  } else if(zeroones[n].isSet()) {
    return zeroones[n];
  } else {
    zeroones[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return zeroones[n];
  }
}

int main() {
  zeroones[0] = ZeroOne(1, 0);
  zeroones[1] = ZeroOne(0, 1);

  int n_input;
  scanf("%d", &n_input);
  for(int i = 0; i < n_input; i++) {
    int n;
    scanf("%d", &n);

    ZeroOne zeroone = fibonacci(n);
    zeroone.print();
  }
}
