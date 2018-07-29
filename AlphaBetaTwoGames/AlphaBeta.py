
###############################################################################
# Alpha-Beta algorithm works for any game board that has the following methods:
#   - getAllSuccessorBoardsForPlayer(player)
#   - score() # Returns -1 for computer win and +1 for user win and 0 for ties
#   - print()
def alphabeta(aBoard, depth, alpha, beta, player):
    v = aBoard.score()
    selectedBoard = None
    if 0 < depth and 0 == v:
        if 0 < player:
            boards = aBoard.getAllSuccessorBoardsForPlayer(player)
            if 0 == len(boards):
              v = 0
            else:
              v = -1
              
            for c in boards:
                if None == selectedBoard:
                  selectedBoard = c
                #c.print()
                abresult = alphabeta(c, depth - 1, alpha, beta, -1)
                if abresult[0] > v:
                    v = abresult[0]
                    selectedBoard = c
                alpha = max(alpha, v)
                if beta <= alpha:
                    break
        else:
            boards = aBoard.getAllSuccessorBoardsForPlayer(player)
            if 0 == len(boards):
              v = 0
            else:
              v = 1
              
            for c in aBoard.getAllSuccessorBoardsForPlayer(player):
                if None == selectedBoard:
                  selectedBoard = c
                #c.print()
                abresult = alphabeta(c, depth - 1, alpha, beta, 1)
                if abresult[0] < v:
                    v = abresult[0]
                    selectedBoard = c
                beta = min(beta, v)
                if beta <= alpha:
                    break

    return (v, selectedBoard)

if __name__ == "__main__":
  print('This module cannot be run stand-alone.')
  