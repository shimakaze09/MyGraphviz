//
// Created by Admin on 8/03/2025.
//

#include <MyGraphviz/core.h>

#include <sstream>

#include <cassert>

using namespace My;

Graphviz::Subgraph::~Subgraph() {
  for (auto subgraph : subgraphs)
    delete subgraph;
}

Graphviz::Subgraph& Graphviz::Subgraph::GetSubgraph(
    const std::string& subgraphID) {
  return *subgraphs[subgraphID2idx.find(subgraphID)->second];
}

Graphviz::Subgraph& Graphviz::Subgraph::RegisterGraphAttr(std::string key,
                                                          std::string value) {
  graphAttrs.emplace_back(std::move(key), std::move(value));
  return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::RegisterGraphNodeAttr(
    std::string key, std::string value) {
  graphNodeAttrs.emplace_back(std::move(key), std::move(value));
  return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::RegisterGraphEdgeAttr(
    std::string key, std::string value) {
  graphEdgeAttrs.emplace_back(std::move(key), std::move(value));
  return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::GenSubgraph(std::string ID) {
  subgraphID2idx[ID] = subgraphs.size();
  auto newSubGraph = new Subgraph{registrar, std::move(ID)};
  subgraphs.push_back(newSubGraph);
  return *subgraphs.back();
}

Graphviz::Subgraph& Graphviz::Subgraph::AddNode(size_t nodeIdx) {
  nodeIndices.push_back(nodeIdx);
  return *this;
}

Graphviz::Subgraph& Graphviz::Subgraph::AddEdge(size_t edgeIdx) {
  edgeIndices.push_back(edgeIdx);
  return *this;
}

std::string Graphviz::Subgraph::Dump(bool isSub, bool isDigraph,
                                     size_t indent) const {
  std::stringstream ss;

  std::string eop = isDigraph ? "->" : "--";

  auto qoute = [](const std::string& id) {
    return "\"" + id + "\"";
  };

  auto print_indent = [&]() -> std::stringstream& {
    for (size_t i = 0; i < indent; i++)
      ss << "  ";
    return ss;
  };

  print_indent();

  if (isSub)
    ss << "sub";

  ss << "graph " << qoute(id) << " {" << std::endl;

  indent++;

  auto dumpAttrs = [&](std::string_view head, const auto& attrs) {
    if (attrs.empty())
      return;

    print_indent() << head << " [" << std::endl;
    indent++;
    for (const auto& [key, value] : attrs)
      print_indent() << key << " = " << "\"" << value << "\"" << std::endl;
    indent--;
    print_indent() << "]" << std::endl;
  };

  dumpAttrs("graph", graphAttrs);
  dumpAttrs("node", graphNodeAttrs);
  dumpAttrs("edge", graphEdgeAttrs);

  for (const auto& subgraph : subgraphs)
    ss << subgraph->Dump(true, isDigraph, indent);

  const auto& nodeIDs = registrar->GetNodes();
  const auto& edgeIDs = registrar->GetEdges();
  const auto& nodeAttrs = registrar->GetNodeAttrs();
  const auto& edgeAttrs = registrar->GetEdgeAttrs();

  for (size_t nodeIdx : nodeIndices) {
    const auto& nodeID = nodeIDs[nodeIdx];
    auto target = nodeAttrs.find(nodeIdx);
    if (target == nodeAttrs.end())
      print_indent() << nodeID << std::endl;
    else
      dumpAttrs(nodeID, target->second);
  }

  for (size_t edgeIdx : edgeIndices) {
    const auto& [lhs, rhs] = edgeIDs[edgeIdx];
    std::string head =
        qoute(nodeIDs[lhs]) + " " + eop + " " + qoute(nodeIDs[rhs]);
    auto target = edgeAttrs.find(edgeIdx);
    if (target == edgeAttrs.end())
      print_indent() << head << std::endl;
    else
      dumpAttrs(head, target->second);
  }

  indent--;
  print_indent() << "}" << std::endl;

  return ss.str();
}

Graphviz::Graph::Graph(std::string id, bool isDigraph)
    : Subgraph{new Registrar, std::move(id)}, isDigraph{isDigraph} {}

Graphviz::Graph::~Graph() {
  delete registrar;
}

std::string Graphviz::Graph::Dump() const {
  std::stringstream ss;

  ss << "strict ";

  if (isDigraph)
    ss << "di";

  ss << Subgraph::Dump(false, isDigraph, 0);

  return ss.str();
}
