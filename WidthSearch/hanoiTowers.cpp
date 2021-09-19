#include <iostream>
#include <list>
#include "StateNode.h"
#include "WorldState.h"

class InitialWorldState: public WorldState {
 public:

     InitialWorldState(): WorldState() {
         for (int k = 0; k < this->kernelsAmount; k++) {
             for (int d = 0; d < this->disksAmount; d++) {
                 if (k == 0) {
                     this->kernels[k][d]->size = d + 1;
                 }
             }
         }
     }
};

class GoalWorldState: public WorldState {
 public:

     GoalWorldState(): WorldState() {
         for (int k = 0; k < this->kernelsAmount; k++) {
             for (int d = 0; d < this->disksAmount; d++) {
                 if (k == 2) {
                     this->kernels[k][d]->size = d + 1;
                 }
             }
         }
     }
};

class Solver {
    
    WorldState* initialState;
    WorldState* goalState;
    bool solved;
    StateNode* rootNode;
    StateNode* victoryNode;

 public:

    Solver(WorldState* initialState, WorldState* goalState) {
        this->solved = false;
        this->initialState = initialState;
        this->goalState = goalState;
        this->rootNode = new StateNode(this->initialState, 0);
        this->rootNode->root = this->rootNode;
        this->victoryNode = NULL;
    }

     void solve() {
         int maxDepth = 0;
         while (this->victoryNode == NULL) {
             this->rootNode->solve(goalState, &victoryNode, maxDepth);
             maxDepth++;
         }
         this->solved = true;
         victoryNode->printPath();
     }
};

int main() {
    WorldState* initialState;
    WorldState* goalWorldState;
    Solver* solver;

    initialState = new InitialWorldState();
    goalWorldState = new GoalWorldState();
    solver = new Solver(initialState, goalWorldState);
    //initialState->print();
    //goalWorldState->print();
    solver->solve();
    return 0;
}
