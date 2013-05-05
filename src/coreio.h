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
    if ( !strcmp(className, "LINEARSHEET") )
        return CLASS_LSHEET;
    if ( !strcmp(className, "STACK") )
        return CLASS_STACK;
    return -1;
}

int CIO_readData (char * filename, void *destClassP)
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
        thisData = DO_New_s(fileBuffer);
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

int CIO_writeData (char * filename, void *srcClassP, int classType)
{
    FILE *thisfile = fopen(filename, "w");
    char meta[20], lineBuffer[80];
    int i;
    switch (classType) {
        case 0:
        {
            LinearSheetClass_A *thisClass = (LinearSheetClass_A *) srcClassP;
            strcpy(meta, "META?LINEARSHEET");
            fprintf(thisfile, "%s", meta);
            for (i=0; i<thisClass->length; i++)
            {
                strcpy(lineBuffer, DO_serialize(thisClass->data[i]));
                fprintf(thisfile, "\n%s", lineBuffer);
            }
            break;
        }
        default:
            return STS_FAIL;
    }
    fclose(thisfile);
    return STS_OK;
}
