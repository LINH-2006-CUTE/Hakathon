#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    char category[100];
    float price;
    int isDiscontinued;//danh dau ban/ngunf ban
} Food;

typedef struct Node {
    Food foods;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} FoodList;

void newFoodList(FoodList* list) {
    list->head = NULL;
}

void addFood(FoodList* list) {
    Food newFood;
    int check;
    do {
        check = 0;
        printf("Nhap ma mon an:");
        scanf("%d",&newFood.id);
        getchar();

        Node* temp=list->head;
        while (temp != NULL) {
            if (temp->foods.id == newFood.id) {
                check = 1;
                printf("Mon an da ton tai\n");
                break;
            }
            temp = temp->next;
        }
    } while (check);

    printf("Nhap ten mon an: ");
    fgets(newFood.name, sizeof(newFood.name), stdin);
    newFood.name[strcspn(newFood.name, "\n")] = '\0';

    printf("Nhap ten danh muc: ");
    fgets(newFood.category, sizeof(newFood.category), stdin);
    newFood.category[strcspn(newFood.category, "\n")] = '\0';

    printf("Nhap gia mon: ");
    scanf("%f", &newFood.price);
    getchar();
    newFood.isDiscontinued = 0;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->foods =newFood;
    newNode->next =NULL;

    if (list->head ==NULL) {
        list->head =newNode;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Da them mon an\n");
}

void printFoodList(FoodList* list) {
    Node* current = list->head;
    if (current == NULL) {
        printf("Chua co mon an nao\n");
        return;
    }
    printf("Danh sach mon an:\n");
    while (current != NULL) {
        if (!current->foods.isDiscontinued) {
            printf("ID: %d, Ten mon an: %s, Danh muc: %s, Gia: %.2f\n",current->foods.id, current->foods.name, current->foods.category, current->foods.price);
        }
        current = current->next;
    }
}

void updateFood(FoodList* list) {
    int id;
    printf("Nhap ma mon an can cap nhat: ");
   scanf("%d", &id) ;

    Node* current = list->head;
    while (current != NULL) {
        if (current->foods.id == id) {
            printf("Nhap ten mon an moi: ");
            fgets(current->foods.name, sizeof(current->foods.name), stdin);
            current->foods.name[strcspn(current->foods.name, "\n")] = '\0';
            getchar();
            printf("Nhap danh muc moi: ");
            fgets(current->foods.category, sizeof(current->foods.category), stdin);
            current->foods.category[strcspn(current->foods.category, "\n")] = '\0';
            getchar();
            printf("Nhap gia moi: ");
            scanf("%f",current->foods.price);
            getchar();
            printf("Da cap nhat thong tin mon an\n");
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay mon an co ma %d\n",id);
}

void markDiscontinued(FoodList* list) {
    int id;
    printf("Nhap ma mon an can danh dau ngung ban:");
    scanf("%d", &id);
    Node* current = list->head;
    while (current != NULL) {
        if (current->foods.id == id) {
            if (current->foods.isDiscontinued) {
                printf("Mon an da duoc danh dau ngung ban\n");
            } else {
                current->foods.isDiscontinued = 1;
                printf("Da danh dau mon an co ma %d la ngung ban\n",id);
            }
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay mon an co id %d\n", id);
}

void printDiscontinuedFoods(FoodList* list) {
    Node* current = list->head;
    int found = 0;
    printf("Danh sach mon an da ngung ban:\n");
    while (current != NULL) {
        if (current->foods.isDiscontinued) {
            printf("ID: %d, Ten mon an: %s, Danh muc: %s, Gia: %.2f\n",
                   current->foods.id, current->foods.name, current->foods.category, current->foods.price);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Chua co mon an nao ngung ban\n");
    }
}

void searchFood(FoodList* list) {
    char name[100];
    printf("Nhap ten mon an can tim kiem: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    Node* current = list->head;
    int found = 0;
    if (current == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("Ket qua tim kiem:\n");
    while (current != NULL) {
        if (strstr(current->foods.name, name) != NULL) {
            printf("ID: %d, Ten mon an: %s, Danh muc: %s, Gia: %.f, Trang thai: %s\n",
                   current->foods.id, current->foods.name, current->foods.category, current->foods.price);

            if (current->foods.isDiscontinued) {
                printf("Ngung bann");
            }else {
                printf("dang ban");
            }
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Khong tim thay mon an co ten chua \"%s\"",name);
    }
}

void sortFoodList(FoodList*list) {
    if (list->head == NULL) {
        return;
    }
    Node* i;
    Node* j;
    for (i = list->head; i!=NULL; i =i->next) {
        for (j = i->next; j!=NULL; j =j->next) {
            if (i->foods.price > j->foods.price) {
                Food temp =i->foods;
                i->foods =j->foods;
                j->foods =temp;
            }
        }
    }
    printf("Da sap xep danh sach mon an theo gia tang dan\n");
}

void freeFoodList(FoodList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main(void) {
    FoodList list;
    newFoodList(&list);
    int choice;
    do {
        printf("1. Them mon an\n");
        printf("2. Hien thi danh sach mon dang ban\n");
        printf("3. Cap nhat thong tin mon an\n");
        printf("4. Danh dau ngung ban\n");
        printf("5. Hien thi danh sach mon an da ngung ban\n");
        printf("6. Tim kiem theo ten mon\n");
        printf("7. Sap xep mon theo gia tang dan\n");
        printf("8. Thoat chuong trinh\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice) ;
        getchar();

        switch (choice) {
            case 1:
                addFood(&list);
                break;
            case 2:
                printFoodList(&list);
                break;
            case 3:
                updateFood(&list);
                break;
            case 4:
                markDiscontinued(&list);
                break;
            case 5:
                printDiscontinuedFoods(&list);
                break;
            case 6:
                searchFood(&list);
                break;
            case 7:
                sortFoodList(&list);
                printFoodList(&list);
                break;
            case 8:
                printf("Thoat chuong trinh\n");
                freeFoodList(&list);
                break;
            default:
                printf("nhap lai\n");
        }
    } while (choice != 8);
    return 0;
}