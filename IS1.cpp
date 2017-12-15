/*
 * 双轨密码编程实现
 *
 * 姓名 刘元兴
 * 学号 20143714
 * 输入 明文
 * 输出 密文
 * 设计思想 从输入流中按字符逐个读取非空格字符
 * 设置奇偶标识,将奇数输入字符存入 odd 数组,
 * 将偶数输入字符存入 even 数组,输入完毕后先
 * 输出 odd 数组,再输出 even 数组即可.
 * 编程语言 c++
 * 编译环境 CLion 2016.3
 * */
#include <iostream>

#define MAXSIZE 100

using namespace std;
char odd[MAXSIZE];
char even[MAXSIZE];

int main() {
    int mark = 1;   //0表示偶数,1表示奇数
    int oddCount = 0;
    int evenCount = 0;
    char c;
    cout << "作业一:双轨密码编程实现" << endl;
    c = cin.get();
    while (c != '\n') {
        if (c != ' ') {
            if (mark == 1) {
                odd[oddCount++] = c;
                mark = 0;
            } else {
                even[evenCount++] = c;
                mark = 1;
            }
        }
        c = cin.get();
    }
    for (int i = 0; i < oddCount; ++i) {
        if (i == 0)
            cout << (char) toupper(odd[i]);
        else
            cout << (char) tolower(odd[i]);
    }
    cout << " ";
    for (int j = 0; j < evenCount; ++j) {
        if (j == 0)
            cout << (char) toupper(even[j]);
        else
            cout << (char) tolower(even[j]);
    }
    cout << endl;
    return 0;
}