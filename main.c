
//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T 3 2 0 5
#include <stdio.h>


#include <math.h>
#include <string.h>

#include <stdlib.h>
#define GRAPH_
typedef struct GRAPH_NODE_ *pnode;
typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int visit;
    int wight;
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;
void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head , int num);
// void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode *head ,int x,int y);
int TSP_cmd(pnode head);
void deleteGraph_cmd(pnode* head){
    /* delete the whole graph, shall free every node and edge structs*/
    if (*head == NULL){
        return;
    }
    // init vars
    pnode* p = head;
    pedge e = NULL;
    // pnode toFreeNode;
    // pedge toFreeEdge;

    while(*p)
        // loop over all the node "linked list"
    {
        pnode toFreeNode = *p;
        pedge  pass_edge = toFreeNode ->edges;
        pedge pf;
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
void delete_node_cmd(pnode *head ,int num){
    if(! head){
        return;
    }
    if(!(*head))
        return;

    node * pointer =*head;
    while(pointer != NULL){

    if( pointer ->node_num ==num){
        node * pointer2 = pointer ->next;
        while(pointer2  !=NULL &&pointer2 ->node_num ==num ){
            pointer2 = pointer2 ->next;
        }

        if( pointer == *head){
            *head = pointer2;
        }
        if (pointer !=* head){
            (*head) ->next = pointer2;
        }


        while(pointer !=pointer2){
            node * p= pointer;
            //free the edges
            pedge pf;
            pedge pass_edge =p ->edges;
            while (pass_edge){
                pf =pass_edge ;
                pass_edge = pass_edge->next;
                free(pf);
            }
//            if (pf!= NULL){
//                free(pf);
//            }
            pointer =pointer->next;
            free(p);
        }

        }

        pointer = pointer ->next;

}
}
void insert_node_cmd(pnode *head){

    //the first node we need to creat

//    scanf("%d " , &num_of_node) ;
    node* new = (node*)malloc(sizeof(node));
    if(!new) {
        printf("error");
        return;
    }

        //there is no elements in the list
        if(!(*head)){
            int num_of_node;
            scanf("%d " , &num_of_node) ;
            new -> next = NULL;
            new ->edges = NULL;
            new ->node_num = num_of_node;
            *head = new;

            //start to ger edges
            edge* pass_e ;
            while (scanf("%d " , &num_of_node) ==1 ) {
            edge* new_e = (edge*) malloc(sizeof(edge));
            if(!new_e) {
                printf("error");
                return;}
            int wight_of_node;
            scanf("%d" , &wight_of_node);
            node* endpoint = (node*) malloc(sizeof(node));
            if(!endpoint) {
                printf("error");
                return;}
            endpoint ->node_num = num_of_node;
            new_e -> endpoint =endpoint;
            new_e->weight=wight_of_node;
            new_e ->next =NULL;
            if(new ->edges == NULL){
                new ->edges = new_e;
                pass_e = new_e;
            }
            else{
                pass_e ->next =new_e;
                pass_e = new_e;
            }

        }}
        else{
            int num_of_node;
            scanf("%d " , &num_of_node) ;
            
            node * pass =(*head);
            while(pass ->next != NULL &&pass ->node_num != num_of_node){
                pass = pass->next;
            }

            if(pass ->next != NULL){
                pass ->next =pass ->next->next;
                delete_node_cmd(head,num_of_node);
                while(pass ->next != NULL){
                    pass = pass->next;
                }
            }

            new -> next = NULL;
            new ->edges = NULL;
            new ->node_num = num_of_node;
            pass ->next =new;
            //start to ger edges
            edge* pass_e = new->edges;

//            scanf("%d " , &num_of_node);
            while (scanf("%d " , &num_of_node)==1 ) {
                edge* new_e = (edge*) malloc(sizeof(edge));
                if(!new_e) {
                    printf("error");
                    return;}
                int wight_of_node;
                scanf("%d" , &wight_of_node);
                node* endpoint = (node*) malloc(sizeof(node));
                if(!endpoint) {
                    printf("error");
                    return;}
                endpoint ->node_num = num_of_node;
                new_e -> endpoint =endpoint;
                new_e->weight=wight_of_node;
                new_e ->next =NULL;
                if(new ->edges == NULL){
                    new ->edges = new_e;
                    pass_e = new_e;
                }
                else{
                    pass_e ->next =new_e;
                    pass_e = new_e;
                }
//                scanf("%d " , &num_of_node);
                }
        }}

void build_graph_cmd(pnode *head){
   
    int  size ;
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
        scanf("%c", &t) ;

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
            printf("Dijsktra shortest path: %d \n",shortsPath_cmd(head,start,end));
            return;
        }
        if (t=='T'){
            printf("TSP shortest path: %d \n",TSP_cmd(*head));
            return;
        }
    }

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
             pass->wight = __INT_MAX__;
             pedge ed =pass ->edges;
             while(ed){
                 ed -> endpoint -> wight =__INT_MAX__;
                 ed = ed ->next;
             }
             pass = pass->next;

         }
    int min= __INT_MAX__;
        //  int start ;
        //  int end;
        // scanf("%d" ,&start );
        // scanf("%d" ,& end );
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
              min= __INT_MAX__;
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
        int D = shortsPath_cmd(&graph,arr[i], arr[i+1]);
        if (D == -1)
        {
            tempWeight = __INT_MAX__;
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
    weight = __INT_MAX__;
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
    if (weight == __INT_MAX__){
        weight = -1;
    }
    return weight;
}

    


int main(){

    char t='h';
    pnode head =NULL;
    char c;
    while (scanf("%c ",&c)!=EOF || t == ' '){

    if(c=='A'){
        build_graph_cmd(&head);}

    if(c=='B'){
        insert_node_cmd(&head);
    }
      if(c=='D'){
          int num;
          scanf("%d" , &num);
          delete_node_cmd(&head,num);
      }
      if(c=='S'){
         int start ;
         int end;
         scanf("%d" ,&start );
         scanf("%d" ,& end );
          printf("Dijsktra shortest path: %d \n",shortsPath_cmd(&head,start,end));
      }
      if (c=='T'){
          printf("TSP shortest path: %d \n",TSP_cmd(head));
      }
      //A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
      char t;
      scanf("%c",&t);
    }
    if (head != NULL){
        deleteGraph_cmd(&head);
    }
//    if (n != NULL){
//        free(n);
//    }
    return 0;
}


