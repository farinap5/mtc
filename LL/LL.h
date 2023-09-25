#ifndef LL_H
#define LL_H

/*
 * This Linked List represents the tape.
 */

typedef struct Node {
  char simble;
  struct Node *Nex;
  struct Node *Pre;
} Node;

int LLTapeAddNode(Node *init, char simble);
Node *LLInitTape(char simble);
Node *LLMovePtr(Node *ptr, char dir);
void LLDelNode(Node *init, int id);
void LLShowTape(Node *init);

#endif // LL_H
