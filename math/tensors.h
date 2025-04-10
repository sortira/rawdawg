#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define the tensor structure
struct tensor {
    int ndim;       // Number of dimensions
    int *dim;       // Array storing dimension sizes
    double *data;   // Array storing tensor elements
};

// Utility function prototypes
char* util_return_formatted_string(char *inner_str, int n);
int array_printf_dbl(const char *fmt, const double *data);
int get_product(int *a, int size);

// Tensor function prototypes
struct tensor* tensor_init(int ndim, int *dim);
void tensor_print(struct tensor *p);
void tensor_flatten(struct tensor *p, double *out);
struct tensor* tensor_elementwise_mult(struct tensor *a, struct tensor *b);
double tensor_dot_product(struct tensor *a, struct tensor *b);

int get_flat_index(int ndim, int *dim, ...) {
    va_list args;
    va_start(args, dim);

    int flat_index = 0;
    int stride = 1;

    for (int d = ndim - 1; d >= 0; d--) {
        int index = va_arg(args, int);
        flat_index += index * stride;
        stride *= dim[d];
    }

    va_end(args);
    return flat_index;
}

// Function to calculate product of array elements
int get_product(int *a, int size) {
    int product = 1;
    for (int i = 0; i < size; i++) {
        product *= *(a + i);
    }
    return product;
}

// Initialize a tensor with given dimensions
struct tensor* tensor_init(int ndim, int *dim) {
    struct tensor *ret = malloc(sizeof(struct tensor));
    ret->ndim = ndim;
    ret->dim = dim;
    
    int total_elements = get_product(dim, ndim);
    ret->data = calloc(total_elements, sizeof(double));
    return ret;
}

// Print tensor contents
void tensor_print(struct tensor *p) {
    int n = get_product(p->dim, p->ndim) * 3;
    
    int nm = *(p->dim + p->ndim - 1);
    char *inner_str = malloc(3 * nm + 3);
    
    inner_str[0] = '[';
    int pos = 1;
    
    for (int i = 0; i < nm; i++) {
        pos += sprintf(inner_str + pos, "%f,", p->data[i]);
    }
    inner_str[pos - 1] = ']'; // Replace last comma with closing bracket
    inner_str[pos] = '\0';

    int i = 0;
    char *buf;
    while (i <= p->ndim - 2) {
        buf = util_return_formatted_string(inner_str, *(p->dim + p->ndim - 2 - i));
        free(inner_str);
        inner_str = buf;
        i++;
    }

    printf("%s\n", buf);  // Ensure output is printed
    free(buf);
}

// Utility function to format tensor output
char* util_return_formatted_string(char *inner_str, int n) {
    char *s = malloc(strlen(inner_str) * n + n + 2);
    s[0] = '[';
    s[1] = '\0';
    
    for (int i = 0; i < n * 2; i++) {
        if (i % 2 == 0) {
            strcat(s, inner_str);
        } else {
            strcat(s, ",");
        }
    }
    
    s[strlen(inner_str) * n + n] = ']';
    s[strlen(inner_str) * n + n + 1] = '\0';
    return s;
}

// Flatten a tensor into a 1D array
void tensor_flatten(struct tensor *p, double *out) {
    int total_elements = get_product(p->dim, p->ndim);
    memcpy(out, p->data, total_elements * sizeof(double));
}

// Perform element-wise multiplication of two tensors
struct tensor* tensor_elementwise_mult(struct tensor *a, struct tensor *b) {
    if (a->ndim != b->ndim || memcmp(a->dim, b->dim, a->ndim * sizeof(int)) != 0) {
        printf("Error: Tensor dimensions must match for element-wise multiplication.\n");
        return NULL;
    }
    
    struct tensor *result = tensor_init(a->ndim, a->dim);
    int total_elements = get_product(a->dim, a->ndim);
    
    for (int i = 0; i < total_elements; i++) {
        result->data[i] = a->data[i] * b->data[i];
    }
    return result;
}

// Compute the dot product of two tensors (only valid for 1D tensors)
double tensor_dot_product(struct tensor *a, struct tensor *b) {
    if (a->ndim != 1 || b->ndim != 1 || a->dim[0] != b->dim[0]) {
        printf("Error: Dot product is only valid for 1D tensors of the same length.\n");
        return 0.0;
    }
    
    double dot_product = 0.0;
    for (int i = 0; i < a->dim[0]; i++) {
        dot_product += a->data[i] * b->data[i];
    }
    return dot_product;
}

// Function to print an array of doubles
int array_printf_dbl(const char *fmt, const double *data) {
    int n = 0;
    const char *p = fmt;
    const double *x = data;
    
    while (*p) {
        if (*p == '%') {
            p++;
            if (*p != 'f') return -1; // Error handling
            n += printf("%f", *x++);
        } else {
            putchar(*p);
            n++;
        }
        p++;
    }
    return n;
}
