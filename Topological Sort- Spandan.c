#include <stdio.h>
#include <stdlib.h>

#define V_MAX 101 //Maximum number of vertices allowed in the graph
#define E_MAX 10000

struct Vertex
{
    int index;
    int ops;
    struct Vertex *adj;
};
struct Graph
{
    struct Vertex vertices[V_MAX];
    int V_num;
};

void BuildGraph (char* filename, struct Graph *G)
{
    FILE *ifp;

    int adj_list[V_MAX][V_MAX];
    int i, j;

    for (i=0; i<V_MAX; i++)
        for (j=0; j<V_MAX; j++)
            adj_list[i][j] = 0;

    ifp = fopen (filename, "r");
    if (ifp==NULL)
        {
           printf("No such file \"%s\" !\n", filename);
           exit(0);
        }
    else
    {
        char line [BUFSIZ];
        i=0;
        while (fgets(line, sizeof line, ifp) != NULL)
        {
            j=0;
            char *start = line;
            int field, n;

            while (sscanf (start, "%d%n", &field, &n)==1)
            {
                //printf("%d ", field);
                start +=n;
                adj_list[i][j] = field;
                j++;
            }
            i++;
        }
    }
    G->V_num = i;  // Set the number of vertices in the graph

    struct Vertex* p=NULL;
    for (i=0; i < G->V_num; i++)
    {
        p = &G->vertices[i];
        p->index = adj_list[i][0];
        p->ops = 0;
        p->adj = NULL;

        for (j=1; adj_list[i][j]!=0; j++)
        {
            p->adj = malloc(sizeof (struct Vertex));
            p = p->adj;
            p->index = adj_list[i][j];
            p->ops = 0;
            p->adj = NULL;
        }
    }
    fclose(ifp);
}

int TopologicalSort (struct Graph *G, int queue[])
{
    int indegree[V_MAX], i, front=0, rear=0;
    struct Vertex *ptr;

    for (i = 0; i<=G->V_num; i++)
    {
        indegree[i] = 0; G->vertices[i].ops++;
        //Count vertices.ops as operations for corresponding vertex
    }
    for (i = 0; i <G->V_num; i++)
    {
        ptr = &G->vertices[i]; ptr->ops++;
        //Count ptr->ops as operations for corresponding vertex
        while((ptr->adj) != NULL)
        {
            ptr = ptr->adj;
            indegree[ptr->index]++; ptr->ops++;
            //Count ptr->ops as operations for corresponding edge
        }
    }
    //Enqueue Vertices with zero indegree (front=0, rear=0)
    for (i=0; i<G->V_num; i++)
    {
        G->vertices[i].ops++;
        //Count the if condition below
        if (!indegree[i+1])
        {
            queue[rear] = i; G->vertices[i].ops++;
            //Count the enqueue operation
            rear++;
        }
    }
    //Peel the zero-indegree vertices
    while (rear > front )
    {
        ptr = &G->vertices[queue[front]];
        G->vertices[queue[front]].ops++;
        //Count the dequeue operation above
        front++;

        while( ptr->adj != NULL)
        {
            ptr = ptr->adj; ptr ->ops++;  //Count edge operation

            indegree[ptr->index]--;
            if ((indegree[ptr->index]==0))
            {
                queue[rear] = ptr->index-1; G->vertices[ptr->index-1].ops++;    //Count the if condition below as vertex operation
                rear++;
            }
        }
    }
    return (front < G->V_num); //Return iscycle flag based on whether all the nodes are removed from Q and inserted into S or not!
 }

void BuildOutput (char* infile, int iscycle, int queue[], struct Graph G)
{

    FILE *ofp;
    int i, flag=0;
/*
    char *outfile;
    if (infile=="in1.txt")
    {
        outfile="out1.txt";
        flag = 1;
    }

    else if (infile=="in2.txt")
        outfile="out2.txt";
    else if (infile=="in3.txt")
        outfile="out3.txt";
    else if (infile=="in4.txt")
        outfile="out4.txt";
    else if (infile=="in5.txt")
        outfile="out5.txt";
    else if (infile=="in6.txt")
        outfile="out6.txt";
    else if (infile=="in7.txt")
        outfile="out7.txt";
*/
    ofp = fopen (infile, "w");

    //CASE A:
    if (iscycle)
    {
        fprintf (ofp, "This graph has a cycle!");
        return;
    }

    for (i=0; i<G.V_num; i++)
    {
        if (i%10==0)
            fprintf(ofp, "\n");
        fprintf (ofp, "%d ", queue[i]+1);
    }

    //CASE B:

    struct Vertex *ptr=NULL;
    int V_op_count=0, E_op_count=0, Edge_count=0, Vertex_count=G.V_num;

    for (i=0; i<G.V_num; i++)
    {
        //if (flag==1)
            fprintf (ofp, "\nVertex %d: %d", G.vertices[i].index, G.vertices[i].ops);
    }
    for (i=0; i<G.V_num; i++)
    {
        ptr = &G.vertices[i];

        V_op_count += ptr->ops;

        while (ptr->adj != NULL)
        {
            ptr = ptr->adj;
            Edge_count++;
            E_op_count += ptr->ops;

            //if (flag==1)
                fprintf (ofp, "\nEdge (%d to %d): %d", G.vertices[i].index, ptr->index, ptr->ops);
        }
    }

    //CASE C:
    fprintf (ofp, "\nNumber of vertices in the graph: %d", Vertex_count);
    fprintf (ofp, "\nNumber of edges in the graph: %d", Edge_count);

    fprintf (ofp, "\n\nTotal number of operations charged to all verticies is: %d", V_op_count);
    fprintf (ofp, "\nTotal number of operations charged to edges is: %d", E_op_count);
    fprintf (ofp, "\nTotal number of operations is: %d", V_op_count+E_op_count);

    fclose(ofp);
}


int main(int argc, char *argv[])
{
    struct Graph G;
    int queue [V_MAX], iscycle;
    BuildGraph (argv[1],&G);
    iscycle = TopologicalSort (&G, queue);
    BuildOutput ("out.txt", iscycle, queue, G);
    return 0;
}

