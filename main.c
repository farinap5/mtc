#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LL/LL.h"

int testSimble(char s, char *slist) {
  for (int i = 0; i < strlen(slist); i++) {
    if (s == slist[i] || s == '-')
      return 0;
  }
  return 1;
}

/*
  @param v Verbosity
  @param qAccept Accept state
  @param transaction transaction matrix
  @param nt Number of transactions in matrix
  @param word Word to test
  @param list of simbles
  @return
*/
int testWord(int v, char qAccept, char transaction[][16], int nt, char *word, char *slist) {
  char currentState = '1';
  Node *head = LLInitTape(word[0]);

  if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = 0x0;
  int n = strlen(word);
  
  for (int i = 1; i < n; i++) {
    LLTapeAddNode(head, word[i]);
  }
  LLTapeAddNode(head,'-');
  Node *ptr = head;

  int error = 0;
  while (currentState != qAccept) {
    int aux = 0;
    if (testSimble(ptr->simble, slist) != 0) {
      printf("Error: Simble %c from %s not defined in simbles\n", ptr->simble, word);
      return 1;
    }

    for (int i=0; i < nt; i++) {
      if (currentState == transaction[i][0] && ptr->simble == transaction[i][2]) {
        if (testSimble(transaction[i][4], slist) != 0) {
          printf("Error: Simble %c not defined!\n", transaction[i][4]);
          return 1;
        }

        // 1 a x D 2
        // 0 2 4 6 8
        ptr->simble = transaction[i][4];
        ptr = LLMovePtr(ptr,transaction[i][6]);
        char pstate = currentState;
        currentState = transaction[i][8];
        if (v > 0)
          printf("q:%c Read:%c Write:%c Move:%c Newq:%c\n", 
            pstate, transaction[i][2], transaction[i][4], 
            transaction[i][6], currentState);
        if (v > 1)
          LLShowTape(head);
        aux = 1;
        break;
      }
    }
    /*
      If reach here with aux == 0, then no iteration has been concluded and the language
      did not accept.
    */
    if (aux == 0)
      return 1;
  }
  return 0;
}


int main(int argc, char *argv[]) {
  char *fname = "file.txt";
  FILE *file;
  char t[4];
  char simbles[16];
  char qAccept;
  char ntransactions[10];
  int nt;
  int ttt; // tapes to test
  int v = 0;

  for (int i=0; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) {
      fname = argv[i+1];
    } else if (strcmp(argv[i], "-h") == 0) {
      printf("Usage: ./a.out -f file.txt\n");
      return 0;
    } else if (strcmp(argv[i], "-v") == 0) {
      v = atoi(argv[i+1]);
    }

  }

  printf("Open file %s\n",fname);
  file = fopen(fname, "r");
  if (!file) {
    printf("Error: No file found.\n");
    return 0;
  }

  fgets(simbles, 16, file);
  printf("Simbles: %s",simbles);
  
  qAccept = getc(file);
  printf("Accept on %c\n",qAccept);

  fscanf(file, "%2d", &nt);
  printf("%d Transactions\n",nt);

  char transaction[nt][16];
  // Write newline to t
  fgets(t, 16, file);
  // Write transactions to the matrix
  for (int i=0; i < nt; i++) {
    fgets(transaction[i], 16, file);
  }

  fscanf(file, "%1d", &ttt);
  printf("%d tapes to test\n",ttt);
  //char words[ttt][64];
  fgets(t, 16, file);
  for (int i=0; i < ttt; i++) {
    char word[64];
    fgets(word, 64, file);
    int a = testWord( v, qAccept, transaction, nt, word, simbles);
    if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = 0x0;
    if (a == 0) {
      printf("%s OK\n",word);
    } else {
      printf("%s not OK\n",word);
    }
  }
  return 0;
}
