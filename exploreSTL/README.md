## C++ STL体系结构课程小结

### STL六大部件
1. 容器(Containers)
2. 分配器(Allocators)
3. 算法(Algorithms)
4. 迭代器(Iterators)
5. 适配器(Adapters)
6. 仿函数(Functors)

### STL六大部件的关系
容器是存储数据的数据结构。  
分配器管理容器的内存。  
算法操作容器的数据。  
迭代器是容器和算法之间的桥梁，算法通过迭代器访问容器的元素。 
适配器起转换的作用。   
仿函数是作用像函数的类。

### 六大部件的使用示例
```c++
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main()
{
    int ia[6] = { 1, 2, 3, 4, 5, 6};
    vector<int, allocator<int>> vi(ia, ia+6);
        ↑           ↑
    container    allocator
           algorithm            iterator
               ↓                   ↓
    cout << count_if(vi.begin(), vi.end(), 
            not1(bind2nd(less<int>(), 40)));
                   ↑      ↑      ↑
                   |      | function_object
                function_adapter 

    return 0;
}
```

### 更方便的迭代 range-based for statement (since C++11)
自C++11开始，可以使用如下形式进行迭代。
```c++
for ( decl : coll ) {
    statement
}
```
```c++
for ( int i : { 2, 3, 4, 5} ) {
    cout << i << endl;
}
```
要注意的是，如果需要对元素进行修改，那么在声明变量的时候需要声明为引用。
```c++
vector<double> vec;
for ( auto elem : vec ) {
    cout << elem << endl;
}
for ( auto& elem : vec ) {
    elem *= 3;
}
```

### auto关键字 auto keyword(since C++11)
有些时候，某些类型的声明非常长，写起来很麻烦，C++11之后提供了auto关键字，编译器会自动对类型进行推导。  
应该注意的是，不应该滥用这一个关键字，在使用的时候最好清楚自己所需要的类型是什么。  