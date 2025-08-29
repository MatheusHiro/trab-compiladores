#include <stdio.h>

int a[3] = {1,4,3};
int b = 1;
int c = 3;

int teste(int x){
    printf("%d", x);
    return 9;
}

int main(){
    b = teste(c);
}