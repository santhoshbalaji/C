// #ifndef hash_h
// #define hash_h
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define SIZE 10

static const int prime_mod[] = {
    1, /* For 1 << 0 */
    2,         3,          7,         13,       31,        61,
    127,       251,        509,       1021,     2039,      4093,
    8191,      16381,      32749,     65521, /* For 1 << 16 */
    131071,    262139,     524287,    1048573,  2097143,   4194301,
    8388593,   16777213,   33554393,  67108859, 134217689, 268435399,
    536870909, 1073741789, 2147483647 /* For 1 << 31 */
};

struct DataItem {
  void *data;
  void *key;
};

struct Table {
  int size;
  int noccupied;
  int index;
  struct DataItem *hashArray;
};

struct Table *createtable() {
  struct Table *table = (struct Table *)malloc(sizeof(struct Table));
  table->size = prime_mod[7];
  int size = prime_mod[7];
  //   struct DataItem *hashArrayy[] = (struct DataItem *)calloc(size,
  //   sizeof(struct DataItem));
  table->noccupied = 0;
  table->index = 7;
  table->hashArray = (struct DataItem *)calloc(size, sizeof(struct DataItem));
  return table;
}

struct DataItem *item;

struct DataItem *dummy;

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------

int g(char *p) { return *((unsigned int *)p); }

int hashCode(struct Table *table, void *key) {
  int k = g((char *)key);
  int code = k % table->size;
  if (code < 0)
    code = -code;
  return code;
}

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------

struct DataItem *search(struct Table *table, void *key) {
  int hashIndex = hashCode(table, key);
  int tempHash = hashIndex;
  while ((table->hashArray + hashIndex)->key != 0) {
    if ((table->hashArray + hashIndex)->key == key) {
      return table->hashArray + hashIndex;
    }
    hashIndex++;

    if (hashIndex == table->size)
      hashIndex = 0;
    if (hashIndex == tempHash) {
      break;
    }
  }
  return NULL;
}

void *shift_table(struct Table *table) {

  // printf("Entered\n");
  int size = (table)->size;
  int noccu = (table)->noccupied;
  int index = (table)->index;
  index++;
  int sizeOfArray = sizeof(prime_mod) / sizeof(int);
  if (index == sizeOfArray) {
    index--;
  }
  (table)->index = index;
  (table)->size = prime_mod[index];
  (table)->hashArray =
      (struct DataItem *)realloc((table)->hashArray, (table)->size);
  // printf("%p\n", table->hashArray);
  // struct Table *t = createtable();
  // t->size = prime_mod[(table)->index];
  // t->hashArray = (struct DataItem *)realloc(table, size);
  // for (int i = 0; i < prime_mod[index--]; i++) {
  //   if (((*table)->hashArray + i) != NULL) {
  //     item = ((*table)->hashArray + i);
  //     // printf("hello\n");
  //     *(t->hashArray + i) = *item;
  //   }
  // }
  // *table = *t;
  // return t;
}

void replace(struct Table *table, struct DataItem *item, int hashIndex) {
  // printf("Entered Replace -- \n");
  if ((table->hashArray + hashIndex)->key == item->key) {
    // printf("Entered Replace if_condition\n");
    *(table->hashArray + hashIndex) = *item;
    printf("-- %p\n", (table->hashArray + hashIndex)->data);
    // printf("%p -- , ", (table->hashArray + hashIndex));
    printf("-- %p\n", table->hashArray);
    // printf("HashIndex -- %d\n", hashIndex);
    int occ = table->noccupied;
    occ++;
    table->noccupied = occ;
  } else {
    if ((table->hashArray + hashIndex)->key != 0) {
      hashIndex++;
      add(table, item, hashIndex);
    }
  }
}

void add(struct Table *table, struct DataItem *item, int hashIndex) {
  // printf("Entered Add -- \n");
  if ((table->hashArray + hashIndex)->key == 0) {
    *(table->hashArray + hashIndex) = *item;
    printf("-- %p\n", (table->hashArray + hashIndex)->data);
    printf("Size -- %d\n",(table->size));
    int occ = table->noccupied;
    occ++;
    table->noccupied = occ;
  } else {
    replace(table, item, hashIndex);
  }
}

void insert(struct Table *table, void *key, void *data) {
  int size = table->size;
  int noccu = table->noccupied;
  int index = table->index;

  if (noccu == (size - 2)) {
    shift_table(table);
  }

  struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
  item->data = data;
  item->key = key;

  int hashIndex = hashCode(table, key);

  if ((table->hashArray + hashIndex)->key == 0) {
    add(table, item, hashIndex);
    // printf("Index -- add -- %d\n", hashIndex);
  } else {
    replace(table, item, hashIndex);
    // printf("%d -- ",*(int *)(table->hashArray + hashIndex)->data);
    // printf("Index -- replace -- %d\n", hashIndex);
  }
}

struct DataItem *delete_item(struct Table *table, struct DataItem *item) {
  void *key = item->key;

  // dummy->key = NULL;
  // dummy->data = NULL;

  int hashIndex = hashCode(table, key);

  while ((table->hashArray + hashIndex)->key != 0) {

    if ((table->hashArray + hashIndex)->key == key) {
      struct DataItem *temp = table->hashArray + hashIndex;
      *(table->hashArray+hashIndex) = NULL;
      return temp;
    }

    // ++hashIndex;
    hashIndex++;
    if (hashIndex == table->size) {
      hashIndex = 0;
    }
  }

  return NULL;
}

void display(struct Table *table) {
  int i = 0;
  int size = table->size;
  int count = 0;
  int occ = table->noccupied;
  printf("count -- %d , occ -- %d\n", count, occ);
  int s = sizeof(table->hashArray) / sizeof(struct DataItem);
  // printf("Size -- %d\n", s);
  // printf("size -- %d\n", size);
  // printf("Occu -- %d\n", occ);
  // printf("%p\n", table->hashArray);
  // printf("\n");
  // while (!(count == occ)) {
  //   if ((table->hashArray + i)->key != 0) {
  //     printf("Hello -- ");
  //     item = (table->hashArray + i);
  //     // printf("Count -- %d\n", count);
  //     // char *k;
  //     // strcpy(k, (char *)(table->hashArray + i)->key);
  //     // printf("%p\n", (table->hashArray + i));
  //     // int v = *(int *)item->data;
  //     printf("-- %p\n", (table->hashArray + i)->data);
  //     count++;
  //   }
  //   i++;
  //   if (i == size) {
  //     i = 0;
  //   }
  // }
  printf("Size -- %d\n", size);
  for (i = 0; i < size; i++) {

    if ((table->hashArray + i)->key != 0) {
      item = (table->hashArray + i);
      // printf("i if -- %d\n ", i);
      // printf(" (%c,%d) ,", *((char *)(table->hashArray + i)->key),
      //        *((int *)(table->hashArray + i)->data));
      // printf("-- %p\n", (table->hashArray + i)->data);
      int v = *(int *)item->data;
      printf("(%d),", v);
      count++;
    } 
      // printf("i else -- %d\n", i);
      // printf("");
  }
  printf("\n");
  printf("Count = %d\n", count);
}

void check_table_size(struct Table *table) {
  int count = 0;
  // shift_table(table);
  while (table->size >= count) {
    printf("%p\n", (table->hashArray + count));
    count++;
  }
  // count = 0;
  // printf("\n");
  // shift_table(table);
  // while (table->size >= count) {
  //   printf("%p\n", (table->hashArray + count));
  //   count++;
  //}
}

// char *toString(void *k) {
//   printf("\n");
//   char* b;
//   b = (char *(*)k);
//   return b;
// }

// void *write(void *ptr) {
//   char *array;
//   *array = ((char*)ptr);
//   printf("%s\n", array);
// }

// #endif
int main() {

  printf("Started\n");
  struct Table *t, *t1;
  t = createtable();
  t1 = createtable();
  // check_table_size(t);
  int s = sizeof(prime_mod) / sizeof(int);
  printf("size of prime_mod -- %d\n", s);
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
  char *k3 = "d";
  int v3 = 24;
  insert(t, &k3, &v3);
  insert(t1, &k3, &v3);
  char *k4 = "e";
  int v4 = 25;
  insert(t, &k4, &v4);
  insert(t1, &k4, &v4);
  // check_table_size(t);
  v = 2121;
  printf("--------------------------Table1-----------------------\n");
  display(t);

  item = search(t, &k);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));

  } else {
    printf("Element not found\n");
  }

    delete_item(t, item);

  item = search(t, &k);

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

  delete_item (t1,item);
  item = search(t1, &k);

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