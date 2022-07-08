#include<stdio.h>

#include<conio.h>

#include<stdlib.h>

#include<string.h>

struct store {
  char name[30];
  char price[30];
  int id;
  int quantity;
  char category[30];
  char date[12];
  char company[30];

}
s;

long si = sizeof(s);

void input();
void display();
void search();
void searchById();
void searchByName();
void modify();
void del();
void sort();
void sortById();
void sortByName();

FILE * fp;

int main() {

  int ch;
  while (1) {

    printf("\n<== departmental store ==>\n");
    printf("1.Add item\n");
    printf("2.Item Info\n");
    printf("3.Search item\n");
    printf("4.Modify item \n");
    printf("5.Delete item\n");
    printf("6.Sort item \n");
    printf("0.Exit\n\n");
    printf("Enter your choice from 1-6  or 0 to exit ");
    scanf("%d", & ch);
    switch (ch) {
    case 0:
      exit(0);

    case 1:
      input();
      break;

    case 2:
      display();
      break;

    case 3:
      search();
      break;

    case 4:
      modify();
      break;

    case 5:
      del();
      break;

    case 6:
      sort();
      break;

    default:
      printf("Invalid Choice");
    }
    getch();
  }
  return 0;
}

void input() {

  system("cls");
  fp = fopen("store.txt", "ab");
  printf("Enter item Name: ");
  fflush(stdin);
  gets(s.name);
  printf("Enter the price: ");
  scanf("%s", s.price);
  printf("Enter the item id(in numbers):");
  scanf("%d", & s.id);
  printf("Enter the quantity: ");
  scanf("%d", & s.quantity);
  printf("Enter the category : ");
  scanf("%s", s.category);
  printf("Enter the name of company: ");
  scanf("%s", s.company);
  printf("Enter the date: ");
  fflush(stdin);
  gets(s.date);
  fwrite( & s, sizeof(s), 1, fp);
  printf("Record Saved Successfully");
  fclose(fp);
}

void display() {
  system("cls");
  printf("<== Item Info ==>\n\n");
  printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\t  \n", "Name", "price", "id", "quantity", "category", "date", "company");
  fp = fopen("store.txt", "rb");
  while (fread( & s, sizeof(s), 1, fp) == 1) {
    printf("%s\t %s\t %d\t %d\t\t %s\t %s\t %s\t \n", s.name, s.price, s.id, s.quantity, s.category, s.date, s.company);
  }
  fclose(fp);
  printf("Press any key to continue...");
}

void search() {
  system("cls");
  int ch;

  while (1) {

    printf("\n<== departmental store ==>\n");
    printf("<== Search ==>\n");
    printf("1.Search By Id\n");
    printf("2.Search By Name\n");
    printf("0.Back To Main Menu\n");
    printf("\n\nEnter your choice: ");
    scanf("%d", & ch);

    switch (ch) {
    case 0:
      main();
      break;

    case 1:
      searchById();
      break;

    case 2:
      searchByName();
      break;

    default:
      printf("Invalid Choice");

    }
    getch();
  }
}

void searchById() {
  system("cls");
  int rl, f = 0;
  printf("Enter Id to search: ");
  scanf("%d", & rl);
  printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\t  \n", "Name", "price", "id", "quantity", "category", "date", "company");
  fp = fopen("store.txt", "rb");
  while (fread( & s, sizeof(s), 1, fp) == 1) {
    if (rl == s.id) {
      f = 1;
      printf("%s\t %s\t %d\t %d\t\t %s\t %s\t %s\t \n", s.name, s.price, s.id, s.quantity, s.category, s.date, s.company);
      break;
    }
  }
  fclose(fp);
  if (f == 0)
    printf("Record Not Found...");
  else
    printf("Record Found Successfully...");

}

void searchByName() {
  system("cls");
  char na[30];
  int f = 0;
  printf("Enter Name to search: ");
  fflush(stdin);
  gets(na);
  printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\t  \n", "Name", "price", "id", "quantity", "category", "date", "company");
  fp = fopen("store.txt", "rb");
  while (fread( & s, sizeof(s), 1, fp) == 1) {
    if (strcmpi(na, s.name) == 0) {
      f = 1;
      printf("%s\t %s\t %d\t %d\t %s\t %s\t %s\t \n", s.name, s.price, s.id, s.quantity, s.category, s.date, s.company);
      break;
    }
  }
  fclose(fp);
  if (f == 0)
    printf("Record Not Found...");
  else
    printf("Record Found Successfully...");

}

void modify() {
  system("cls");
  int rl, f = 0;
  printf("Enter Id To Modifiy: ");
  scanf("%d", & rl);
  fp = fopen("store.txt", "rb+");
  while (fread( & s, sizeof(s), 1, fp) == 1) {
    if (rl == s.id) {
      f = 1;
      printf("Enter new item Name: ");
      fflush(stdin);
      gets(s.name);
      printf("Enter the new item id(in numbers): ");
      scanf("%s", s.id);
      printf("Enter the new price: ");
      scanf("%d", & s.price);
      printf("Enter the new quantity: ");
      scanf("%d", & s.quantity);
      printf("Enter the new category : ");
      scanf("%s", s.category);
      printf("Enter the new name of company: ");
      scanf("%s", s.company);
      printf("Enter the new date: ");
      fflush(stdin);
      gets(s.date);
      fseek(fp, -si, 1);
      fwrite( & s, sizeof(s), 1, fp);
      fclose(fp);
      break;
    }
  }
  if (f == 0)
    printf("Record Not Found...");
  else
    printf("Modified Successfully...");

}

void del() {
  system("cls");
  int rl, f = 0;
  printf("Enter id to delete: ");
  scanf("%d", & rl);

  FILE * ft;
  fp = fopen("store.txt", "rb");
  ft = fopen("temp.txt", "ab");

  while (fread( & s, sizeof(s), 1, fp) == 1) {
    if (rl == s.id) {
      f = 1;
    } else {
      fwrite( & s, sizeof(s), 1, ft);
    }

  }
  fclose(fp);
  fclose(ft);
  remove("store.txt");
  rename("temp.txt", "store.txt");

  if (f == 0)
    printf("Record Not Found...");
  else
    printf("Record Deleted Successfully...");

}

void sort() {
  system("cls");
  int ch;

  while (1) {

    printf("\n<== departmental store ==>\n");
    printf("<== Sort ==>\n");
    printf("1.Sort By id\n");
    printf("2.Sort By Name\n");
    printf("0.Back To Main Menu\n");
    printf("\n\nEnter your choice: ");
    scanf("%d", & ch);

    switch (ch) {
    case 0:
      main();
      break;

    case 1:
      sortById();
      break;

    case 2:
      sortByName();
      break;

    default:
      printf("Invalid Choice");

    }
    getch();
  }

}

void sortById() {
  system("cls");

  int c = 0, i, j;
  struct store s1[50], t;
  printf("\n<== departmental store ==>\n");
  printf("<== Sort By Id ==>\n");
  fp = fopen("store.txt", "rb");
  while (fread( & s, sizeof(s), 1, fp) == 1)
    s1[c++] = s;

  for (i = 0; i < c - 1; i++) {
    for (j = i + 1; j < c; j++) {
      if (s1[i].id > s1[j].id) {
        t = s1[i];
        s1[i] = s1[j];
        s1[j] = t;

      }
    }
  }

  printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\t  \n", "Name", "price", "id", "quantity", "category", "date", "company");

  for (i = 0; i < c; i++)
    printf("%s\t %s\t %d\t %d\t\t %s\t %s\t %s\t \n", s1[i].name, s1[i].price, s1[i].id, s1[i].quantity, s1[i].category, s1[i].date, s1[i].company);
}

void sortByName() {
  system("cls");

  int c = 0, i, j;
  struct store s1[30], t;
  printf("\n<== departmental store ==>\n");
  printf("<== Sort By Name ==>\n");
  fp = fopen("store.txt", "rb");
  while (fread( & s, sizeof(s), 1, fp) == 1)
    s1[c++] = s;

  for (i = 0; i < c - 1; i++) {
    for (j = i + 1; j < c; j++) {
      if (strcmpi(s1[i].name, s1[j].name) > 1) {
        t = s1[i];
        s1[i] = s1[j];
        s1[j] = t;

      }

    }
  }

  printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\t  \n", "Name", "price", "id", "quantity", "category", "date", "company");

  for (i = 0; i < c; i++)
    printf("%s\t %s\t %d\t %d\t\t %s\t %s\t %s\t \n", s1[i].name, s1[i].price, s1[i].id, s1[i].quantity, s1[i].category, s1[i].date, s1[i].company);
}
