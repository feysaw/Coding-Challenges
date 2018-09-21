#include <stdio.h>
#include <string.h>

int hankelize(double **in_arr, int rows, int cols, double **out_arr) {
    if (!rows || !cols || !in_arr || !out_arr) {
        return 0;
    }
    
    int idx = (rows + cols) - 1;
    double vals[idx];
    int count[idx];
    memset(vals, 0, sizeof(vals));
    memset(count, 0, sizeof(count));
    
    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            vals[ii + i] += in_arr[i][ii];
            count[ii + i]++;
        }
    }
    
    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            out_arr[i][ii] = vals[ii + i] / count[ii + i];
        }
    }
    
    return 1;
}

int main()
{
    double A[3][6] = {
        {2, 5, -1, 9, -3, 6},
        {7, 4, 2, 4, 2, 10},
        {3, -2, -10, 1, 4, 2}
    };
    double *input_arr[3] = {
        A[0],
        A[1],
        A[2]
    };
    int M = 3;
    int N = 6;
    double temp[3][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    double *hankelized[3] = {
        temp[0],
        temp[1],
        temp[2]
    };
    int ret = hankelize(input_arr, 3, 6, hankelized);
    
    if (!ret) {
        printf("Could not Hankelize input array. Check parameters.\n");
    } else {
        printf("Hankelized output:\n\n[");
        
        for (int i = 0; i < M; i++) {
            if (i > 0) {
                printf(" ");
            }
            
            for (int ii = 0; ii < N; ii++) {
                printf(" %f", hankelized[i][ii]);
            }
            
            if (i < (M - 1)) {
                printf("\n");
            }
        }
        
        printf(" ]");
    }
    
    return 0;
}