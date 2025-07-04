#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "matrix_operations.h"
#include "algo_funcs.h"


int is_empty_line(const char *line) {
    int i;
    for (i = 0; line[i] != '\0'; i++) {
        if (!isspace(line[i])) {
            return 0; 
        }
    }
    return 1; 
}


Matrix* load_matrix_from_file(const char* file_name) {
    FILE* file; Matrix* matrix; int rows; int cols; int row; int col; char* token; char line[1024];
    file = fopen(file_name, "r");
    rows = 0;
    cols = 0;
    while (fgets(line, sizeof(line), file)) {
        if (is_empty_line(line)) {
            continue;  
        }
        rows++;
        if (rows == 1) {  
            token = strtok(line, ",");
            while (token) {
                cols++;
                token = strtok(NULL, ",");
            }
        }
    }
    matrix = create_matrix(rows, cols);
    rewind(file);
    row = 0;
    while (fgets(line, sizeof(line), file)) {
        if (is_empty_line(line)) continue;  
        col = 0;
        token = strtok(line, ",");
        while (token) {
            matrix->data[row][col] = atof(token);
            col++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    fclose(file);
    return matrix;
}

int main(int argc, char* argv[]) {
    char* goal;
    char* file_name;
    Matrix* input_matrix; 
    Matrix* similarity_matrix;
    Matrix* ddg_matrix ;
    Matrix* norm_matrix;
    (void)argc;
    goal = argv[1];
    file_name = argv[2];
    input_matrix = load_matrix_from_file(file_name);
    if ((strcmp(goal, "sym") == 0)) {
        similarity_matrix = sym(input_matrix);
        print_matrix(similarity_matrix);
        free_matrix(similarity_matrix);
    } else if (strcmp(goal, "ddg") == 0) {
        ddg_matrix = full_ddg(input_matrix);
        print_matrix(ddg_matrix);
        free_matrix(ddg_matrix);
    } else{
        norm_matrix = full_norm(input_matrix);
        print_matrix(norm_matrix);
        free_matrix(norm_matrix);
    }

    free_matrix(input_matrix);
    return 0;
}

