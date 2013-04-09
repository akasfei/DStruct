#include <stdio.h>
#include <stdlib.h>

enum
{
  CLASS_LSHEET = 0,
  CLASS_STACK,
  CLASS_QUEUE,
  CLASS_STRING,
  CLASS_ARRAY,
  CLASS_WSHEET,
  CLASS_BTREE,
  CLASS_GRAPH
}

void *readDataFunc (char * filename, int classDef) 
{

}

typedef struct DataStoreInterface
{
  char *fileName;
  void *(*readData)(char * filename, int classDef) = &readDataFunc;
  void *(*storeData)(char * filename, int classDef) = &storeDataFunc;
}