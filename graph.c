#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "graph.h"


void deleteGraph_cmd(pnode* head)
{
 pnode temp = *head; 
    while (temp!= NULL) 
    {
        pedge e = temp->edges;
        while (e != NULL) 
        {
            pedge tmp1 = e;
            e = e->next;
            free(tmp1);
        }
        pnode tmp2 = temp;
        temp = temp->next;
        free(tmp2);
    }
    *head = NULL;
}
void build_graph_cmd(pnode *head) 
{
    deleteGraph_cmd(head);
    int num = 0;
    scanf("%d", &num);
    char node = 'A';
    scanf("%c", &node);
    for (int k = 0; k < num; ++k)
    {
        scanf("%c", &node);
        insert_node_cmd(head);
    }
}


pnode get_node(int numNode, pnode *head) 
{
    pnode tmp = *head;
    while (tmp != NULL)
    {
        if (tmp->node_num == numNode)
        {
            return tmp;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return NULL;
}


void delete_node_cmd(pnode *head){ 
    int x;
	scanf("%d", &x);
	pnode copy = *head;
	while (copy != NULL) 
    {
		if (copy->edges != NULL && copy->edges->endpoint->node_num == x) 
        {
			pedge new = copy->edges;
			copy->edges = copy->edges->next;
			free(new);
		}
		copy = copy->next;
	}
	pnode tmp1 = *head, next = *head;
	next = tmp1->next;
	while (next) {
		if (next->node_num == x) 
        {
			tmp1->next = next->next;
			free(next);
			next = tmp1;
		}
		else {
			tmp1 = next;
			next = tmp1->next;
		}
	}
}

void insert_node_cmd(pnode *head)
{
    int x = -1;
    scanf("%d", &x);
    pnode p_get = get_node(x,head);
    if (p_get == NULL)
    {
        p_get = (pnode)malloc(sizeof(node));
        if (p_get == NULL)
        {
            return;
        }
        p_get->node_num = x;
        p_get->next = *head;
        p_get->edges = NULL;
        *head = p_get;
    }
    else
    {
        pedge p_e = p_get->edges;
        while (p_e != NULL)
        {
            pedge tmp = p_e->next;
            free(p_e);
            p_e = tmp;
        }
        p_get->edges = NULL;
    }
    int dest = -1;
    pedge *e_new = &(p_get->edges);
    int d = scanf("%d", &dest);
    while (d != 0 && d != EOF){
        pnode v_d = get_node(dest,head);
        if (v_d== NULL){
            v_d = (pnode)malloc(sizeof(node));
            if (v_d == NULL)
            {
                return;
            }
            v_d->node_num = dest;
            v_d->edges = NULL;
            v_d->next = *head;
            *head =v_d;
        }
        int weight = -1;
        scanf("%d", &weight);

        *e_new = (pedge)malloc(sizeof(edge));
        if ((*e_new) == NULL)
        {
            return;
        }
        (*e_new)->weight = weight;
        (*e_new)->endpoint = v_d;
        (*e_new)->next = NULL;
        e_new = &((*e_new)->next);
        d = scanf("%d", &dest);
    }
}

        



    

  