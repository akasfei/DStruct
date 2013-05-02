int LinearSheetInit (LinearSheetClass *L, LinearSheetObject newObj)
{
  if (L->head != NULL)
    return STS_FAIL;
  L->_this = L->head = (LinearSheetObject *)malloc(sizeof LinearSheetObject);
  if (L->head == NULL)
    return STS_FAIL;
  L->head->prev = L->head->next = NULL;
  L->length = 1;
  return STS_OK;
}

int LinearSheetDestroy (LinearSheetClass *L)
{
  if (L->head != NULL)
    return STS_FAIL;
  L->_this = L->head;
  for (; L->_this = L->_this->next; _this->next != NULL)
  {
    if (L->_this->prev != NULL) {
      free(L->_this->prev);
      L->_this->prev = NULL;
    }
  }
  free(L->_this);
  L->head = L->_this = NULL;
  L->length = 0;
  free(L);
  return STS_OK;
}

int LinearSheetInsert (LinearSheetClass *L, DataObject *obj, int position)
{
  if (L->_this == NULL)
    L->_this = L->head;
  LinearSheetObject *obj_to_ins = (LinearSheetObject *)malloc(sizeof LinearSheetObject)
  return STS_OK;
}

int LinearSheetInsertH (LinearSheetClass *L, DataObject *obj)
{
  return LinearSheetInsert (L, obj, 0);
}

int LinearSheetGet (LinearSheetClass *L, int position, DataObject *e)
{
  int i;
  if (position >= 0 && position < L->length)
  {
    L->_this = L->head;
    for (i=0; i<position; i++, L->_this = L->_this->next);
    *e = L->_this;
    return STS_OK;
  }
  else
    return STS_FAIL;
}

int LinearSheetQuery (LinearSheetClass *L, DataObject target, int (*compare)(DataObject obj1, DataObject obj2), DataObject *des)
{    
    for (L->_this = L->head; L->_this != NULL; i++, L->_this = L->_this->next)
    {
        if ( (*compare) (L->_this, target) == 1 )
        {
            des = L->_this;
            return STS_OK;
        }
    }
    return STS_FAIL;
}

int LinearSheetRemove (LinearSheetClass *L, int position, DataObject *removedObj)
{
    int i;
    if (L->_this == NULL)
        return STS_FAIL;
    L->_this->prev->next = L->_this->next;
    L->_this->next->prev = L->_this->prev;
    free(L->_this);
    L->_this = NULL;
    return STS_OK;
}

int LinearSheetTraverse (LinearSheetClass *L, int (*visit) (DataObject))
{
    for (L->_this = L->head; L->_this != NULL; i++, L->_this = L->_this->next)
    {
        (*visit) (L->data[i]);
    }
    return STS_OK;
}

typedef struct LinearSheetClass
{
  struct LinearSheetObject *head, *_this;
  int length;
  int (*insert) (LinearSheetClass *L, DataObject *obj, int position) = NULL;
  int (*insertH) (LinearSheetClass *L, DataObject *obj) = NULL;
}LinearSheetClass;

typedef struct LinearSheetObject
{
  DataObject data;
  struct LinearSheetObject *next = NULL, *prev = NULL;
}LinearSheetObject;
