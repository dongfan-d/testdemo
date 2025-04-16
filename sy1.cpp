#include <iostream>
#include <vector>

// 计算GCD（最大公约数）
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b;
    std::cout << "输入两个整数计算GCD: ";
    std::cin >> a >> b;
    std::cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;
    return 0;
}

