/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    startingVertex_ = "p1-" + std::to_string(startingTokens);
    g_.insertVertex(startingVertex_);
    Vertex player1Vertex;
    Vertex player2Vertex;

    g_.insertVertex("p2-" + std::to_string(startingTokens));

    for (int token = startingTokens - 1; token >= 0; token--) {
       //std::cout << token << std::endl;
       player1Vertex = "p1-" + std::to_string(token);
       player2Vertex = "p2-" + std::to_string(token);
       g_.insertVertex(player1Vertex);
       g_.insertVertex(player2Vertex);
    }
    
    for (Vertex v : g_.getVertices()) {
       char c = v[1];
       std::string tokenString = v.substr(3);
       unsigned token = stoi(tokenString);
       if (token >= 2) {
         if (c == '1') {
            g_.insertEdge(v, "p2-" + std::to_string(token - 2));
            g_.insertEdge(v, "p2-" + std::to_string(token - 1));
            g_.setEdgeWeight(v, "p2-" + std::to_string(token - 2), 0);
            g_.setEdgeWeight(v, "p2-" + std::to_string(token - 1), 0);
         } else {
            g_.insertEdge(v, "p1-" + std::to_string(token - 2));
            g_.insertEdge(v, "p1-" + std::to_string(token - 1));
            g_.setEdgeWeight(v, "p1-" + std::to_string(token - 2), 0);
            g_.setEdgeWeight(v, "p1-" + std::to_string(token - 1), 0);
         }
       } else if (token == 1) {
         if (c == '1') {
            g_.insertEdge(v, "p2-" + std::to_string(token - 1));
            g_.setEdgeWeight(v, "p2-" + std::to_string(token - 1), 0);
         } else {
            g_.insertEdge(v, "p1-" + std::to_string(token - 1));
            g_.setEdgeWeight(v, "p1-" + std::to_string(token - 1), 0);
         }
       }
    }

}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  Vertex currVertex = startingVertex_;
  while (true) {
    if (currVertex[3] == '0') {
       //don't add any more edges since we have reached the end of our state graph
       break;
    }
    vector<Vertex> adjVertices = g_.getAdjacent(currVertex);
    int randVertex = rand() % adjVertices.size();
    path.push_back(Edge(currVertex, adjVertices[randVertex]));
    currVertex = adjVertices[randVertex];
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
  Edge finalEdge = path[path.size() - 1];
  Vertex finalEdgeDest = finalEdge.dest;
  if (finalEdgeDest == "p2-0") { //player 1 wins
     for (unsigned i = 0; i < path.size(); i++) {
       Edge currEdge = path[i];
       int weight = g_.getEdgeWeight(currEdge.source, currEdge.dest);
       if (i % 2 == 0) { //player 1's turn
          g_.setEdgeWeight(currEdge.source, currEdge.dest, weight + 1);
       } else { //player 2's turn
          g_.setEdgeWeight(currEdge.source, currEdge.dest, weight - 1);
       }
     }
  } else { //player 2 wins
     for (unsigned i = 0; i < path.size(); i++) {
       Edge currEdge = path[i];
       int weight = g_.getEdgeWeight(currEdge.source, currEdge.dest);
       if (i % 2 == 0) { //player 1's turn
          g_.setEdgeWeight(currEdge.source, currEdge.dest, weight - 1);
       } else { //player 2's turn
          g_.setEdgeWeight(currEdge.source, currEdge.dest, weight + 1);
       }
     }
  }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
