#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graphAlgo.h"
int main(){

    char chr;
    int num_of_nodes, idx, node_id;
    int weight, dest_node;
    int num;
    pnode head = NULL;
    pnode n = NULL;
    // pedge e, tempE;
    
    for(;scanf("%c ",&chr)!=EOF;){
        if (chr == 'A'){ // case A create whole graph (linked list of nodes and ea node hold list of edges)
            if (head != NULL){
                deleteGraph_cmd(&head);
                head = NULL;
            }
            scanf("%d ",&num_of_nodes);
            idx = 0;
            while(idx < num_of_nodes){
                scanf("%c ",&chr);
                scanf("%d ",&node_id); // start of new node
                n = (pnode)malloc(sizeof(node));
                if (n == NULL){
                    deleteGraph_cmd(&head);
                    return -1;
                }
                n->node_id = node_id;
                insert_node_cmd(&head, n); // add node to the linked list of nodes 
                // e = n->edges; // add the edges now.
                while (scanf("%d ",&dest_node) == 1){
                    scanf("%d ",&weight);
                    insert_edge(&head, n->node_id, weight, dest_node);
                }
                idx++;
                n = NULL;
                // printGraph_cmd(head);
                // printf("\n");
            }
        }
        else if (chr == 'B'){ // B case - add specific one node
            if (scanf("%d ",&node_id)){ // else, skip.
                n = get_node(&head, node_id);  // get or add&&get node to the linked list of nodes 
                if (n->edges != NULL){
                    freeEdges(&(n->edges));
                    if (n->edges != NULL){
                        n->edges = NULL;
                    }
                }
                // insert_node_cmd(&head, n);
                while (scanf("%d ",&dest_node) == 1){
                    scanf("%d ",&weight);
                    insert_edge(&head, n->node_id, weight, dest_node);
                }
                n = NULL;
            }
        }
        else if (chr == 'D'){ // delete node
            scanf("%d ",&node_id);
            delete_node_cmd(&head, node_id);
        }
        else if (chr == 'S'){ // shortest path
            int src, dest;
            scanf("%d ",&src);
            scanf("%d ",&dest);
            printf("Dijsktra shortest path: %d \n",shortest_path(head, src, dest));
        }
        else if (chr == 'T'){ // TSP - idont know when we ended to get inputs for TSP...
            int size;
            scanf("%d ",&size);
            int * arr = (int*)malloc(size*sizeof(int));
            if (arr == NULL){
                deleteGraph_cmd(&head);
                return -1;
            }
            int i = 0;
            while (i < size){
                scanf("%d ",&num);
                arr[i] = num;
                i++;
            }
            printf("TSP shortest path: %d \n",TSP(head, &arr[0], i));
            free(arr);
        }
        // printGraph_cmd(head);
    }
    if (head != NULL){
        deleteGraph_cmd(&head);
    }
    if (n){
        free(n);
    }
    return 0;
}