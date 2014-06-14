/*************************************************************************
	> File Name: findPalindromeSubstring.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月24日 星期六 11时15分54秒
    > Description: 寻找最长的回文子串
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;

char* LongestPalindrome1(const char* str){
    if(str==NULL) return NULL;
    int n = strlen(str);
    int maxlen = 1;
    int startidx=0;
    //table 表示以i为开始j为结束的字串是否为回文
    bool** table = new bool*[n];
    for(int i=0;i<n;i++) table[i]=new bool[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) table[i][j]=false;
    }
    //任意单个字符本身就是回文，所以将以i为开始并以i为结束的字串定义为true
    for(int i=0;i<n;i++) table[i][i]=true;
    //任意两个连续字符如果相等，则也是回文
    for(int i=0;i<n-1;i++){
        if(str[i]==str[i+1]){
            table[i][i+1]=true;
            maxlen=2;
            startidx=i;
        }
    }
    //对于每个字符开始以长度3为开始，
    //如果S(i)==S(j=i+len-1)&&以S(i+1)开始S(j-1)结束的字串是回文，
    //那么S(i)-S(j)也是回文
    for(int len=3;len<=n;len++){
        for(int i=0;i<n-len+1;i++){
            int j=i+len-1;
            if(str[i]==str[j]&&table[i+1][j-1]){
                maxlen=len;
                startidx=i;
                table[i][j]=true;
            }
        }
    }
    for(int i=0;i<n;i++) delete table[i];
    delete table;
    char* res=new char[maxlen+1];
    for(int i=0;i<maxlen;i++)  res[i]=str[startidx+i];
    res[maxlen]='\0';
    return res;
}
/*预处理string，将"abcdef"变成形如"^#a#b#c#d#e#f#$"
* 的形式，^表示头$表示结束*/
string preProcess(string s){
    int n=s.length();
    if(n==0) return "^$";
    string res = "^";
    for(int i=0;i<n;i++)  res+="#"+s.substr(i,1);
    res+="#$";
    return res;
}
/*这个算法的解释详见这里：
 *http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 *与上面网址提到的代码相比，这里的代码过程略有冗余，但是逻辑更加清楚
* */
string LongestPalindrome2(string str){
    string t=preProcess(str);
    int n=t.length();cout<<t<<endl;
    //radius[i]表示以i为中心的回文的半径
    //算上i本身则回文总长为2*radius[i]+1
    //回文头索引为 i-radius[i], 回文尾索引为 i+radius[i]
    int* radius=new int[n];
    //center表示当前回文的中心轴索引，right表示回文的尾索引
    int center=0, right=0;
    for(int i=1;i<n-1;i++){
        //i-center=center-i_mirror
        int i_mirror=center*2-i;
        if(right<=i){
            radius[i]=0;
            while( (i-radius[i]-1>=0)&&(i+radius[i]+1<n)
                  &&(t[i-radius[i]-1]==t[i+radius[i]+1]) ){
                      radius[i]++;
                  }
            center=i;
            right=i+radius[i];
        }else if(radius[i_mirror]>right-i){
            radius[i]=right-i;
            while( (i-radius[i]-1>=0)&&(i+radius[i]+1<n)
                  &&(t[i-radius[i]-1]==t[i+radius[i]+1]) ){
                      radius[i]++;
                  }
            center=i;
            right=i+radius[i];
        }else{
            radius[i]=radius[i_mirror];
        }
    }
    int maxlen=0, max_center=0;
    for(int i=1;i<n-1;i++){
        if(radius[i]>maxlen){
            max_center=i;
            maxlen=radius[i];
        }
        //cout<<radius[i]<<" ";
    }
    delete radius;
    //找到预处理之后的string t 中最长回文的中心max_center和半径max_len
    //则 t 中对应的回文头为 max_center-max_len
    //对应到原 string str 中：先减去 "^$" max_center-maxlen-1
    //再除以2，所以 str 中 start=(max_center-maxlen-1)/2;
    int start=(max_center-maxlen-1)/2;
    return str.substr(start,maxlen);
}
int main(){
    const char* str="abaabcabcdcbdddefgaacd";
    char* res1=LongestPalindrome1(str);
    cout<<str<<" : "<<res1<<endl;
    string res2 = LongestPalindrome2(str);
    cout<<str<<" : "<<res2<<endl;
    delete res1;
    return 0;
}
