#include "hashing.c"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  //   dummyItem = (struct DataItem *)malloc(sizeof(struct DataItem));
  //   dummyItem->data = -1;
  //   dummyItem->key = -1;

  //   struct DataItem *item = (struct DataItem *)malloc(sizeof(struct
  //   DataItem)); item->data = data; item->key = key;

  printf("Started");
  struct Table *t, *t1;
  t = createtable();
  t1 = createtable();

  char *k = "hell";
  int v = 21;
  insert(t, &k, &v);
  insert(t1, &k, &v);
  char *k1 = "lleh";
  int v1 = 22;
  insert(t, &k1, &v1);
  insert(t1, &k1, &v1);
  char *k2 = "c";
  int v2 = 23;
  insert(t, &k2, &v2);
  insert(t1, &k2, &v2);

  printf("----------------------------Table1-----------------------\n");
  display(t);

  item = search(t, &k);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));

  } else {
    printf("Element not found\n");
  }

  //   delete(t, item);

  item = search(t, &k1);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  item = search(t, &k2);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  printf("----------------------------Table2-----------------------\n");
  display(t1);

  item = search(t1, &k);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  // delete (item);
  item = search(t1, &k1);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  item = search(t1, &k2);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }
  //   unsigned int s = size_t;
  //   printf("%d\n", s);

  //   printf("%d\n", g("hell"));
  //   printf("%d\n", g("string"));
  //   printf("%d\n", g("gnirts"));
  // printf("-----------------------------------------\n");
  //   printf("%d\n", g("hello"));
  //   printf("%d\n", g("olleh"));

  //   chk2 = (char)100;
  //   v2 = 24;
  //   insert(&k2, &v2);

  //   item = search(&k2);

  //   display();

  //   if (item != NULL) {
  //     printf("Element found: %d\n", *((int *)item->data));
  //   } else {
  //     printf("Element not found\n");
  //   }
}