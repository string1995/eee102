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




unsigned long int transfer_double_decimals_to_unsigned_long_int_for_single(const double& d)
{
    if(d > 0.09999999999 && d < 0.100000000001) return 1;
    if(d > 0.19999999999 && d < 0.200000000001) return 2;
    if(d > 0.29999999999 && d < 0.300000000001) return 3;
    if(d > 0.39999999999 && d < 0.400000000001) return 4;
    if(d > 0.49999999999 && d < 0.500000000001) return 5;
    if(d > 0.59999999999 && d < 0.600000000001) return 6;
    if(d > 0.69999999999 && d < 0.700000000001) return 7;
    if(d > 0.79999999999 && d < 0.800000000001) return 8;
    if(d > 0.89999999999 && d < 0.900000000001) return 9;
    return 0;
}


unsigned long int transfer_double_decimals_to_unsigned_long_int(const double& d)
{
    if(transfer_double_decimals_to_unsigned_long_int_for_single(d)) return transfer_double_decimals_to_unsigned_long_int_for_single(d);

    unsigned long int t = (unsigned long int)(d*(1000000000));

    while(d != 0 && (t % (t/10) == 0 || t % (t/10) == 9) && t > 100) t /= 10;

    if((unsigned long int)(d*(1000000000)) % 1000 == 999) return ++t;

    return t;
}


inline unsigned long int get_double_decimals_part(const double& d)
{
    double t;
    return transfer_double_decimals_to_unsigned_long_int(fabs(d) - floor(fabs(d)));
} 

inline unsigned long int get_double_integer_part(const double& d)
{
    return (unsigned long int)floor(fabs(d));
}

inline bool get_double_is_negative(const double& d)
{
    return (d < 0)? true : false;
}


inline unsigned short get_one_decimal(const unsigned long int& t, unsigned short point)
{
    return (t / (unsigned int)pow(10, point - 1)) % 10;
}

unsigned short get_long_int_length(long int t)
{
    int count = 0;
    while(t){

        t /= 10;
        count++;
    }

    return count;
}


unsigned int get_repeart_part(const unsigned long int& t)
{
    unsigned short i = 1;
    unsigned short len = get_long_int_length(t);

    while(i < len){

        unsigned short count = 0;
        while(i < len && get_one_decimal(t, ++i) != get_one_decimal(t, 1));

        for(unsigned short j = 1; j < i; j++){

            if(get_one_decimal(t, j) == get_one_decimal(t, j + i - 1)) count++;
        }

        if(count == i - 1) return t % (unsigned int)pow(10, i - 1);
    }

    return 0;
}
/*
void repeated_decimal_to_fraction(double d)
{
    get_double_integer_part(d)
    unsigned long int decimal = get_double_decimals_part(d);
    unsigned int body = get_repeart_part(decimal);

    for(unsigned short i = get_long_int_length(body); i < )

}

*/
int main()
{
    vector<int> a;
    a.push_back(4);a.push_back(3);a.push_back(2);a.push_back(5);a.push_back(3);a.push_back(3);
    vector<int> b;
    b.push_back(2);b.push_back(4);b.push_back(3);b.push_back(5);

    Fraction f(5,20);


    

   // for(int i =0; i < a.size(); i++) cout << a[i] <<endl;

    //try{

    cout << get_repeart_part(132123354) << endl ;
    //}catch(const char* msg){
     //   cerr << msg << endl;
    //}
    return 0;
}