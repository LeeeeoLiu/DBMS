/*
 * 钥控加密编程实现
 *
 * 姓名 刘元兴
 * 学号 20143714
 * 输入 明文 密钥
 * 输出 密文
 * 设计思想 将输入的明文存入 input 字符数组,将输入
 * 的密钥存入 key 字符数组和 prori 字符数组,使用
 * sort 函数对 prori 数组按字典增序进行快速排序,然后从0开始
 * 对 prori 数组中的元素与 key 数组中的元素进行比
 * 对,得到该元素在 key 数组中的 index,依次输出序号
 * 为 index,index+key 数组的长度, index+2*key
 * 数组的长度...的 input 数组元素,当 index+k*key
 * 数组的长度>input 数组的长度时跳出循环.
 * 编程语言 c++
 * 编译环境 CLion 2016.3
 * */
#include <iostream>
#include <algorithm>

#define MAXSIZE 100
using namespace std;
char input[MAXSIZE];
char key[MAXSIZE];
char prori[MAXSIZE];

int main() {
    cout << "作业一:钥控加密编程实现" << endl;
    cout << "请输入明文:" << endl;
    int inputCount = 0;
    int keyCount = 0;
    int index;
    int tmp;
    char c;
    c = cin.get();
    while (c != '\n') {
        if (c != ' ') {
            input[inputCount++] = c;
        }
        c = cin.get();
    }
    cout << "请输入密钥:" << endl;
    c = cin.get();
    while (c != '\n') {
        if (c != ' ') {
            key[keyCount] = c;
            prori[keyCount] = c;
            keyCount++;
        }
        c = cin.get();
    }
    sort(prori, prori + keyCount);
    for (int i = 0; i < keyCount; ++i) {
        index = 0;
        //得到按优先级排序的输出列号
        while (prori[i] != key[index]) {
            index++;
        }
        tmp = index;
        //循环输出 index 列
        while (tmp < inputCount) {
            cout << (char) toupper(input[tmp]);
            tmp = tmp + keyCount;
        }


    }
    cout << endl;
    return 0;
}