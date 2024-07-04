# Poker Evaluator

This project is a command-line application written in [C], designed to compare card combinations between two players and determine the winner. The program evaluates the players' hands based on a standard set of rules and the five community cards available on the table.

Run the program in the command line:
  
    ./poker [number of players]

(if the number of players is not specified it defaults to 2)

# Input and Output Format

The cards are represented by a pair of characters:

    The first character indicates the rank: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A for sequentially {2}, {3}, ... {10}, {J}, {Q}, {K}, {A}.
    The second character indicates the suit: h, d, s, c for ♥ (hearts), ♦ (diamonds), ♠ (spades), ♣ (clubs).

The program will not terminate after solving a single instance but will continue until there are no more instances in the input (End of File).

Comparing Two Players

Each input instance consists of three lines:

    The first line contains two cards of the first player.
    The second line contains two cards of the second player.
    The third line contains five community cards lying on the table.

Program responds for each instance by indicating which player won:

    Player 1 if the first player wins,
    Player 2 if the second player wins,
    Draw if there is a tie.

Cards on a line are separated by spaces. Each line in the output is terminated with a newline character.
