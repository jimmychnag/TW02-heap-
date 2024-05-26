#include <stdio.h>
#include <stdlib.h>
https://www.geeksforgeeks.org/building-heap-from-array/
#define size 10
//----------------------------------//
void enqueue();
int*  dequeue();
void swap();
void TopDown();
void createQueue();
int  cmp();
//----------------------------------//
int **queue[size];
int front = -1;
int rear = -1;
int *deData = (int *)malloc(sizeof(int)); // 存放dequeue()出來的記憶體位置

struct TreeNode{
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(int a, int b){
  return (a > b) ? a : b ;
}

void TopDown(){
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    deData = dequeue();
    root->val  = *deData;
    root->left = NULL;
    root->right = NULL;
    printf("%d" , root->val);
    if(root->left == NULL){
      deData = dequeue();
      root->left = deData;
      (root->left)->val = *deData;
      root->left->left = NULL;
      root->left->right = NULL;
    }
    else if(root->right == NULL){
      deData = dequeue(); 
      root->right = deData;
      (root->right)->val = *deData;
      root->right->left = NULL;
      root->right->right = NULL;
    }
}
void enqueue(int *data){
    if(rear != size){
      queue[++rear] = data;
    }
    else printf("Queue is full\n");
}

int* dequeue(){
    if(front != rear){
      return queue[++front];
    }
    else{
      printf("Queue is empty");
      return NULL;
    }
}

void CreateQueue(int *arr){
    int front = -1;
    int rear  = -1;
    int i = 0;
    while(arr[i]){
      enqueue(&arr[i++]);
    }
}


int main()
{
    int arr[size] = {3,5,7,9,11};
    CreateQueue(&arr[0]);
    TopDown();

    
}