#include "../exec/csv_utils.h"
#include "../math/tensors.h"
void test_csv_utils() {
    csv_dataset dataset;
    load_csv(&dataset, "data.csv");
    printf("Rows: %d, Columns: %d\n", get_row_count(&dataset), get_col_count(&dataset));
    display_csv(&dataset, 5);
    void *val = get_value(&dataset, 2, 1);
    column *col_ptr = &dataset.columns[1]; // Column 1 is "name"

    if (col_ptr->type == TYPE_INT) {
        printf("Value at (2,1): %d\n", *(int *)val);    
    } else if (col_ptr->type == TYPE_DOUBLE) {
        printf("Value at (2,1): %lf\n", *(double *)val);
    } else if (col_ptr->type == TYPE_STRING) {
        printf("Value at (2,1): %s\n", (char *)val);
    } else {
        printf("Unknown type at (2,1)\n");
}

}

void test_tensor() {
    int *dim1 = malloc(1 * sizeof(int)); // 1D Tensor
    dim1[0] = 3;
    struct tensor *t1 = tensor_init(1, dim1);
    struct tensor *t2 = tensor_init(1, dim1);
    
    // Assign values
    t1->data[0] = 1.0;
    t1->data[1] = 2.0;
    t1->data[2] = 3.0;
    
    t2->data[0] = 4.0;
    t2->data[1] = 5.0;
    t2->data[2] = 6.0;
    
    printf("Tensor 1:");
    tensor_print(t1);
    printf("\nTensor 2:");
    tensor_print(t2);
    
    // Test element-wise multiplication
    struct tensor *t_mult = tensor_elementwise_mult(t1, t2);
    if (t_mult) {
        printf("\nElement-wise Multiplication:");
        tensor_print(t_mult);
    }
    
    // Test dot product
    double dot = tensor_dot_product(t1, t2);
    printf("\nDot Product: %f\n", dot);
    
    // Test flattening
    double flat[3];
    tensor_flatten(t1, flat);
    printf("\nFlattened Tensor 1: ");
    for (int i = 0; i < 3; i++) {
        printf("%f ", flat[i]);
    }
    printf("\n");
    
    // Free allocated memory
    free(t1->data);
    free(t1);
    free(t2->data);
    free(t2);
    if (t_mult) {
        free(t_mult->data);
        free(t_mult);
    }
}


int main() {
    //test_csv_utils();
    test_tensor();
    return 0;
}