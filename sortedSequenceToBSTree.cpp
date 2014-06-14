/*************************************************************************
	> File Name: sortedSequenceToBSTree.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2014年05月29日 星期四 17时03分43秒
    > Description: 1. Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
    2. Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 ************************************************************************/

#include<iostream>
using namespace std;
template <class T>
class ListNode{
public:
    T data;
    ListNode<T>* next;
    ListNode(T a){
        data=a;
        next=NULL;
    }
};
template <class T>
class List{
public:
    ListNode<T>* head;
    List(){head=NULL;}
    List(T a[],int n){
        head=NULL;
        for(int i=n-1;i>=0;i--){
            ListNode<T>* node=new ListNode<T>(a[i]);
            if(head!=NULL)
                node->next=head;
            head=node;
        }
    }
    ~List(){
        ListNode<T>* tmp;
        while(head!=NULL){
            tmp=head;
            head=head->next;
            delete tmp;
        }
        head=NULL;
    }
};
template <class T>
class BSTNode{
public:
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;
    BSTNode(T d){
        data=d;
        left=right=NULL;
    }
};
template <class T>
BSTNode<T>* sortedArrayToBST(T a[],int n){
    if(n<=0) return NULL;
    int mid=n/2;
    BSTNode<T>* root=new BSTNode<T>(a[mid]);
    root->left=sortedArrayToBST(a,mid);
    root->right=sortedArrayToBST(a+mid+1,n-mid-1);
    return root;
}
//这个神奇的引用 ListNode<T>*& 巧妙地完成了要求
template <class T>
BSTNode<T>* sortedListToBST(ListNode<T>*& head,int n){
    if(n<=0) return NULL;
    int mid=n/2;
    BSTNode<T>* lchild=sortedListToBST(head,mid);
    BSTNode<T>* root=new BSTNode<T>(head->data);
    head=head->next;
    root->left=lchild;
    root->right=sortedListToBST(head,n-mid-1);
}
template <class T>
void inOrder(BSTNode<T>* root){
    if(root==NULL) return;
    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
}
template <class T>
void destruction(BSTNode<T>* root)
{
    if(root==NULL) return;
    destruction(root->left);
    destruction(root->right);
    cout<<"delete "<<root->data<<", ";
    delete root;
    root=NULL;
}
int main(){
    int a[7]={1,2,3,4,5,6,7};
    BSTNode<int>* t1=sortedArrayToBST(a,sizeof(a)/sizeof(a[0]));
    List<int> list(a,sizeof(a)/sizeof(a[0]));
    ListNode<int>* head=list.head;
    BSTNode<int>* t2=sortedListToBST(head,sizeof(a)/sizeof(a[0]));
    inOrder(t1);cout<<endl;
    inOrder(t2);cout<<endl;
    destruction(t1);cout<<endl;
    destruction(t2);cout<<endl;
    return 0;
}
