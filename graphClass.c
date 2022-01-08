#include <stdio.h>
#include <stdlib.h>
typedef struct GRAPH_NODE_ *pnode; // shall be declared before struct edge since we hold node pointer inside the edge

typedef struct edge_ { // edge struct
    int weight;
    pnode endpoint;
    struct edge_* next;
} edge, *pedge;

typedef struct GRAPH_NODE_ { // node struct
    int node_id;
    pedge edges;
    struct GRAPH_NODE_* next;
    int dist;
    int state;
} node, *pnode;

void printGraph_cmd(pnode head){
    /*print graph, loop over the whole list of nodes, and print node_id then all its edges details*/
    // init vars
    pnode p = head;
    pedge e;
    while(p){
        // loop over all the node "linked list"
        e = p->edges;
        printf("node id: %d out_edges: ",p->node_id);
        while(e){
            // loop over all the edges of specific node
            printf("(to %d, weight %d) ",e->endpoint->node_id, e->weight);
            e = e->next;
        }
        p = p->next;
        printf("\n");
    }
}

void freeEdges(pedge * eHead){
    /* loop over all the edges of specific node and delete them -> means, free those edges */
    pedge toFreeEdge;
    while (*eHead){
        toFreeEdge = *eHead;
        eHead = &((*eHead)->next);
        free(toFreeEdge);
    }
    if (*eHead != NULL){
        free(*eHead);
    }
}


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
        e = toFreeNode->edges;
        if (e != NULL){
            freeEdges(&e);    
        }
        p = &((*p)->next);
        free(toFreeNode);
    }
    return;
}

void build_graph_cmd(pnode * head){
    if (*head){
        deleteGraph_cmd(&head[0]);
    }
}

void insert_node_cmd(pnode * head, pnode item){
    // EASY CASE - list isnt exist -> just point the head to the start and the list holds 1 nodes alone
    if (*head == NULL){
        *head = item;
        return;
    }
    
    /* insert node item via node_id order 
    3 scenrios:
        1- item shall be added as the new head of the list
        2- item shall be added somewhere in the middle of the list
        3- item shall be added as the last item of the list
         */
    // case 1:
    if ((*head)->node_id > item->node_id){
        item->next = *head;
        *head = item;
        return;
    }
    if ((*head)->node_id == item->node_id){
        return;
    }
    
    // init vars
    pnode* p = head;
    pnode next = (*p)->next;
    
    // case 2:
    while(next){
    // loop over all the node "linked list"
        if(next->node_id == item->node_id){
            return;
        }
        if(next->node_id > item->node_id){
            (*p)->next = item;
            item->next = next;
            return;
        }
        next = next->next;
        p = &((*p)->next);
    }
    
    // case 3:
    (*p)->next = item;
    item->next = NULL;
    return;
}


void delete_node_cmd(pnode * head, int node_id){
    /*
    stages:
        1- find the node along the list
        2- remove(and free) all his IN_EDGES from the other nodes (they OUT_EDGES at the other nodes)
        3- remove(and free) the node and his outEdges
    */
    // stage 1:
    pnode node_to_del;
    pnode p = *head;
    if (p->node_id == node_id){ // node to delete is first in the linked list
        node_to_del = p;
        *head = p->next;
    }
    else { // not the first -> shall loop over the list and get it.
        pnode prevNode;   
        while (p != NULL){
            prevNode = p;
            if(p->next->node_id == node_id){
                node_to_del = p->next; // save the node we gonna delete
                prevNode->next = node_to_del->next;  // change his prevNode.next to point on the next of the delete_node
                break;
            }   
            p = p->next;
        }
    }
    // stage 2:
    p = *head;
    pedge eHead = (pedge)malloc(sizeof(pedge));
    pedge toDeleteEdge;
    while (p != NULL){
        pedge eHead = p->edges;
        /* loop over all the edges of specific node and delete them -> means, free those edges */
        if (eHead != NULL && eHead->endpoint->node_id == node_id){
            toDeleteEdge = eHead;
            eHead = eHead->next;
            free(toDeleteEdge);
            p->edges = eHead;
            eHead = NULL; // found the relevant edge to remove and deleted it.
        }
        while (eHead != NULL){
            pedge prev;
            prev = eHead;
            if (eHead->next != NULL && eHead->next->endpoint->node_id == node_id){
                toDeleteEdge = eHead->next;
                prev->next = toDeleteEdge->next;
                free(toDeleteEdge);
                eHead = NULL; // found the relevant edge to remove and deleted it.
                // ^ kinda like break
            }
            else {
                eHead = eHead->next;
            }
        }    
        p = p->next;
    }
    free(eHead);
    // stage 3:
    freeEdges(&(node_to_del->edges));
    free(node_to_del);           
}

pnode get_node(pnode * head, int node_id){ 
    /* if node_id is not exists: create new node and add it with insert function to the graph */
    if (node_id < 0){ 
        // invalid node_id number
        return NULL;
    }
    
    pnode p = *head;
    while (p){
        if (p->node_id == node_id){
            return p;
        }
        p = p->next;
    }
    p = (node*)malloc(sizeof(node));
    if (p == NULL){
        deleteGraph_cmd(head);
        return NULL;
    }
    p->node_id = node_id;
    insert_node_cmd(head, p);
    return p;
}

int get_size(pnode head){
    /* return size of node -> O(n) running time! its expensive function! */
    pnode p = head;
    int size = 0;
    while (p){
        size++;
        p = p->next;
    }
    return size;
}

void insert_edge(pnode * head, int from, int weight, int to){
    pedge e = (edge *)malloc(sizeof(edge));
    if (e == NULL){
        printf("failed to allocate memory, edge from %d, weight %d, to %d\n",from, weight, to);
        return;
    }
    e->endpoint = get_node(head, to);
    e->weight = weight;
    e->next = NULL;
    pnode pn = get_node(head, from);
    pedge *pe = &(pn->edges);
    while(*pe){
        pe = &((*pe)->next);
    }
    *pe = e; //set next to e
    return;
}