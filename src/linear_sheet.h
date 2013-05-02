typedef struct LinearSheetClass
{
  struct LinearSheetObject *head, *_this;
  int length;
  int (*insert) (struct LinearSheetClass *, DataObject, int);
  int (*insertH) (struct LinearSheetClass *, DataObject);
  int (*get) (struct LinearSheetClass *, int, DataObject *);
  int (*remove) (struct LinearSheetClass *, int, DataObject *);
  int (*clear) (struct LinearSheetClass *L);
}LinearSheetClass;

typedef struct LinearSheetObject
{
  DataObject data;
  struct LinearSheetObject *next, *prev;
}LinearSheetObject;

int LinearSheetDestroy (LinearSheetClass *L)
{
  if (L->head != NULL)
    return STS_FAIL;
  L->_this = L->head;
  for (; L->_this = L->_this->next; L->_this->next != NULL)
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
  int i;
  if (position < 1 || position > L->length)
    return STS_FAIL;
  L->_this = L->head;
  LinearSheetObject * obj_to_ins = (LinearSheetObject *)malloc(sizeof (LinearSheetObject));
  for (i=1; i < position; i++, L->_this = L->_this->next);
  L->_this->next->prev = obj_to_ins;
  obj_to_ins->prev = L->_this;
  obj_to_ins->next = L->_this->next;
  L->_this->next = obj_to_ins;
  L->length++;
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
    e = &(L->_this->data);
    return STS_OK;
  }
  else
    return STS_FAIL;
}

int LinearSheetQuery (LinearSheetClass *L, DataObject target, int (*compare)(DataObject obj1, DataObject obj2), DataObject *des)
{
    for (L->_this = L->head; L->_this != NULL; L->_this = L->_this->next)
    {
        if ( (*compare) (L->_this->data, target) == 1 )
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

int LinearSheetTraverse (LinearSheetClass *L, int (*visit) (LinearSheetObject))
{
    int mark;
    for (L->_this = L->head; L->_this != NULL; L->_this = L->_this->next)
    {
        mark = (*visit) (*(L->_this));
        if (mark > 0)
            return STS_FAIL;
    }
    return STS_OK;
}

int LinearSheetInit (LinearSheetClass *L, DataObject newObj)
{
  if (L->head != NULL)
    return STS_FAIL;
  L->_this = L->head = (LinearSheetObject *)malloc(sizeof (LinearSheetObject));
  if (L->head == NULL)
    return STS_FAIL;
  L->head->data = newObj;
  L->head->prev = L->head->next = NULL;
  L->length = 1;
  L->insert = &LinearSheetInsert;
  L->remove = &LinearSheetRemove;
  L->get = &LinearSheetGet;
  L->insertH = &LinearSheetInsertH;
  return STS_OK;
}
