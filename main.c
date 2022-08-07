#include "SecondaryFunctions.h"
#include "Tree.h"

int main() {
    int option = -1;
    node *root = NULL, *unb = NULL;
    char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Find an farthest item"};
    root = create(root);
    while (option) {
        option = dialog(msgs);
        if (option == 1) {
            int key;
            printf("Enter key: ");
            scanf("%d", &key);
            printf("Enter information: ");
            scanf("%*c");
            char *information = getString();
            root = add(root, key, information);
            free(information);
        }
        if (option == 2) {
            node *tmp;
            int key;
            printf("Enter key: ");
            scanf("%d", &key);
            if (!search(root, key)){
                printf("Node with this key not found\n");
            }
            else {
                info *infoList = search(root, key)->info;
                int optionForGettingInfo;
                printf("1. All information associated with this key\n");
                printf("2. A specific item from a list of information\n");
                scanf("%d", &optionForGettingInfo);
                if (optionForGettingInfo == 1) {
                    while (infoList != NULL) {
                        printf("%s ", infoList->info);
                        infoList = infoList->next;
                    }
                }
                else if (optionForGettingInfo == 2) {
                    int numInLst;
                    printf("Enter number of information in list: ");
                    scanf("%d", &numInLst);
                    info *info = search(root, key)->info;
                    int i = 1;
                    while (info) {
                        if (i == numInLst) {
                            printf("%s ", info->info);
                            break;
                        }
                        i++;
                        info = info->next;
                    }
                    if (info == NULL) {
                        printf("Version not found\n");
                    }
                }
            }
        }
        if (option == 3) {
            int key;
            printf("Enter key you want to remove: ");
            scanf("%d", &key);
            root = extract(root, key);
        }
        if (option == 4) {
            print(root, 0);
        }
        if (option == 5) {
            int key;
            printf("Enter key: ");
            scanf("%d", &key);
            printf("The furthest key: %d", findFurthestItem(root, key));
        }
    }
    return 0;
}
