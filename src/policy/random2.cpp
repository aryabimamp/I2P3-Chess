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

int Value;

int minimax(State* node, int depth, int max){
  if(depth==0){
    return node->evaluate();
  }

  if(max==1){
    Value = -1000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    auto legal = node->legal_actions;
    
    for(auto i : legal){
      State* changestate = node->next_state(i);
      Value = std::max(Value, minimax(changestate,depth-1,0));
    }
    return Value;
  }

  else if(max==0){
    Value = 1000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    auto legal = node->legal_actions;
    for(auto i : legal){
      State* changestate = node->next_state(i);
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
int player = state->player;
int w = (player==1)? 1000 : -1000;
int ev;
if(player==1){
  for(auto i : actions){

  State* changestate = state->next_state(i);

  ev = minimax(changestate,depth,1);
    if(ev <= w){
    w = ev;
    k = i;
    }
  }
}
return k;
else{
  for(auto i : actions){

  State* changestate = state->next_state(i);

  ev = minimax(changestate,depth,0);
   if(ev >= w){
   w = ev;
   k = i;
   }
  }
}
return k;
}