#define LS_MAX 255

typedef struct LinearSheetClass_A
{
    DataObject *data;
    int length;
    int thisPos;
    int (*insert) (struct LinearSheetClass_A *, DataObject, int);
    int (*insertH) (struct LinearSheetClass_A *, DataObject);
    int (*get) (struct LinearSheetClass_A *, int, DataObject *);
    int (*remove) (struct LinearSheetClass_A *, int, DataObject *);
    int (*clear) (struct LinearSheetClass_A *L);
}LinearSheetClass_A;

int LinearSheetDestroy_A (LinearSheetClass_A *L)
{
    int i;
    for (i=0; i < L->length; i++)
    {
        free(L->data);
    }
    L->length = 0;
    free(L);
    return STS_OK;
}

int LinearSheetClear_A (LinearSheetClass_A *L)
{
    if (L->length < 1)
        return STS_FAIL;
    int i;
    for (i=0; i < L->length; i++)
    {
        L->data[i].dataInt = 0;
        strcpy (L->data[i].dataText, "");
    }
    L->length = 0;
    return STS_OK;
}

int LinearSheetInsert_A (LinearSheetClass_A *L, DataObject obj, int position)
{
    int i;
    if (L->length >= LS_MAX)
        return STS_OVERFLOW;
    if (position >= L->length && position < 0)
        return STS_FAIL;
    L->thisPos = position;
    for (i = L->length; i > position; i--)
        L->data[i] = L->data[i-1];
    L->data[position] = obj;
    L->length++;
    return STS_OK;
}

int LinearSheetGet_A (LinearSheetClass_A *L, int position, DataObject *e)
{
  if (position >= 0 && position < L->length)
  {
    *e = L->data[position];
    return STS_OK;
  }
  else
    return STS_FAIL;
}

int LinearSheetQuery_A (LinearSheetClass_A *L, DataObject target, int (*compare)(DataObject obj1, DataObject obj2))
{
    int i;
    for (i=0; i< L->length; i++)
    {
        if ( (*compare) (L->data[i], target) == 1 )
            return i;
    }
    return 0;
}

int LinearSheetRemove_A (LinearSheetClass_A *L, int position, DataObject *removedObj)
{
    int i;
    if (position >= 0 && position < L->length)
    {
        *removedObj = L->data[position];
        for (i = position; i < L->length - 1; i++)
            L->data[i] = L->data[i+1];
        return STS_OK;
    }
    else
        return STS_FAIL;
}

int LinearSheetTraverse_A (LinearSheetClass_A *L, int (*visit) (DataObject))
{
    int i;
    for (i=0; i < L->length; i++)
    {
        (*visit) (L->data[i]);
    }
    return STS_OK;
}

int LinearSheetInsertH_A (LinearSheetClass_A *L, DataObject obj)
{
    return LinearSheetInsert_A (L, obj, 0);
}

int LinearSheetInit_A (LinearSheetClass_A *L)
{
    L->length = 0;
    L->thisPos = 0;
    L->data = (DataObject *)malloc(LS_MAX * sizeof(DataObject) );
    L->insert = &LinearSheetInsert_A;
    L->remove = &LinearSheetRemove_A;
    L->get = &LinearSheetGet_A;
    L->insertH = &LinearSheetInsertH_A;
    L->clear = &LinearSheetClear_A;
    return STS_OK;
}
