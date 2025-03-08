//
// Created by Admin on 8/03/2025.
//

#include <MyGraphviz/MyGraphviz.h>

#include <iostream>

using namespace My;

using namespace std;

int main() {
  Graphviz::Graph g("hello world", true);

  auto a = g.AddNode("a");
  auto b = g.AddNode("b");
  auto c = g.AddNode("c");
  auto d = g.AddNode("d");

  g.AddEdge(a, b);
  g.AddEdge(a, c);
  g.AddEdge(b, d);
  g.AddEdge(c, d);

  cout << g.Dump() << endl;

  return 0;
}
