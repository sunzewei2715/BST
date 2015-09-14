//
//  main.cpp
//  BST
//
//  Created by sun zewei on 15-6-3.
//  Copyright (c) 2015年 sun zewei. All rights reserved.
//

#include <iostream>
using namespace std;

template<class szw>
class treenode
{
public:
    szw key;
    bool v=0;//非递归遍历时标记是否被访问过
    treenode<szw> *l,*r,*p;//左，右，父
};

template<class szw>
class tree
{
public:
    treenode<szw> *root;
    void inorder1(treenode<szw> *root);//中序遍历，递归写法，超方便，调换顺序即可实现前序后序，lcr中，clr前，rlc后
    void inorder2(treenode<szw> *root);//中序遍历，非递归写法，因为有v标记，只能用一次...
    void init();//初始化
    treenode<szw> *findMin(treenode<szw> *t);//找最小
    treenode<szw> *findMax(treenode<szw> *t);//找最大
    treenode<szw> *search(treenode<szw> *t, szw x);//搜索，成功则返回地址，否则返回NULL
    treenode<szw> *successor(treenode<szw> *t);//求后继
    treenode<szw> *predecessor(treenode<szw> *t);//前驱
    void insert(szw x);//插入
    void transplant(treenode<szw> *x, treenode<szw> *y);//将y转移到x，为删除服务，y可为空
    void remove(treenode<szw> *x);//删除
};


template<class szw>
void tree<szw>::transplant(treenode<szw> *x, treenode<szw> *y)
//将y移到x后，只建立了与父节点的关系，未建立与子节点的关系
{
    if(x==root) root=y;//移动到根节点的情况
    else if(x==x->p->l) x->p->l=y;//x为左子节点，建立与父节点的父to子关系
    else x->p->r=y;//x为左子节点，建立与父节点的父to子关系
    if(y!=NULL) y->p=x->p;//建立与父节点的子to父关系
}


template<class szw>
void tree<szw>::remove(treenode<szw> *x)
{
    if(x->l==NULL) {transplant(x,x->r);return;}//左空，右子树直接转移
    if(x->r==NULL) {transplant(x,x->l);return;}//右空，左子树直接转移
    treenode<szw> *qq=findMin(x->r);//找x后继
    if(qq!=x->r)//若后继非右节点
    {
        transplant(qq,qq->r);//完成后继的子树转移到后继位置的转移
        qq->r=x->r;//建立后继转移后与右子节点的父to子关系
        qq->r->p=qq;//建立后继转移后与右子节点的子to父关系
    }
    transplant(x,qq);//后继转移到删除位置
    qq->l=x->l;//建立后继转移后与左子节点的父to子关系
    qq->l->p=qq;//建立后继转移后与左子节点的子to父关系
    
}

template<class szw>
void tree<szw>::insert(szw x)
{
    if(root==NULL) {root=new treenode<szw>;root->key=x;root->p=NULL;return;}//空树
    treenode<szw> *t=root,*q;
    while(t!=NULL)
    {
        q=t;//保留父节点
        if(x<t->key) t=t->l;//向左下降
        else t=t->r;//向右下降
    }
    t=new treenode<szw>;
    t->p=q;t->key=x;
    if(x<q->key) q->l=t;
    else q->r=t;
    return;
}

template<class szw>
treenode<szw> *tree<szw>::predecessor(treenode<szw> *t)
{
    if(t->l!=NULL) return findMax(t->l);
    else while(t->p!=NULL && t==t->p->l) t=t->p;
    return t->p;
}

template<class szw>
treenode<szw> *tree<szw>::successor(treenode<szw> *t)
{
    if(t->r!=NULL) return findMin(t->r);
    else while(t->p!=NULL && t==t->p->r) t=t->p;
    return t->p;
}

template<class szw>
treenode<szw> *tree<szw>::search(treenode<szw> *t, szw x)
{
    while(t!=NULL && t->key!=x)
    {
        if(x<t->key) t=t->l;
        else t=t->r;
    }
    return t;
}

template<class szw>
treenode<szw> *tree<szw>::findMax(treenode<szw> *t)
{
    while(t->r!=NULL)
        t=t->r;
    return t;
}

template<class szw>
treenode<szw> *tree<szw>::findMin(treenode<szw> *t)
{
    while(t->l!=NULL)
        t=t->l;
    return t;
}

template<class szw>
void tree<szw>::init()
{
    treenode<szw> *t1,*t2,*t3,*t4,*t5,*t6,*t7,*t8;
    root=new treenode<szw>;
    t1=new treenode<szw>;
    t2=new treenode<szw>;
    t3=new treenode<szw>;
    t4=new treenode<szw>;
    t5=new treenode<szw>;
    t6=new treenode<szw>;
    t7=new treenode<szw>;
    t8=new treenode<szw>;
    
    
    root->key=6;
    root->p=NULL;
    
    t1->key=1;root->l=t1;t1->p=root;
    t5->key=5;t1->r=t5;t5->p=t1;
    t3->key=3;t5->l=t3;t3->p=t5;
    t2->key=2;t3->l=t2;t2->p=t3;
    t4->key=4;t3->r=t4;t4->p=t3;
    t8->key=8;root->r=t8;t8->p=root;
    t7->key=7;t8->l=t7;t7->p=t8;
}

template<class szw>
void tree<szw>::inorder1(treenode<szw> *t)
{
    if(t==NULL) return;
    inorder1(t->l);
    cout<<t->key<<' ';
    inorder1(t->r);
}

template<class szw>
void tree<szw>::inorder2(treenode<szw> *t)
{
    int i=1,n=8;
    while(i<=n)
    {
        while(t->l!=NULL && t->l->v==0)//v用来标记是否被访问过
            t=t->l;
        if(t->v==0)
        {
            cout<<t->key<<' ';
            t->v=1;
            i++;
        }
        if(t->r!=NULL && t->r->v==0) t=t->r;
        else t=t->p;
    }
}

int main()
{
    tree<int> tt;
    tt.init();
    return 0;
}


