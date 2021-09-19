#ifndef world_state
#define world_state

#include <iostream>

class Disk {
 public:

    int size;

    Disk(int size) {
        this->size = size;
    }
};

class WorldState {
 public:
     Disk*** kernels;
     int kernelsAmount;
     int disksAmount;

     WorldState() {
         this->kernelsAmount = 3;
         this->disksAmount = 3;

         this->kernels = new Disk** [this->kernelsAmount];
         for (int k = 0; k < kernelsAmount; k++) {
             this->kernels[k] = new Disk* [this->disksAmount];
             for (int d = 0; d < this->disksAmount; d++) {
                 this->kernels[k][d] = new Disk(0);
             }
         }
     }

     void print() {
         for (int d = 0; d < this->disksAmount; d++) {
             for (int k = 0; k < this->kernelsAmount; k++) {
                 std::cout << this->kernels[k][d]->size << "\t";
             }
             std::cout << std::endl;
         }
     }

     WorldState* copy() {
         WorldState* copyWorldState;

         copyWorldState = new WorldState();
         for (int k = 0; k < this->kernelsAmount; k++)
             for (int d = 0; d < this->disksAmount; d++) {
                 copyWorldState->kernels[k][d]->size = this->kernels[k][d]->size;
             }
         return copyWorldState;
     }
    
    bool same(WorldState* otherWorldState) {
        for (int d = this->disksAmount - 1; d >= 0; d--)
            for (int k = 0; k < this->kernelsAmount; k++)
                if (this->kernels[k][d]->size != otherWorldState->kernels[k][d]->size)
                    return false;
        return true;
    }
};

#endif
