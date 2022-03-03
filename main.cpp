/*
 * main.cpp
 *
 *  Created on: Jun 10, 2021
 *      Author: d-w-h
 */

#include <stdio.h>

typedef struct memo_table {
    bool is_set;
    long long int num_paths;
} m_table;

m_table ** create_table(int n, int m) {

    m_table ** table = new m_table * [n + 1];

    for(int i = 0; i < n + 1; ++i)
        table[i] = new m_table[m + 1];

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            table[i][j].is_set = false;
            table[i][j].num_paths = 0;
        }
    }

    return table;
}

void delete_table(m_table ** table, int n) {

    for(int i = 0; i < n + 1; ++i)
        delete [] table[i];

    delete [] table;

}

long long int num_paths_grid(int n, int m, m_table ** table) {
    long long int num_paths = 0;
    long long int num_paths1 = 0;
    long long int num_paths2 = 0;

    if(n == 0 || m == 0)
        return 0;

    if((n == 1) || (m == 1))
        return 1;

    if(table[n][m].is_set)
        return table[n][m].num_paths;

    if(n >= 0 && m >= 0) {
        num_paths1 = num_paths_grid(n - 1, m, table);
        num_paths2 = num_paths_grid(n, m - 1, table);
    }

    num_paths = num_paths1 + num_paths2;
    table[n][m].is_set = true;
    table[n][m].num_paths = num_paths;

    return num_paths;
}

int main(int argc, char * argv[]) {

    int n = 18;
    int m = 18;

    //Allocate memory for memo table
    m_table ** table = create_table(n, m);

    //Compute number of paths
    long long int num_paths = num_paths_grid(n, m, table);

    //Free allocated data
    delete_table(table, n);

    //Print data
    printf("number of paths: %I64d\n", num_paths);

    return 0;
}
