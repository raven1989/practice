/*************************************************************************
	> File Name: reverseBits.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月24日 星期六 18时51分52秒
    > Description: 反转比特位，如把1010->0101
 ************************************************************************/
 /*分而治之
  *                    01101001
  *                     /    \
  *                  0110   1001
  *                  /  \   /  \
  *                01   10 10   01
  *                /\   /\ /\   /\
  *               0 1  1 0 1 0  0 1
  *               \/   \/  \/   \/
  *               10   01  01   10
  *                \   /    \   /
  *                0110     1001
  *                   \      /
  *                   10010110
 * */

#include<iostream>
#include<bitset>
using namespace std;
typedef char uint;
uint DivideConquer(uint x,uint mask,uint n){
    if(n==1) return x;
    //把连续的掩码分成高半位和低半位，如 11110000->11000000,00110000
    uint hi_mask = mask&(mask<<(n/2));
    uint lo_mask = mask&(mask>>(n/2));
    DivideConquer(x,hi_mask,n/2);
    DivideConquer(x,lo_mask,n/2);
    //归并起来，把高半位与低半位互换，如 0110->1001 
    uint x_sub=((x&hi_mask)>>(n/2))|((x&lo_mask)<<(n/2));
    x&=(~mask);
    x|=x_sub;
    return x;
}
uint switchBits(uint x){
    uint n=sizeof(x)*8;
    uint mask=~(0);
    return DivideConquer(x,mask,n);
}
int main(){
    uint x=0b01101001;
    bitset<8> bx(x);
    bitset<8> bres(switchBits(x));
    cout<<bx<<" : "<<bres<<endl;
    return 0;
}

