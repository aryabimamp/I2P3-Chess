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
  int Value = (max) ? -1000 : 1000;

  if(max){
    for(auto moves : legal){
      State* changestate = node->next_state(moves);
      Value = std::max(Value, minimax(changestate,depth-1,0));
    }
    return Value;
  }
  else{
    for(auto moves : legal){
      State* changestate = node->next_state(moves);
      Value = std::min(Value, minimax(changestate,depth-1,1));
    }
    return Value;
  }
}

Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
    
auto actions = state->legal_actions;
Move k;

int whiteorblack = (!state->player) ? -1000 : 1000;

if(!state->player){
  for(auto moves : actions){

  State* changestate = state->next_state(moves);

  int eval = minimax(changestate,depth-1,0);
    if(eval > whiteorblack){
    whiteorblack = eval;
    k = moves;
    }
  }
return k;
}
else{
  for(auto moves : actions){
  
  State* changestate = state->next_state(moves);

  int eval = minimax(changestate,depth-1,1);
   if(eval < whiteorblack){
   whiteorblack = eval;
   k = moves;
   }
  }
return k;
}

}