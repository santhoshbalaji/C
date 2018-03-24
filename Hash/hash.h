// #ifndef hash_h
// #define hash_h
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

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
  table->size = prime_mod[0];
  int size = prime_mod[0];
  //   struct DataItem *hashArrayy[] = (struct DataItem *)calloc(size,
  //   sizeof(struct DataItem));
  table->noccupied = 0;
  table->index = 0;
  table->hashArray = (struct DataItem *)calloc(size, sizeof(struct DataItem));
  return table;
}

struct DataItem *item;

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------

int g(char *p) { return *((unsigned int *)p); }

int hashCode(void *key) {
  int k = g((char *)key);
  int code = k % SIZE;
  if (code < 0)
    code = -code;
  return code;
}

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------

struct DataItem *search(struct Table *table, void *key) {
  int hashIndex = hashCode(key);
  int tempHash = hashIndex;
  while (table->hashArray + hashIndex != NULL ||
         table->hashArray + hashIndex == NULL) {
    if ((table->hashArray + hashIndex)->key == key) {
      return table->hashArray + hashIndex;
    }
    hashIndex++;

    if (hashIndex == SIZE)
      hashIndex = 0;
    if (hashIndex == tempHash) {
      break;
    }
  }
  return NULL;
}

struct Table shift_table(struct Table *table) {
  printf("Entered");
  int size = table->size;
  int noccu = table->noccupied;
  struct Table *t = createtable();
  t->size = prime_mod[table->index];
  t->hashArray = (struct DataItem *)calloc(size, sizeof(struct DataItem));
  for (int i = 0; i < size; i++) {
    if ((table->hashArray + i) != NULL) {
      item = (table->hashArray + i);
      *(t->hashArray + i) = *item;
    }
  }
  return *t;
}

void insert(struct Table *table, void *key, void *data) {

  int size = table->size;
  int noccu = table->noccupied;
  int index = table->index;

  if (noccu == (size - 1)) {
    index++;
    int sizeOfArray = sizeof(prime_mod);
    if (index == sizeOfArray) {
      index--;
    }
    table->index = index;
    table->size = prime_mod[index];
    *table = shift_table(table);
  }

  struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
  item->data = data;
  item->key = key;

  int hashIndex = hashCode(key);
  while ((table->hashArray + hashIndex) != NULL &&
         (table->hashArray + hashIndex) != NULL) {
    if ((table->hashArray + hashIndex)->key == key)
      break;

    hashIndex++;
    if (hashIndex == SIZE)
      hashIndex = 0;
  }

  *(table->hashArray + hashIndex) = *item;
}

struct DataItem *delete_item (struct Table *table, struct DataItem *item) {
  void *key = item->key;

  int hashIndex = hashCode(key);

  while (table->hashArray + hashIndex != NULL) {

    if ((table->hashArray + hashIndex)->key == key) {
      struct DataItem *temp = table->hashArray + hashIndex;

      return temp;
    }

    ++hashIndex;
    hashIndex++;
    if (hashIndex == SIZE) {
      hashIndex = 0;
    }
  }

  return NULL;
}

void display(struct Table *table) {
  int i = 0;
  int size = table->size;
  for (i = 0; i < size; i++) {
    if ((table->hashArray + i) != NULL) {
      printf(" (%s,%d) ,", (char *)(table->hashArray + i)->key,
             *((int *)(table->hashArray + i)->data));
    } else
      printf(" e , ");
  }

  printf("\n");
}

// #endif