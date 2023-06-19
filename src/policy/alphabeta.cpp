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

int value;

int abpruning(State* node, int depth, int max, int alpha, int beta){
  if(depth==0){
    return node->evaluate();
  }

  if(max==1){
    value = -1000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    auto legal = node->legal_actions;
    
    for(auto i : legal){
      State* changestate = node->next_state(i);
      value = std::max(value, abpruning(changestate,depth-1,0,alpha,beta));
      alpha = std::max(alpha, value);
      if(alpha>=beta){
        break;
      }
    }
    return value;
  }

  else if(max==0){
    value = 1000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    auto legal = node->legal_actions;
    for(auto i : legal){
      State* changestate = node->next_state(i);
      value = std::min(value, abpruning(changestate,depth-1,1,alpha,beta));
      beta = std::min(beta, value);
      if(beta<=alpha){
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
int w = -100;
int ev;
for(auto i : actions){
  
  State* changestate = state->next_state(i);

  ev = abpruning(changestate,depth,0, -1000, 1000);

  if(ev >= w){
    w = ev;
    k = i;
  }

}
  return k;
}