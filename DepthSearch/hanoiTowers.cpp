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
    std::list<StateNode*> victoryNodes;

 public:

    Solver(WorldState* initialState, WorldState* goalState) {
        this->solved = false;
        this->initialState = initialState;
        this->goalState = goalState;
        this->rootNode = new StateNode(this->initialState, 0);
        this->rootNode->root = this->rootNode;
    }

     void solve() {
         this->rootNode->solve(goalState, &victoryNodes);
         this->solved = true;
         StateNode* lowestPriceNode = NULL;
         int sulutionsAmount = 0;
         
         for (std::list<StateNode*>::iterator i = victoryNodes.begin(); i != victoryNodes.end(); i++) {
             if (lowestPriceNode == NULL || (*i)->pathCost < lowestPriceNode->pathCost) {
                 lowestPriceNode = *i;
             }
             sulutionsAmount++;
         }
         
         //std::cout << "solutions: " << sulutionsAmount << std::endl;
         if (lowestPriceNode != NULL) {
             lowestPriceNode->printPath();
         }
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
