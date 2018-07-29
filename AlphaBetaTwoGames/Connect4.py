import AlphaBeta
from copy import deepcopy


class Connect4Board:
  emptyBoard = [
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0],
            [0,0,0,0,0,0]]
                
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
    
    
  def __init__(self, currentPositions = emptyBoard, placeToPlay = 0, player = 0):
    self.positions = deepcopy(currentPositions)
    y = self.getLowestOpenPositionInColumn(placeToPlay)
    self.positions[placeToPlay][y] = player
  
  def getLowestOpenPositionInColumn(self, c):
    for i in range(0, 6):
      if 0 == self.positions[c][i]:
        return i
    return 6
    
  def getOpenPositions(self):
    return [i for i in range(0, 7) if 6 > self.getLowestOpenPositionInColumn(i)]
    
  def getAllSuccessorBoardsForPlayer(self, player):
    return [Connect4Board(self.positions, p, player) for p in self.getOpenPositions()]
    
  def score(self):
      for pattern in Connect4Board.winPatterns:
          sum = 0
          for pos in pattern:
              sum += self.positions[pos[0]][pos[1]]
          if 4 == sum or -4 == sum:
              return sum // 4
      return 0
  
  def print(self):
    print(' {:3}   {:3}   {:3}   {:3}   {:3}   {:3}   {:3}'.format(
      '  A', '  B', '  C', '  D', '  E', '  F', '  G'))
    print('------------------------------------------')
    print('|{:3} | {:3} | {:3} | {:3} | {:3} | {:3} | {:3} |'.format(
      self.positions[0][5], self.positions[1][5], self.positions[2][5], self.positions[3][5],
      self.positions[4][5], self.positions[5][5], self.positions[6][5]))
    print('------------------------------------------')
    print('|{:3} | {:3} | {:3} | {:3} | {:3} | {:3} | {:3} |'.format(
      self.positions[0][4], self.positions[1][4], self.positions[2][4], self.positions[3][4],
      self.positions[4][4], self.positions[5][4], self.positions[6][4]))
    print('------------------------------------------')
    print('|{:3} | {:3} | {:3} | {:3} | {:3} | {:3} | {:3} |'.format(
      self.positions[0][3], self.positions[1][3], self.positions[2][3], self.positions[3][3],
      self.positions[4][3], self.positions[5][3], self.positions[6][3]))
    print('------------------------------------------')
    print('|{:3} | {:3} | {:3} | {:3} | {:3} | {:3} | {:3} |'.format(
      self.positions[0][2], self.positions[1][2], self.positions[2][2], self.positions[3][2],
      self.positions[4][2], self.positions[5][2], self.positions[6][2]))
    print('------------------------------------------')
    print('|{:3} | {:3} | {:3} | {:3} | {:3} | {:3} | {:3} |'.format(
      self.positions[0][1], self.positions[1][1], self.positions[2][1], self.positions[3][1],
      self.positions[4][1], self.positions[5][1], self.positions[6][1]))
    print('------------------------------------------')
    print('|{:3} | {:3} | {:3} | {:3} | {:3} | {:3} | {:3} |'.format(
      self.positions[0][0], self.positions[1][0], self.positions[2][0], self.positions[3][0],
      self.positions[4][0], self.positions[5][0], self.positions[6][0]))
    print('------------------------------------------')
    print()

    
if __name__ == "__main__":
  #############################################################################
  # Game: 
  startBoard = Connect4Board()
  score = 0 
  currentBoard = startBoard
  nextBoard = None
  openPositions = currentBoard.getOpenPositions()
  #currentBoard.print()

  while (None != currentBoard) and \
      (0 <= currentBoard.score()) and \
      (0 < len(openPositions)):
    currentBoard.print()
    
    # Loop getting user input until user selects a valid open position
    pos = -1
    while not pos in openPositions:
      pos = ord(input('Select position: ')[0]) - ord('A')
    
    # Make a board that includes user's chosen move
    nextBoard = Connect4Board(currentBoard.positions, pos, 1)
    nextBoard.print()
    
    # Get the computer oponent's move and resulting score
    score, currentBoard = AlphaBeta.alphabeta(nextBoard, 7, -1, 1, -1)
    
    if None != currentBoard:
      openPositions = currentBoard.getOpenPositions()

    if 0 > score:
      print('Computer is going to win!')
    elif 0 < score:
      print('Human can force a win!')
   
  if None != currentBoard:
    currentBoard.print()
  else:
    nextBoard.print()

  if 0 < score:
    print('***Winner: Player 1')
  elif 0 == score:
    print('Tie Game')
  else:
    print('***Winner: Computer')
