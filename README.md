# Algorithms for Intelligent Computer Players

## MiniMax
A MiniMax algorithm is a recursive algorithm for choosing the next move in any two-player game where players alternate turns. It is guaranteed to produce a computer opponent who plays flawlessly (if you are willing to wait long enough between moves for the computer to "think")

## Alpha–beta Pruning
From Wikipedia:
Alpha–beta pruning is a search algorithm that seeks to decrease the number of nodes that are evaluated by the minimax algorithm in its search tree. It is an adversarial search algorithm used commonly for machine playing of two-player games (Tic-tac-toe, Chess, Go, etc.).
- https://en.wikipedia.org/wiki/Alpha–beta_pruning

### AlphaBetaTwoGames
This directory contains a Python implementation of the AlphaBeta algorithm along with two different games that both use the same algorithm: TicTacToe.py and Connect4.py. Both games should be run from a terminal. They display the game boards with ASCII art. The TicTacToe Computer Opponent never makes a mistake. The Connect4 Computer opponent plays well but has limited foresight, so it can be beaten by expert players.

To use the AlphaBeta algorithm implemented here for different games, all you have to do is create a Python class to encapsulate the "game board" for you game. You Board class must provide only two methods for use by AlphaBeta:
```Python
  def getAllSuccessorBoardsForPlayer(self, player):
    """ """
    
  def score(self):
    """ """

```

The ```player``` argument to ```getAllSuccessorBoardsForPlayer()``` has the value ```-1``` for the minimizing player and ```1``` for the maximizing player. ```getAllSuccessorBoardsForPlayer()``` must return a list of Board instances, one for each game board configurations that the specified player could create from the current state of the board.

The ```score()``` method must return an integer score for the current board state. If the maximizing player has won, the returned score must be ```1```. If the minimizing player has won, the returned score must be ```-1```. If neither player has won, the score returned should be between -1 and 1 with a value based on how much the board favors one player or the other.

Use one of the following commands to play the games:
```console
python TicTacToe.py
```
  ~ or ~
```console
python Connect4.py
```
 
 ### Connect4AlphaBetaPython
 This directory contains a Python Connect4 game with a smart computer opponent and a graphical display made using Cocos2D.
 ![Image of Connect4](http://cdn.rawgit.com/erikbuck/GameAI/master/Connect4AlphaBetaPython/Connect4.png)
 
 If you already have Cocos2D installed run teh game with
 ```console
 python Connect4.py
 ```
