
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
void deleteGraph_cmd(pnode* head){
    /* delete the whole graph, shall free every node and edge structs*/
    if (*head == NULL){
        return;
    }
    // init vars
    pnode* p = head;
    pedge e;
    pnode toFreeNode;
    // pedge toFreeEdge;

    while(*p)
        // loop over all the node "linked list"
    {
        toFreeNode = *p;
        pnode  pass_edge = toFreeNode->edges;
        pnode pf;
        if (e != NULL){
            while (pass_edge){
                pf =pass_edge ;
                pass_edge = pass_edge->next;
                free(pf);
            }

        }
        p = &((*p)->next);
        free(toFreeNode);
    }
    return;
}

pnode get_node(pnode *head, int node_id){

    pnode p = *head;
    while (p !=NULL){
        if (p->node_num == node_id){
            return p;
        }
        p = p->next;
    }
    return NULL;
}
void build_graph_cmd(pnode *head){
    char a []="A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2";
    int first = 1;
    int  size ;
//    size = a[3];
    scanf("%d", &size);
    //the first n
    char t;
    scanf("%c",&t);
    while(t== ' '){
        scanf("%c",&t);
    }
    while(size!=0) {
        insert_node_cmd(head);
        size = size - 1;
        char t;
        if (scanf("%c", &t) == 32);
        if(t=='D'){
            int num;
            scanf("%d" , &num);
            delete_node_cmd(head ,num);

            return;
        }
        if(t =='S'){
            int start ;
            int end;
            scanf("%d" ,&start );
            scanf("%d" ,& end );
            printf("Dijsktra shortest path: %d \n",shortsPath_cmd(&head,start,end));
            return;
        }
        if (t=='T'){
            printf("TSP shortest path: %d \n",TSP_cmd(head));
        }
    }//14

    return;

}

int  shortsPath_cmd(pnode *head, int start,int end){
    //check
    if(!head ||!(*head)){
        return 0;
    }
    node * pass = (*head);
         while(pass !=NULL){
             pass ->visit=0;
             pass->wight = INT_MAX;
             pedge ed =pass ->edges;
             while(ed){
                 ed -> endpoint -> wight =INT_MAX;
                 ed = ed ->next;
             }
             pass = pass->next;

         }
    int min= INT_MAX;
//         int start ;
//         int end;
//         scanf("%d" ,&start );
//         scanf("%d" ,& end );
         if(start == end){
             return 0;
         }
         
         
         //there is no list
         if(!(* head)){
             return -1;
         }

         //the first node
         node * next =get_node(head , start);
    if(next==NULL){
        return -1;
    }
         next ->wight = 0;
         next ->visit =1;

         while (next->node_num !=end){

             if(!(next ->edges)){
                 return -1;
             }
            edge *ed =next ->edges;
              min= INT_MAX;
             int next_node =-1;
             int node_wight =next ->wight;

             while (ed!=NULL)
             {
                 // sunOfNode.getWeight() > (node.getWeight() + neighborEdge.getWeight())
                 int new_weight = ed ->weight + node_wight;
                 if( new_weight < ed->endpoint ->wight ){

                      //pnode  r =get_node(head ,ed->endpoint ->node_num) ;
//                      r->wight =new_weight;
                     ed->endpoint ->wight =new_weight;
                 }
                 if(ed->endpoint ->wight <min){
                     min = ed->endpoint ->wight;
                     next_node = ed ->endpoint ->node_num;
                 }
                 ed=ed->next;
             }
             if(next_node ==-1 ) {
                 return (-1);
             }
              next =get_node(head ,next_node );
             if(next==NULL)
                 return -1;
            next -> wight =min;
             if(!next || next ->visit ==1){
                 return -1;
             }

             next ->visit =1;


//             /ed = next ->edges;
         }
       
         return min;
     }
//int fac (int num_of_nodes){
//    int count =1;
//    while(num_of_nodes!=1){
//        count *=num_of_nodes;
//        num_of_nodes--;
//    }
//}
int weight;
pnode graph;
int arrlenth;
void input_Array(int* fromArr,int* toArr, int arrLenght)
{
    for (int i = 0; i < arrLenght; ++i)
    {
        toArr[i] = fromArr[i];
    }
}

void swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i]= arr[j];
    arr[j] = temp;
}

void PermotitionOfArr(int* arr, int arrLength)
{

    int tempWeight = 0;
    for (int i = 0; i < arrLength-1; ++i)
    {
        int D = shortsPath_cmd(graph,arr[i], arr[i+1]);
        if (D == -1)
        {
            tempWeight = INT_MAX;
            return;
        }
        tempWeight += D;
    }
    if (tempWeight < weight)
    {
        weight = tempWeight;
    }
}

void permotion( int start ,int* arr, int arrLength){
    if (start == arrLength -1 ){
        PermotitionOfArr(arr, arrLength);
        return;
    }
    for (int i = start; i < arrLength; ++i) {
        int* arrCopy = (int*)(calloc(arrLength, sizeof(int)));
        input_Array(arr,arrCopy,arrLength);
        swap(arrCopy,start, i);
        permotion(start + 1, arrCopy, arrLength);
        free(arrCopy);
    }
}

int TSP_cmd(pnode head)
{
    weight = INT_MAX;
    arrlenth = -1;
    graph = head;
    scanf("%d", &arrlenth);
    int *arr = (int *) (calloc(arrlenth, sizeof(int)));

    for (int i = 0; i < arrlenth; i++) {
        scanf("%d", &arr[i]);
    }
    int *arrCopy = (int *) (calloc(arrlenth, sizeof(int)));
    input_Array(arr,arrCopy,arrlenth);
    permotion(0,arrCopy,arrlenth);
    free(arr);
    free(arrCopy);
    if (weight == INT_MAX){
        weight = -1;
    }
    return weight;
}