typedef struct DataObject
{
	int dataInt;
	char dataText[255];
}DataObject;

void swapDataObject (DataObject * obj1, DataObject * obj2)
{
	DataObject *temp;
	temp = obj1;
	obj1 = obj2;
	obj2 = temp;
	return;
}
