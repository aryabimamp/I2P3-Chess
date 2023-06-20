#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int abpruning(State* node, int depth, int max, int alpha, int beta){
  if(!node->legal_actions.size()){
      node->get_legal_actions();
  }

  if(depth==0||node->legal_actions.size()==0){
    return node->evaluate();
  }

  auto legal = node->legal_actions;
  int value = (max) ? -1000 : 1000;

  if(max){
    for(auto moves : legal){
      State* changestate = node->next_state(moves);
      value = std::max(value, abpruning(changestate,depth-1,0,alpha,beta));
      alpha = std::max(alpha, value);
      if(alpha>beta){
        break;
      }
    }
    return value;
  }
  else{
    for(auto moves : legal){
      State* changestate = node->next_state(moves);
      value = std::min(value, abpruning(changestate,depth-1,1,alpha,beta));
      if(alpha<beta){
        break;
      }
    }
    return value;
  }

}

Move Alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
    
auto actions = state->legal_actions;
Move k;
int whiteorblack = (!state->player) ? -1000 : 1000;

if(!state->player){
  for(auto moves : actions){

  State* changestate = state->next_state(moves);

  int eval = abpruning(changestate,depth-1,0,-1000,1000);
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

  int eval = abpruning(changestate,depth-1,1,-1000,1000);
   if(eval < whiteorblack){
   whiteorblack = eval;
   k = moves;
   }
  }
return k;
}

}