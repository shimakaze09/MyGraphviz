//
// Created by Admin on 8/03/2025.
//

#include <MyGraphviz/MyGraphviz.h>

#include <iostream>

using namespace My;

using namespace std;

int main() {
  Graphviz::Graph graph("hello world", true);

  graph.AddEdge("a", "b").AddEdge("a", "c").AddEdge("b", "d").AddEdge("c", "d");

  cout << graph.Dump() << endl;

  return 0;
}
