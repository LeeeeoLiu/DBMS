/*
 * 换位密码编程实现
 *
 * 姓名 刘元兴
 * 学号 20143714
 * 输入 明文
 * 输出 列换位加密密文 周期换位加密密文
 * 设计思想 通过优先级数组 prior 中的输出顺序
 * 使用数学表示控制数组下标将数组输出
 * 编程语言 c++
 * 编译环境 CLion 2016.3
 * */
#include <iostream>

#define MAXSIZE 100
using namespace std;
char input[MAXSIZE];
int prior[4] = {2, 4, 1, 3};

int main() {
    cout << "作业二:换位密码编程实现" << endl;
    cout << "请输入明文:" << endl;
    char c;
    int inputCount = 0;
    c = cin.get();
    while (c != '\n') {
        if (c != ' ') {
            input[inputCount++] = (char) toupper(c);
        }
        c = cin.get();
    }
    cout << "列换位加密,若矩阵为3x4,按照2-4-1-3的顺序加密,则密文为:" << endl;
    for (int i = 0; i < 4; ++i) {
        int tmp = prior[i] - 1;
        //循环输出 tmp 列
        while (tmp < inputCount) {
            cout << (char) toupper(input[tmp]);
            tmp = tmp + 4;
        }
    }
    cout << endl;
    cout << "周期换位加密,若周期为4,f为" << endl << "i:       1   2   3   4" << endl << "f(i):    2   4   1   3" << endl << "则密文为:"
         << endl;
    int d = 0;
    int tmp = 0;
    while (inputCount > 0) {
        if (d == 4) {
            d = 0;
            tmp += 4;
        }
        cout << input[prior[d++] + tmp - 1];
        inputCount--;
    }
    cout << endl;
    return 0;
}