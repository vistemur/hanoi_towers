#ifndef state_node
# define state_node

#include <iostream>
#include <list>
#include <string>
#include "WorldState.h"

class StateNode {
 public:
    WorldState* worldState;
    int pathCost;
    StateNode** childStates;
    int childStatesAmount;
    StateNode* root;
    StateNode* parent;
    std::string madeFromMove;
    bool solved;

    StateNode(WorldState* worldState, int pathCost) {
        this->worldState = worldState;
        this->pathCost = pathCost;
        this->root = NULL;
        this->childStatesAmount = 0;
        this->childStates = NULL;
        this->parent = NULL;
        this->madeFromMove = "";
        this->solved = false;
    }
    
    void solve(WorldState* goalState, std::list<StateNode*>* victoryNodes) {
        if (this->solved)
            return;
        this->solved = true;
        
        this->generateNodes();
        for (int c = 0; c < this->childStatesAmount; c++) {
            if (this->childStates[c]->worldState->same(goalState) == false) {
                this->childStates[c]->solve(goalState, victoryNodes);
            } else {
                victoryNodes->push_back(this->childStates[c]);
            }
        }
    }
    
    void generateNodes() {
        int kernelsAmount = this->worldState->kernelsAmount;
        int kernelDepth = this->worldState->disksAmount;
        this->childStates = new StateNode*[kernelsAmount * kernelsAmount];
        
        for (int originKernel = 0; originKernel < kernelsAmount; originKernel++) {
            int originDepth = getTopNode(this->worldState->kernels[originKernel], kernelDepth);
            if (originDepth != -1) {
                for (int toKernel = 0; toKernel < kernelsAmount; toKernel++) {
                    if (originKernel != toKernel) {
                        int topNodeDepth = getTopNode(this->worldState->kernels[toKernel], kernelDepth);
                        if (topNodeDepth == -1) {
                            addState(originKernel, originDepth, toKernel, kernelDepth - 1);
                        } else if (topNodeDepth != 0 && this->worldState->kernels[originKernel][originDepth]->size < this->worldState->kernels[toKernel][topNodeDepth]->size) {
                            addState(originKernel, originDepth, toKernel, topNodeDepth - 1);
                        }
                    }
                }
            }
        }
    }
        
    int getTopNode(Disk** kernel, int depth) {
        for (int currentDepth = 0; currentDepth < depth; currentDepth++) {
            if (kernel[currentDepth]->size != 0) {
                return currentDepth;
            }
        }
        return -1;
    }
    
    void addState(int fromK, int fromD, int toK, int toD) {
        StateNode* newWorldState = makeNewStateNodeByReplacement(fromK, fromD, toK, toD);
        StateNode* dublicate = this->root->getDublicate(newWorldState);
        
        if (dublicate == NULL) {
            this->childStates[this->childStatesAmount] = newWorldState;
            this->childStatesAmount += 1;
        } else if (newWorldState->pathCost < dublicate->pathCost) {
            this->childStates[this->childStatesAmount] = dublicate;
            this->childStatesAmount += 1;
            dublicate->updatePathCost(newWorldState->pathCost);
            dublicate->parent = this;
            delete newWorldState;
        }
    }

    StateNode* makeNewStateNodeByReplacement(int fromK, int fromD, int toK, int toD) {
        WorldState* newWorldState;
        StateNode* newStateNode;

        newWorldState = this->worldState->copy();
        newWorldState->kernels[toK][toD]->size = newWorldState->kernels[fromK][fromD]->size;
        newWorldState->kernels[fromK][fromD]->size = 0;
        newStateNode  = new StateNode(newWorldState, this->pathCost + 1);
        newStateNode->madeFromMove = "from [" + std::to_string(fromK) + "] [" + std::to_string(fromD) + "]" + " to [" + std::to_string(toK) + "] [" + std::to_string(toD) + "]";
        newStateNode->parent = this;
        newStateNode->root = this->root;
        return newStateNode;
    }
    
    StateNode* getDublicate(StateNode* state) {
        if (this->worldState->same(state->worldState))
            return this;
        for (int c = 0; c < this->childStatesAmount; c++) {
            StateNode* dublicate = this->childStates[c]->getDublicate(state);
            if (dublicate != NULL)
                return dublicate;
        }
        return NULL;
    }
    
    void updatePathCost(int newPathCost) {
        this->pathCost = newPathCost;
        newPathCost++;
        for (int c = 0; c < this->childStatesAmount; c++) {
            if (this->childStates[c]->pathCost > newPathCost) {
                this->childStates[c]->updatePathCost(newPathCost);
                this->childStates[c]->parent = this;
            }
        }
    }
    
    void printPath() {
        if (this->parent != NULL) {
            this->parent->printPath();
        }
        std::cout << this->madeFromMove << "\n";
        worldState->print();
    }
};

# endif
