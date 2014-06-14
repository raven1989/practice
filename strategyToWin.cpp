/*************************************************************************
	> File Name: strategyToWin.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月26日 星期一 14时21分06秒
    > Description: There are n coins in a line. Two players take turns to take a coin from one of the ends of the line until there are no more coins left. The player with the larger amount of money wins. Try to get as much money as you can.
    http://leetcode.com/2011/02/coins-in-line.html
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;
const int MAX_N=100;

void printMoves(int P[][MAX_N], int A[], int N) {
      int sum1 = 0, sum2 = 0;
      int m = 0, n = N-1;
        bool myTurn = true;
    while (m <= n) {
            int P1 = P[m+1][n]; // If take A[m], opponent can get...
            int P2 = P[m][n-1]; // If take A[n]
            cout << (myTurn ? "I" : "You") << " take coin no. ";
        if (P1 <= P2) {
                  cout << m+1 << " (" << A[m] << ")";
                  m++;
                
        } else {
                  cout << n+1 << " (" << A[n] << ")";
                  n--;
                
        }
            cout << (myTurn ? ", " : ".\n");
            myTurn = !myTurn;
          
    }
      cout << "\nThe total amount of money (maximum) I get is " << P[0][N-1] << ".\n";

}
int wholePosibilities(int a[],int n){
    /*p[i][j] 表示当序列剩下{a[i]...a[j]} 时，所能获得的最大钱数。
     * 此时面对两个选择，选择a[i] 或者选择a[j]。
     * 假设选择了a[i]，轮到对手选择，他所面临的选择为a[i+1] 和a[j]，
     * 认为对手会选择当前序列下对自己最有利的coin，
     * 即使剩下的序列，也就是留给你的序列的p较小，
     * 如果他选择a[i+1] ，则p[i+2][j]，如果他选择a[j]，则p[i+1][j-1]，
     * 留给你的是两者中的小者。
     * 所以，如果你选择了a[i]，那么你获得的最大钱数为
     * pi=a[i]+min(p[i+2][j],p[i+1][j-1])
     * 同理，如果你选择了a[j]，那么你获得的最大钱数为
     * pj=a[j]+min(p[i+1][j-1],p[i][j-2])
     * 所以，当一个选手面对序列{a[i]...a[j]} 时，他所能获得的最大钱数为
     * p[i][j]=max(pi,pj)
     * 对于p[i][j]，它的初始值为p[0][0]...p[i][i]...p[n-1][n-1]，
     * 表示当序列仅有一个元素{a[i]}时所能获得的最大钱数，显然就是a[i]，
     * 对于通式 
     * p[i][j]=max( a[i]+min(p[i+2][j],p[i+1][j-1]), a[j]+min(p[i+1][j-1],p[i][j-2]) )
     * 而言，定义如果i||j越界则p[i][j]=0，从而保证形式统一
    * */
    int p[MAX_N][MAX_N]={0};
    int pi2j,pi1j1,pij2;
    for(int interval=0;interval<n;interval++){
        for(int i=0,j=i+interval;j<n;i++,j++){
            pi2j= i+2<n? p[i+2][j]:0;
            pi1j1= (i+1<n && j-1>=0)? p[i+1][j-1]:0;
            pij2= j-2>=0? p[i][j-2]:0;
            p[i][j]=max( a[i]+min(pi2j,pi1j1),a[j]+min(pi1j1,pij2) );
        }
    }
    printMoves(p,a,n);
    return p[0][n-1];
}
int main(){
    int coins[]={3,2,2,3,1,2};
    wholePosibilities(coins,6);
    return 0;
}

