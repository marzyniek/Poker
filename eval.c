#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "eval.h"
#include "constants.h"
#include "structures.h"

void add_ignored_value(int value, int ignored_values[COMPLETE_HAND_SIZE]) {
    for (int i = 0; i < COMPLETE_HAND_SIZE; i++) {
        if (ignored_values[i] == value) {
            return;
        }
        if (ignored_values[i] == -1) {
            ignored_values[i] = value;
            return;
        }
    }
}

bool is_ignored(int value, int ignored_values[COMPLETE_HAND_SIZE]) {
    for (int i = 0; i < COMPLETE_HAND_SIZE; i++) {
        if (ignored_values[i] == -1) {
            return false;
        }
        if (ignored_values[i] == value) {
            return true;
        }
    }
    return false;
}

void fill_with_highest_card_values(int best_hand[EVAL_SIZE], int to_fill, struct card *complete_hand, int ignored_values[COMPLETE_HAND_SIZE]) {
    int index = 6;
    while (to_fill > 0 && index >= 0) {
        if (!is_ignored(complete_hand[index].value, ignored_values)) {
            best_hand[5 - to_fill] = complete_hand[index].value;
            to_fill--;
        }
        index--;
    }
}

void fill_straight_flush(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) values;

    //Get the suit of the straight-flush
    int suit = -1;
    for (int i = 0; i < 4; ++i) {
        if (suits[i] >= 5) {
            suit = i;
        }
    }
    if (suit == -1) {
        return;
    }

    int count = 0;
    struct card prev_card = {-2, -2};
    int highest_value = -1;

    //If ace is the first card of the straight-flush set is as the <prev_card>
    for (int i = 0; i < 4; ++i) {
        if (complete_hand[6 - i].value == 12 && complete_hand[6 - i].suit == suit) {
            prev_card.value = -1;
            prev_card.suit = suit;
            break;
        }
    }

    for (int i = 0; i < 7; ++i) {
        if (complete_hand[i].suit != suit) {
            continue;
        }
        
        if (complete_hand[i].value - 1 == prev_card.value) {
            count++;
            if (count >= 4) {
                highest_value = complete_hand[i].value;
            }
        } 
        else {
            count = 0;
        }
        
        prev_card = complete_hand[i];
    }

    if (highest_value == -1) {
        return;
    }

    for (int i = 0; i < 5; ++i) {
        best_hand[i] = highest_value - i;
    }
}

void fill_straight(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) suits;
    (void) complete_hand;

    int count = 0;
    int last = -1;
    // Ace is present
    if (values[12]) {
        count++;
    }
    for (int i = 0; i < 13; ++i) {
        if (values[i] >= 1) {
            count++;
        } else {
            count = 0;
        }
        
        if (count >= 5) {
            last = i;
        }
    }
    for (int i = 0; i < 5; i++) {
        best_hand[i] = last - i;
    }
}

void fill_flush(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) values;

    for (int i = 0; i < 4; i++) {
        if (suits[i] < 5) {
            continue;
        }
        
        int count = 0;
        for (int j = 0; j < 7; j++) {
            if (complete_hand[6 - j].suit == i) {
                best_hand[count] = complete_hand[6 - j].value;
                count++;
            }
            if (count >= 5) {
                break;
            }
        }
        return;
    }
}

int get_group(int group, int values[VALUES], int ignored_values[COMPLETE_HAND_SIZE]) {
    for (int i = VALUES - 1; i >= 0; i--) {
        if (values[i] == group && !is_ignored(i, ignored_values)) {
            return i;
        }
    }
    return -1;
}

void fill_group(int group, int values[VALUES], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    
    int ignore[COMPLETE_HAND_SIZE];
    memset(ignore, -1, COMPLETE_HAND_SIZE * sizeof(int));
    
    int value = get_group(group, values, ignore);

    if (value == -1) {
        return;
    }
 
    add_ignored_value(value, ignore);

    for (int i = 0; i < group; i++) {
        best_hand[i] = value;
    }

    fill_with_highest_card_values(best_hand, EVAL_SIZE - group, complete_hand, ignore);
}

void fill_pair(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) suits;

    fill_group(2, values, complete_hand, best_hand);

}

void fill_triplet(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) suits;

    fill_group(3, values, complete_hand, best_hand);
}

void fill_poker(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) suits;
    fill_group(4, values, complete_hand, best_hand);
}

void fill_full_house(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) suits;
    (void) complete_hand;

    int ignore[COMPLETE_HAND_SIZE];
    memset(ignore, -1, COMPLETE_HAND_SIZE * sizeof(int));
    
    int triplet = get_group(3, values, ignore);
    if (triplet == -1) {
        return;
    }
    
    add_ignored_value(triplet, ignore);
    
    int pair = get_group(2, values, ignore);
    if (pair == -1) {
        pair = get_group(3, values, ignore);
    }
    if (pair == -1) {
        return;
    }
    best_hand[0] = best_hand[1] = best_hand[2] = triplet;
    best_hand[3] = best_hand[4] = pair;
}

void fill_two_pair(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) suits;

    int ignore[COMPLETE_HAND_SIZE];
    memset(ignore, -1, COMPLETE_HAND_SIZE * sizeof(int));

    int pair1 = get_group(2, values, ignore);

    if (pair1 == -1) {
        return;
    }

    add_ignored_value(pair1, ignore);
    
    int pair2 = get_group(2, values, ignore);
    if (pair2 == -1) {
        return;
    }
    
    add_ignored_value(pair2, ignore);
    
    best_hand[0] = best_hand[1] = pair1;
    best_hand[2] = best_hand[3] = pair2;

    fill_with_highest_card_values(best_hand, 1, complete_hand, ignore);
}

void fill_highest_cards(int values[VALUES], int suits[SUITS], struct card *complete_hand, int best_hand[EVAL_SIZE]) {
    (void) values;
    (void) suits;
    for (int i = 0; i < EVAL_SIZE; i++) {
        best_hand[i] = complete_hand[6 - i].value;
    }
}