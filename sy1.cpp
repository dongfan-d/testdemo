#include <iostream>
#include <vector>

// ����GCD�����Լ����
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b;
    std::cout << "����������������GCD: ";
    std::cin >> a >> b;
    std::cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;
    return 0;
}

