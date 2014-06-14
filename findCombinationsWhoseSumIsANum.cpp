/*************************************************************************
	> File Name: findCombinationsWhoseSumIsANum.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月31日 星期六 21时37分20秒
    > Description: Given a target number, and a series of candidate numbers, print out all combinations, so that the sum of candidate numbers equals to the target.

    Here order is not important, so don’t print the duplicated combination.

    e.g. target is 7, candidate is 2,3,6,7
    output should be 7 and 3+2+2 (but not print 2+3+2, 2+2+3)
 ************************************************************************/
//未完成
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool isCandidate(int tar,int cur_tar,int c[],int n,string& str){
    cout<<"in isCandidate(): "<<cur_tar<<endl;
    if(cur_tar==0) return true;
    if(n<=0) return false;
    bool ok=false;
    for(int i=cur_tar/c[n-1];i>0;i--){
        //int m=cur_tar/c[n-1];
        //for(int i=0;i<m;i++) 
        int tar_t=cur_tar-(c[n-1]*i);
        //if(tar_t<c[0]) continue;
        int l=0,r=n-2,mid;
        while(l<=r){
            mid=(l+r)/2;
            if(c[mid]<tar_t) l=mid+1;
            else r=mid-1;
        }
        l=min(l,r);
        bool tmp=isCandidate(tar,tar_t,c,l+1,str);
        if(tmp){
            cout<<c[n-1]<<"("<<i<<") is candidate."<<endl;
            for(int j=0;j<i;j++)
                str=str+" "+(char)(c[n-1]+'0');
        }
        if(tmp&&cur_tar==tar){ 
           str=str+", ";
           //cout<<str;
        }
        ok=(ok||tmp);
    }
    if(ok){
        //cout<<"in isCandidate(): "<<n<<" OK!"<<endl;
        return true;
    }
    return false;
}
//c[]是排序过的
bool findAllCombinations(int tar,int c[],int n,string& str){
    bool res=false;
    //sort(c,n);
    for(int i=n-1;i>=0;i--){
        cout<<"in findAllCombinations(): "<<i+1<<endl;
        bool tmp=isCandidate(tar,tar,c,i+1,str);
        res=(res||tmp);
    }
    return res;
}
int main(){
    int target=7;
    int c[]={1,2,3,6,7};
    string str="";
    cout<<"target: "<<target<<endl;
    cout<<"candidates: { ";
    for(int i=0;i<sizeof(c)/sizeof(c[0]);i++){
        cout<<c[i]<<" ";
    }
    cout<<"}"<<endl;
    if(findAllCombinations(target,c,sizeof(c)/sizeof(c[0]),str)){
        cout<<str<<endl;
    }
    return 0;
}
