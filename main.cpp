/*
 * main.cpp
 *
 *  Created on: Jun 10, 2021
 *      Author: d-w-h
 */

#include <stdio.h>

typedef struct table_elements {
    bool is_set;
    long long int num_paths;
} t_elem;

t_elem ** create_table(int n, int m) {

    t_elem ** f_table = new t_elem * [n + 1];

    for(int i = 0; i < n + 1; ++i)
        f_table[i] = new t_elem[m + 1];

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            f_table[i][j].is_set = false;
            f_table[i][j].num_paths = 0;
        }
    }

    return f_table;
}

void delete_table(t_elem ** table, int n) {

    for(int i = 0; i < n + 1; ++i)
        delete [] table[i];

    delete [] table;

}

long long int num_paths_grid(int n, int m, t_elem** table) {
    long long int num_paths = 0;
    long long int num_paths1 = 0;
    long long int num_paths2 = 0;

    if(n == 0 || m == 0)
        return 0;

    if((n == 1) || (m == 1))
        return 1;

    if(table[n][m].is_set)
        return table[n][m].num_paths;

    num_paths1 = num_paths_grid(n-1, m, table);
    num_paths2 = num_paths_grid(n, m-1, table);

    num_paths = num_paths1 + num_paths2;
    table[n][m].is_set = true;
    table[n][m].num_paths = num_paths;

    return num_paths;
}

int main(int argc, char* argv[]) {

    int n = 18;
    int m = 18;

    //Allocate memory for memo table
    t_elem ** m_table = create_table(n, m);

    //Compute number of paths
    long long int num_paths = num_paths_grid(n, m, m_table);

    //Free allocated data
    delete_table(m_table, n);

    //Print data
    printf("num_paths_grid: %I64d\n", num_paths);

    return 0;
}
