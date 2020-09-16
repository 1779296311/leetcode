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
#include <vector>
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
void c(std::vector<int> a){
    a[0] = -1;
}
void b(std::vector<int>& a){
    c(a);
}
int main()
{
    //string str  = "12312499--==123";

    //cout <<isPalindrome(14321) <<endl;
    std::vector<vector<int>> t = {{1, 2},{2, 3},{3, 4}};
    t.assign(t.begin(), t.end());
    for(int i=0; i<t.size(); ++i){
        for(int j=0; j<t[i].size(); ++j){
            std::cout<<t[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
