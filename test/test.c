#include "../exec/csv_utils.h"

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

int main() {
    test_csv_utils();
    return 0;
}