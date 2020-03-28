/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: tmp.cpp
*     author   : @JY    
*     data     : 2019--09--06
**********************************************/
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <sstream>
using  namespace  std;
class Rectangle
{
  public:
  		int Volume() const;
  		int length;
  		int width;
  		int height;
};

template<class out_type, class in_type>
out_type convert(const in_type &T){

    stringstream   stream;
    out_type   result;

    stream << T;
    stream >> result;

    return result;
}

bool isPalindrome(int x) {
        if(x < 0){
            return false;
        }

        stringstream  stream;

        string str, cmp;

        stream << x;
        stream >> str;

        cmp    = str;
        reverse(str.begin(), str.end());
        if(str == cmp){
            return true;
        }

        return false;
}

int main()
{
    //string str  = "12312499--==123";

    //cout <<isPalindrome(14321) <<endl;

    int a = 1;
    int b = 10;
    cout <<(a^b == b^a)<<endl;
    return 0;
}
