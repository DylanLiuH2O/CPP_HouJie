## 基础课小结

### 上部

#### 头文件的防卫式声明

防止头文件重复包含发生冲突

``` c++
#ifndef __NAME__
#define __NAME__
...
...
#endif 
```

#### 类的定义

```c++
class complex
{
public:
	...
private:
    ...
};
```

####  inline内联函数

1. 声明在类内的函数自动成为候选内联函数，是否成为内联函数取决于编译器。
2. 使用inline修饰的函数也会成为候选内联函数，但是否成为内联函数同样取决于编译器。

#### 类成员的访问修饰符

1. public的成员可以通过对象调用。
2. private的成员不允许通过对象调用。
3. protected。

#### 构造函数

1. 构造函数没有返回值。
2. 构造函数一般是public的，特殊情况下可以是private的（单例模式）。
3. 可以使用初始化值列表对类成员进行初始化，注意它和赋值的区别。
4. 不能同时存在含有默认参数和没有参数的构造函数，在不使用参数新建对象时会发生冲突。

类的构造过程包括**初始化**、**赋值**......

#### 常量成员函数

当一个函数不需要修改成员变量时，使用const标记使其成为常量成员函数。

```c++
class complex
{
public:
    ...
    double real() const { return re; }
private:
    ...
}
```

#### 友元函数

被friend修饰的函数是友元函数，友元函数是非成员函数但可以访问该类的成员。

相同class的不同object的成员函数互为友元。

#### 函数参数传递

1. 按值传递
2. 按引用传递

设计函数时，首先考虑传引用，传引用比传值更快，尤其是传递对象的情况下，传值需要对对象进行拷贝，会花费较多的时间。

#### 函数返回值

1. 按值返回
2. 按引用返回

当需要返回的对象是在函数内部生成时，应该按值返回，而不应该按引用返回，因为在函数内部生成的对象，作用域在函数内，在函数结束后，自动调用析构函数进行销毁，其生命周期只在函数内。

在涉及流的引用的函数，返回流的引用可以实现输出连用，如下：

```c++
std::ostream&   //返回流的引用，则可以实现cout << a << b << ... << enl;连用
operator << (std::ostream& os, const complex& rhs)
{
    return os << '(' << real(rhs) << ','
              << imag(rhs) << ')';
}
```



#### 操作符重载

1. 成员函数操作符重载

   此类操作符重载函数参数含有隐式的this指针。

   应返回本对象的引用。

2. 非成员函数操作符重载

   该类操作符重载一般会在函数内部生成一个临时对象用作返回值，应按值返回，因为临时对象的生命周期只有在函数内。

   带有流操作的非成员操作符重载，应返回流的引用。




#### Big Three 三个特殊函数

1.  拷贝构造函数
2.  拷贝赋值函数
3.  析构函数

带有指针成员的类必须有拷贝构造和拷贝赋值函数。

如果使用编译器默认的拷贝赋值函数或拷贝构造函数，得到的拷贝只能是浅拷贝。

使用默认拷贝构造函数时，构造时仅仅使新对象的成员指针等于被拷贝对象的成员指针，而并没有申请新的动态空间并拷贝内容。

使用默认的拷贝赋值函数时，亦仅仅使成员指针指向被拷贝对象的动态内存，而原来的内存并没有释放，导致内存泄漏。

在设计拷贝赋值函数时，一定要注意检测**自我赋值**，否则会导致错误。

```c++
inline
String& String::operator=(const String& str)
{
    //检测自我赋值
	if (this == &str)
		return *this;
    
	delete[] m_data;	//①
	m_data = new char[ strlen(str.m_data) + 1 ]; //②
	strcpy(m_data, str.m_data);	//③
	return *this;
}
```

设计拷贝赋值函数遵循四步：①检测自我赋值 ②释放原对象成员指针动态分配的内存 ③分配新空间 ④复制内容



#### Stack栈和Heap堆

1. Stack

   是存在于某作用域（scope）的一块内存空间，调用函数时，函数会有一个Stack用于存储接收的参数及返回地址，函数结束后，栈空间将被回收。

2. Heap

   是一块由操作系统提供的全局内存空间，程序动态分配的内存空间就在这里。空间需要手动回收。

#### 不同种类对象的生命周期

1. stack objects

   ```c++
   class Comples {...};
   ...
   {
       Complex c1(1,2);
   }
   ```

   

   其生命周期所在作用域结束后结束。

   又称为auto object，因为它会被自动回收。

2. static local objects

   ```c++
   class Comples {...};
   ...
   {
       static Complex c1(1,2);
   }
   ```

   

   其生命周期直到程序结束。

3. global objects

   ```c++
   class Comples {...};
   ...
   Complex c3(1,2);
       
   int main()
   {
       ...
   }
   ```

   

   存在于所有作用域之外，其生命周期直到程序结束。

4. heap objects

   ```c++
   class Complex { … };
   ...
   {
   Complex* p = new Complex;
   ...
   delete p;
   }
   ```

   

   其生命周期直到它被delete后结束。

#### 对象创建回收与其内存模型

`留坑待填`



### 下部

#### 转换函数 conversion function

```c++
//定义
class Fraction
{
public:
    Fraction(int num, int den=1)
        : m_numerator(num), m_denominator(den) {}
    //转换函数
    operator double() const {
        return (double)(m_numerator / m_denominator);
    }
private:
    int m_numerator;
    int m_denominator;
}
```



```c++
//调用
Fraction f(3,5);
double d = 4 + f; //这里会调用operator double()将f转换为double类型的数值
```



#### 非explicit单参数构造函数 non-explicit-one-argument ctor （构造函数）

```c++
class Fraction
{
public:
    //这里的构造函数没有用explicit修饰，即non-explicit，且仅需提供一个参数即可构造
    //即one-argument,one-argument意味最少提供一个实参
    Fraction(int num, int den=1)
        : m_numerator(num), m_denominator(den) {}
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
}
```



```c++
//调用
Fraction f(3,5);
Fraction d2 = f + 4;
```

上面代码段中的d2是Fraction类型，因此编译器会试图将后面的表达式转换为Fraction类型，由于Fraction类型的构造函数是non-explicit-one-argument的，所以编译器会将4使用构造函数，转换为Fraction类型的对象，再调用Fraction类型的+重载，对两个Fraction对象进行运算，返回一个Fraction对象。

#### conversion vs. non-explicit-one-argument ctor

对比这转换函数和non-explicit-one-argument ctor，可以发现它们都实现了转换的效果。但是当两种同时存在时，有可能会出现歧义。

```c++
class Fraction
{
public:
    Fraction(int num, int den=1)
        : m_numerator(num), m_denominator(den) {}
    operator double() const {
        return (double)(m_numerator / m_denominator);
    }
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
}
```

这时候如果编译代码

```c++
Fraction f(3,5);
Fraction d2 = f + 4;
```

会提示

```
main.cpp: In function ‘int main()’:
main.cpp:34:19: error: ambiguous overload for ‘operator+’ (operand types are ‘Fraction’ and ‘int’)
    Fraction d = f + 4;
                 ~~^~~
```

这是由于f可以通过转换函数转换为double型数值，然后与4运算，最后结果通过构造函数转换为Fraction对象，并且4也可以通过构造函数转换为Fraction对象，再调用重载的+运算符进行运算，得到Fraction对象，所以编译器无法确定通过哪种路径来进行转换，于是乎编译出错。

#### explicit单参数构造函数 explicit-one-argument ctor

为了解决前面所说的问题，我们可以给构造函数加上explicit进行修饰，来告诉编译器，不要在没有写明调用构造函数时，去隐式自动调用构造函数来进行转换。

```c++
class Fraction
{
public:
    //加上explicit修饰
    explicit Fraction(int num, int den=1)
        : m_numerator(num), m_denominator(den) {}
    operator double() const {
        return (double)(m_numerator / m_denominator);
    }
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
}
```



```c++
Fraction f(3,5);
Fraction d = f + 4;
```

这时候编译代码提示

```
main.cpp: In function ‘int main()’:
main.cpp:34:19: error: conversion from ‘double’ to non-scalar type ‘Fraction’ requested
    Fraction d = f + 4;
                 ~~^~~
```

因为对构造函数使用explicit修饰之后，禁止了编译器隐式调用构造函数进行转换，而此前两条路径都会用到隐式调用构造函数进行转换，因此这时候转换无法完成，编译报错。

对第一条路径进行分析：f可以通过转换函数转换为double型数值，然后与4进行运算得到double数值，但是这时候由于构造函数使用了explicit，无法将double数值隐式构造成为一个Fraction对象，转换失败。

对第二条路径进行分析：4原来可以通过构造函数转换为一个Fraction对象，而现在构造函数使用了explicit修饰，不允许隐式构造，因此转换失败。

那么正确的做法是，对构造函数使用explicit修饰之后，为f + 4这种情况新增一个运算符重载

```c++
class Fraction
{
public:
    explicit Fraction(int num, int den=1)
        : m_numerator(num), m_denominator(den) {}
    operator double() const {
        return (double)(m_numerator / m_denominator);
    }
    //新增运算符重载，右边参数是int类型
    Fraction operator+(int x) {
        return Fraction(...);
    }
    Fraction operator+(const Fraction& f) {
        return Fraction(...);
    }
private:
    int m_numerator;
    int m_denominator;
}
```

此时代码编译通过。