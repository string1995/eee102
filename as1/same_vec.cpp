
/**
 * 函数same_vec()测试  
 *
 * @category eee102-as1
 * @package same_vec.cpp
 * @copyright Copyright (c) 2019 Yimian LIU (https://iotcat.me)
 * @license GNU General Public License 2.0
 * @version 0.0.1
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>


using namespace std;




/****** 用户输入相关函数 ********/

/**
 * 判断char是否为数字
 *
 * @access public 
 * @param char c 待判断的值
 * @return bool true : false
 */
inline bool is_num(const char c)
{
    return (c > 47 && c < 58)? true : false;
}


/**
 * 转换char型数字到int型
 *
 * @access public 
 * @param char c 要转换的值
 * @return int 转换完成的数字
 */
inline int char_to_num(const char c)
{
    return (int)c - (int)'0';
}


/**
 * 从string中提取一个int数字
 *
 * @access public 
 * @param string s 要搜索的string
 * @param int& pos 起始位置 
 * @return int 提取出的数字
 */
int get_int_from_string(const string& s, int& pos)
{
    if(!is_num(s.at(pos))) return 0;

    int t = char_to_num(s.at(pos));

    while(++pos < s.length() && is_num(s.at(pos))){

        t = t * 10 + char_to_num(s.at(pos));
    }

    return t;
}


/**
 * 用户输入值到vector
 *
 * @access public 
 * @param vector<int>& v 待存储的vector
 * @return void
 */
void getVec(vector<int>& v)
{
    string s;

    getline(cin, s);
    int i = 0;
    while(i < s.length()){

        if(is_num(s.at(i))) v.push_back(get_int_from_string(s, i));

        while( ++i < s.length() && !is_num(s.at(i)));
    }
}





/****** 算法一 ********/

/**
 * 判断vector中是否包含特定值
 *
 * @access public 
 * @param int val 需要寻找的值
 * @param vector<int> v 需要遍历的vector 
 * @return bool true : false
 */
bool is_in_vector(const int val, const vector<int>& v)
{
    for(int i = 0; i < v.size(); i++){

        if(val == v[i]) return true;
    }

    return false;
}


/**
 * 是否a中所有的元素b中都存在
 *
 * @access public
 * @param vector<int> a 第一个vector 
 * @param vector<int> b 第二个vector
 * @return bool true : flase
 */
bool is_vec_a_in_b(const vector<int>& a, const vector<int>& b)
{
    int sameElements = 0;

    for(int i = 0; i < a.size(); i++){

        sameElements += is_in_vector(a[i], b);
    }

    return (sameElements == a.size()) ? true : false;
}


/**
 * 判断两vector是否相同
 *
 * @access public
 * @param vector<int> a 第一个vector 
 * @param vector<int> b 第二个vector
 * @return bool true : flase
 */
inline bool same_vec1(const vector<int>& a, const vector<int>& b){

    if(a.size() == 0 && b.size() == 0) return true;
    if(a.size() == 0 || b.size() == 0) return false;

    return is_vec_a_in_b(a,b) && is_vec_a_in_b(b,a);
}





/****** 算法二 ********/

/**
 * 寻找vector中下一个不同的元素
 *
 * @access public
 * @param vector<int> v 待寻找的vector 
 * @param int pos 寻找起始位置 
 * @return void
 */
void next_diff_element(const vector<int>& v, int& pos)
{
    while(pos < v.size() - 1) {

        if(v[pos] != v[++pos]) return;
    }
}


/**
 * 判断两vector是否相同
 *
 * @access public
 * @param vector<int> a 第一个vector 
 * @param vector<int> b 第二个vector
 * @return bool true : flase
 */
bool same_vec2(vector<int> a, vector<int> b){

    if(a.size() == 0 && b.size() == 0) return true;
    if(a.size() == 0 || b.size() == 0) return false;

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




/* 主函数 */
int main()
{
    while(1){
        
        vector<int> a, b;

        cout << "Please input Vector A: ";
        getVec(a);
        cout << "Please input Vector B: ";
        getVec(b);

        cout << "Vector A: ";
        for(int i = 0; i < a.size(); i++){

            cout << a[i] << ", ";
        }

        cout << endl << "Vector B: ";
        for(int i = 0; i < b.size(); i++){

            cout << b[i] << ", ";
        }

        cout << endl << "Result from algorithm 1: " << (same_vec2(a, b)? "Same!" : "Not Same!") << endl;
        cout << "Result from algorithm 2: " << (same_vec2(a, b)? "Same!" : "Not Same!") << endl << endl;

        a.clear();
        b.clear();

        cout << "Please press Ctrl+C to quit!!!" << endl << endl;
    }

    return 0;
}