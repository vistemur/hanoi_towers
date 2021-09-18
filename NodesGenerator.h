#ifndef nodes_generator
#define nodes_generator

#include "StateNode.h"

class NodesGenerator {
 public:
     
    void generateNodes(StateNode* state) {
         state->childStates = new StateNode*[1];
         state->childStates[0] = new StateNode();
        for (int k = 0; k < state->childStates[0]->kernelsAmount; k++) {
            for (int d = 0; d < state->childStates[0]->disksAmount; d++) {
                if (k == 2) {
                    state->childStates[0]->kernels[k][d]->size = state->childStates[0]->disksAmount - d;
                }
            }
        }
         state->childStatesAmount = 1;
    }
};

#endif
