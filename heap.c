#include <stdio.h>
#include <stdlib.h>

#define size 10
//----------------------------------//
void enqueue();
int dequeue();
void swap();
void TopDown();
void createQueue();
//----------------------------------//
int queue[size];
int front = -1;
int rear = -1;


struct TreeNode{
  int val;
  int *left;
  int *right;
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
  
}

void TopDown(){
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val  = dequeue();
    root->left = NULL;
    root->right = NULL;
    printf("%d" , root->val);
    
}
void enqueue(int data){
    if(rear != size){
      queue[++rear] = data;
    }
    else printf("Queue is full\n");
}

int dequeue(){
    if(front != rear){
      return queue[++front];
    }
    else{
      printf("Queue is empty");
      return 0;
    }
}

void CreateQueue(int *arr){
    int front = -1;
    int rear  = -1;
    int i = 0;
    int queue[size];
    while(arr[i]){
      enqueue(arr[i++]);
    }
}


int main()
{
    int arr[size] = {3,5,7,9,11};
    CreateQueue(&arr[0]);
    TopDown();

    
}