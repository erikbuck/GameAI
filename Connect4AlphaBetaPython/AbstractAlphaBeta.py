######################################################################
## by Erik M. Buck 2016
######################################################################

# Begin by importing the cocos package:
from copy import deepcopy
import multiprocessing


######################################################################
#
#
class Board:
    def allWinningPatterns():
        result = []
        
        for x in range(7 - 3):
            for y in range(6):
                result.append(((x,y),(x+1, y), (x+2,y), (x+3,y)))
        for x in range(7):
            for y in range(6 - 3):
                result.append(((x,y),(x, y+1), (x,y+2), (x,y+3)))
        for x in range(7 - 3):
            for y in range(3, 6):
                result.append(((x,y),(x+1, y-1), (x+2,y-2), (x+3,y-3)))
        for x in range(7 - 3):
            for y in range(6 - 3):
                result.append(((x,y),(x+1, y+1), (x+2,y+2), (x+3,y+3)))

        return tuple(result)

    winPatterns = allWinningPatterns()
    
    emptyBoard = [
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0]]
            
    def __init__(self, aBoard=emptyBoard, col=-1, player=0):
        self.board = deepcopy(aBoard)
        self.drop(col, player)

    def drop(self, col, player):
        if 0 <= col and 7 > col:
            row = self.availableRowInCol(col)
            if 0 <= row:
                self.board[col][row] = player
                return True
        return False


    def availableRowInCol(self, col):
        for row in range(6):
           if 0 == self.board[col][row]:
               return row
        return -1

    def score(self):
        for pattern in Board.winPatterns:
            sum = 0
            for pos in pattern:
                sum += self.board[pos[0]][pos[1]]
            if 4 == sum or -4 == sum:
                return (sum, pattern)
        return (0, None)

    def availableColumns(self):
        columnNumbers = (3,2,4,1,5,0,6)
        result = []
        for c in columnNumbers:
            r = self.availableRowInCol(c)
            if -1 < r:
                result.append(c)
        return result

    def isOver(self):
        scoreInfo = self.score();
        
        if 4 == scoreInfo[0] or -4 == scoreInfo[0]:
            return True
        
        for c in range(7):
            r = self.availableRowInCol(c)
            if -1 < r:
                return False
        return True


######################################################################
#
#
def alphabeta(aBoard, depth, alpha, beta, isMaximizing):
    scoreInfo = aBoard.score()
    v = scoreInfo[0]
    #print depth, 'score=', scoreInfo, isMaximizing
    selectedCol = None
    if 0 < depth and 0 == v:
        if isMaximizing:
            v = -10
            for c in aBoard.availableColumns():
                abresult = alphabeta(Board(aBoard.board, c, 1),
                    depth - 1, alpha, beta, False)
                if abresult[0] > v:
                    v = abresult[0]
                    selectedCol = c
                alpha = max(alpha, v)
                if beta <= alpha:
                    break
        else:
            v = 10
            for c in aBoard.availableColumns():
                abresult = alphabeta(Board(aBoard.board, c, -1),
                    depth - 1, alpha, beta, True)
                if abresult[0] < v:
                    v = abresult[0]
                    selectedCol = c
                beta = min(beta, v)
                if beta <= alpha:
                    break
    #print v, selectedCol, isMaximizing
    return (v, selectedCol)


######################################################################
#
#
def findComputerMove(aBoard, depth):
    abresult = alphabeta(aBoard, depth, -10, 10, False)
    if abresult[1] != None:
        exit(abresult[1])
    else:
        exit(-1)

if __name__ == '__main__':
    print 'This module is not intended for use as "main".'
