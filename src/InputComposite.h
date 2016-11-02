#ifndef INPUTCOMPOSITE_H
#define INPUTCOMPOSITE_H

#include "Input.h"

class InputComposite : public Input {
    protected:
        vector<Input* > vec;
    public:
        InputComposite() { }
        bool valid(Input* in) {
            
        }
        
        void add(Input* in) {
            
        }
        
        void rm(Input* in) {
            
        }
        
        Input* getInput() {
            
        }
        
        void separate(Input* in) {
            
        }
        
        bool endOfLine() {
            
        }
};

#endif