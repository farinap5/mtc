#include "LL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLTapeAddNode(Node *init, char msg) {
  Node *new = (Node *)malloc(sizeof(Node));
  new->Nex = NULL;

  if (new == NULL || msg == 0) {
    return 1;
  }
  //strcpy(newChar, msg);
  Node *aux = init;
  new->simble = msg;

  //int c = 1;
  while (aux->Nex != NULL) {
    //c++;
    aux = aux->Nex;
  }
  aux->Nex = new;
  new->Pre = aux;
  return 1;
}

Node *LLInitTape(char msg) {
  Node *new = (Node *)malloc(sizeof(Node));
  //int len = (int)strlen(msg) * (int)sizeof(char);
  //char *newChar = (char *)malloc(len);
  if (new == NULL || msg == 0) {
    return NULL;
  }
  //strcpy(newChar, msg);
  new->simble = msg;
  new->Nex = NULL;
  new->Pre = NULL;
  return new;
}

/*void LLDelNode(Node *init, int id) {
  Node *aux = init;
  while (aux->Nex != NULL) {
    if (aux->id == id) {
      break;
    }
    aux = aux->Nex;
  }
  Node *n = aux->Nex;
  Node *p = aux->Pre;

  p->Nex = n;
  n->Pre = p;
  free(aux->data);
  free(aux);
  return;
}*/

void LLShowTape(Node *init) {
  Node *aux = init;
  while (aux->Nex != NULL) {
    printf("%c", aux->simble);
    aux = aux->Nex;
  }
  printf("%c\n", aux->simble);
}

Node *LLMovePtr(Node *ptr, char dir) {
  if (dir == 'D') return ptr->Nex;
  else if (dir == 'E') return ptr->Pre;
  else {
    printf("Error: LL no direction.");
  }
}