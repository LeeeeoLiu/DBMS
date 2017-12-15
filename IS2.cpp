/*
 * 乘法逆元编程实现
 *
 * 姓名 刘元兴
 * 学号 20143714
 * 输入 a b
 * 输出 a 关于模 b 的乘法逆元
 * 设计思想 利用了 fermat 小定理
 * 编程语言 c++
 * 编译环境 CLion 2016.3
 * */
#include <iostream>

using namespace std;

/*
 * funcion  求最大公约数
 * input int int
 * return int
 *
 * */
int gcd(int a, int b) {
    return b != 0 ? gcd(b, a % b) : a;
}

/*
 * function 求a 的 b 次方
 * input int int
 * return int
 *
 * */
int mul(int a, int b) {
    int res = 1;
    if (b == 0)
        return 1;
    else {
        while (b > 0) {
            res = res * a;
            b--;
        }
        return res;
    }
}

int main() {
    int a, b;
    cout << "作业二:求乘法逆元" << endl;
    cout << "求 a 关于模 b 乘法逆元,请输入 a b(以空格分隔)" << endl;
    cin >> a >> b;
    if (gcd(a, b) == 1) {
        cout << a << "关于模" << b << "乘法逆元是" << mul(a, b - 2) % b << endl;  //fermat小定理
    } else {
        int tmp = 1;
        while (tmp * a % b != 1) {   //根据乘法逆元定义求解
            tmp++;
        }
        cout << a << "关于模" << b << "乘法逆元是" << tmp << endl;
    }

    return 0;
}