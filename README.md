# Algorithms for Intelligent Computer Players

## MiniMax
A MiniMax algorithm is a recursive algorithm for choosing the next move in any two-player game where players alternate turns. It is guaranteed to produce a computer opponent who plays flawlessly (if you are willing to wait long enough between moves for the computer to "think")

## Alpha–beta Pruning
From Wikipedia:
Alpha–beta pruning is a search algorithm that seeks to decrease the number of nodes that are evaluated by the minimax algorithm in its search tree. It is an adversarial search algorithm used commonly for machine playing of two-player games (Tic-tac-toe, Chess, Go, etc.).
- https://en.wikipedia.org/wiki/Alpha–beta_pruning

## AlphaBetaTwoGames
This directory contains a Python implementation of the AlphaBeta algorithm along with two different games that both use the same algorithm: TicTacToe.py and Connect4.py. Both games should be run from a terminal. They display the game boards with ASCII art. The TicTacToe Computer Opponent never makes a mistake. The Connect4 Computer opponent plays well but has limited foresight, so it can be beaten by expert players.

Use one of the following commands to playteh games:
```console
python TicTacToe.py
```
  ~ or ~
```console
python Connect4.py
```
 
 ## Connect4AlphaBetaPython
 This directory caontains a Python Connect4 game with a smart computer opponent and a graphical display made using Cocos2D.
 ![Image of Connect4](http://cdn.rawgit.com/erikbuck/GameAI/master/Connect4AlphaBetaPython/Connect4.png)
