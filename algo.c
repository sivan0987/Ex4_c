#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MIN(a,b) (((a)<(b))?(a):(b))

int long_a;
pnode mygraph;
int weight;

dijkstra_P dijkstra_construction(pnode one, int makor)
{
    dijkstra_P head = NULL;
    dijkstra_P *p_ind = &head;
    while (one != NULL)
    {
        (*p_ind) = (dijkstra_P)malloc(sizeof(dijkstra_P));
        if ((*p_ind) == NULL)
        {
            printf("error");
            exit(0);
        }
        (*p_ind)->node = one;
        if (one->node_num == makor)
        {
            (*p_ind)->weight = 0;
        }
        else
        {
            (*p_ind)->weight = INT_MAX;
        }
        (*p_ind)->infor = 0;
        (*p_ind)->next = NULL;
        p_ind = &((*p_ind)->next);
        one = one->next;
    }
    return head;
}

void dijkstra_remove(dijkstra_P dijkstra)
{
    while (dijkstra != NULL)
    {
        dijkstra_P rem = dijkstra;
        dijkstra = dijkstra->next;
        free(rem);
    }
}

dijkstra_P dijkstraP(dijkstra_P head, int recognize)
{
    while (head != NULL)
    {
        if (head->node->node_num == recognize)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

dijkstra_P Small_node(dijkstra_P head)
{
    dijkstra_P vertex = NULL;
    while (head != NULL)
    {
        if (!head->infor && head->weight < INT_MAX && (vertex == NULL || vertex->weight < head->weight))
        {
            vertex = head;
        }
        head = head->next;
    }
    if (vertex != NULL)
    {
       vertex->infor = 1;
    }
    return vertex;
}
// shortsPath - function
int shortsPath_cmd(pnode head, int star, int end)
{
   dijkstra_P pdijk_1 = dijkstra_construction(head, star);
    dijkstra_P x = Small_node(pdijk_1);
    while (x != NULL)
    {
        pedge i_edge = x->node->edges;
        while (i_edge != NULL)
        {
           dijkstra_P node_1 = dijkstraP(pdijk_1, i_edge->endpoint->node_num);
            int newDist = x->weight + i_edge->weight;
            if (node_1->weight > newDist)
            {
               node_1->weight = newDist;
            }
            i_edge = i_edge->next;
        }
        x = Small_node(pdijk_1);
    }
    int len = dijkstraP(pdijk_1,end)->weight;
    if (len == INT_MAX){
        len = -1;}
    dijkstra_remove(pdijk_1);
    return len;
}


void cpy_deep(int *f, int *t, int len_of_array)
{
    for (int i = 0; i < len_of_array; ++i)
    {
        t[i] = f[i];
    }
}
void swap(int *array, int x, int y)
{
    int helper =array[x];
    array[x] = array[y];
   array[y] = helper;
}

void calculation_p(int *array, int len_of_array)
{
    int w_2 = 0;
    for (int i = 0; i < len_of_array - 1; ++i)
    {
        int len = shortsPath_cmd(mygraph,array[i], array[i + 1]);
        if (len == -1)
        {
            w_2 = INT_MAX;
            return;
        }
       w_2 += len;
    }
    if (w_2 < weight)
    {
        weight = w_2;
    }
}

void permotion(int s, int *arr, int len_of_array)
{
    if (s == len_of_array - 1)
    {
        calculation_p(arr, len_of_array);
        return;
    }
    for (int i = s; i < len_of_array; ++i)
    {
        int *temp_arr = (int *)(calloc(len_of_array, sizeof(int)));
        cpy_deep(arr, temp_arr, len_of_array);
        swap(temp_arr, s, i);
        permotion(s + 1, temp_arr,len_of_array);
        free(temp_arr);
    }
}

void TSP_cmd(pnode head)
{
    long_a = -1;
	weight = INT_MAX;
    mygraph = head;
    scanf("%d", &long_a);
    int *myarr= (int *)(calloc(long_a, sizeof(int)));
    for (int i = 0; i < long_a; i++)
    {
        scanf("%d", &myarr[i]);
    }
    int *arrCopy = (int *)(calloc(long_a, sizeof(int)));
    cpy_deep(myarr, arrCopy, long_a);
    permotion(0, arrCopy, long_a);
    free(myarr);
    free(arrCopy);
    if (weight == INT_MAX)
    {
        weight = -1;
    }
    printf("TSP shortest path: %d \n", weight);
}


