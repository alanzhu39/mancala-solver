#include "Node.h"

int getMove(const Node &node) {
  return node.move;
}

int getValue(const Node &node) {
  return node.value;
}

int getNodeType(const Node &node) {
  return node.node_type;
}

Node makeNode(int move, int value, int node_type) {
  return {move, value, node_type};
}
