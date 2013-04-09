int LinearSheetInit (LinearSheetClass *L, LinearSheetObject newObj)
{
  if (L->head != null)
    return STS_FAIL;
  L->_this = L->head = (LinearSheetObject *)malloc(sizeof LinearSheetObject);
  if (L->head == null)
    return STS_FAIL;
  L->head->prev = L->head->next = null;
  L->length = 1;
  return STS_OK;
}

int LinearSheetDestroy (LinearSheetClass *L)
{
  if (L->head != null)
    return STS_FAIL;
  L->_this = L->head;
  for (; L->_this = L->_this->next; _this->next != null)
  {
    if (L->_this->prev != null) {
      free(L->_this->prev);
      L->_this->prev = null;
    }
  }
  free(L->_this);
  L->head = L->_this = null;
  L->length = 0;
  free(L);
  return STS_OK;
}

int LinearSheetInsert (LinearSheetClass *L, DataObject *obj, int position)
{
  if (L->_this == null)
    L->_this = L->head;
  LinearSheetObject *obj_to_ins = (LinearSheetObject *)malloc(sizeof LinearSheetObject)
  return STS_OK;
}

int LinearSheetInsertH (LinearSheetClass *L, DataObject *obj)
{
  return LinearSheetInsert (L, obj, 0);
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
  struct LinearSheetObject *next = null, *prev = null;
}LinearSheetObject;
