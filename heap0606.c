#include <stdio.h>
#define PQsize 100

int front = -1;
int rear  = -1;

struct P_queue{
    int ExecTime;
    int Resources;
    char Task;
    char Relate;
};
struct P_queue P_queue[100] = {{0,0}};


//1.choose operate ExcuTime or Resources  2.choose action insert or Remove 
//3.data = ExecTime,Resources,Task,Relate 4.if each stage input is 0 then quit
char opertate = 'Q';    //here need to set default value , or it will go wrong, default value do not effect result
char action = 'Q';      //here need to set default value , or it will go wrong, default value do not effect result
struct P_queue Indata;
struct P_queue Outdata;
int  flag = 0;          //flag to decide do or not

//-------------------------------Total Function-----------------------------------------//
void swap(struct P_queue *a,struct P_queue *b);
void insertPQ(struct P_queue data);
struct P_queue removePQ();
void cmpMax(struct P_queue *root , struct P_queue *leftNode , struct P_queue *rightNode);
void cmpMin(struct P_queue *root , struct P_queue *leftNode , struct P_queue *rightNode);
void built_heap(struct P_queue arr[] , int N);
void revise_BT(int i);
//--------------------------------------------------------------------------------------//

void swap(struct P_queue *a,struct P_queue *b){
    struct P_queue temp = *a;
    *a = *b;
    *b = temp;
}

void revise_BT(int i){
    if (opertate == 'E' || opertate == 'e'){//cmpMin
        int j = 0;
        while(j != i){//from first to check (here may can improve)
            int l = j*2+1;
            int r = j*2+2;
            cmpMin(&P_queue[j],&P_queue[l],&P_queue[r]);
            j++;
        }
    }
    else if(opertate == 'R' || opertate == 'r'){//cmpMax
        int j = i;
        while(j != -1){//from last to check (here may can improve)
            int l = j*2+1;
            int r = j*2+2;
            cmpMax(&P_queue[j],&P_queue[l],&P_queue[r]);
            j--;
        }
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
        struct P_queue data = P_queue[++front];
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
    struct P_queue *min = root;
    if(leftNode->ExecTime != 0 && leftNode->ExecTime < min->ExecTime){                   
        swap(leftNode,min);                                     
        min = root;
    }
    if(rightNode->ExecTime != 0 && rightNode->ExecTime < min->ExecTime){
        swap(rightNode,min);
        min = root;
    }
}

void built_heap(struct P_queue arr[] , int N){//max_heap and min_heap is the same function, only "cmpMax" need change to "cmpMin"
    int i = 0;
    while(i<N){
        insertPQ(arr[i]);
        i++;
    }
}

int main(){

    

    while(flag == 0){
        flag ++;

        struct P_queue arr[] = {{10,3,'A',0},{5,2,'B',0},{15,5,'C',0},{8,4,'D',0}};  //{ ExcuTime , Resources , Task , Relate }
        int N = sizeof(arr)/sizeof(arr[0]);

        printf("input opertate : (E or e for ExcuTime ,  R or r for Resources ,if other then quit) \n");
        scanf(" %c" , &opertate);
        
        built_heap(arr,N);

        if(opertate == 'E' || opertate == 'e'){
            for(int i = 0 ; i < rear+1 ; i++){
                printf("%d , %C \n",P_queue[i].ExecTime , P_queue[i].Task);
            }

            printf("do min_heap for ExcuTime\n\n");//less ExcuTime on top of root
            while(1){//if input other char , the loop will quit
                printf("input action : (I or i for Insert data , R or r for Remove data ,if other the quit) \n");
                scanf("%s" , &action);
                if (action == 'i' || action == 'I'){
                    printf("Insert your data use this form : ExecTime,Resources,Task,Relate \n");
                    int result;
                    result  = scanf("%d,%d, %c, %c" , &Indata.ExecTime , &Indata.Resources , &Indata.Task , &Indata.Relate);
                    if (result == 4){
                        printf("input data is : %d,%d,%c,%c\n" , Indata.ExecTime , Indata.Resources , Indata.Task , Indata.Relate);

                        insertPQ(Indata);
                        printf("after Insert data : \n");
                        for(int i = 0 ; i < rear+1 ; i++){
                            printf("%d , %C \n",P_queue[i].ExecTime , P_queue[i].Task);
                        }
                    }
                    else{
                        printf("your form is wrong\n");
                    }
                }
                else if (action == 'r' || action == 'R'){
                    printf("Remove data\n");
                    Outdata = removePQ();

                    printf("remove data is : %d,%d,%c,%c \n" , Outdata.ExecTime , Outdata.Resources , Outdata.Task , Outdata.Relate);
                    printf("after  remove data : \n");
                    for(int i = 0 ; i < rear+1 ; i++){
                        printf("%d , %C \n",P_queue[i].ExecTime , P_queue[i].Task);
                    }
                }
                else break;
            }
        }
        else if(opertate == 'R' || opertate == 'r'){
            for(int i = 0 ; i < rear+1 ; i++){
                printf("%d , %C \n",P_queue[i].Resources , P_queue[i].Task);
            }            

            printf("do max_heap for Resources\n");//more Resources on top of root
            while(1){//if input other char , the loop will quit
                printf("input action : (I or i for Insert data , R or r for Remove data ,if other the quit) \n");
                scanf("%s" , &action);
                if (action == 'i' || action == 'I'){
                    printf("Insert your data use this form : ExecTime,Resources,Task,Relate \n");
                    int result;
                    result  = scanf("%d,%d, %c, %c" , &Indata.ExecTime , &Indata.Resources , &Indata.Task , &Indata.Relate);
                    if (result == 4){
                        printf("input data is : %d,%d,%c,%c\n" , Indata.ExecTime , Indata.Resources , Indata.Task , Indata.Relate);

                        insertPQ(Indata);
                        printf("after Insert data : \n");
                        for(int i = 0 ; i < rear+1 ; i++){
                            printf("%d , %C \n",P_queue[i].Resources , P_queue[i].Task);
                        }
                    }
                    else{
                        printf("your form is wrong\n");
                    }
                }
                else if (action == 'r' || action == 'R'){
                    printf("Remove data\n");
                    Outdata = removePQ();

                    printf("remove data is : %d,%d,%c,%c \n" , Outdata.ExecTime , Outdata.Resources , Outdata.Task , Outdata.Relate);
                    printf("after  remove data : \n");
                    for(int i = 0 ; i < rear+1 ; i++){
                        printf("%d , %C \n",P_queue[i].Resources , P_queue[i].Task);
                    }
                }
                else break;
            }
        }
        else break;
    }

    return 0;
}