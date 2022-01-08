#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <math.h>
#include <limits.h>

/**
 * @brief set all nodes distances to 'inf' except the src node which will be 0
 * 
 * @param head 
 * @param src 
 */
void initiate_nodes(pnode head, int src){
    // dist- holds the miniml distance from src, initially -1.
    //state- describes state of node i dijksta process: 0- dist is -1, 1- seen but not visited, 2- visited.

    pnode curr = head;
    while(curr){
        curr->dist = -1; 
        curr->state = 0;
        curr = curr->next;
    }
    curr = get_node(&head, src);
    curr -> dist = 0;
    curr -> state = 1;
}

void print_status(pnode head){//for debug help
            // printf("***\n");
    while(head){
            // printf("dist of node %d: %d\n",head->node_id, head->dist);
            // printf("state of node %d: %d\n",head->node_id, head->state);
        head = head->next;
    }
            //printf("***\n");
}

int shortest_path(pnode head, int src, int dest){
    //set all distances to -1, state to 0 (unseen).
    //set src dist to 0 and state to 1, update nighbors distance and insert his nighbors to list
    //  {run over list, take minimal distance node as current
    //  update distance to nighbors, add them to list. set current to visited.}
    //repeat until list is empty
    pnode dest_pnode = get_node(&head, dest);
    pnode curr_node = head;
    initiate_nodes(head, src);
    int min_node_id = 0;
    while(min_node_id != -1){//stop if no relevant node was found
        // print_status(head);  // debug print
        min_node_id = -1;
        curr_node = head;
        int min_dist = -1;
        while(curr_node){
            if(curr_node->state == 1){
                if(min_dist == -1 || min_dist > curr_node -> dist){
                    min_node_id = curr_node -> node_id;
                    min_dist = curr_node->dist;
                }
            }
            curr_node = curr_node->next;
        }
        if(min_node_id != -1){
            curr_node = get_node(&head, min_node_id);
            pedge e= curr_node -> edges;
            //ease edges
            while(e){
                //condition: the endnode is unseen, or seen (not visited) and has bigger distance than dist+weight
                if(e->endpoint->state==0 || (e->endpoint->state==1 && (curr_node->dist + e->weight) < e->endpoint -> dist)){
                    e->endpoint->state = 1;
                    e->endpoint -> dist = curr_node->dist + e->weight;
                }
                e = e->next;
            }
            curr_node -> state = 2;
        }
    }
    
    return dest_pnode -> dist; 
    //how to improve- efficient data structure to keep relevant nodes (state 1)
}

int get_node_index(int size, int dists[size][size], int id){
    for (int i = 0; i < size; i++)
    {
        if(dists[0][i+1] == id){
            return i+1;
        }
    }
    return -1;
    
}

int get_distance(int size, int dists[size][size], int len, int path[]){
    //calculate length of path
    int dist = 0;
    // printf("path: ");
    // for (int i = 0; i < len; i++)
    // {
    //     printf("%d,",path[i]);
    // }
    // putchar('\n');
    for (int i = 0; i < len-1; i++)
    {
        int src_i = get_node_index(size, dists, path[i]);
        int dest_i = get_node_index(size, dists, path[i+1]);
        // printf("index of %d: %d\n",path[i],src_i);
        // printf("index of %d: %d\n",path[i+1],dest_i);
        int temp_dist = dists[src_i][dest_i];
        // printf("dist from 0 to 1: %d\n",dists[1][2]);
        // printf("dist from %d to %d: %d\n",path[i],path[i+1],temp_dist);
        if(temp_dist == -1){//impossible path
            return INT_MAX;
        }
        dist += temp_dist;
    }
    // printf("path distance: %d\n", dist);
    return dist;
}


int recursive_TSP(int size, int dists[size][size], int *path, int len1, int *nodes, int len2){
    
    if(len2 == 0){
        return get_distance(size, dists, len1, path);
    }
    int min_dist = INT_MAX;
    for (int i = 0; i < len2; i++){
        path[len1] = nodes[i];//extend path by 1 node
        int new_nodes[len2-1], c=0;
        for(int j = 0; j<len2; j++ ){//create new list of spare nodes (node that are not part of the path)
            if(j!=i){
                new_nodes[c] = nodes[j];
                c++;
            }
        } 
        int curr_dist = recursive_TSP(size, dists, path, len1+1, new_nodes, len2-1);
        if(curr_dist != -1 && min_dist > curr_dist){
            min_dist = curr_dist;
        }
    }
    return min_dist;
}


int TSP(pnode head, int * tspArr, int size){
    // create dists matrix (compute pairs distance, first row is nodes id)
    int dists[size+1][size+1];
    dists[0][0] = -1;
    for (int i = 0; i < size; i++)
    {
        //set rows and columns to node_id
        dists[0][i+1] = tspArr[i];
        dists[i+1][0] = tspArr[i];
    }
    //fill the matrix- TODO
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            dists[i+1][j+1] = shortest_path(head, tspArr[i], tspArr[j]);
        }
        
    }
    //debug print matrix
            // printf("dist matrix:\n");
    for (int i = 0; i < size+1; i++)
    {
        for (int j = 0; j < size+1; j++)
        {
            // printf("%d,",dists[i][j]);
        }
            // putchar('\n'); 
    }
            // printf("dist from 0 to 1: %d\n",dists[1][2]);
    int *path = (int *)malloc(size*sizeof(int));
    int min_dist = recursive_TSP(size+1, dists, path, 0, tspArr, size);
    free(path);
    // run rec_TSP
    if(min_dist == INT_MAX){
        return -1;
    }
    return min_dist;
}