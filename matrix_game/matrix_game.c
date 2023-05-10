#include <stdio.h>
#include <stdlib.h>

static void gen_ran_mat(int **mat) { printf("gen_ran_mat\n"); }

static void make_mat_from_file(int **mat) { printf("make_mat_from_file\n"); }

static void show_scores() { printf("show_scores\n"); }

static void take_uname(char *uname) {
  printf("Username: ");
  scanf("%s", uname);
  printf("Username is %s\n", uname);
}

static void play_manual(int **mat) { printf("play_manual\n"); }

static void play_auto(int **mat) { printf("play_auto\n"); }

static void show_game_menu(int **mat) {
  int choice = -1;
  printf("1. Manual mode\n");
  printf("2. Automatic mode\n");
  printf("3. Return to main menu\n");
  scanf("%d", &choice);
  if (choice == 1) {
    play_manual(mat);
  } else if (choice == 2) {
    play_auto(mat);
  } else if (choice == 3) {
    return;
  } else {
    printf("try again not implemented (game menu)\n");
    exit(EXIT_FAILURE);
  }
}

static void show_main_menu() {
  int choice = -1;
  printf("1. Generate random matrix\n");
  printf("2. Make matrix from file\n");
  printf("3. Show scores of users\n");
  printf("4. Exit\n");
  printf("Choice: ");
  scanf("%d", &choice);
  if (choice == 1 || choice == 2) {
    char uname[64] = {0};
    int **mat = malloc(16 * sizeof(int *));
    int i;
    for (i = 0; i < 16; ++i) {
      mat[i] = malloc(16 * sizeof(int));
    }
    if (choice == 1) {
      gen_ran_mat(mat);
    } else {
      make_mat_from_file(mat);
    }
    take_uname(uname);
    show_game_menu(mat);
    for (i = 0; i < 16; ++i) {
      free(mat[i]);
      mat[i] = 0;
    }
    free(mat);
    mat = 0;
  } else if (choice == 3) {
    show_scores();
  } else if (choice == 4) {
    exit(EXIT_SUCCESS);
  } else {
    printf("try again not implemented (main menu)\n");
    exit(EXIT_FAILURE);
  }
  printf("\n");
}

int main() {
  while (1) {
    show_main_menu();
  }
  return 0;
}
