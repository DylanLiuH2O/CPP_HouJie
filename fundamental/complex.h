#ifndef __COMPLEX__ //防卫式声明，防止头文件重复包含
#define __COMPLEX__ //带#的是条件编译语句
#include <iostream>

class complex
{
public: //访问修饰符，public的成员可以通过对象直接调用，而private成员不允许直接通过对象访问
    complex(double r = 0, double i = 0)     //含有默认参数的构造函数，构造函数不含有返回值，构造函数一般必须是pulicd的，特殊情况下（如单例模式），构造函数可以是privated的
        : re(r), im(i)                      //初始化值列表，一个类的构造过程包括初始化、赋值，与在赋值阶段才给成员赋值相比，使用初始值列表更快
    {}
    complex& operator += (const complex&);  //对+=进行重载，
    double real() const { return re; }      //定义在class body内的函数自动会被列入inline函数候选列表，是否成为inline函数由编译器决定
    double imag() const { return im; }      //inline函数适用于较小、较为简单的函数，inline函数相比于普通函数来说较快
                                            //成员函数的右括号和花括号之间的const表明这是一个常量成员函数，常量成员函数不允许修改类成员
                                            //因此当函数明确不需要改变类成员时，最好标明const
private:
    double re, im; 

    friend complex& __doapl(complex*, const complex&);  //声明友元函数，友元函数可以直接访问该类的私有成员
                                                        //另外，相同class的不同object的成员函数互为友元
};

inline double
real(const complex& x)
{
    return x.real();
}

inline double
imag(const complex& x)
{
    return x.imag();
}

inline complex
conj(const complex& x)  //共轭复数
{
    return complex(real(x), - imag(x));
}

inline complex&
__doapl(complex* ths, const complex& r) //do assignment plus
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex& //运算应返回左边对象的引用
complex::operator += (const complex& rhs) //运算符右边的对象不需要改变，且传引用较快，因此使用const修饰，类型为引用
{
    return __doapl(this, rhs);    //该函数是类成员函数，因此包含一个该对象的隐式this指针
    //如果待返回的对象是在函数内新创建的（即local object）
    //由于其生命周期只有在函数内，因此应返回对象的拷贝
    //也就是return by value，而不应该return by reference
}
inline complex  //结果在函数内由一个临时对象生成，因此应该返回结果的拷贝，return by value
operator + (const complex& lhs, const complex& rhs)
{
    return complex( real(lhs) + real(rhs),
                    imag(lhs) + imag(rhs) );
}
inline complex
operator + (const complex& lhs, const double& rhs)
{
    return  complex( real(lhs) + rhs, imag(lhs));
}

inline complex
operator + (const double& lhs, const complex& rhs)
{
    return complex(lhs + real(rhs), imag(rhs));
}

inline complex
operator + (const complex& rhs)
{
    return rhs; //这里会生成一个local object，并return by value
}

inline complex
operator - (const complex& rhs)
{
    return complex(-real(rhs), -imag(rhs));
}

inline bool
operator == (const complex& lhs, const complex& rhs)
{
    return real(lhs) == real(rhs) && imag(lhs) == imag(rhs);
}

inline bool
operator == (const complex& lhs, const double& rhs)
{
    return real(lhs) == rhs && lhs.imag() == 0;
}

inline bool
operator == (const double& lhs, const complex& rhs)
{
    return lhs == real(rhs) && rhs.imag() == 0;
}

inline bool
operator != (const complex& lhs, const complex& rhs)
{
    return real(lhs) != real(rhs) || imag(lhs) != imag(rhs);
}

inline bool 
operator != (const complex& lhs, const double& rhs)
{
    return real(lhs) != rhs || imag(lhs) != 0;
}

inline bool 
operator != (const double& lhs, const complex& rhs)
{
    return lhs != real(rhs) || imag(rhs) != 0;
}

std::ostream&   //返回流的引用，则可以实现cout << a << b << ... << enl;连用
operator << (std::ostream& os, const complex& rhs)
{
    return os << '(' << real(rhs) << ','
              << imag(rhs) << ')';
}

#endif  //__COMPLEX__