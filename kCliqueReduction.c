#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int **non_edges_F(int N, int M, int **edges, int *all_edges_nr)
{
    for (int i = 1; i < N; i++)
    {
        *all_edges_nr += i;
    }

    int **all_edges = malloc((*all_edges_nr + 1) * sizeof(int *));

    for (int i = 0; i < *all_edges_nr; i++){
        all_edges[i] = calloc(2, sizeof(int));
    }

    int row = 0;

    for (int i = 1; i < N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            all_edges[row][0] = i;
            all_edges[row][1] = j;
            row++;
        }
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < *all_edges_nr; j++)
            if ((all_edges[j][0] == edges[i][0] && all_edges[j][1] == edges[i][1]) ||
                (all_edges[j][0] == edges[i][1] && all_edges[j][1] == edges[i][0]))
            {
                all_edges[j][0] = 0;
                all_edges[j][1] = 0;
                break;
            }
    }
    return all_edges;
}

void update_nr_of_positions(int nr, int *nr_of_positions, int *check)
{
    if (nr == *check)
    {
        *nr_of_positions = *nr_of_positions + 1;
        *check = *check * 10;
    }
}

void update_nr_of_positions2(int nr, int *nr_of_positions)
{
    int n = 0;
    while (nr != 0){
        nr /= 10;
        n++;
    }
    *nr_of_positions = n;
}

void reset_vars(int *nr_of_positions, int *check)
{
    *nr_of_positions = 1;
    *check = 10;
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
    for (int i = 0; i < M; i++){
        edges[i] = calloc(2, sizeof(int));
    }


    int current_row = 0;
    while (read_steps){
        fscanf(file, "%d", &edges[current_row][0]); // clique size
        fscanf(file, "%d", &edges[current_row][1]);
        current_row++;
        read_steps--;
    }

    char ch[100];

    char *C = malloc(90000000 * sizeof(char));
   
    int nr_of_positions_i, nr_of_positions_j, nr_of_positions_u, nr_of_positions_v;
    int check_i, check_j, check_u, check_v;

    int strlen_C = 0;

    char *point_last_poz = C;

    reset_vars(&nr_of_positions_i, &check_i);
    reset_vars(&nr_of_positions_u, &check_u);


    /*COMPLEXITATE: O(n^2)+ 2*O(lg n + 1) = O(n^2)*/
    /*I for: K "variaza" in functie de n-> k={n/2, n/3, etc};
     Worst case: O(n)*/
    for (int i = 1; i <= K; i++)      
    {
        update_nr_of_positions(i, &nr_of_positions_i, &check_i);
        strcpy(point_last_poz++, "(");
        strlen_C++;

        for (int u = 1; u <= N; u++)       /*II for: Worst case: O(n)*/
        {
            update_nr_of_positions(u, &nr_of_positions_u, &check_u);

            strcpy(point_last_poz++, "x");
            strlen_C++;

            sprintf(ch, "%d", i);           // O(lg n + 1); pt input=100 -> face 3 pasi
            strcpy(point_last_poz, ch);     // xi
            point_last_poz += nr_of_positions_i;
            strlen_C += nr_of_positions_i;

            sprintf(ch, "%d", u);           // O(lg n + 1); pt input=100 -> face 3 pasi
            strcpy(point_last_poz, ch);     // xiu
            point_last_poz += nr_of_positions_u;
            strlen_C += nr_of_positions_u;

            if (u != N)
            {
                strcpy(point_last_poz++, "V");
                strlen_C++;
            }
        }
        
        reset_vars(&nr_of_positions_u, &check_u);
        strcpy(point_last_poz, ")^");
        strlen_C += 2;
        point_last_poz += 2;
    }




    reset_vars(&nr_of_positions_i, &check_i); 
    reset_vars(&nr_of_positions_j, &check_j);
    reset_vars(&nr_of_positions_v, &check_v);



    /*COMPLEXITATE: O(n^3)+ 4*O(lg n + 1) = O(n^3)*/
    /*I for: K "variaza" in functie de n-> k={n/2, n/3, etc};
     Worst case: O(n)*/ 

    for (int i = 1; i < K; i++)               //K "variaza" in functie de n-> k={n/2, n/3, etc}; Worst case: O(n)
    {
        update_nr_of_positions(i, &nr_of_positions_i, &check_i);

        for (int j = i + 1; j <= K; j++)      //K "variaza" in functie de n-> k={n/2, n/3, etc}; Worst case: O(n)
        {
            update_nr_of_positions(j, &nr_of_positions_j, &check_j);

            for (int v = 1; v <= N; v++)      //O(n)
            {
                update_nr_of_positions(v, &nr_of_positions_v, &check_v);

                strcpy(point_last_poz, "(~x");
                point_last_poz += 3;
                strlen_C += 3;

                sprintf(ch, "%d", i);            // O(lg n + 1);
                strcpy(point_last_poz, ch);      //(~xi
                point_last_poz += nr_of_positions_i;
                strlen_C += nr_of_positions_i;

                sprintf(ch, "%d", v);            // O(lg n + 1);
                strcpy(point_last_poz, ch);      //(~xiv
                point_last_poz += nr_of_positions_v;
                strlen_C += nr_of_positions_v;

                strcpy(point_last_poz, "V~x");
                point_last_poz = point_last_poz + 3;
                strlen_C += 3;

                sprintf(ch, "%d", j);            // O(lg n + 1);
                strcpy(point_last_poz, ch);      //(~xivV~xj
                point_last_poz += nr_of_positions_j;
                strlen_C += nr_of_positions_j;

                sprintf(ch, "%d", v);            // O(lg n + 1);
                strcpy(point_last_poz, ch);      //(~xivV~xjv
                point_last_poz += nr_of_positions_v;
                strlen_C += nr_of_positions_v;

                strcpy(point_last_poz, ")^");    //(~xivV~xiv)
                point_last_poz += 2;
                strlen_C += 2;
            }

            reset_vars(&nr_of_positions_v, &check_v);
        }
        reset_vars(&nr_of_positions_j, &check_j);
    }

  

    int all_edges_nr = 0;
    int **non_edges = non_edges_F(N, M, edges, &all_edges_nr);

    int nr_of_positions_i_e1, nr_of_positions_i_e2;
    int check_non_edge1, check_non_edge2;

    reset_vars(&nr_of_positions_i_e1, &check_non_edge1);
    reset_vars(&nr_of_positions_i_e2, &check_non_edge2);
    reset_vars(&nr_of_positions_i, &check_i);
    reset_vars(&nr_of_positions_j, &check_j);


    /*COMPLEXITATE: O(n^3)+ 4*O(lg n + 1) = O(n^3)*/
    /*I for: O(n^2)*/ 
    for (int l = 0; l < all_edges_nr; l++)    //all_edges_nr= n(n-1)/2 
    {
        update_nr_of_positions2(non_edges[l][0], &nr_of_positions_i_e1);
        update_nr_of_positions2(non_edges[l][1], &nr_of_positions_i_e2);

        if (non_edges[l][0] == 0 && non_edges[l][1] == 0)
            continue;

        else
        {
            for (int i = 1; i <= K; i++)                 //K "variaza" in functie de n-> k={n/2, n/3, etc}; Worst case: O(n)
            {
                update_nr_of_positions(i, &nr_of_positions_i, &check_i);

                for (int j = 1; j <= K; j++)            //K "variaza" in functie de n-> k={n/2, n/3, etc}; Worst case: O(n)
                {
                    update_nr_of_positions(j, &nr_of_positions_j, &check_j);

                    strcpy(point_last_poz, "(~x"); //(~x
                    point_last_poz += 3;
                    strlen_C += 3;

                    sprintf(ch, "%d", i);                // O(lg n + 1);
                    strcpy(point_last_poz, ch); //(~xi
                    point_last_poz += nr_of_positions_i;
                    strlen_C += nr_of_positions_i;

                    sprintf(ch, "%d", non_edges[l][0]);   // O(lg n + 1);
                    strcpy(point_last_poz, ch); //(~xiu
                    point_last_poz += nr_of_positions_i_e1;
                    strlen_C += nr_of_positions_i_e1;

                    strcpy(point_last_poz, "V~x");// (~xiuV~x
                    point_last_poz += 3;
                    strlen_C += 3;

                    sprintf(ch, "%d", j);                // O(lg n + 1);
                    strcpy(point_last_poz, ch); // (~xiuV~xj
                    point_last_poz += nr_of_positions_j;
                    strlen_C += nr_of_positions_j;

                    sprintf(ch, "%d", non_edges[l][1]);  // O(lg n + 1);
                    strcpy(point_last_poz, ch); // (~xiuV~xjv
                    point_last_poz += nr_of_positions_i_e2;
                    strlen_C += nr_of_positions_i_e2;

                    strcpy(point_last_poz, ")^");
                    point_last_poz += 2;
                    strlen_C += 2;
                }

                reset_vars(&nr_of_positions_j, &check_j);
            }

            reset_vars(&nr_of_positions_i, &check_i);
        }
    }

    C[strlen_C - 1] = '\0';
    printf("%s", C);
    
}

int main(int argvc, char *argv[])
{
    read_input(argv[1]);
    return 0;
}