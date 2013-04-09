int CIO_getDataType (char * metadata)
{
    int i, j;
    char className[16];
    for (i=0; metadata[i] != '?'; i++);
    for (++i, j=0; metadata[i] != '\n'; i++, j++)
    {
        className[j] = metadata[i];
    }
    className[j] = '\0';
    if ( strcmp(className, "LINEARSHEET") )
        return CLASS_LSHEET;
    if ( strcmp(className, "STACK") )
        return CLASS_STACK;
    return -1;
}

DataObject *CIO_getDataContent (char * dataContent)
{
    int i, j;
    char propertyCache[255];
    DataObject *thisData = (DataObject *)malloc(sizeof (DataObject));
    for (i=0, j=0; dataContent[i] != '?'; i++, j++)
        propertyCache[j] = dataContent[i];
    propertyCache[j] = '\0';
    thisData->dataInt = atoi(propertyCache);
    for (++i, j=0; dataContent[i] != '\n'; i++, j++)
        propertyCache[j] = dataContent[i];
    propertyCache[j] = '\0';
    strcpy(thisData->dataText, propertyCache);
    return thisData;
}

int *CIO_readDataFunc (char * filename, void *destClassP)
{
    FILE *thisfile = fopen(filename, "r");
    char fileBuffer[255];
    DataObject *thisData;
    int dataType;
    fgets(fileBuffer, 255, thisfile); // get meta data
    dataType = CIO_getDataType(fileBuffer);
    do
    {
        fgets(fileBuffer, 255, thisfile);
        thisData = CIO_getDataContent(fileBuffer);
        switch ( dataType )
        {
            case CLASS_LSHEET:
            {
                LinearSheetClass_A *thisClass = (LinearSheetClass_A *)destClassP;
                thisClass->insertH(thisClass, *thisData);
                break;
            }
            default:
            {
                return STS_FAIL;
                break;
            }
        }
    }while ( !feof(thisfile) );
    return STS_OK;
}

typedef struct CoreIO
{
  char *fileName;
  void *(*readData)(char *, int);
  void *(*storeData)(char *, int);
}CoreIO;
