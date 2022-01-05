#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    char t="h";
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
//A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 T 3 2 0 5