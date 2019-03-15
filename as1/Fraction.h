
/**
 * 分数运算 Fraction 
 *
 * @category eee102-as1
 * @package Fraction.h
 * @copyright Copyright (c) 2019 Yimian LIU (https://iotcat.me)
 * @license GNU General Public License 2.0
 * @version 0.0.1
 */


#ifndef _Fraction_H_
#define _Fraction_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;


/**
 * 分数运算
 *
 * @author yimian LIU
 * @category eee102-as1
 * @package Fraction.h
 */
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
        Fraction operator +(const Fraction& obj) const{
            return Fraction(this->top() * obj.bottom() + this->bottom() * obj.top(), this->bottom() * obj.bottom());
        };

        /* 减法重载 */
        Fraction operator -(const Fraction& obj) const{
            return Fraction(this->top() * obj.bottom() - this->bottom() * obj.top(), this->bottom() * obj.bottom());
        };

        /* 乘法重载 */
        Fraction operator *(const Fraction& obj) const{
            return Fraction(this->top() * obj.top(), this->bottom() * obj.bottom());
        };

        /* 除法重载 */
        Fraction operator /(const Fraction& obj) const{
            return Fraction(this->top() * obj.bottom(), this->bottom() * obj.top());
        };

        /* 求余重载 */
        Fraction operator %(const Fraction& obj) const{
            return Fraction(fmod(this->val(), obj.val()));
        };

        /* 求余重载 */
        Fraction operator %(const int t) const{
            return Fraction(fmod(this->val(), t));
        };

        /* 求余重载 */
        Fraction operator %(const double t) const{
            return Fraction(fmod(this->val(), t));
        };

        /* 负号重载 */
        Fraction operator -() const{
            return Fraction(-this->top(), this->bottom());
        };

        /* 倒数重载 */
        Fraction operator ~() const{
            return Fraction(this->bottom(), this->top());
        };

        /* 小于号重载 */
        bool operator <(const Fraction& obj) const{
            return (this->val() < obj.val())? true : false;
        };

        /* 小于等于号重载 */
        bool operator <=(const Fraction& obj) const{
            return (this->val() <= obj.val())? true : false;
        };

        /* 大于号重载 */
        bool operator >(const Fraction& obj) const{
            return (this->val() > obj.val())? true : false;
        };

        /* 大于等于号重载 */
        bool operator >=(const Fraction& obj) const{
            return (this->val() >= obj.val())? true : false;
        };

        /* 等于号重载 */
        bool operator ==(const Fraction& obj) const{
            return (this->top() == obj.top() && this->bottom() == obj.bottom())? true : false;
        };

        /* 不等于号重载 */
        bool operator !=(const Fraction& obj) const{
            return (!(this->top() == obj.top() && this->bottom() == obj.bottom()))? true : false;
        };

        /* 前++重载 */
        Fraction operator ++(){
            if(_isNegative) _top -= _bottom;
            else _top += _bottom;
            return *this;
        };

        /* 后++重载 */
        Fraction operator ++(int){
            Fraction f = *this;
            if(_isNegative) _top -= _bottom;
            else _top += _bottom;
            return f;
        };

        /* 前--重载 */
        Fraction operator --(){
            if(_isNegative) _top += _bottom;
            else _top -= _bottom;
            return *this;
        };

        /* 后--重载 */
        Fraction operator --(int){
            Fraction f = *this;
            if(_isNegative) _top += _bottom;
            else _top -= _bottom;
            return f;
        };

        /* 赋值重载 */
        void operator =(const Fraction& obj){ 
            set(obj.top(), obj.bottom());
        };

        /* 赋值重载 */
        void operator =(const double& d){ 
            set(d);
        };

        /* 加法赋值重载 */
        Fraction operator +=(const Fraction& obj){
            set(this->top() * obj.bottom() + this->bottom() * obj.top(), this->bottom() * obj.bottom());
            return *this;
        };

        /* 减法赋值重载 */
        Fraction operator -=(const Fraction& obj){
            set(this->top() * obj.bottom() - this->bottom() * obj.top(), this->bottom() * obj.bottom());
            return *this;
        };

        /* 乘法赋值重载 */
        Fraction operator *=(const Fraction& obj){
            set(this->top() * obj.top(), this->bottom() * obj.bottom());
            return *this;
        };

        /* 除法赋值重载 */
        Fraction operator /=(const Fraction& obj){
            set(this->top() * obj.bottom(), this->bottom() * obj.top());
            return *this;
        };

        /* 输出流重载 */
        friend ostream &operator <<(ostream &o, Fraction f){ 
            o << f.toStr();
            return o;
        };

        /* 输入流重载 */
        friend istream &operator >>(istream &i, Fraction &f){
            string s;
            stringstream ss;
            i >> s;
            if(s.find("/") != s.npos){
                int top, bottom;

                ss << s.substr(0, s.find("/"));
                ss >> top;
                ss.clear(); //清stream缓存
                ss.str("");
                ss << s.substr(s.find("/") + 1);
                ss >> bottom;
                f.set(top, bottom);
            }else{
                double val;
                ss << s;
                ss >> val;
                f.set(val);
            }
        };

        /* 分数形式输入配置 */
        inline void set(int top = 0, int bottom = 1){
            ini();
            adjust_minus(top, bottom);
            is_bottom_zero();
            simplify();
        };

        /* 小数形式输入配置 */
        inline void set(double d = 0){
            ini();
            is_double_negative(d);

            if(get_long_int_length(get_double_decimals_part(d)) > 3) repeated_decimal_to_fraction(d);

            if(_bottom == 0) dec_to_frac_direct(d);

            simplify();
        };

        /* 提取小数结果 */
        inline double val() const{
            return (double)_top / _bottom * ((_isNegative) ? -1 : 1);
        }

        /* 提取string形式分数结果 */
        inline string toStr(){
            stringstream ss;
            if(_top == 0) return "0";
            ss << ((_isNegative) ? "-" : "") << _top << ((_bottom == 1)? "" : "/");
            if(_bottom != 1) ss << _bottom;
            return ss.str();
        };

        /* 提取分子 */
        inline int top() const{
            return ((_isNegative) ? -1 : 1) * (int) _top;
        };

        /* 提取分母 */
        inline int bottom() const{
            return (int)_bottom;
        };


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
        };

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
        };

        /* 处理分母为0 */
        inline void is_bottom_zero() const{
            if(_bottom == 0){
                throw "Division by zero condition!";
            }
        };

        /* 通分，找最大公约数 */
        int get_common_divisor() const;

        /* 分数化简 */
        inline void simplify(){
            int t_divisor = get_common_divisor();

            _top /= t_divisor;
            _bottom /= t_divisor;
        };

        /* 针对double处理负号 */
        inline void is_double_negative(double& d){
            if(d < 0){
                d *= -1;
                _isNegative = true;
            }else{
                _isNegative = false;
            }
        };

        /* 去除空格 */
        void remove_space(string& s) const{

            while(1){

                size_t pos = s.find(" ");
                if(pos == string::npos) return;
                s.erase(pos, 1);
            }
        };

        /* 小数强制转分数 */
        void dec_to_frac_direct(double d);

        /* 无限循环小数转分数 - 补丁 */
        unsigned long int transfer_double_decimals_to_unsigned_long_int_for_single(const double& d) const;

        /* 转换double小数部分到长整型 */
        unsigned long int transfer_double_decimals_to_unsigned_long_int(const double& d);

        /* 获取double小数整数部分 */
        inline unsigned long int get_double_integer_part(const double& d) const{
            return (unsigned long int)floor(fabs(d));
        };

        /* 获取double小数部分 */
        inline unsigned long int get_double_decimals_part(const double& d){
            double t;
            return transfer_double_decimals_to_unsigned_long_int(fabs(d) - floor(fabs(d)));
        };

        /* 获取小数部分的某一位 */
        inline unsigned short get_one_decimal(const unsigned long int& t, unsigned short point) const{
            return (t / (unsigned int)pow(10, point - 1)) % 10;
        };

        /* 获取 int 长度 */
        unsigned short get_long_int_length(long int t) const;

        /* 获取循环小数循环体 */
        unsigned int get_repeat_part(const unsigned long int& t);

        /* 检查循环体顺序 */
        void confirm_repeat_part(const unsigned long int& t, unsigned int& repeat, unsigned short& start);

        /* 循环小数转分数 */
        void repeated_decimal_to_fraction(double d);


};


/**
 * 小数强制转分数
 *
 * @access private
 * @param double d 要转换的值
 * @return void
 */
void Fraction::dec_to_frac_direct(double d)
{
    unsigned short t = get_long_int_length(get_double_decimals_part(d));

    _top = d * (int)pow(10, t);
    _bottom = (unsigned int)pow(10, t);
}


/**
 * 找最大公约数
 *
 * @access private
 * @param void
 * @return int 最大公约数
 */
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


/**
 * 无限循环小数转分数 - 补丁
 *
 * @access private
 * @param double d 需要过滤的数
 * @return unsigned long int 转换结果
 */
unsigned long int Fraction::transfer_double_decimals_to_unsigned_long_int_for_single(const double& d) const
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


/**
 * 转换double小数部分到长整型
 *
 * @access private
 * @param double d 需要转换的数
 * @return unsigned long int 转换结果
 */
unsigned long int Fraction::transfer_double_decimals_to_unsigned_long_int(const double& d)
{
    if(transfer_double_decimals_to_unsigned_long_int_for_single(d)) return transfer_double_decimals_to_unsigned_long_int_for_single(d);

    unsigned long int t = (unsigned long int)(d*(1000000000));

    while(d != 0 && (t % (t/10) == 0 || t % (t/10) == 9) && t > 100) t /= 10;

    if((unsigned long int)(d*(1000000000)) % 1000 == 999) return ++t;

    return t;
}


/**
 * 获取 int 长度
 *
 * @access private
 * @param long int t 需要测量的数
 * @return unsigned short 测量长度
 */
unsigned short Fraction::get_long_int_length(long int t) const
{
    int count = 0;
    while(t){

        t /= 10;
        count++;
    }

    return count;
}


/**
 * 获取循环小数循环体
 *
 * @access private
 * @param unsigned long int t 长整型的小数部分
 * @return unsigned int 循环体
 */
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


/**
 * 检查循环体顺序
 *
 * @access private
 * @param unsigned long int t 长整型的小数部分
 * @param unsigned short& repeat 循环体部分 引用
 * @param unsigned short& start 循环起始位置 引用
 * @return void
 */
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


/**
 * 循环小数转分数
 *
 * @access private
 * @param double d 待转小数
 * @return void
 */
void Fraction::repeated_decimal_to_fraction(double d)
{

    unsigned long int t = get_double_decimals_part(d);

    unsigned short start = 0;
    unsigned int up, down = 0;

    unsigned int repeat = get_repeat_part(t);

    cout << repeat << endl;

    confirm_repeat_part(t, repeat, start);

    cout << repeat << endl;

    for(int i = 0; i < get_long_int_length(repeat); i++){

        down += 9 * (unsigned int)pow(10, i);
    }

    down *= (unsigned int)pow(10, (get_long_int_length(t) - start));

    cout << down << endl;

    up = t % (unsigned int)pow(10, get_long_int_length(repeat)) + (t / (unsigned int)pow(10, start)) * ((unsigned int)pow(10, get_long_int_length(repeat)) - 1);

    up = up + get_double_integer_part(d) * down;

    cout << up << endl;
    _top = up;
    _bottom = down;
}


#endif