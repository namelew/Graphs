# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define TAM 6
#define INT_MAX 2147483647

typedef struct{
    int control;
    int value;
    int parent;
}NodePath;