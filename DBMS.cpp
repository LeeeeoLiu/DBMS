/*
 * DBMS.cpp
 *
 * Created by Leeeeo on 2017.3.30
 *
 * Input   学生(学号:是,姓名:否,性别:否,年龄:否)
 *         课程(课程号:是,课程名:否,学分:否)
 *         选课(学生:学号,课程:课程号,成绩)
 *
 * Output  学生.txt
 *         #学生,学号:主键,姓名,性别,年龄
 *         课程.txt
 *         #选课,学生:主键,课程:主键,成绩
 *
 * Description just a easy case for simple m:n convert from ER Model to Data Model
 */

#include <iostream>
#include <fstream>

#define MAX_LENTH 10000

using namespace std;

int main() {
    string entityA, entityB, assoAB, tmpStr;
    int flag = 0;
    cin >> entityA;
    cin >> entityB;
    cin >> assoAB;

    tmpStr = entityA;
    while (tmpStr != "") {
        string tmpStrName = tmpStr.substr(0, tmpStr.find("("));
        ofstream outFile;
        outFile.open(tmpStrName + ".txt");
        outFile << "#" << tmpStrName << ",";
        if (tmpStr.substr(tmpStr.find(":") + 1, tmpStr.find(",") - tmpStr.find(":") - 1) == "是") {
            outFile << tmpStr.substr(tmpStr.find("(") + 1, tmpStr.find(":") - tmpStr.find("(") - 1) << ":主键";
        } else
            outFile << tmpStr.substr(tmpStr.find("(") + 1, tmpStr.find(":") - tmpStr.find("(") - 1);
        while (tmpStr.find(",") < MAX_LENTH) {
            tmpStr = tmpStr.substr(tmpStr.find(",") + 1, tmpStr.size() - tmpStr.find(",") + 1);
            if (tmpStr.substr(tmpStr.find(":") + 1, tmpStr.find(",") - tmpStr.find(":") - 1) == "是") {
                outFile << "," << tmpStr.substr(0, tmpStr.find(":")) << ":主键";
            } else {
                outFile << "," << tmpStr.substr(0, tmpStr.find(":"));
            }
        }
        if (tmpStr.substr(tmpStr.find(":") + 1, tmpStr.find(")") - tmpStr.find(":") - 1) == "是") {
            outFile << ":主键";
        }
        outFile.close();
        tmpStr = entityB;
        if (flag)
            break;
        flag = 1;
    }

    tmpStr = assoAB;
    string tmpStrName = tmpStr.substr(0, tmpStr.find("("));
    ofstream outFile;
    outFile.open(tmpStrName + ".txt");
    outFile << "#" << tmpStrName << ",";
    outFile << tmpStr.substr(tmpStr.find("(") + 1, tmpStr.find(":") - tmpStr.find("(") - 1) << ":主键";
    tmpStr = tmpStr.substr(tmpStr.find(",") + 1, tmpStr.size() - tmpStr.find(",") + 1);
    outFile << "," << tmpStr.substr(tmpStr.find("(") + 1, tmpStr.find(":") - tmpStr.find("(") - 1) << ":主键";
    tmpStr = tmpStr.substr(tmpStr.find(",") + 1, tmpStr.size() - tmpStr.find(",") + 1);

    while (tmpStr.find(",") < MAX_LENTH) {
        outFile << "," << tmpStr.substr(0, tmpStr.find(","));
        tmpStr = tmpStr.substr(tmpStr.find(",") + 1, tmpStr.size() - tmpStr.find(",") + 1);
    }
    outFile << "," << tmpStr.substr(0, tmpStr.find(")"));
    outFile.close();

    return 0;
}
