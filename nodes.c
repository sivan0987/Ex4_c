#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

void insert_node_cmd(pnode *head){

    //the first node we need to creat

//    scanf("%d " , &num_of_node) ;
    node* new = (node*) malloc(sizeof(node));
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
                delete_node_cmd(&head,num_of_node);
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

        if( pointer == head){
            * head = pointer2;
        }
        if (pointer != head){
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


    //  free(new);

//  int  shortsPath_cmd(pnode *head){
// printf("BCJDSCBJB");
// node * pass = (*head);
// while(pass !=NULL){
//     pass ->visit=0;
//     pass->wight = -1;
//     pass = pass->next;

// }

// int start ;
// int end;
// scanf("%d" ,&start );
// scanf("%d" ,& end );
// if(start == end){
//     return 0;
// }
// printf("%d \n" ,start);
// printf("%d" ,end);
// // printf("%d",start);
// //there is no list
// if(!(* head)){
//      return -1;
// }

// //the first node
// node * next =get_node(head , start);
// next ->wight = 0;
// next ->visit =1;
// if(next==NULL){
//     return -1;
// }
// while (next->node_num !=end){

//     if(!(next ->edges)){
//         return -1;
//     }
//     edge *ed =next ->edges;
//     int min= 1000;
//     int next_node =-1;
//     int node_wight =next ->wight;

//     while (ed!=NULL)
//     {
//         // sunOfNode.getWeight() > (node.getWeight() + neighborEdge.getWeight())
//         int new_weight = ed ->weight + node_wight;
//         if( new_weight < ed->endpoint ->wight ){
//             ed->endpoint ->wight =new_weight;
//         }
//         if(ed->endpoint ->wight <min){
//             min = ed->endpoint ->wight;
//             next_node = ed ->endpoint ->node_num;
//         }
//         ed=ed->next;
//     }
//     if(next_node ==-1 ) {
//         return (-1);
//     }
//     node * next =get_node(head ,next_node );
//     if(!next || next ->visit ==1){
//         return -1;
//     }
//     next->visit=1;

// }
// printf("bvjhbfhdvb");
// printf("%d" , next ->wight);
// return next ->wight;
// }
//T 3 2 0 5