#include <iostream>
#include "Fraction.h"

using namespace std;

int main()
{
    Fraction a;
    Fraction b(3,-4);
    Fraction c(5);
    Fraction d(-3.14);
    Fraction e = 1.333333;
    Fraction f = -b;


    Fraction q(-3.2);

    iFraction p(q);

    p += q + p;

    //q = p;

    iFraction o;


    cout << convertF(convertF(q));


/*
    cout << "Output in Fraction Form: " << endl;
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


    cout << "Output Numerator: " << endl;
    cout << "a: " << a.top() << endl;
    cout << "b: " << b.top() << endl;
    cout << "c: " << c.top() << endl;
    cout << "d: " << d.top() << endl;
    cout << "e: " << e.top() << endl;
    cout << "f: " << f.top() << endl << endl;


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
        Fraction g(1,0);
    }catch(const char* msg){
        cout << msg << endl;
    }

    cout << endl << "************ This is the END of TEST section !! ************" << endl << endl;
    cout << "Have a try by YOURSELF!!    (Press Ctrl+C to quit)" << endl;

    while(1){

        try{
            cout << endl << "Please Input a Fraction(-3/5) or a Decimals(e.g. 3.14): ";
            cin >> a;
            cout << a << endl;
        }catch(const char* msg){
            cout << endl << msg << endl;
        }


    }
    */
    return 0;
}