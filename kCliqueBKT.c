#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int find_edge(int a, int b, int M, int **edges)
{
    for (int i = 0; i < M; i++)
        if ((edges[i][0] == a && edges[i][1] == b) || (edges[i][0] == b && edges[i][1] == a))
            return 1;

    return 0;
}

int check_if_clique(int K, int subset_of_K[], int M, int **edges)
{
    int nr = 0;
    for (int i = 0; i < K - 1; i++)
    {
        for (int j = i + 1; j < K; j++)
        {
            if (find_edge(subset_of_K[i], subset_of_K[j], M, edges) != 1)
                return 0;
        }
    }
    return 1;
}

void exit_Subset()
{
    printf("True\n");
    exit(0);
}

void Subset(int N, int K, int current_index, int subset_of_K[], int i, int M, int **edges, int *solution)
{

    if (current_index == K)
    {
        *solution = check_if_clique(K, subset_of_K, M, edges);
    
        if (*solution)
            exit_Subset();  //exit backtracking

        return; 
    }

    if (i > N)
        return;

    subset_of_K[current_index] = i;
    Subset(N, K, current_index + 1, subset_of_K, i + 1, M, edges, solution);
    Subset(N, K, current_index, subset_of_K, i + 1, M, edges, solution);
}


int read_input(char *path)
{

    FILE *file;
    char *line = NULL;
    int len = 0;
    int K, N, M, a, b;

    file = fopen(path, "rw+");

    fscanf(file, "%d", &K); // clique size
    fscanf(file, "%d", &N); // number of nodes in graph
    fscanf(file, "%d", &M); // number of edges in graph

    int read_steps = M;

    /*allocate the edges matrix*/
    int **edges = malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++)
    {
        edges[i] = calloc(2, sizeof(int));
    }

    int current_row = 0;
    while (read_steps)
    {
        fscanf(file, "%d", &edges[current_row][0]); // clique size
        fscanf(file, "%d", &edges[current_row][1]);
        current_row++;
        read_steps--;
    }

    int *subset_of_K = malloc(K * sizeof(int)); // declared here; stores the solution
    int solution = 0;
    Subset(N, K, 0, subset_of_K, 1, M, edges, &solution);

    printf("False\n");
}

int main(int argvc, char *argv[])
{
    read_input(argv[1]);
    return 0;
}