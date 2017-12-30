# chess-challenge

This challenge given to my friend applying for job opportunity. Finding it interesting I wanted to give it an attempt from my side.
Condition is to use latest GNU C++ compiler standards and implement a fairely stripped down version of chess.

<b>Disclaimer: (I don't own any copyright to challenge statement or idea of challenge provided by it's owner company. This is my hobby attempt at it and not an readymade solution other people to use.)</b>

Here is challenge statement:-

<pre>
You decide to make a simpler version of the game,
suited for our rapid-pace, 140-character culture. You reckon six different types of pieces
is two too many and that the game has way too many esoteric rules to follow (who
needs En Passant, castling, and promotion?)

You design a simpler version, cruise-chess, and sketch out the following rules:
● Cruise-chess is played on the same 64-square board as regular chess.
● The only pieces are kings, pawns, rooks, and bishops. No knights or queens.
● En Passant, castling, and promotion are not valid moves.
● When pawns reach the end of the board they cannot move any further.
● Edge case conditions for game termination such as the threefold repetition and
fifty-move rule do not apply. The game is only ended when a player is in
checkmate, or has no legal moves left. In both cases, they lose. cruise-chess is a
game of psychological endurance and some games will never terminate.
● In all cases where the rules leave ambiguity, the game mechanics operate in the
same way as they do in old-chess.


Initial​ ​Board​ ​Layout

8|BR .. BB .. BK BB .. BR|
7|BP BP BP BP BP BP BP BP|
6|.. .. .. .. .. .. .. ..|
5|.. .. .. .. .. .. .. ..|
4|.. .. .. .. .. .. .. ..|
3|.. .. .. .. .. .. .. ..|
2|WP WP WP WP WP WP WP WP|
1|WR .. WB .. WK WB .. WR|
-----------------------
A B C D E F G H
R - Rook
B - Bishop
P - Pawn
K - King
W - White
B - Black


Input/Output
__________________________________________________________________________
Part of your fame as a world-renowned ASCII game-maker comes from your exact, minimal
game interfaces. You design cruise-chess to have an extremely simple input/output format:
====​ ​BEGIN​ ​GAME​ ​OUTPUT​ ​====
-----------------------
8|BR .. BB .. BK .. .. BR|
7|BP BP BP BP .. BP BP BP|
6|.. .. .. .. .. .. .. ..|
5|.. .. BB .. BP .. .. ..|
4|.. .. .. .. WP .. .. ..|
3|.. .. .. .. .. WP .. ..|
2|WP WP WP WP .. .. WP WP|
1|WR .. WB .. WK WB .. WR|
-----------------------
A B C D E F G H
In check: N
Move: W
====​ ​ ​END​ ​GAME​ ​OUTPUT​ ​ ​====



Inputs are specified as source,destination coordinate pairs, followed by the system newline. If a
move is invalid no output is produced, the game should immediately prompt the player for
another input. Players take turns playing cruise-chess using the same terminal.
====​ ​BEGIN​ ​GAME​ ​INPUT​ ​====
A2,A4
====​ ​ ​END​ ​GAME​ ​INPUT​ ​ ​====
When the game is won, lost, or tied it should print a single line and exit:
====​ ​BEGIN​ ​GAME​ ​OUTPUT​ ​====
Winner: W
====​ ​ ​END​ ​GAME​ ​OUTPUT​ ​ ​====
Where valid winners are `W` - White, `B` - Black, `D` - Draw.
Implementation

__________________________________________________________________________
</pre>
