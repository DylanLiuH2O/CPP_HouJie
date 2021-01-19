#include "string.h"
#include <iostream>

using namespace std;

int main()
{
    String s1("hello"); //测试构造函数
    String s2("world");
    cout << s1 << endl;
    cout << s2 << endl;

    String s3(s2);  //测试拷贝构造函数
    cout << s3 << endl; //测试操作符重载

    s3 = s1;    //测试拷贝赋值函数
    cout << s3 << endl;
    cout << s2 << endl;
    cout << s1 << endl;

    return 0;
}