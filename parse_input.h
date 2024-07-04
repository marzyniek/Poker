#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "constants.h"

#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

int parse_players(int argc, char **argv);

struct card parse_card(char value, char suit);

process_output_value read_line(int cards, struct card *array);

process_output_value read_input(struct card hands[MAX_PLAYERS][2], struct card *table, int players);

#endif