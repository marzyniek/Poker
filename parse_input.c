#include <stdio.h>
#include <stdlib.h>

#include "parse_input.h"
#include "structures.h"
#include "constants.h"

int parse_players(int argc, char **argv) {
    switch (argc) {
        case 1:
            return 2;
        case 2:
            return atoi(argv[1]);
        default:
            return 0;
    }
}

struct card parse_card(char value, char suit) {
    int card_value;
    int card_suit;

    switch (value) {
        case 'T':
            card_value = 8;
            break;
        case 'J':
            card_value = 9;
            break;
        case 'Q':
            card_value = 10;
            break;
        case 'K':
            card_value = 11;
            break;
        case 'A':
            card_value = 12;
            break;
        default:
            card_value = value - '0' - 2;
    }
    switch (suit) {
        case 'h':
            card_suit = 0;
            break;
        case 'd':
            card_suit = 1;
            break;
        case 's':
            card_suit = 2;
            break;
        case 'c':
            card_suit = 3;
            break;
        default:
            card_suit = -1;
    }

    return (struct card) {card_value, card_suit};
}

process_output_value read_line(int cards, struct card *array) {
    for (int parsed = 0; parsed < cards; parsed++) {
        char card_val[2];
        char card_suit[2];
        
        if (scanf(" %1[TJQKA2-9]", card_val) == 1 && scanf("%1[cdhs]", card_suit) == 1)  {
            array[parsed] = parse_card(*card_val, *card_suit);
        } else {
            if (getchar() == EOF) {
                return INPUT_EOF;
            }
            fprintf(stderr, "invalid card\n");
            return INPUT_ERROR;
        }
    }
    if (getchar() != '\n') {
        fprintf(stderr, "wrong number of cards on line\n");
        return INPUT_ERROR;
    }
    return INPUT_OK;
}

process_output_value read_input(struct card hands[MAX_PLAYERS][2], struct card *table, int players) {
    for (int i = 0; i < players; i++) {
        
        process_output_value output_value;
        if ((output_value = read_line(2, hands[i])) != INPUT_OK) {
            return output_value;
        }
    }
    return (read_line(TABLE_SIZE, table)) == INPUT_OK ? INPUT_OK : INPUT_ERROR;
}