#include <stdio.h>
#define PQsize 100

int front = -1;
int rear  = -1;

struct P_queue{
    int ExecTime;
    int Resources;
};
struct P_queue P_queue[100] = {{0,0}};

//-------------------------------Total Function-----------------------------------------//
void swap(struct P_queue *a,struct P_queue *b);
void insertPQ(struct P_queue data);
struct P_queue removePQ();
void cmpMax(struct P_queue *root , struct P_queue *leftNode , struct P_queue *rightNode);
void cmpMin(struct P_queue *root , struct P_queue *leftNode , struct P_queue *rightNode);
void max_heap(struct P_queue arr[] , int N);
void revise_BT(int i);
//--------------------------------------------------------------------------------------//

void swap(struct P_queue *a,struct P_queue *b){
    struct P_queue temp = *a;
    *a = *b;
    *b = temp;
}

//check whether the node is following the max/min heap rules
void revise_BT(int i){
    int j = i;
    while(j != -1){//from last to check (here may can improve)
        int l = j*2+1;
        int r = j*2+2;
        cmpMax(&P_queue[j],&P_queue[l],&P_queue[r]);
        //cmpMin(&P_queue[j],&P_queue[l],&P_queue[r]);
        j--;
    }
}

//insertPQ function is not only include insert data to P_queue ,but also check that if the BT is max/min heap
void insertPQ(struct P_queue data){
    if (rear != PQsize) { // queue not full
        P_queue[++rear] = data;
        revise_BT(rear);
    }
    else printf("P_queue is full");
}

//removePQ function is not only remove data from P_queue ,but also let the highest priorty replace by the at last leaf
struct P_queue removePQ(){
    struct P_queue default_value = {0,0};
    if(rear > -1){ //queue not empty
        struct P_queue data = P_queue[++front];//the front value in upper if judge be added
        P_queue[front] = P_queue[rear];
        P_queue[rear] = default_value;
        rear--;
        revise_BT(rear);
        front--;
        return data;
    }
    else {
        printf("P_queue is empty");
        return default_value;
    }
}


//cmpMax function is for Max Resources
void cmpMax(struct P_queue *root , struct P_queue *leftNode , struct P_queue *rightNode){ // a is root , b is left node , c is right node
    struct P_queue *max = root;
    if(leftNode->Resources != 0 && leftNode->Resources > max->Resources){                   
        swap(leftNode,max);                                     
        max = root;
    }
    if(rightNode->Resources != 0 && rightNode->Resources > max->Resources){
        swap(rightNode,max);
        max = root;
    }
}

//cmpMin function is for Min ExecuteTime 
void cmpMin(struct P_queue *root , struct P_queue *leftNode , struct P_queue *rightNode){ // a is root , b is left node , c is right node
    struct P_queue *max = root;
    if(leftNode->ExecTime != 0 && leftNode->ExecTime < max->ExecTime){                   
        swap(leftNode,max);                                     
        max = root;
    }
    if(rightNode->ExecTime != 0 && rightNode->ExecTime < max->ExecTime){
        swap(rightNode,max);
        max = root;
    }
}

void max_heap(struct P_queue arr[] , int N){//max_heap and min_heap is the same function, only "cmpMax" need change to "cmpMin"
    int i = 0;
    while(i<N){
        insertPQ(arr[i]);
        i++;
    }
}

int main(){
    struct P_queue arr[] = {{10,4},{5,2},{15,7},{12,5},{18,3},{16,9},{12,100}};  //{ ExcuTime , Resources }
    int N = sizeof(arr)/sizeof(arr[0]);

    max_heap(arr,N);

    //---------------check max_heap--------------//
    printf("first print:\n");
    for(int i = 0 ; i < N ; i++){
        printf("%d\n",P_queue[i].Resources);
    }
    
    /*
    //---------------check max_heap--------------//
    for(int i = 0 ; i < N ; i++){
        printf("%d\n",P_queue[i].ExecTime);
    }
    */


    //------------------test result----------------------//
    printf(" remove : %d\n" , removePQ().Resources);
    printf("after remove print:\n");
    for(int i = 0 ; i < rear+1 ; i++){
        printf("%d\n",P_queue[i].Resources);
    }

    struct P_queue Indata = {2,200};
    insertPQ(Indata);
    printf("\n\n");
    for(int k = 0 ; k < rear+1 ; k++){
        printf("%d\n " , P_queue[k].Resources);
    }

    printf(" remove : %d\n" , removePQ().Resources);
    printf("after remove print:\n");
    for(int i = 0 ; i < rear+1 ; i++){
        printf("%d\n",P_queue[i].Resources);
    }

    struct P_queue In1data = {2,100};
    insertPQ(In1data);
    printf("\n\n");
    for(int k = 0 ; k < rear+1 ; k++){
        printf("%d\n " , P_queue[k].Resources);
    }
    //-----------------------------------------------------//

    return 0;
}