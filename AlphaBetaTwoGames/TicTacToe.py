import AlphaBeta

class TicTacToeBoard:
  #     A | B | C
  #     ---------
  #     D | E | F
  #     ---------
  #     G | H | I
  emptyBoard = {'A':0, 'B':0, 'C':0,
                'D':0, 'E':0, 'F':0,
                'G':0, 'H':0, 'I':0}
                
  def __init__(self, currentPositions = emptyBoard, placeToPlay = 'A', player = 0):
    self.positions = dict(currentPositions)
    self.positions[placeToPlay] = player
    
  def getOpenPositions(self):
    return [p for p in self.positions.keys() if self.positions[p] == 0]
    
  def getAllSuccessorBoardsForPlayer(self, player):
    return [TicTacToeBoard(self.positions, p, player) for p in self.getOpenPositions()]
    
  def score(self):
    result = 0
    
    if self.positions['A'] == self.positions['B'] and self.positions['A'] == self.positions['C']:
      result = self.positions['A']
    elif  self.positions['D'] == self.positions['E'] and self.positions['D'] == self.positions['F']:
      result = self.positions['D']
    elif  self.positions['G'] == self.positions['H'] and self.positions['G'] == self.positions['I']:
      result = self.positions['G']
    elif  self.positions['A'] == self.positions['D'] and self.positions['A'] == self.positions['G']:
      result = self.positions['A']
    elif  self.positions['B'] == self.positions['E'] and self.positions['B'] == self.positions['H']:
      result = self.positions['B']
    elif  self.positions['C'] == self.positions['F'] and self.positions['C'] == self.positions['I']:
      result = self.positions['C']
    elif  self.positions['A'] == self.positions['E'] and self.positions['A'] == self.positions['I']:
      result = self.positions['A']
    elif  self.positions['C'] == self.positions['E'] and self.positions['C'] == self.positions['G']:
      result = self.positions['C']
    
    return result
  
  def print(self):
    print('{:3} | {:3} | {:3}'.format(self.positions['A'], self.positions['B'], self.positions['C']))
    print('----------------')
    print('{:3} | {:3} | {:3}'.format(self.positions['D'], self.positions['E'], self.positions['F']))
    print('----------------')
    print('{:3} | {:3} | {:3}'.format(self.positions['G'], self.positions['H'], self.positions['I']))
    print()

    
if __name__ == "__main__":
  #############################################################################
  # Game: 
  startBoard = TicTacToeBoard()
  score = 0 
  currentBoard = startBoard
  nextBoard = None

  while (None != currentBoard) and \
      (0 <= currentBoard.score()) and \
      (0 < len(currentBoard.getOpenPositions())):
    currentBoard.print()
    
    # Loop getting user input until user selects a valid open position
    pos = ''
    while (not pos in currentBoard.positions) or \
        (0 != currentBoard.positions[pos]):
      pos = input('Select position: ')
    
    # Make a board that includes user's chosen move
    nextBoard = TicTacToeBoard(currentBoard.positions, pos, 1)
    
    # Get the computer oponent's move and resulting score
    score, currentBoard = AlphaBeta.alphabeta(nextBoard, 10, -1, 1, -1)

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

