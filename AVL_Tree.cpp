/*********************************************************************************************************************
     **
     **  Program to insert and delete into an AVL tree.
     **  AVL tree is self balancing binary tree. Difference of height of left or right subtree
     **
     **  There are four different use cases to insert and delete into AVL tree
	 **     1. left left   - needs ones right rotation
	 **     2. left right  - needs one left and one right rotation
	 **     3. right left  - needs one right and one left rotation
	 **     4. right right - needs one left rotation
	 **
     **  Display in Inorder, Preorder, Postorder manner
     **  Tree is printed in 2dimensional from top to bottom in left to right way
     
     **  Written By:    Akash Vishwas Londhe
     **
*********************************************************************************************************************/

#include<bits/stdc++.h>
#define count 10
using namespace std;

typedef struct node
{
	
	int data;
	struct node *left;
	struct node *right;
	int height;
	
}NODE;

void inorder(NODE *root)
{
	
	if(root->left)
		inorder(root->left);
		
	printf(" %d ",root->data);
	
	if(root->right)
		inorder(root->right);
	
}

void preorder(NODE *root)
{
	
	printf(" %d ",root->data);
	
	if(root->left)
		preorder(root->left);	
	
	if(root->right)
		preorder(root->right);
		
}

void postorder(NODE *root)
{
	
	if(root->left)
		postorder(root->left);
			
	if(root->right)
		postorder(root->right);
		
	printf(" %d ",root->data);
		
}

int height(NODE *root)
{
	
	if(root==NULL)
		return 0;
	return root->height;
	
}

int setHeight(NODE *root)
{
	
	if(root==NULL)	
		return 0;
	int left = root->left!=NULL ? root->left->height:0;
	int right = root->right!=NULL ? root->right->height:0;
	
	return 1+(left>right?left:right);
	
}

NODE * rotateRight(NODE *root)
{

	NODE *tmp=root->left;
	root->left=root->left->right;
	tmp->right=root;
	root->height=setHeight(root);
	tmp->height=setHeight(tmp);
	
	return tmp;
		
}

NODE * rotateLeft(NODE *root)
{

	NODE *tmp=root->right;
	root->right=root->right->left;
	tmp->left=root;
	root->height=setHeight(root);
	tmp->height=setHeight(tmp);
	
	return tmp;
		
}

NODE * avlTreeInsert(NODE *root, int data)
{
	
	if(root==NULL)
	{
		NODE * tmp=(NODE *)malloc(sizeof(NODE));
		tmp->data=data;
		tmp->height=1;
		return tmp;
	}
	if(data < root->data)
		root->left=avlTreeInsert(root->left,data);
	else
		root->right=avlTreeInsert(root->right,data);
	
	root->height = setHeight(root);
	int balance = height(root->left) - height(root->right);
	
	if(balance > 1)
	{
		if( height(root->left->left) >= height(root->left->right) )
		{
			 return rotateRight(root);
		}
		else
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
	}
	if(balance < -1)
	{
		if( height(root->right->right) >= height(root->right->left) )
		{
			 return rotateLeft(root);
		}
		else
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}
	
	return root;
	
}

int largest(NODE * root)
{
    
	if(root->right==NULL)
		return root->data;
	largest(root->right);
	
}

int smallest(NODE * root)
{
    
	if(root->left==NULL)
		return root->data;
	largest(root->left);
	
}


NODE * avlTreeDelete(NODE *root,int data)
{
    
	if(data<root->data)	
		root->left=avlTreeDelete(root->left,data);
	else if(data>root->data)
		root->right=avlTreeDelete(root->right,data);
	else
	{
		if(root->left==NULL)
		{
			NODE * tmp=(NODE*)malloc(sizeof(NODE));
			tmp=root->right;
			free(root);
			return tmp;
		}
		else if(root->right==NULL)
		{
			NODE * tmp=(NODE*)malloc(sizeof(NODE));
			tmp=root->left;
			free(root);
			return tmp;
		}
		
		//using left subtree
		int max=largest(root->left);
		root->data=max;
		root->left=avlTreeDelete(root->left,max);
		
		//using right subtree
		/*
		int min=smallest(root->right);
		root->data=min;
		root->right=avlTreeDelete(root->right,min);
		*/	
	}
	
	if(root==NULL)
		return root;
		
	root->height=setHeight(root);
	
	int balance = height(root->left) - height(root->right);
	
	if(balance>1)
	{
		if(height(root->left->left) >= height(root->left->right))
		{
			return rotateRight(root);
		}	
		else
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		
	}
	if(balance < -1)
	{
		if( height(root->right->right) >= height(root->right->left) )
		{
			 return rotateLeft(root);
		}
		else
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
	}		
		
	return root;
	
}

void printTree(NODE *root, int space)
{
	
	if(root==NULL)
		return;
	
	space = space+count;
	
	printTree(root->right, space);
	
	for(int i=count;i<=space;i++)
		printf(" ");
	printf("%d\n\n",root->data);
	
	printTree(root->left, space);
	
}

int main()
{
	
	NODE * root=avlTreeInsert(root,10);
	
	root=avlTreeInsert(root,20);
	root=avlTreeInsert(root,30);
	root=avlTreeInsert(root,40);
	root=avlTreeInsert(root,50);
	root=avlTreeInsert(root,25);
	
	printf(" Inorder Traversal : ");
	inorder(root);
	
	printf("\n Preorder Traversal : ");
	inorder(root);
	
	printf("\n Postorder Traversal : ");
	inorder(root);
	
	printTree(root,0);
	
	root=avlTreeDelete(root,10);
	root=avlTreeDelete(root,20);
	root=avlTreeDelete(root,25);
	printf("\n\n\n Inorder Traversal : ");
	inorder(root);
	
	printf("\n Preorder Traversal : ");
	inorder(root);
	
	printf("\n Postorder Traversal : ");
	inorder(root);
	
	printTree(root,0);
	
	
	getchar();
	return 0;
	
}
