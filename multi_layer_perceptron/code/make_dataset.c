#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_LINE 256
#define DATA_LINE 5


int main(int argc, char **argv) {
    int i, j, k, m, n, K;
    int N_train = 10000, N_validation = 100, N_test = 100;
    int *n_sample = NULL;
    int ***line = NULL;
    int pixel_line, LSB;
    float pixel;
    
    FILE *fp = NULL;
    
    if(argc < 3) {
        printf("Specify the data path!\n");
        return -1;
    }
    
    char *dataset_path = argv[1];
    char *data_path = argv[2];
    char file_path[MAX_LINE];
    
    initialize_seed();
    
    sprintf(file_path, "%s/sample.txt", dataset_path);
    
    if((fp = fopen(file_path, "r")) == NULL) {
        exit(-1);
    }
    
    fscanf(fp, "%d", &K);
    
    printf("K: %d\n", K);
    
    if((n_sample = (int *)malloc((K + 1) * sizeof(int))) == NULL) {
        exit(-1);
    }
    
    for(k = 1; k <= K; k++) {
        fscanf(fp, "%d", &n_sample[k]);
        printf("class %d: %d\n", k, n_sample[k]);
    }

    fclose(fp);
    
    if((line = (int ***)malloc((K + 1) * sizeof(int **))) == NULL) {
        exit(-1);
    }
    
    line[0] = NULL;
    
    for(k = 1; k <= K; k++) {
        if((line[k] = (int **)malloc((n_sample[k] + 1) * sizeof(int *))) == NULL) {
            exit(-1);
        }
        
        for(i = 1; i <= n_sample[k]; i++) {
            sprintf(file_path, "%s/sample_%d/%d-%d.txt", dataset_path, k, k, i);
            
            if((fp = fopen(file_path, "r")) == NULL) {
                exit(-1);
            }
            
            if((line[k][i] = (int *)malloc(DATA_LINE * sizeof(int))) == NULL) {
                exit(-1);
            }
            
            for(j = 0; j < DATA_LINE; j++) {
                fscanf(fp, "%d", &line[k][i][j]);
            }
            fclose(fp);
        }
    }
    
    // Write "train_data.txt"
    sprintf(file_path, "%s/train_data.txt", data_path);
    
    if((fp = fopen(file_path, "w")) == NULL) {
        exit(-1);
    }
    
    fprintf(fp, "%d\n", N_train);
    
    for(n = 0; n < N_train; n++) {
        k = rand() % K + 1;
        i = rand() % n_sample[k] + 1;
        
        fprintf(fp, "%d\n", k);
        
        for(j = 0; j < DATA_LINE; j++) {
            pixel_line = line[k][i][j];
            for(m = 0; m < DATA_LINE; m++) {
                LSB = pixel_line % 10;
                if(LSB) {
                    pixel = rand_normal(0.8f, 0.1f);
                    if(pixel > 1.0f) {
                        pixel = 0.0f;
                    }
                    fprintf(fp, "%f\n", pixel);
                } else {
                    fprintf(fp, "0.0\n");
                }
                pixel_line /= 10;
            }
        }
    }
    
    fclose(fp);
    
    // Write "validation_data.txt"
    sprintf(file_path, "%s/validation_data.txt", data_path);
    
    if((fp = fopen(file_path, "w")) == NULL) {
        exit(-1);
    }
    
    fprintf(fp, "%d\n", N_validation);
    
    for(n = 0; n < N_validation; n++) {
        k = rand() % K + 1;
        i = rand() % n_sample[k] + 1;
        
        fprintf(fp, "%d\n", k);
        
        for(j = 0; j < DATA_LINE; j++) {
            pixel_line = line[k][i][j];
            for(m = 0; m < DATA_LINE; m++) {
                LSB = pixel_line % 10;
                if(LSB) {
                    pixel = rand_normal(0.8f, 0.1f);
                    if(pixel > 1.0f) {
                        pixel = 0.0f;
                    }
                    fprintf(fp, "%f\n", pixel);
                } else {
                    fprintf(fp, "0.0\n");
                }
                pixel_line /= 10;
            }
        }
    }
    
    fclose(fp);
    
    // Write "test_data.txt"
    sprintf(file_path, "%s/test_data.txt", data_path);
    
    if((fp = fopen(file_path, "w")) == NULL) {
        exit(-1);
    }
    
    fprintf(fp, "%d\n", N_test);
    
    for(n = 0; n < N_test; n++) {
        k = rand() % K + 1;
        i = rand() % n_sample[k] + 1;
        
        fprintf(fp, "%d\n", k);
        
        for(j = 0; j < DATA_LINE; j++) {
            pixel_line = line[k][i][j];
            for(m = 0; m < DATA_LINE; m++) {
                LSB = pixel_line % 10;
                if(LSB) {
                    pixel = rand_normal(0.8f, 0.1f);
                    if(pixel > 1.0f) {
                        pixel = 0.0f;
                    }
                    fprintf(fp, "%f\n", pixel);
                } else {
                    fprintf(fp, "0.0\n");
                }
                pixel_line /= 10;
            }
        }
    }
    
    fclose(fp);
    
    return 0;
}
