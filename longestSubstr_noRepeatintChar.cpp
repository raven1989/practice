/*************************************************************************
	> File Name: longestSubstr_noRepeatintChar.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月25日 星期日 16时32分55秒
    > Longest Substring Without Repeating Characters
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

string LSSnoRepeatChar(string& str){
    string s=str;
    int n=str.length();
    for(int i=0;i<n;i++){
        if(str[i]<='Z') s[i]+=('a'-'A');
    }
    int start=0, len=0;
    int max_start=start, max_len=len;
    int idx[26];
    for(int i=0;i<26;i++) {
        idx[i]=-1;
        //cout<<idx[i]<<" ";
    }
    //cout<<endl;
    //idx 存储26个字母出现在s 中的最近一次的索引
    int* table = new int[n];
    //table 存储s 中对应索引的字母上一次出现的位置索引，
    //第一次出现则为-1，eg:
    // 0  1  2 3  4  5  6  7 8  9
    // a  b  c b  d  e  f  g c  h
    //-1 -1 -1 1 -1 -1 -1 -1 2 -1
    for(int i=0;i<n;i++){
        table[i]=idx[s[i]-'a'];
        idx[s[i]-'a']=i;
    }
    for(int i=0;i<n;i++) cout<<table[i]<<" "; cout<<endl;
    //寻找目标子串
    int tmp_len=0;
    for(int i=0;i<n;i++){
        //if(table[i]<start) 分为两种情况：
        //1. table[i]=-1 ，即第一次出现，简单处理i 继续往前
        //2. table[i]!=-1 且<start，这说明当前字符出现重复，
        //但在子串开始位置之前，对子串并不影响，所以i 也继续向前
        if(table[i]<start) len++;
        //3. 当table[i]>=start 时，说明子串中出现重复：
        //这时候就要截断子串，判断是否比之前记录到的要长
        //然后start 设置到上一次重复位置之后一位，即table[i]+1，
        //而这之后一直到i 都是不重复的且长度为i-start+1，
        //所以i 不用回溯，从i+1 继续执行
        else{
            if(len>max_len){
                max_len=len;
                max_start=start;
            }
            start=table[i]+1;
            len=i-start+1;
        }
    }
    if(len>max_len){
        max_len=len;
        max_start=start;
    }
    delete table;
    return s.substr(max_start,max_len);
}

int main(){
    string str="abcbdefgchij";
    cout<<str<<" : "<<LSSnoRepeatChar(str)<<endl;
    return 0;
}
