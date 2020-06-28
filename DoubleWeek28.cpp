/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek28.cpp
*     author   : @ JY
*     date     : 2020--06--18
**********************************************/
#include <iostream>
#include <algorithm>
#include <stack>
#include <climits>
#include <vector>
#include <stdlib.h>
class Solution{
    public:
        ::std::vector<int> findPrices(::std::vector<int>& prices){
            ::std::vector<int> res;
            int tmp = 0;
            for(int i=0; i<prices.size(); ++i){
                tmp = 0;
                for(int j=i+1; j<prices.size(); ++j){
                    if(prices[i] >= prices[j]){
                        tmp = prices[j];
                        break;
                    }
                }
                res.push_back(prices[i]-tmp);
            }
            return res;
        }

        ::std::vector<int> findPrices2(::std::vector<int>& prices){
            ::std::vector<int>res(prices);
            ::std::stack<int> st;
            for(int i=0; i<prices.size(); ++i){
                while(st.size() && prices[i] < prices[st.top()]){
                    res[st.top()] -= prices[i];
                    st.pop();
                }
                st.push(i);
            }
            return res;
        }
        //---------dou----shi----zheng---shu-----3--------------
        int minSumLengths(::std::vector<int>& arr, int target){
            int left  = 0;
            int right = 0;
            int sum   = 0;
            int res   = INT_MAX;
            ::std::vector<int> dp(arr.size(), 1e8);
            while(right<arr.size()){
                sum = sum + arr[right];
                while(sum>target){
                    sum = sum - arr[left++];
                }
                if(sum == target){
                    if(left)res = ::std::min(res,right-left+1+dp[left-1]);
                    dp[right]   = right - left + 1;
                }
                if(right)dp[right] = ::std::min(dp[right], dp[right-1]);
                ++right;
            }
            return res>arr.size()?-1:res;
        }
        //-------------------------3--------------
        int minSumLengths2(::std::vector<int>& arr, int target){
            ::std::vector<::std::vector<int>> dp(arr.size(), ::std::vector<int>(arr.size(), 0));
            for(int i=0; i<arr.size(); ++i){
                for(int j=i; j<arr.size(); ++j){
                    if(i==j){
                        dp[i][j] = arr[i];
                        continue;
                    }
                    dp[i][j] = dp[i][j-1] + arr[j];
                }
            }

            for(int i=0; i<arr.size(); ++i){
                for(int j=0; j<arr.size(); ++j){
                    ::std::cout<<dp[i][j]<<"  ";
                }
                ::std::cout<<::std::endl;
            }

            ::std::vector<::std::pair<int,int>> tmp;
            for(int i=0; i<arr.size(); ++i){
                for(int j=0; j<arr.size(); ++j){
                    if(dp[i][j] == target){
                        tmp.push_back(::std::make_pair(i,j));
                    }
                }
            }
            if(tmp.size() < 2)return -1;
            //::std::cout<<"as"<<::std::endl;

            sort(tmp.begin(), tmp.end(),[](::std::pair<int,int>& p1, ::std::pair<int,int>& p2){
                            return p1.first < p2.first;
                    });

            int min1 = INT_MAX;
            int min2 = INT_MAX;
            int res  = INT_MAX;

            for(int i=1; i<=tmp.size(); ++i){
                int E = tmp[i-1].second;
                min1  = tmp[i-1].second-tmp[i-1].first+1;
                min2  = INT_MAX;
                for(int j=i; j<tmp.size(); ++j){
                    if(E < tmp[j].first){
                        min2 = ::std::min(min2,tmp[j].second-tmp[j].first+1);
                    }
                }
                if(min2==INT_MAX)continue;
                ::std::cout<<min1<<"---"<<min2<<::std::endl;
                res = ::std::min(res,min1+min2);
            }
            return res==INT_MAX?-1:res;
        }
        int minDistance(::std::vector<int>& houses, int m){
            sort(houses.begin(), houses.end());
            ::std::vector<::std::vector<int>>cost(houses.size(), ::std::vector<int>(houses.size(),0));
            for(int i=0; i<houses.size(); ++i){
                for(int j=i; j<houses.size(); ++j){
                    int mid = (i+j)>>1;
                    for(int k=i; k<=j; ++k){
                        cost[i][j] += abs(houses[k] - houses[mid]);
                    }
                }
            }
            ::std::vector<::std::vector<int>> dp(houses.size(), ::std::vector<int>(m+1,1e8));

            for(int i=0; i<houses.size(); ++i){
                for(int j=1; j<=m; ++j){
                    for(int t=j-1; t<=i; ++t){
                        int tmp  = 0;
                        if(t)tmp = dp[t-1][j-1];
                        dp[i][j] = ::std::min(dp[i][j], tmp+cost[t][i]);
                    }
                }
            }
            return dp[houses.size()-1][m];
        }
};

class SubrectangleQueries{
public:
    ::std::vector<::std::vector<int>> matrix;
    SubrectangleQueries(::std::vector<::std::vector<int>>& rectangle){
        matrix.assign(rectangle.begin(), rectangle.end());
    }
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue){
        for(int i=row1; i<=row2; ++i){
            for(int j=col1; j<=col2; ++j){
                matrix[i][j] = newValue;
            }
        }
    }
    
    int getValue(int row, int col) {
        return matrix[row][col];
    }
};

int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<int> nums = {1,1,1,2,2,2,4,4};
    //::std::vector<int> nums = {7,3,4,7};
    //::std::vector<int> nums = {3,1,1,1,5,1,2,1};
    //::std::vector<int> nums = {3,2,2,4,3};
    int target = 6;
    ::std::cout<<te.minSumLengths(nums, target)<<::std::endl;
    return 0;
}


