#include <iostream>
#include "complex.h"
using namespace std;

int main()
{
    complex c1(2, 1);
    complex c2;
    complex c3;


    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;

    cout << endl;

    c2 = c1 + 5;    cout << "c2 = c1 + 5,  c2: " << c2 << endl;
    c2 = 7 + c1;    cout << "c2 = 7 + c1,  c2: " << c2 << endl;
    c2 = c1 + c2;   cout << "c2 = c1 + c2, c2: " << c2 << endl;
    c2 += c1;       cout << "c2 += c1,     c2: " << c2 << endl;
    c2 += 3;        cout << "c2 += 3,      c2: " << c2 << endl;
    c2 = -c1;       cout << "c2 = -c1,     c2: " << c2 << endl;
    c3 = +c1;       cout << "c3 = +c1,     c3: " << c3 << endl;

    cout << endl;

    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;

    cout << endl;

    cout << "(c1 == c2): " << (c1 == c2) << endl;
    cout << "(c1 != c2): " << (c1 != c2) << endl;
    cout << "(c1 == c3): " << (c1 == c3) << endl;
    cout << "(c1 != c3): " << (c1 != c3) << endl;
    cout << "conj(c1): " << conj(c1) << endl;

    return 0;
}
/*output:
c1: (2,1)
c2: (0,0)
c3: (0,0)

c2 = c1 + 5,  c2: (7,1)
c2 = 7 + c1,  c2: (9,1)
c2 = c1 + c2, c2: (11,2)
c2 += c1,     c2: (13,3)
c2 += 3,      c2: (16,3)
c2 = -c1,     c2: (-2,-1)
c3 = +c1,     c3: (2,1)

c1: (2,1)
c2: (-2,-1)
c3: (2,1)

(c1 == c2): 0
(c1 != c2): 1
(c1 == c3): 1
(c1 != c3): 0
conj(c1): (2,-1)
*/