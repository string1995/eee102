#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

#define DOUBLE_MAX_LENGTH 6


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
        /* 默认构造 */
        Fraction(){
            ini();
            _bottom = 1;
        };
        /* 分子，分母输入构造 */
        Fraction(int top, int bottom){
            set(top, bottom);
        };
        /* 小数输入构造 */
        Fraction(double d){
            set(d);
        };

        /* 拷贝构造 */
        Fraction(const Fraction& obj){
            set(obj.top(), obj.bottom());
        };

        /* 析构 */
        ~Fraction(){};

        /* 加法重载 */
        Fraction operator+(const Fraction& obj){
            Fraction f(this->top() * obj.bottom() + this->bottom() * obj.top(), this->bottom() * obj.bottom());
            return f;
        }


        inline void set(int top = 0, int bottom = 1){
            ini();
            adjust_minus(top, bottom);
        }

        inline void set(double d = 0){
            ini();
            is_double_negative(d);

            if(get_long_int_length(get_double_decimals_part(d)) > 3) repeated_decimal_to_fraction(d);

            if(_bottom == 0) dec_to_frac_direct(d);

            simplify();
        }

        /* 提取小数结果 */
        inline double val() const{
            return (double)_top / _bottom * ((_isNegative) ? -1 : 1);
        }
        /* 提取string形式分数结果 */
        inline string toStr(){
            simplify();
            stringstream ss;
            ss << ((_isNegative) ? "-" : "") << _top << "/" << _bottom;
            return ss.str();
        };
        /* 提取分子 */
        inline int top() const{
            return ((_isNegative) ? -1 : 1) * (int) _top;
        }
        /* 提取分母 */
        inline int bottom() const{
            return (int)_bottom;
        }

    private:
        /* 主要变量 */
        unsigned int _top;
        unsigned int _bottom;
        bool _isNegative;


        /* 初始化 */
        inline void ini(){
            _top = 0;
            _bottom = 0;
            _isNegative = false;
        }

        /* 处理负号 */
        inline void adjust_minus(int top, int bottom){
            if(top < 0 && bottom < 0){
                _isNegative = false;
                _top = -1 * top;
                _bottom = -1 * bottom;
                return;
            }
            if(bottom < 0){
                _isNegative = true;
                _top = top;
                _bottom = -1 * bottom;
                return;
            }
            if(top < 0){
                _isNegative = true;
                _top = (-1 * top);
                _bottom = bottom;
                return;
            }
            _top = top;
            _bottom = bottom;
        }

        /* 处理分母为0 */
        inline void is_bottom_zero() const{
            if(_bottom == 0){
                throw "Division by zero condition!";
            }
        }

        /* 通分，找最大公约数 */
        int get_common_divisor() const;
        inline void simplify(){
            int t_divisor = get_common_divisor();

            _top /= t_divisor;
            _bottom /= t_divisor;
        }

        /* 针对double处理负号 */
        inline void is_double_negative(double& d){
            if(d < 0){
                d *= -1;
                _isNegative = true;
            }else{
                _isNegative = false;
            }
        }

        /* 小数强制转分数 */
        void dec_to_frac_direct(double d);

        /* 无限循环小数转分数 - 补丁 */
        unsigned long int transfer_double_decimals_to_unsigned_long_int_for_single(const double& d);

        /* 转换double小数部分到长整型 */
        unsigned long int transfer_double_decimals_to_unsigned_long_int(const double& d);

        /* 获取double小数整数部分 */
        inline unsigned long int get_double_integer_part(const double& d){
            return (unsigned long int)floor(fabs(d));
        }

        /* 获取double小数部分 */
        inline unsigned long int get_double_decimals_part(const double& d){
            double t;
            return transfer_double_decimals_to_unsigned_long_int(fabs(d) - floor(fabs(d)));
        } 

        /* 获取小数部分的某一位 */
        inline unsigned short get_one_decimal(const unsigned long int& t, unsigned short point){
            return (t / (unsigned int)pow(10, point - 1)) % 10;
        }

        /* 获取 int 长度 */
        unsigned short get_long_int_length(long int t);

        /* 获取循环小数循环体 */
        unsigned int get_repeat_part(const unsigned long int& t);

        /* 检查循环体顺序 */
        void confirm_repeat_part(const unsigned long int& t, unsigned int& repeat, unsigned short& start);

        /* 循环小数转分数 */
        void repeated_decimal_to_fraction(double d);


};



void Fraction::dec_to_frac_direct(double d)
{
    unsigned short t = get_long_int_length(get_double_decimals_part(d));

    _top = d * (int)pow(10, t);
    _bottom = (unsigned int)pow(10, t);
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




unsigned long int Fraction::transfer_double_decimals_to_unsigned_long_int_for_single(const double& d)
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


unsigned long int Fraction::transfer_double_decimals_to_unsigned_long_int(const double& d)
{
    if(transfer_double_decimals_to_unsigned_long_int_for_single(d)) return transfer_double_decimals_to_unsigned_long_int_for_single(d);

    unsigned long int t = (unsigned long int)(d*(1000000000));

    while(d != 0 && (t % (t/10) == 0 || t % (t/10) == 9) && t > 100) t /= 10;

    if((unsigned long int)(d*(1000000000)) % 1000 == 999) return ++t;

    return t;
}


unsigned short Fraction::get_long_int_length(long int t)
{
    int count = 0;
    while(t){

        t /= 10;
        count++;
    }

    return count;
}


unsigned int Fraction::get_repeat_part(const unsigned long int& t)
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

void Fraction::confirm_repeat_part(const unsigned long int& t, unsigned int& repeat, unsigned short& start)
{
    unsigned short len = get_long_int_length(repeat);

    for(unsigned short i = get_long_int_length(t); i > len; i--){

        bool k = false;

        if(len == 1 && get_one_decimal(t, i) == get_one_decimal(repeat, 1)) k = true;

        if(len == 2 && ((get_one_decimal(t, i) == get_one_decimal(repeat, 1) && get_one_decimal(t, i+1) == get_one_decimal(repeat, 2)) || (get_one_decimal(t, i+1) == get_one_decimal(repeat, 1) && get_one_decimal(t, i) == get_one_decimal(repeat, 2)))) k = true;

        if(len == 3 && ((get_one_decimal(t, i) == get_one_decimal(repeat, 1) && get_one_decimal(t, i+1) == get_one_decimal(repeat, 2) && get_one_decimal(t, i+2) == get_one_decimal(repeat, 3)) || (get_one_decimal(t, i+1) == get_one_decimal(repeat, 1) && get_one_decimal(t, i+2) == get_one_decimal(repeat, 2) && get_one_decimal(t, i) == get_one_decimal(repeat, 3)) || (get_one_decimal(t, i+2) == get_one_decimal(repeat, 1) && get_one_decimal(t, i) == get_one_decimal(repeat, 2) && get_one_decimal(t, i+1) == get_one_decimal(repeat, 3)))) k = true;
        
        if(k){
            repeat = t / (unsigned int)pow(10, i -1 - len) - (t / (unsigned int)pow(10, i - 1)) * (unsigned int)pow(10, len);
            start = i;
            break;
        }
    }
}

void Fraction::repeated_decimal_to_fraction(double d)
{

    unsigned long int t = get_double_decimals_part(d);

    unsigned short start = 0;
    unsigned int up, down = 0;

    unsigned int repeat = get_repeat_part(t);

    //cout << repeat << endl;

    confirm_repeat_part(t, repeat, start);

    //cout << repeat << endl;

    for(int i = 0; i < get_long_int_length(repeat); i++){

        down += 9 * (unsigned int)pow(10, i);
    }

    down *= (unsigned int)pow(10, (get_long_int_length(t) - start));

    //cout << down << endl;

    up = t % (unsigned int)pow(10, get_long_int_length(repeat));

    up = up + get_double_integer_part(d) * down;

    //cout << up << endl;
    _top = up;
    _bottom = down;
}




int main()
{
    vector<int> a;
    a.push_back(4);a.push_back(3);a.push_back(2);a.push_back(5);a.push_back(3);a.push_back(3);
    vector<int> b;
    b.push_back(2);b.push_back(4);b.push_back(3);b.push_back(5);

    Fraction f(-4,1);
    Fraction g(-4,1);
    Fraction k=f+g;

    Fraction l = f;

    double c;


   // for(int i =0; i < a.size(); i++) cout << a[i] <<endl;

    try{
        cout << k.toStr() << endl;

    //repeated_decimal_to_fraction(2.666);
    }catch(const char* msg){
        cerr << msg << endl;
    }

    return 0;
}