//
// Created by Admin on 8/03/2025.
//

#include <MyGraphviz/Registrar.h>

#include <cassert>

using namespace My::Graphviz;

bool Registrar::IsRegisteredNode(const std::string& ID) const {
  return id2idx.find(ID) != id2idx.end();
}

bool Registrar::IsRegisteredEdge(size_t lhs, size_t rhs) const {
  auto target_lhs = node2edge.find(lhs);
  if (target_lhs == node2edge.end())
    return false;

  auto target_rhs = target_lhs->second.find(rhs);
  if (target_rhs == target_lhs->second.end())
    return false;

  return true;
}

bool Registrar::IsRegisteredEdge(const std::string& lhsID,
                                 const std::string& rhsID) const {
  size_t lhs = GetNodeIdx(lhsID);
  size_t rhs = GetNodeIdx(rhsID);

  return IsRegisteredEdge(lhs, rhs);
}

size_t Registrar::GetNodeIdx(const std::string& ID) const {
  assert(IsRegisteredNode(ID));
  return id2idx.find(ID)->second;
}

size_t Registrar::GetEdgeIdx(const std::string& lhsID,
                             const std::string& rhsID) const {
  size_t lhs = GetNodeIdx(lhsID);
  size_t rhs = GetNodeIdx(rhsID);

  assert(IsRegisteredEdge(lhs, rhs));

  return node2edge.find(lhs)->second.find(rhs)->second;
}

size_t Registrar::RegisterNode(std::string ID) {
  size_t idx = nodes.size();
  id2idx[ID] = idx;
  nodes.push_back(std::move(ID));
  return idx;
}

size_t Registrar::RegisterEdge(size_t lhs, size_t rhs) {
  size_t idx = edges.size();
  edges.emplace_back(lhs, rhs);
  node2edge[lhs][rhs] = idx;
  return idx;
}

Registrar& Registrar::RegisterNodeAttr(size_t nodeIdx, std::string key,
                                       std::string value) {
  nodeAttrs[nodeIdx].emplace(std::move(key), std::move(value));
  return *this;
}

Registrar& Registrar::RegisterEdgeAttr(size_t edgeIdx, std::string key,
                                       std::string value) {
  edgeAttrs[edgeIdx].emplace(std::move(key), std::move(value));
  return *this;
}

Registrar& Registrar::DeregisterNodeAttr(size_t nodeIdx,
                                         const std::string& key) {
  nodeAttrs[nodeIdx].erase(key);
  return *this;
}

Registrar& Registrar::DeregisterEdgeAttr(size_t edgeIdx,
                                         const std::string& key) {
  edgeAttrs[edgeIdx].erase(key);
  return *this;
}
