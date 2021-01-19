#ifndef __STRING__
#define __STRING__

#include <iostream>
#include <cstdlib>
#include <cstring>

class String
{
public:
    String(const char *cstr = 0);           //含默认参数的构造函数
    String(const String &str);              //拷贝构造函数
    String& operator=(const String &str);   //拷贝赋值函数
    ~String();                              //析构函数
    char *get_c_str() const { return m_data; }

private:
    char *m_data;
};

inline
String::String(const char *cstr)
{
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    } else {
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::String(const String &str)
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

inline
String& String::operator=(const String &str)
{
    if (this == &str)
        return *this;

    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

inline
String::~String()
{
    delete[] m_data;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.get_c_str();
    return os;
}


#endif