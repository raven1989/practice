/*************************************************************************
	> File Name: maxDistance.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月25日 星期日 15时25分55秒
    > Given an array A of integers, find the maximum of j-i subjected to the constraint of A[i] < A[j].
    >http://leetcode.com/2011/05/a-distance-maximizing-problem.html
 ************************************************************************/

#include<iostream>
using namespace std;
int maxDistance(int* a,int n){
    if(a==NULL) return -1;
    //可能的开始索引，即i 的可能取值，
    //这个形成后，其存储的索引所对应与a 中的值一定是降序的
    int* pStarts=new int[n];
    int pnum=0;
    pStarts[pnum++]=0;
    int min=a[0];
    for(int i=1;i<n;i++){
        if(a[i]<min){
            pStarts[pnum++]=a[i];
            min=a[i];
        }
    }
    //寻找最大的j-i
    for(int j=n-1;j>=0;j--)
    for(int i=0;(i<pnum&&pStarts[i]<=j);i++){
        if(a[j]>a[pStarts[i]])  return (j-pStarts[i]);
    }
    return 0;
}
int main(){
    int a[]={4,3,5,2,1,3,2,3};
    cout<<sizeof(a);
    cout<<" int a[]={4,3,5,2,1,3,2,3}"<<endl;
    cout<<" : "<<maxDistance(a,sizeof(a)/sizeof(a[0]))<<endl;
    return 0;
}
