#include "../constants.h"

typedef enum { TYPE_INT, TYPE_DOUBLE, TYPE_STRING, TYPE_UNKNOWN } data_type;

typedef struct {
    char name[MAX_STRING_LEN];
    data_type type;
    void *data;  // Pointer to store int[], double[], or char*[]
} column;

typedef struct {
    column columns[MAX_COLS];
    int row_count;
    int col_count;
} csv_dataset;

data_type detect_type(const char *value) {
    int has_dot = 0, is_number = 1;
    for (int i = 0; value[i] != '\0'; i++) {
        if (value[i] == '.') {
            if (has_dot) return TYPE_STRING;
            has_dot = 1;
        } else if (!isdigit(value[i])) {
            is_number = 0;
            break;
        }
    }
    if (is_number) return TYPE_INT;
    if (has_dot) return TYPE_DOUBLE;
    return TYPE_STRING;
}

void load_csv(csv_dataset *dataset, const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", file_path);
        return;
    }
    dataset->row_count = 0;
    dataset->col_count = 0;
    char line[MAX_STRING_LEN * MAX_COLS];
    
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",\n");
        while (token && dataset->col_count < MAX_COLS) {
            strcpy(dataset->columns[dataset->col_count].name, token);
            dataset->columns[dataset->col_count].type = TYPE_UNKNOWN;
            dataset->columns[dataset->col_count].data = NULL;
            dataset->col_count++;
            token = strtok(NULL, ",\n");
        }
    }
    while (fgets(line, sizeof(line), file) && dataset->row_count < MAX_ROWS) {
        char *token = strtok(line, ",\n");
        int col = 0;
        
        while (token && col < dataset->col_count) {
            data_type detected_type = detect_type(token);
            column *col_ptr = &dataset->columns[col];
            if (col_ptr->type == TYPE_UNKNOWN) {
                col_ptr->type = detected_type;
                switch (col_ptr->type) {
                    case TYPE_INT:
                        col_ptr->data = malloc(MAX_ROWS * sizeof(int));
                        break;
                    case TYPE_DOUBLE:
                        col_ptr->data = malloc(MAX_ROWS * sizeof(double));
                        break;
                    case TYPE_STRING:
                        col_ptr->data = malloc(MAX_ROWS * sizeof(char *));
                        for (int i = 0; i < MAX_ROWS; i++)
                            ((char **)col_ptr->data)[i] = malloc(MAX_STRING_LEN * sizeof(char));
                        break;
                    default: break;
                }
            } else if (col_ptr->type != detected_type) {
                printf("Error: Column '%s' contains mixed data types.\n", col_ptr->name);
                fclose(file);
                exit(1);
            }
            switch (col_ptr->type) {
                case TYPE_INT:
                    ((int *)col_ptr->data)[dataset->row_count] = atoi(token);
                    break;
                case TYPE_DOUBLE:
                    ((double *)col_ptr->data)[dataset->row_count] = atof(token);
                    break;
                case TYPE_STRING:
                    strcpy(((char **)col_ptr->data)[dataset->row_count], token);
                    break;
                default: break;
            }
            col++;
            token = strtok(NULL, ",\n");
        }
        dataset->row_count++;
    }
    fclose(file);
}

void display_csv(csv_dataset *dataset, int num_rows) {
    if (num_rows > dataset->row_count) num_rows = dataset->row_count;
    for (int j = 0; j < dataset->col_count; j++) {
        printf("%s\t", dataset->columns[j].name);
    }
    printf("\n");
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < dataset->col_count; j++) {
            column *col_ptr = &dataset->columns[j];
            switch (col_ptr->type) {
                case TYPE_INT:
                    printf("%d\t", ((int *)col_ptr->data)[i]);
                    break;
                case TYPE_DOUBLE:
                    printf("%lf\t", ((double *)col_ptr->data)[i]);
                    break;
                case TYPE_STRING:
                    printf("%s\t", ((char **)col_ptr->data)[i]);
                    break;
                default:
                    printf("?\t");
                    break;
            }
        }
        printf("\n");
    }
}

int get_row_count(csv_dataset *dataset) { return dataset->row_count; }
int get_col_count(csv_dataset *dataset) { return dataset->col_count; }

void *get_value(csv_dataset *dataset, int row, int col) {
    if (row >= dataset->row_count || col >= dataset->col_count) return NULL;
    column *col_ptr = &dataset->columns[col];
    switch (col_ptr->type) {
        case TYPE_INT:
            return &((int *)col_ptr->data)[row];
        case TYPE_DOUBLE:
            return &((double *)col_ptr->data)[row];
        case TYPE_STRING:
            return ((char **)col_ptr->data)[row];
        default:
            return NULL;
    }
}

void free_csv(csv_dataset *dataset) {
    for (int j = 0; j < dataset->col_count; j++) {
        column *col_ptr = &dataset->columns[j];
        if (col_ptr->data) {
            if (col_ptr->type == TYPE_STRING) {
                for (int i = 0; i < dataset->row_count; i++)
                    free(((char **)col_ptr->data)[i]);
            }
            free(col_ptr->data);
        }
    }
}


