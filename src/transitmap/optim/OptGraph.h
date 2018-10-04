// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef TRANSITMAP_GRAPH_OPTIM_OPTGRAPH_H_
#define TRANSITMAP_GRAPH_OPTIM_OPTGRAPH_H_

#include <set>
#include <string>

#include "util/graph/UndirGraph.h"
#include "transitmap/graph/Edge.h"
#include "transitmap/graph/TransitGraph.h"

using transitmapper::graph::TransitGraph;
using transitmapper::graph::Node;
using transitmapper::graph::Edge;
using util::graph::UndirGraph;

namespace transitmapper {
namespace optim {

struct EtgPart {
  Edge* etg;
  bool dir;

  EtgPart(Edge* etg, bool dir) : etg(etg), dir(dir){};
};

struct OptEdgePL {
  OptEdgePL() {};
  std::vector<EtgPart> etgs;

  EtgPart getFirstEdge() const;
  EtgPart getLastEdge() const;

  std::string getStrRepr() const;
};

struct OptNodePL {
  const Node* node;

  OptNodePL(const Node* node) : node(node){};
  OptNodePL() : node(0){};
};

typedef util::graph::Node<OptNodePL, OptEdgePL> OptNode;
typedef util::graph::Edge<OptNodePL, OptEdgePL> OptEdge;

class OptGraph : public UndirGraph<OptNodePL, OptEdgePL> {
 public:
  explicit OptGraph(TransitGraph* toOptim);

  TransitGraph* getGraph() const;

  size_t getNumNodes() const;
  size_t getNumNodes(bool topo) const;
  size_t getNumEdges() const;
  size_t getNumRoutes() const;
  size_t getMaxCardinality() const;

  double getMaxCrossPen() const;
  double getMaxSplitPen() const;

  void simplify();

  static graph::Edge* getAdjacentEdge(const OptEdge* e, const OptNode* n);

 private:
  TransitGraph* _g;

  OptNode* getNodeForTransitNode(const Node* tn) const;

  void build();
  bool simplifyStep();

  static EtgPart getFirstEdge(const OptEdge*);
  static EtgPart getLastEdge(const OptEdge*);
};
}
}

#endif  // TRANSITMAP_GRAPH_OPTIM_OPTGRAPH_H_
