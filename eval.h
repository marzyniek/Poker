#include "structures.h"
#include "constants.h"

#ifndef EVAL_H
#define EVAL_H

/* fill_* functions fill the array <best_hand> with cards that are part of the specific card combination, 
 * if the specific combination of cards is not present in <complete_hand> function does not modify anything  */


void fill_straight_flush(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_straight(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_flush(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_group(int group, int values[VALUES], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_pair(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_triplet(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_poker(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_full_house(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_two_pair(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

void fill_highest_cards(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]);

/* Returns the value that is present in the array <values> exactly <group> times and is not present in the array <ignored_values> */
int get_group(int group, int values[VALUES], int ignored_values[COMPLETE_HAND_SIZE]);

/* Sets new <value> to ignore in the array <ignored_values> */
void add_ignored_value(int value, int ignored_values[COMPLETE_HAND_SIZE]);

/* Fills the rest of array <bast_hand> with cards from <complete_hand> that have the highest value and are not present in <ignored_values> */
void fill_with_highest_card_values(int best_hand[EVAL_SIZE], int to_fill, struct card *complete_hand, int ignored_values[COMPLETE_HAND_SIZE]);

/* Returns true if value is present in the array <ignored_values> */
bool is_ignored(int value, int ignored_values[COMPLETE_HAND_SIZE]);

#endif