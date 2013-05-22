#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "views.h"
#include "models.h"
#include "linear_sheet_a.h"
#include "bintree.h"
#include "coreio.h"

/*void CTRL_initUI ()
{

}*/

int CTRL_init(BinTreeClass *BTree)
{
    char filename[] = "data\\BinTree.db";
    int mark=0;
    mark += BinTreeInit(BTree);
    mark += CIO_readData(filename, (void *) BTree);
    if (mark > STS_OK)
        return STS_FAIL;
    return STS_OK;
}

int CTRL_exit(BinTreeClass * thisClass)
{
    int mark;
    printf("Saving and Exiting...");
    mark = CIO_writeData("data\\BinTree.db", (void *)thisClass, CLASS_BTREE);
    if (mark > 0)
        printf("ERROR %d", mark);
    return mark;
}

int CTRL_main()
{
    int cmd, ibuf, pos, mark;
    char sbuf[20];
    BinTreeClass BTree;
    if (CTRL_init(&BTree) > 0)
        return STS_FAIL;
    menu:
    RENDER_menu_BT();
    scanf("%d", &cmd);
    getchar();
    switch (cmd)
    {
        case 0:
            return STS_OK;//CTRL_exit((void *)&LSheet);
        case 1:
            BinTreeView(&BTree);
            break;
        case 2:
            printf("Select: 0. parent; 1. left child; 2. right child\n");
            scanf("%d", &pos);
            getchar();
            mark = BinTreeSelect(&BTree, pos);
            if (mark > 0)
                printf("ERROR %d", mark);
            break;
        case 3:
            printf("Enter data field 1 (int): ");
            scanf("%d", &ibuf);
            getchar();
            printf("Enter data field 2 (string): ");
            scanf("%s", sbuf);
            getchar();
            printf("Insert as: 1. left child; 2. right child\n");
            scanf("%d", &pos);
            getchar();
            mark = BinTreeInsert(&BTree, pos, *DO_New(ibuf, sbuf));
            if (mark > 0)
                printf("ERROR %d", mark);
            break;
        case 4:
            printf("Enter data field 1 (int): ");
            scanf("%d", &ibuf);
            getchar();
            printf("Enter data field 2 (string): ");
            scanf("%s", sbuf);
            getchar();
            BTree._this->data = *DO_New(ibuf, sbuf);
            break;
        case 5:
            mark = BinTreeRemove(&BTree);
            if (mark > 0)
                printf("ERROR %d", mark);
            break;
    }
    printf("Press ENTER to continue.");
    getchar();
    goto menu;
    return 0;
}
