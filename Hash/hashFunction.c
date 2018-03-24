#include <stdio.h>

int hashcode(void *p){
    printf("%d\n",*((int *)p));
    return *((int *)p);
}

int main(){
    char c = "aas";
    void* i = &c;
    printf("%d\n",hashcode(i));
}