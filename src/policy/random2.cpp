#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int minimax(State* node, int depth, bool max){
if(!node->legal_actions.size()){
      node->get_legal_actions();
  }

  if(depth==0||node->legal_actions.size()==0){
    return node->evaluate();
  }

  auto legal = node->legal_actions;

  if(max){
    int Value = -1000;
    for(auto i : legal){
      State* changestate = node->next_state(i);
      Value = std::max(Value, minimax(changestate,depth-1,0));
    }
    return Value;
  }
  else{
    int Value = 1000;
    for(auto i : legal){
      State* changestate = node->next_state(i);
      Value = std::min(Value, minimax(changestate,depth-1,0));
    }
    return Value;
  }
}

Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
    
auto actions = state->legal_actions;
Move k;

if(!state->player){
  int b = -1000;
  for(auto i : actions){

  State* changestate = state->next_state(i);

  int ev = minimax(changestate,depth-1,0);
    if(ev > b){
    b = ev;
    k = i;
    }
  }
return k;
}
else{
  int w = 1000;
  for(auto i : actions){
  
  State* changestate = state->next_state(i);

  int ev = minimax(changestate,depth-1,1);
   if(ev < w){
   w = ev;
   k = i;
   }
  }
return k;
}

}