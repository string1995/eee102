#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

#define DOUBLE_MAX_LENGTH 6


namespace std {
string to_string(int val) {
    char buf[20];
    sprintf(buf, "%d", val);
    return string(buf);
}
 
string to_string(unsigned val) {
    char buf[20];
    sprintf(buf, "%u", val);
    return string(buf);
}
 
string to_string(long val) {
    char buf[20];
    sprintf(buf, "%ld", val);
    return string(buf);
}
 
string to_string(unsigned long val) {
    char buf[20];
    sprintf(buf, "%lu", val);
    return string(buf);
}
 
string to_string(float val) {
    char buf[200];
    sprintf(buf, "%f", val);
    return string(buf);
}
 
string to_string(double val) {
    char buf[2000];
    sprintf(buf, "%f", val);
    return string(buf);
}
string to_string(long double val) {
    char buf[20000];
    sprintf(buf, "%Lf", val);
    return string(buf);
}
}



using namespace std;

#define __method_2


bool is_in_vector(const int val, const vector<int>& v)
{
    for(int i = 0; i < v.size(); i++){

        if(val == v[i]) return true;
    }

    return false;
}

bool is_vec_a_in_b(const vector<int>& a, const vector<int>& b)
{
    int sameElements = 0;

    for(int i = 0; i < a.size(); i++){

        sameElements += is_in_vector(a[i], b);
    }

    return (sameElements == a.size()) ? true : false;
}


#ifdef __method_1

inline bool same_vec(const vector<int>& a, const vector<int>& b){

    return is_vec_a_in_b(a,b) && is_vec_a_in_b(b,a);
}

#endif


void next_diff_element(const vector<int>& v, int& pos)
{
    while(pos < v.size() - 1) {

        if(v[pos] != v[++pos]) return;
    }
}

#ifdef __method_2

bool same_vec(vector<int> a, vector<int> b){

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for(int posA, posB = 0; ; ){

        if(a[posA] != b[posB]) return false;

        if(posA >= a.size() - 1 && posB >= b.size() - 1) break;

        next_diff_element(a, posA);
        next_diff_element(b, posB);
    }

    return true;
}

#endif


class Fraction {

    public:
        Fraction(int top = 0, int bottom = 1);
        inline double val() const{
            return (double)_top/_bottom;
        }
        inline string toStr(){
            simplify();
            stringstream ss;
            ss << _top << "/" << _bottom;
            return ss.str();
        };

    private:
        int _top;
        int _bottom;
        void _check(){

        }
        inline void adjust_minus(){
            if(_bottom < 0){
                _top *= -1;
                _bottom *= -1;
            }
        }
        inline void is_bottom_zero() const{
            if(_bottom == 0){
                throw "Division by zero condition!";
            }
        }
        int get_common_divisor() const;
        inline void simplify(){
            int t_divisor = get_common_divisor();

            _top /= t_divisor;
            _bottom /= t_divisor;
        }

};


Fraction::Fraction(const int top, const int bottom)
{
    _top = top;
    _bottom = bottom;
}


int Fraction::get_common_divisor() const
{
    int t_top = _top;
    int t_bottom = _bottom;

    /* ensure that t_top is not smaller than t_buttom */
    if(t_top < t_bottom){
        t_top ^= t_bottom;
        t_bottom = t_top ^ t_bottom;
        t_top ^= t_bottom;
    }

    for(int tmp; t_bottom != 0;){

        tmp = t_top % t_bottom;
        t_top = t_bottom;
        t_bottom = tmp;
    }

    return t_top;
}

/*
void get_decimal_repeating_part(double f)
{
    double t_dec = f - (int)f;

    
}
*/
int get_double_decimals_length(double d)
{
    ostringstream out;
    //out.precision(18);//覆盖默认精度
    out<<d;
    string s= out.str();
    return s.length();
}


/* 两位以上*/
unsigned long int transfer_double_decimals_to_unsigned_long_int(double d)
{
    unsigned long int t = (unsigned long int)(d*(1000000000));

    while(d != 0 && t % (t/10) == 0 && t > 100) t /= 10;

    return t;
}


inline unsigned long int get_double_decimals_part(double d)
{
    return transfer_double_decimals_to_unsigned_long_int(d-floor(d));
} 





int main()
{
    vector<int> a;
    a.push_back(4);a.push_back(3);a.push_back(2);a.push_back(5);a.push_back(3);a.push_back(3);
    vector<int> b;
    b.push_back(2);b.push_back(4);b.push_back(3);b.push_back(5);

    Fraction f(5,20);


    

   // for(int i =0; i < a.size(); i++) cout << a[i] <<endl;

    //try{
    cout << get_double_decimals_part(34234)<<endl;
    //cout << f.val();
    //}catch(const char* msg){
     //   cerr << msg << endl;
    //}
    return 0;
}