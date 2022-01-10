#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <limits.h>
#include "graph.h"
#include <ctype.h>


int main()
{
    pnode help = NULL;
    pnode *head = &help;
    char c ;
    while (scanf("%c", &c) != EOF)
    {
        if (c == 'A')
        {
            build_graph_cmd(head);
        }
        if (c == 'B')
        {
            insert_node_cmd(head);
        }
        if (c == 'D')
        {
            delete_node_cmd(head);
        }
        if (c == 'S')
        {
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int dis = shortsPath_cmd(*head, src, dest);
            printf("Dijsktra shortest path: %d \n", dis);
        }
        if (c == 'T') 
        {
            TSP_cmd(*head);
        }
    }
    deleteGraph_cmd(head);
    return 0;
}