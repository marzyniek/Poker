#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "eval.h"
#include "structures.h"
#include "constants.h"
#include "parse_input.h"

/* Compares 2 cards provided by pointers.
 * Returns the difference of card values. */
int card_cmp(const void *p1, const void *p2) {
    struct card card_1 = *(struct card *) p1;
    struct card card_2 = *(struct card *) p2;
    
    if (card_1.value < card_2.value) {
        return -1;
    }
    if (card_1.value > card_2.value) {
        return 1;
    }
    return 0;
}

// For every player combines cards from the table <table> and cards from player's hand and puts it into <complete_hands>
void set_complete_hands(struct card complete_hands[MAX_PLAYERS][COMPLETE_HAND_SIZE], 
                        struct card hands[MAX_PLAYERS][HAND_SIZE], struct card *table, int players) {
    for (int i = 0; i < players; i++) {
        for (int j = 0; j < 5; j++) {
            complete_hands[i][j] = table[j];
        }
        complete_hands[i][5] = hands[i][0];
        complete_hands[i][6] = hands[i][1];
        qsort(complete_hands[i], COMPLETE_HAND_SIZE, sizeof(struct card), card_cmp);
    }
}

/*  Updates the counts of each card value and suit
 *  The <values> array is updated such that 'values[value]' holds the number of cards with that value in the player's hand
 *  Same for suits */
void set_count(struct card complete_hand[COMPLETE_HAND_SIZE], int values[VALUES], int suits[SUITS]) {
    for (int i = 0; i < COMPLETE_HAND_SIZE; i++) {
        values[complete_hand[i].value]++;
        suits[complete_hand[i].suit]++;
    }
}


int get_max_value(int possible_winners[MAX_PLAYERS][EVAL_SIZE], size_t length, int index) {
    int max_value = -1;
    for (size_t i = 0; i < length; i++) {
        if (possible_winners[i][index] > max_value) {
            max_value = possible_winners[i][index];
        }
    }
    return max_value;
}

int check_state(int possible_winners[MAX_PLAYERS][EVAL_SIZE], int players) {
    int max_value;
    int count = 0;
    int winner = -1;
    
    for (int i = 0; i < players; i++) {
        if (possible_winners[i][0] > -1) {
            count++;
        }
    }
    
    if (count == 0) {
        return winner;  
    } 

    count = 0;
    
    for (int index = 0; index < EVAL_SIZE; index++) {
        max_value = get_max_value(possible_winners, (size_t) players, index);
        for (int player = 0; player < players; player++) {
            if (possible_winners[player][index] == max_value) {
                count++;
                winner = player + 1;
            }
        }
    // Only one player has winning hand
        if (count == 1) {
            return winner;
        }
        count = 0;
    }
    return 0;
}

int compare_hands(struct card complete_hands[MAX_PLAYERS][COMPLETE_HAND_SIZE], int players) {
    CompareFunctionPointer compare_functions[] = {
            &fill_straight_flush,
            &fill_poker,
            &fill_full_house,
            &fill_flush,
            &fill_straight,
            &fill_triplet,
            &fill_two_pair,
            &fill_pair,
            &fill_highest_cards,
            NULL
    };
    
    int possible_winners[MAX_PLAYERS][EVAL_SIZE];
    memset(possible_winners, -1, sizeof possible_winners);
    
    int values[MAX_PLAYERS][VALUES] = {{0}};
    int suits[MAX_PLAYERS][SUITS] = {{0}};
    
    for (int i = 0; i < players; i++) {
        set_count(complete_hands[i], values[i], suits[i]);
    }
    
    for (int func_index = 0; compare_functions[func_index] != NULL; func_index++) {
        
        for (int player = 0; player < players; player++) {
            compare_functions[func_index](values[player], suits[player], complete_hands[player], possible_winners[player]);
        }
        
        int state = check_state(possible_winners, players);
        if (state > -1) {
            return state;
        }
    }
    return -1;
}

int get_outcome(struct card hands[MAX_PLAYERS][HAND_SIZE], struct card *table, int players) {
    struct card complete_hands[MAX_PLAYERS][COMPLETE_HAND_SIZE];
    set_complete_hands(complete_hands, hands, table, players);
    
    return compare_hands(complete_hands, players);
}

int main(int argc, char **argv) {

    int players = parse_players(argc, argv);
    if (players == 0) {
        return 0;
    }
    struct card hands[MAX_PLAYERS][HAND_SIZE];
    struct card table[TABLE_SIZE];
    process_output_value return_value;
    while ((return_value = read_input(hands, table, players)) == INPUT_OK) {
        int winner = get_outcome(hands, table, players);
        
        if (winner == 0) {
            printf("Draw\n");
        }
        else {
            printf("Player %d\n", winner);
        }
    }
    if (return_value == INPUT_ERROR) {
        return 1;
    }
    return 0;
}
