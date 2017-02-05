// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#include <cassert>
#include <vector>
#include "Edge.h"
#include "Node.h"

using namespace transitmapper;
using namespace graph;

// _____________________________________________________________________________
Edge::Edge(Node* from, Node* to, geo::PolyLine pl, double w,
    double s) : _from(from), _to(to), _width(w), _spacing(s) {
  setGeom(pl);
}

// _____________________________________________________________________________
Node* Edge::getFrom() const {
  return _from;
}

// _____________________________________________________________________________
Node* Edge::getTo() const {
  return _to;
}

// _____________________________________________________________________________
const std::vector<RouteOccurance>& Edge::getTripsUnordered()
const {
  return _routes;
}

// _____________________________________________________________________________
std::vector<RouteOccurance>* Edge::getTripsUnordered() {
  return &_routes;
}

// _____________________________________________________________________________
RouteOccurance* Edge::getTripsForRoute(const Route* r) const {
  for (size_t i = 0; i < _routes.size(); i++) {
    RouteOccurance* to = const_cast<RouteOccurance*>(&_routes[i]);
    if (to->route == r) {
      return to;
    }
  }
  return 0;
}

// _____________________________________________________________________________
RouteOccWithPos Edge::getTripsForRouteUnder(const Route* r,
    const std::vector<size_t> ordering) const {
  for (size_t i = 0; i < _routes.size(); i++) {
    const RouteOccurance& to = _routes[i];
    if (to.route == r) {
      size_t pos = std::find(ordering.begin(), ordering.end(), i) - ordering.begin();
      return std::pair<RouteOccurance*, size_t>(const_cast<RouteOccurance*>(&to), pos);
    }
  }
  return std::pair<RouteOccurance*, size_t>(0, 0);
}

// _____________________________________________________________________________
void Edge::addRoute(const Route* r, const Node* dir) {
  _routes.push_back(RouteOccurance(r, dir));
}

// _____________________________________________________________________________
bool Edge::containsRoute(const Route* r) const {
  if (getTripsForRoute(r)) return true;

  return false;
}

// _____________________________________________________________________________
size_t Edge::getCardinality() const {
  return _routes.size();
}

// _____________________________________________________________________________
double Edge::getWidth() const {
  return _width;
}

// _____________________________________________________________________________
double Edge::getSpacing() const {
  return _spacing;
}

// _____________________________________________________________________________
double Edge::getTotalWidth() const {
  return getWidth() * _routes.size() + getSpacing() * (_routes.size() - 1);
}

// _____________________________________________________________________________
std::vector<const Route*> Edge::getSharedRoutes(const Edge& e)
const {
  std::vector<const Route*> ret;
  for (auto& to : _routes) {
    if (e.containsRoute(to.route)) ret.push_back(to.route);
  }

  return ret;
}

// _____________________________________________________________________________
const geo::PolyLine& Edge::getGeom() const {
  return _geom;
}

// _____________________________________________________________________________
void Edge::setGeom(const geo::PolyLine& p) {
  _geom = p;
}