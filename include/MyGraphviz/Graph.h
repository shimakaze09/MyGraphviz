//
// Created by Admin on 8/03/2025.
//

#pragma once

#include "Subgraph.h"

namespace My::MyGraphviz {
class Graph : public Subgraph {
 public:
  Graph(std::string id, bool isDigraph = false);
  ~Graph();

  Graph(Graph&&) noexcept;
  Graph& operator=(Graph&&) noexcept;

  std::string Dump() const;

  bool IsDigraph() const noexcept { return isDigraph; }

 private:
  bool isDigraph;
};
}  // namespace My::MyGraphviz
