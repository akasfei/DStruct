#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "views.h"
#include "models.h"
#include "bintree.h"
#include "linear_sheet_A.h"
#include "coreio.h"

/*void CTRL_initUI ()
{

}*/

int CTRL_init(LinearSheetClass_A *LSheet)
{
    char filename[] = "data\\LinearSheet";
    int mark=0;
    mark += LinearSheetInit_A(LSheet);
    mark += CIO_readData(filename, (void *) LSheet);
    if (mark > STS_OK)
        return STS_FAIL;
    return STS_OK;
}

int CTRL_main()
{
    int cmd, ibuf, pos, mark;
    char sbuf[20];
    LinearSheetClass_A LSheet;
    if (CTRL_init(&LSheet) > 0)
        return STS_FAIL;
    menu:
    RENDER_menu_LS();
    scanf("%d", &cmd);
    getchar();
    switch (cmd)
    {
        case 0:
            return 0;
        case 1:
        {
            printf("Enter data field 1 (int): ");
            scanf("%d", &ibuf);
            getchar();
            printf("Enter data field 2 (string): ");
            scanf("%s", &sbuf);
            getchar();
            printf("Insert position: ");
            scanf("%d", &pos);
            getchar();
            mark = LSheet.insert(&LSheet, *DO_New(ibuf, sbuf), pos);
            if (mark > 0)
                printf("ERROR CODE %d.\n", mark);
            break;
        }
        case 2:
        {
            DataObject obj;
            printf("Input position: ");
            scanf("%d", &pos);
            getchar();
            mark = LSheet.get(&LSheet, pos, &obj);
            if (mark > 0)
                printf("ERROR CODE %d.\n", mark);
            printf("%s", DO_serialize(obj));
            break;
        }
        case 4:
        {
            DataObject obj;
            printf("Positon to remove: ");
            scanf("%d", &pos);
            getchar();
            mark = LSheet.remove(&LSheet, pos, &obj);
            if (mark > 0)
                printf("ERROR CODE %d.\n", mark);
            printf("Removed object: %s", DO_serialize(obj));
            break;
        }
        case 5:
        {
            DataObject obj;
            printf("Input 32767 to confirm: ");
            scanf("%d", &pos);
            getchar();
            mark = 1;
            if (pos == 32767)
                mark = LSheet.clear(&LSheet);
            if (mark > 0)
                printf("ERROR CODE %d.\n", mark);
            break;
        }
    }
    goto menu;
    return 0;
}
