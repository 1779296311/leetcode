/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: twoSum.c
*     author   : @JY    
*     data     : 2019--09--03
**********************************************/
#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize){
    for(int i=0; i< numsSize; i++){
        for(int j=i + 1;j<numsSize; j++){
            if(target == nums[i] + nums [j]){
                int *resault  = (int *) malloc(sizeof(int) * (*returnSize));
                resault[0]    = i;
                resault[1]    = j;
                return        resault;
            }
        }
    }
    return NULL;
}

int main(int argc,const char *argv[]){
    int nums[5]     = {1,2,4,6,2};
    int size        = 2;
    
    printf("%d -- %d\n",twoSum(nums, 5, target, &size)[0],twoSum(nums, 5, target, &size)[1]);


    return 0;
} 
