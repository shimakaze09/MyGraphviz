# MyGraphviz

**My** **Graphviz** C++ wrapper

[![repo-size](https://img.shields.io/github/languages/code-size/shimakaze09/MyGraphviz?style=flat)](https://github.com/shimakaze09/MyGraphviz/archive/main.zip) [![tag](https://img.shields.io/github/v/tag/shimakaze09/MyGraphviz)](https://github.com/shimakaze09/MyGraphviz/tags) [![license](https://img.shields.io/github/license/shimakaze09/MyGraphviz)](LICENSE)

## Example

 ```c++
 #include <MyGraphviz/MyGraphviz.h>
 #include <iostream>
 
 using namespace My;
 using namespace std;
 
 int main() {
   Graphviz::Graph graph("hello world", true);
 
   auto& registrar = graph.GetRegistrar();
 
   auto v_a = registrar.RegisterNode("a");
   auto v_b = registrar.RegisterNode("b");
   auto v_c = registrar.RegisterNode("c");
   auto v_d = registrar.RegisterNode("d");
 
   auto e_ab = registrar.RegisterEdge(v_a, v_b);
   auto e_ac = registrar.RegisterEdge(v_a, v_c);
   auto e_bd = registrar.RegisterEdge(v_b, v_d);
   auto e_cd = registrar.RegisterEdge(v_c, v_d);
 
   graph
     .AddEdge(e_ab)
     .AddEdge(e_ac)
     .AddEdge(e_bd)
     .AddEdge(e_cd);
 
   cout << graph.Dump() << endl;
 }
 ```

**other example**

- [attribute](src/test/01_attr/main.cpp)
- [subgraph](src/test/02_subgraph/main.cpp) 
