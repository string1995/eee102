#include <iostream>
#include <cstdlib>
#include "Fraction.h"

using namespace std;

int main()
{
    iFraction a;
    iFraction b(1,3,-4);
    iFraction c = convertF(Fraction(3,-4));
    iFraction d(-3.14);
    iFraction e = 1.333333;
    iFraction f = -b;



    cout << "Output in iFraction Form: " << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
    cout << "d: " << d << endl;
    cout << "e: " << e << endl;
    cout << "f: " << f << endl << endl;


    cout << "Output in Decimals Form: " << endl;
    cout << "a: " << a.val() << endl;
    cout << "b: " << b.val() << endl;
    cout << "c: " << c.val() << endl;
    cout << "d: " << d.val() << endl;
    cout << "e: " << e.val() << endl;
    cout << "f: " << f.val() << endl << endl;


    cout << "Output integer: " << endl;
    cout << "a: " << a.integer() << endl;
    cout << "b: " << b.integer() << endl;
    cout << "c: " << c.integer() << endl;
    cout << "d: " << d.integer() << endl;
    cout << "e: " << e.integer() << endl;
    cout << "f: " << f.integer() << endl << endl;


    cout << "Output Numerator: " << endl;
    cout << "a: " << a.itop() << endl;
    cout << "b: " << b.itop() << endl;
    cout << "c: " << c.itop() << endl;
    cout << "d: " << d.itop() << endl;
    cout << "e: " << e.itop() << endl;
    cout << "f: " << f.itop() << endl << endl;


    cout << "Output Denominator: " << endl;
    cout << "a: " << a.bottom() << endl;
    cout << "b: " << b.bottom() << endl;
    cout << "c: " << c.bottom() << endl;
    cout << "d: " << d.bottom() << endl;
    cout << "e: " << e.bottom() << endl;
    cout << "f: " << f.bottom() << endl << endl;

    cout << "-b = " << -b << endl;
    cout << "~b = " << ~b << endl << endl;


    cout << b << " + " << e << " = " << b+e << endl;
    cout << b << " - " << e << " = " << b-e << endl;
    cout << b << " * " << e << " = " << b*e << endl;
    cout << b << " / " << e << " = " << b/e << endl;
    cout << e << " % " << c << " = " << e%c << endl << endl;

    cout << b << " + " << 4.44 << " = " << b+4.44 << endl;
    cout << 4.44 << " + " << b << " = " << 4.44+b << endl;
    cout << b << " - " << 3 << " = " << b-3 << endl;
    cout << b << " * " << 2.33333 << " = " << b*2.33333 << endl;
    cout << 2.33333 << " * " << b << " = " << 2.33333*b << endl;
    cout << b << " / " << 5 << " = " << b/5 << endl;
    cout << e << " % " << 1 << " = " << e%1 << endl << endl;

    cout << "b++ = " << b++;
    cout << "; b = " << b << endl;
    cout << "++b = " << ++b;
    cout << "; b = " << b << endl;

    cout << "b-- = " << b--;
    cout << "; b = " << b << endl;
    cout << "--b = " << --b;
    cout << "; b = " << b << endl << endl;


    cout << "b += c; b = " << (b+=c) << endl;
    cout << "b -= c; b = " << (b-=c) << endl;
    cout << "b *= c; b = " << (b*=c) << endl;
    cout << "b /= c; b = " << (b/=c) << endl << endl;


    cout << "if b > c ?? " << ((b>c)? "Yes" : "No") << endl;
    cout << "if b < c ?? " << ((b<c)? "Yes" : "No") << endl;
    cout << "if b >= c ?? " << ((b>=c)? "Yes" : "No") << endl;
    cout << "if b <= c ?? " << ((b<=c)? "Yes" : "No") << endl;
    cout << "if b == c ?? " << ((b==c)? "Yes" : "No") << endl;
    cout << "if b == -f ?? " << ((b==-f)? "Yes" : "No") << endl;
    cout << "if b != c ?? " << ((b!=c)? "Yes" : "No") << endl << endl;


    cout << "Devide 0 test: ";

    try{
        iFraction g(2,1,0);
    }catch(const char* msg){
        cout << msg << endl;
    }

    cout << endl << "************ This is the END of TEST section !! ************" << endl << endl;
    system("pause");

    return 0;
}