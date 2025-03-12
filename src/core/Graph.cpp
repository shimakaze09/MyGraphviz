//
// Created by Admin on 8/03/2025.
//

#include <MyGraphviz/Graph.h>

#include <MyGraphviz/Registry.h>

#include <sstream>

#include <cassert>

using namespace My::MyGraphviz;

Graph::Graph(std::string id, bool isDigraph)
    : Subgraph{new Registry, std::move(id)}, isDigraph{isDigraph} {}

Graph::~Graph() {
  delete registry;
}

std::string Graph::Dump() const {
  std::stringstream ss;

  ss << "strict ";

  if (isDigraph)
    ss << "di";

  ss << Subgraph::Dump(false, isDigraph, 0);

  return ss.str();
}

Graph::Graph(Graph&& g) noexcept
    : Subgraph{std::move(g)}, isDigraph{g.isDigraph} {
  g.registry = nullptr;
}

Graph& Graph::operator=(Graph&& g) noexcept {
  Subgraph::operator=(std::move(g));
  isDigraph = g.isDigraph;
  g.registry = nullptr;
  return *this;
}
