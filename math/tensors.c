#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct tensor{
    int ndim;//no. of dimensions
    int *dim;//store the dimensions

    double *ten;//store all the tensors
};

char* util_returnFormattedString(char *innerStr,int n);
int arrayprintf_dbl(const char *fmt, const double *data) {
    int n = 0;
    const char *p = fmt;
    const double *x = data;
    while (*p) {
      if (*p == '%') {
        // complicate as needed ...
        p++;
        if (*p != 'f') return -1; // error
        n += printf("%f", *x++);
      } else {
        putchar(*p);
        n++;
      }
      p++;
    }
    return n;
}


int getPdt(int *a,int s){
    //a = array, s = sizeof(a)
    int pdt = 1;
    for(int i = 0;i < s;i++){
        pdt *= *(a+i);
    }
    return pdt;
}
struct tensor* tensor_init(int ndim,int *dim){
    //O(n)
    //Initialises all the elements in the tensor as 0
    struct tensor *ret = malloc(sizeof(struct tensor));
    (*ret).ndim = ndim;
    (*ret).dim = dim;

    //determine no. of elements in tensor
    int pdt = 1;
    for(int i = 0;i < ndim;i++){
        pdt *= *(dim + i);
    }
    (*ret).ten = calloc(pdt,sizeof(double));
    return ret;
}
void tensor_print(struct tensor *p){
    char* pnt;
    int t = (*p).ndim;
    printf("\nNDIM=%d\n",t);
    int n = 0;//stores no. of maximum no. of characters required for printing tensor

    //get the maximum no. of characters required for printing tensor
    while(t > -1){
        n += (t == (*p).ndim)?(getPdt((*p).dim,t) * 3):(getPdt((*p).dim,t) * 2);
        t -= 1;
    }
    pnt = malloc(n + 1);

    int nm = *((*p).dim+(*p).ndim-1);
    printf("\nNM=%d\n",nm);
    char *innerStr = malloc(3 *  nm + 3);

    *(innerStr) = '[';
    for(int i = 0;i < 3 *  nm + 3;i++){
        if(i % 3 == 0){
            *(innerStr + i + 1) = '%'; 
        }
        else if(i % 3 == 1){
            *(innerStr + i + 1) = 'f'; 
        }
        else{
            *(innerStr + i + 1) = ',';
        }
    }

    *(innerStr + 3 * nm + 1) = ']';
    *(innerStr + 3 * nm + 2) = '\0';
    printf("\nINNERSTR=%s\n",innerStr);
    //access each element and create the innerString for each
    t = (*p).ndim;
    //len = *(*p.dim + *p.ndim - 2 - i)
    int i = 0;
    char *buf;
    while(i <= (*p).ndim - 2){
        buf = util_returnFormattedString(innerStr,*((*p).dim + (*p).ndim - 2 - i));
        free(innerStr);
        innerStr = buf;
        i++;
    }

    //actually print the array elements
    printf("\nBUF=%s\n",buf);
    arrayprintf_dbl(buf,(*p).ten);
}

char* util_returnFormattedString(char *innerStr,int n){
    char *s = malloc(strlen(innerStr) * n + n + 2);
    *s = '[';
    *(s+1) = '\0';
    for(int i = 0;i < n * 2;i++){
        if(i % 2 == 0){//check remainder by 2 value
            strcat((s),innerStr);
        }
        else{
            strcat((s),",");
        }
        //printf("MIDFORMAT=%s",s);
    }
    *(s + strlen(innerStr) * n + n) = ']';
    *(s + strlen(innerStr) * n + n + 1) = '\0';
    //printf("\nREFORMAT=%s\n",s);
    return(s);
}


//test 