//
// Created by Admin on 8/03/2025.
//

#pragma once

#include <unordered_map>
#include <unordered_set>

#include <string>

namespace My::Graphviz {
class Registrar;

class Subgraph {
 public:
  Subgraph(Registrar* registrar, std::string id)
      : registrar{registrar}, id{std::move(id)} {}

  ~Subgraph();

  const std::string& GetID() const noexcept { return id; }

  Subgraph& GetSubgraph(const std::string& subgraphID);

  Registrar& GetRegistrar() { return *registrar; }

  // return new subgraph
  Subgraph& GenSubgraph(std::string ID);

  // return *this
  Subgraph& RegisterGraphAttr(std::string key, std::string value);
  Subgraph& RegisterGraphNodeAttr(std::string key, std::string value);
  Subgraph& RegisterGraphEdgeAttr(std::string key, std::string value);

  Subgraph& DeregisterGraphAttr(const std::string& key);
  Subgraph& DeregisterGraphNodeAttr(const std::string& key);
  Subgraph& DeregisterGraphEdgeAttr(const std::string& key);

  bool HaveNode(size_t nodeIdx) const;
  bool HaveEdge(size_t edgeIdx) const;
  Subgraph& AddNode(size_t nodeIdx);
  Subgraph& AddEdge(size_t edgeIdx);
  Subgraph& EraseNode(size_t nodeIdx);
  Subgraph& EraseEdge(size_t edgeIdx);

 protected:
  Subgraph(Subgraph&&) = default;
  Subgraph& operator=(Subgraph&&) noexcept = default;

  std::string Dump(bool isSub, bool isDigraph, size_t indent) const;

  Registrar* registrar;

 private:
  std::string id;

  std::unordered_map<std::string, std::string> graphAttrs;
  std::unordered_map<std::string, std::string> graphNodeAttrs;
  std::unordered_map<std::string, std::string> graphEdgeAttrs;

  std::vector<Subgraph*> subgraphs;
  std::unordered_map<std::string, size_t> subgraphID2idx;

  std::unordered_set<size_t> nodeIndices;
  std::unordered_set<size_t> edgeIndices;
};
}  // namespace My::Graphviz
