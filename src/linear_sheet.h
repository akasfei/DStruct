enum
{
  STS_OK = 0,
  STS_FAIL,
  STS_OVERFLOW,
  STS_CRASH,
  STS_MAX
}

typedef struct LinearSheetClass 
{
  struct LinearSheetObject *head, *_this;
  int length;
}LinearSheetClass;

typedef struct LinearSheetObject 
{
  int def_property;
  struct LinearSheetObject *next = null, *prev = null;
}LinearSheetObject;

int LinearSheetInit (LinearSheetClass *L, LinearSheetObject newObj) 
{
  if (L->head != null)
    return STS_FAIL;
  L->_this = L->head = (LinearSheetObject *)malloc(sizeof LinearSheetObject);
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