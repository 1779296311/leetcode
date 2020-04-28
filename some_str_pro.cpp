/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_str_pro.cpp
*     author   : @ JY
*     date     : 2020--04--27
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int min_editDistanceDP(string a, string b, int del, int add, int rep){
            int sizea = a.size();
            int sizeb = b.size();
            vector<vector<int>> dp(sizea+1,vector<int>(sizeb+1,0));
            for(int i=0; i<=sizeb; ++i){
                dp[0][i] = i*add;
            }
            for(int i=0; i<=sizea; ++i){
                dp[i][0] = i*del;
            }
            for(int i=1; i<=sizea; ++i){
                for(int j=1; j<=sizeb; ++j){
                    if(a[i-1] == b[j-1]){
                        dp[i][j] = dp[i-1][j-1];
                    }else{
                        dp[i][j] = dp[i-1][j-1] + rep;
                    }
                    dp[i][j] = min(dp[i][j],min(dp[i-1][j]+del,dp[i][j-1]+add));
                }
            }
            return dp[sizea][sizeb];
        }
        int min_editDistance(string a, string b,int del, int add, int rep){
            return process1(a,b,a.length()-1,b.length()-1,del,add,rep);
        }
        int process1(string a, string b, int i, int j, int del, int add, int rep){
            if(!i){
                return j*add;
            }
            if(!j){
                return i*del;
            }
            int res = process1(a,b,i-1,j-1,del,add,rep);
            if(a[i] != b[j]){
                res = res + rep;
            }
            return
                min(res,min(process1(a,b,i-1,j,del,add,rep)+del,process1(a,b,i,j-1,del,add,rep)+add));
        }
        /*--------------字符串交叉-----------------------------------------------------------------------------------*/
        bool is_CrossDP(string a, string b, string c){
            int sizea = a.length();
            int sizeb = b.length();
            int sizec = c.length();
            if(sizea + sizeb != sizec){
                return false;
            }
            vector<vector<int>> dp(sizea+1, vector<int>(sizeb+1,false));
            for(int i=1; i<=sizeb; ++i){
                if(b[i-1] == c[i-1]){
                    dp[0][i] = true;
                }
            }
            for(int j=1; j<=sizea; ++j){
                if(a[j-1] == c[j-1]){
                    dp[j][0] = true;
                }
            }
            for(int i=1; i<=sizea; ++i){
                for(int j=1; j<=sizeb; ++j){
                    if(a[i-1]==c[i+j-1] && dp[i-1][j]){
                        dp[i][j] = true;
                    }
                    if(b[j-1]==c[i+j-1] && dp[i][j-1]){
                        dp[i][j] = true;
                    }
                }
            }
            return dp[sizea][sizeb];
        }
        bool is_Cross(string a, string b, string c){
            int sizea = a.length();
            int sizeb = b.length();
            int sizec = c.length();
            if(sizea+sizeb != sizec){
                return false;
            }
            return process2(a,b,c,sizea-1,sizeb-1);
        }
        bool process2(string a, string b, string c, int i, int j){
            if(a[i] != c[i+j+1] && b[j] != c[i+j+1]){
                return false;
            }
            if(!i && a[i] == c[j+1]){
                for(int k=0; k<=j; ++k){
                    if(b[k] != c[k]){
                        return false;
                    }
                }
                return true;
            }
            if(!j && b[j] == c[i+1]){
                for(int k=0; k<=i; ++k){
                    if(a[k] != c[k]){
                        return false;
                    }
                }
                return true;
            }
            bool res = false;
            if(a[i] == c[i+j+1]){
                res = res | process2(a,b,c,i-1,j);
            }
            if(b[j] == c[i+j+1]){
                res = res |  process2(a,b,c,i,j-1);
            }
            return res;
        }
        /*---------------------------------最长公共子序列---------------------------------------------------------------------------*/
        int longest_strDP(string a, string b){
            int sizea = a.length();
            int sizeb = b.length();
            vector<int> dp(sizeb+1,0);
            int old   = 0;
            int tmp   = 0;
            int res   = 0;
            for(int i=1; i<=sizea; ++i){
                for(int j=1; j<=sizeb; ++j){
                    tmp = dp[j];
                    dp[j] = max(dp[j],dp[j-1]);
                    if(a[i-1] == b[j-1]){
                        dp[j] = max(dp[j],old+1);
                    }
                    old = tmp;
                    res = max(res,dp[j]);
                }
                old = 0;
            }
            return res;
        }
        int longest_str(string a, string b){
            int n   = 0;
            int res =   process3(n,a,b,a.length()-1, b.length()-1);
            cout<<"n: "<<n<<endl;
            return res;
        }
        int process3(int &n,string a, string b, int i, int j){
            ++n;
            if(i<0 || j<0){
                return 0;
            }
            int v1 = process3(n,a,b,i-1,j);
            int v2 = process3(n,a,b,i,j-1);
            if(a[i] == b[j]){
                return max(v1,max(v2,process3(n,a,b,i-1,j-1)+1));
            }
            return max(v1,v2);
        }
        /*---------------------------------最长公共子chuan---------------------------------------------------------------------------*/
        int longest_strSon(string a, string b){
            int res = 0;
            for(int i=0; i<a.length(); ++i){
                for(int j=0;j<b.length(); ++j){
                    if(a[i] == b[j]){
                        res = max(res,process4(a,b,i,j));
                    }
                }
            }
            return res;
        }
        int process4(string a, string b ,int i, int j){
            if(i<0 || j<0 || a[i] != b[j]){
                return 0;
            }
            return process4(a,b,i-1,j-1)+1;
        }
        int longest_strSonDP(string a, string b){
            int sizea    = a.length();
            int sizeb    = b.length();
            int strEnd   = 0;
            int cow = 0;
            int rol = sizeb-1;
            int len = 0;
            int res = 0;
            int i   = 0;
            int j   = rol;
            while(cow<sizea){
                i   = cow;
                j   = rol;
                len = 0;
                while(i<sizea && j<sizeb){
                    if(a[i] == b[j]){
                        ++len;
                    }else{
                        len = 0;
                    }
                    if(len > res){
                        res     = len;
                        strEnd  = i;
                    }
                    ++i;
                    ++j;
                }
                if(rol>0){
                    --rol;
                }else{
                    ++cow;
                }
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string a = "abcuuuuuuuyuio";
    string b = "123";
    string c = "1a2bcuuuyuio";

    string a1 = "asjfkajsfh";
    string c1 = "asjfkajsf0000000hoooooo";
    string b1 = "asdasdasd";

    string a2 = "asjfddkajsfh";
    string b2 = "asdasd";
    string c2 = "aasjsfdasddkajsfhd";

    string a3 = "asjaskdjlasjdlkasfoiqefhadglsjdhffddkajsfh";
    string b3 = "asdassdasdjahsfjhalkfzlxvhklxcvxhvd";
    string c3 = "aasjaskdjlasjdlkasfoiqefhadglsjdhffddkajsfhasdassdasdjahsfjhalkfzlvxhklxcvxhvsdkdjlajsdlkafsoiqehfadglsjdhffddkajsfh";
    string c4 = "asjaskdjlasjdlkasfoiqefhadglsjdhffddkajsfhooooooooo";
    cout<<te.longest_strSonDP(a1,c1)<<endl;
    cout<<te.longest_strSon(a1,c1)<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<te.longest_strSonDP(a2,c1)<<endl;
    cout<<te.longest_strSon(a2,c1)<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<te.longest_strSonDP(a1,b1)<<endl;
    cout<<te.longest_strSon(a1,b1)<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<te.longest_strSonDP(a3,c3)<<endl;
    cout<<te.longest_strSon(a3,c3)<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<te.longest_strSonDP(a2,c2)<<endl;
    cout<<te.longest_strSon(a2,c2)<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<te.longest_strSonDP(a,a)<<endl;
    cout<<te.longest_strSon(a,a)<<endl;
    cout<<"-----------------------------"<<endl;

    //cout<<te.longest_strDP(a,c)<<endl;
    //cout<<te.longest_strDP(a,c)<<endl;
    //cout<<te.longest_str(a,c)<<endl;
    //cout<<te.longest_strSonDP(a3,c4)<<endl;
    //cout<<te.is_Cross(a,b,c)<<endl;
    //cout<<te.is_CrossDP(a,b,c)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.is_Cross(a1,b1,c1)<<endl;
    //cout<<te.is_CrossDP(a1,b1,c1)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.is_Cross(a2,b2,c2)<<endl;
    //cout<<te.is_CrossDP(a2,b2,c2)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.is_Cross(a3,b3,c3)<<endl;
    //cout<<te.is_CrossDP(a3,b3,c3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(b1,b2,1,2,3)<<endl;
    //cout<<te.min_editDistance(b1,b2,1,2,3)<<endl;
    //cout<<te.min_editDistanceDP(a,b,1,2,3)<<endl;
    //cout<<te.min_editDistance(a,b,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(b2,b4,1,2,3)<<endl;
    //cout<<te.min_editDistance(b2,b4,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(a,b3,1,2,3)<<endl;
    //cout<<te.min_editDistance(a,b3,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    //cout<<te.min_editDistanceDP(a,b4,1,2,3)<<endl;
    //cout<<te.min_editDistance(a,b4,1,2,3)<<endl;
    //cout<<"-----------------------------"<<endl;
    return 0;
}
