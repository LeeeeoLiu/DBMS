/*
 * Vigenere编程实现
 *
 * 姓名 刘元兴
 * 学号 20143714
 * 输入 明文 密钥
 * 输出 密文
 * 设计思想 将输入的明文存入 input 字符数组,给密钥
 * 设置一个 keyindex (从0开始)来标记当前已经使用到
 * 的密钥元素,若 keyindex 等于密钥长度,则初始化为0;
 * 依次取出 input 字符数组中的元素,减去'A'与密钥元
 * 素减去'A'的差相加,结果模上26,再加上'A',这样可以
 * 省去构造一个 Vigenere 表的空间
 * 编程语言 c++
 * 编译环境 CLion 2016.3
 * */
#include <iostream>

#define MAXSIZE 100
using namespace std;
char key[11] = {'L', 'I', 'U', 'Y', 'U', 'A', 'N', 'X', 'I', 'N', 'G'};
int keySize = sizeof(key);
char input[MAXSIZE];

int main() {
    cout << "作业三:Vigenere编程实现" << endl;
    cout << "(密钥为 LIUYUANXING )" << endl;
    cout << "请输入明文:" << endl;
    int inputCount = 0;
    int keyCount = 0;
    int keyIndex = 0;
    int tmp;
    char c;
    c = cin.get();
    while (c != '\n') {
        if (c != ' ') {
            input[inputCount++] = (char) toupper(c);
        }
        c = cin.get();
    }
    cout << "Vigenere加密结果:" << endl;
    for (int i = 0; i < inputCount; ++i) {
        if (keyIndex == keySize)
            keyIndex = 0;
        cout << (char) ((input[i] - 'A' + key[keyIndex++] - 'A') % 26 + 'A');  //根据 fi(a)=(a+ki)mod n 计算输出
    }

    return 0;
}