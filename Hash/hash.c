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

int size = 10;

int count = 0;

struct DataItem {
  void *data;
  void *key;
};

struct Table {
  int size;
  struct DataItem *hashArra[];  
};

struct Table *createtable() {
  //   struct DataItem *item = (struct DataItem *)malloc(sizeof(struct
  //   DataItem)); item->data = data; item->key = key;
  struct Table *table = (struct Table *)malloc(sizeof(struct Table));
  //   table->size = 10;
  return table;
}

struct DataItem *hashArray[SIZE];
// struct DataItem *dummyItem;
struct DataItem *item;

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------

int g(char *p) { return *((unsigned int *)p); }

int hashCode(void *key) {
  int k = g((char *)key);
  printf("HashCode -- %d\n", k);
  int code = k % SIZE;
  //   printf("HashCode -- %d\n", code);
  if (code < 0)
    code = -code;
  return code;
}

// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------

struct DataItem *search(void *key) {
  // get the hash
  int hashIndex = hashCode(key);
  //   printf("search-index -- %d, key - %p\n", hashIndex,
  //  (char *)(hashArray[hashIndex]->key));
  // move in array until an empty
  while (hashArray[hashIndex] != NULL) {
    // printf("hashIndex -- %d\n", hashIndex);
    if (hashArray[hashIndex]->key == key)
      return hashArray[hashIndex];

    // go to next cell
    hashIndex++;
    if (hashIndex == SIZE) {
      hashIndex = 0;
    }
    // wrap around the table
    // hashIndex %= SIZE;
    // printf("hashIndex -- %d\n" , hashIndex);
  }
  //   printf("No such key\n");
  //   exit(EXIT_FAILURE);
}

void insert(void *key, void *data) {

  struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
  item->data = data;
  item->key = key;

  // get the hash
  int hashIndex = hashCode(key);
  //   printf("insert-index -- %d", hashIndex);
  // move in array until an empty or deleted cell
  while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != NULL) {
    if (hashArray[hashIndex]->key == key)
      break;

    // go to next cell
    hashIndex++;
    if (hashIndex == SIZE) {
      hashIndex = 0;
    }

    // wrap around the table
    // hashIndex %= SIZE;
  }

  //   display();
  hashArray[hashIndex] = item;
}

struct DataItem *delete (struct DataItem *item) {
  void *key = item->key;

  // get the hash
  int hashIndex = hashCode(key);

  // move in array until an empty
  while (hashArray[hashIndex] != NULL) {

    if (hashArray[hashIndex]->key == key) {
      struct DataItem *temp = hashArray[hashIndex];

      // assign a dummy item at deleted position
      //   hashArray[hashIndex] = dummyItem;
      return temp;
    }

    // go to next cell
    ++hashIndex;

    if (hashIndex == SIZE) {
      hashIndex = 0;
    }

    // wrap around the table
    // hashIndex %= SIZE;
  }

  return NULL;
}

void display() {
  int i = 0;

  for (i = 0; i < SIZE; i++) {
    if (hashArray[i] != NULL) {
      printf(" (%s,%d) ,", (char *)hashArray[i]->key,
             *((int *)hashArray[i]->data));
    } else
      printf(" e , ");
  }

  printf("\n");
}

// -------------------------------------------------------------------------------------------------------

//  ------------------------------------------------------------------------------------------------------

struct DataItem *searchh(struct Table *table, void *key) {
  // get the hash
  int hashIndex = hashCode(key);
  int tempHash = hashIndex;
  // printf(" (%c) \n,", *((char *)table->hashArra[hashIndex]->key));
  while (table->hashArra[hashIndex] != NULL ||
         table->hashArra[hashIndex] == NULL) {
    // printf("hashIndex -- %d\n", hashIndex);
    if (table->hashArra[hashIndex]->key == key) {
      //   printf("HashCode --------%d\n", hashIndex);
      //   printf("Size --------%d\n", SIZE);
      return table->hashArra[hashIndex];
    }
    hashIndex++;

    // printf("HashCode --------%d\n", hashIndex);
    // printf("Size --------%d\n", SIZE);
    if (hashIndex == SIZE)
      hashIndex = 0;
    if (hashIndex == tempHash) {
      break;
    }
  }
  //   struct DataItem *i = NULL;
  //   printf("%d\n", hashIndex);
  // move in array until an empty

  // go to next cell
  return NULL;
}

void insertt(struct Table *table, void *key, void *data) {

  struct DataItem *item = (struct DataItem *)malloc(sizeof(struct DataItem));
  item->data = data;
  item->key = key;

  // get the hash
  int hashIndex = hashCode(key);
  //   printf("insert-index -- %d\n", hashIndex);
  // move in array until an empty or deleted cell
  int size = sizeof(*table);
  printf("%d\n", size);
  while (table->hashArra[hashIndex] != NULL &&
         table->hashArra[hashIndex]->key != NULL) {
    if (table->hashArra[hashIndex]->key == key)
      break;

    // go to next cell
    hashIndex++;
    if (hashIndex == SIZE)
      hashIndex = 0;

    // wrap around the table
    // hashIndex %= SIZE;
  }

  //   display();
  table->hashArra[hashIndex] = item;
}

struct DataItem *deletee(struct Table *table, struct DataItem *item) {
  void *key = item->key;

  // get the hash
  int hashIndex = hashCode(key);

  // move in array until an empty
  while (table->hashArra[hashIndex] != NULL) {

    if (table->hashArra[hashIndex]->key == key) {
      struct DataItem *temp = table->hashArra[hashIndex];

      // assign a dummy item at deleted position
      //   hashArray[hashIndex] = dummyItem;
      return temp;
    }

    // go to next cell
    ++hashIndex;
    hashIndex++;
    if (hashIndex == SIZE) {
      hashIndex = 0;
    }

    // wrap around the table
    // hashIndex %= SIZE;
  }

  return NULL;
}

void displayy(struct Table *table) {
  int i = 0;

  for (i = 0; i < size; i++) {
    if (table->hashArra[i] != NULL) {
      printf(" (%s,%d) ,", (char *)table->hashArra[i]->key,
             *((int *)table->hashArra[i]->data));
    } else
      printf(" e , ");
  }

  printf("\n");
}

// ---------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------

int main() {
  //   dummyItem = (struct DataItem *)malloc(sizeof(struct DataItem));
  //   dummyItem->data = -1;
  //   dummyItem->key = -1;

  //   struct DataItem *item = (struct DataItem *)malloc(sizeof(struct
  //   DataItem)); item->data = data; item->key = key;

  struct Table *t, *t1;
  t = createtable();
  t1 = createtable();

  char *k = "hell";
  int v = 21;
  insertt(t, &k, &v);
  insertt(t1, &k, &v);
  char *k1 = "lleh";
  int v1 = 22;
  insertt(t, &k1, &v1);
  insertt(t1, &k1, &v1);
  char *k2 = "c";
  int v2 = 23;
  insertt(t, &k2, &v2);
  insertt(t1, &k2, &v2);

  printf("----------------------------Table1-----------------------\n");
  displayy(t);

  item = searchh(t, &k);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));

  } else {
    printf("Element not found\n");
  }

  //   deletee(t, item);

  item = searchh(t, &k1);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  item = searchh(t, &k2);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  printf("----------------------------Table2-----------------------\n");
  displayy(t1);

  item = searchh(t1, &k);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  // delete (item);
  item = searchh(t1, &k1);

  if (item != NULL) {
    printf("Element found: %d\n", *((int *)item->data));
  } else {
    printf("Element not found\n");
  }

  item = searchh(t1, &k2);

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