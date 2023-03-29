#ifndef Node_H
#define Node_H

/*
 * Node types:
 * -1: Undefined
 * 0: Exact
 * 1: Lower bound
 * 2: Upper bound
 */
struct Node {
  int move;
  int value;
  int node_type;
};

int getMove(const Node &node);
int getValue(const Node &node);
int getNodeType(const Node &node);
Node makeNode(int move, int value, int node_type);

#endif