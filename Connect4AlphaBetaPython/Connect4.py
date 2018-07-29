######################################################################
## A Cocos2D version of "Connect Four"
## by Erik M. Buck 2016
######################################################################

from AbstractAlphaBeta import *
import cocos
from cocos.actions import *
import pyglet

gravity = -9.8 / 20.0       # Acceleration per update interval

# load images with pyglet
redCheckerImage = pyglet.resource.image('CheckerRedSmall.png')
blackCheckerImage = pyglet.resource.image('CheckerBlackSmall.png')
legendImage = pyglet.resource.image('Legend.png')
gameOverImage = pyglet.resource.image('GameOver.png')

# Calculate window size based on image sizes
wWidth = redCheckerImage.width * 7
wHeight = redCheckerImage.height * 6 + legendImage.height

######################################################################
# Subclass Action to move any target Node with an approximation of
# gravitational accelleration and "bounce"
class GravityAction(Action):

    def init(self, start_pos, dest_pos, initial_velocity = 0):
        """ destination_pos is the position the Action will eventually
            move its target to """
        self.start_pos = start_pos
        self.dest_pos = dest_pos
        self.y_velocity = initial_velocity
    
    def start(self):
        self.target.position = self.start_pos
    
    def step(self, dt):
        self.y_velocity += gravity
        (x, y) = self.target.position
        new_y_pos = y + self.y_velocity
        (target_x, target_y) = self.dest_pos
        dist_to_go = target_y - new_y_pos # How far to destination?

        if dist_to_go > 0:                # Are we past destination?
            self.y_velocity = -0.1 * self.y_velocity     # Bounce
            new_y_pos = target_y + dist_to_go  # Move back up

        self.target.position = (x, new_y_pos) # Set target's position.

    def done(self):
        (x, y) = self.target.position
        (target_x, target_y) = self.dest_pos
        dist_to_go = target_y - y         # How far to destination?
        return -0.01 < dist_to_go


######################################################################
# Subclass a Layer to craete visual game board
class GameBoard(cocos.layer.ColorLayer):
    is_event_handler = True
    
    def __init__(self):
        # Always call super in the constructor:
        super( GameBoard, self ).__init__(32, 32, 32, 255)
        
        self.shouldUseSubprocess = True;
        self.gameOverSprite = cocos.sprite.Sprite(gameOverImage,
            (wWidth * 0.5, wHeight * 0.5))
        self.add(self.gameOverSprite)
        self.pieces = {}
        self.subprocess = None
        self.isTwoPlayer = False
        self.restart()
        
        legendPos = (
             redCheckerImage.width * 3.5,
             redCheckerImage.height * 6 + legendImage.height * 0.5)
        legendSprite = cocos.sprite.Sprite(legendImage, legendPos)
        legendSprite.alpha = 0.0
        self.add(legendSprite)
        legendSprite.do(Repeat(FadeTo(225, 0.5)+FadeTo(255, 0.5)))

    def restart(self):
        for key in self.pieces:
            self.remove(self.pieces[key])
        self.board = Board()
        self.currentPlayer = 1
        self.pieces = {}
        self.isReadyForNextMove = True;
        self.remove(self.gameOverSprite)
    
    def imageForCurrentPlayer(self):
        if 1 == self.currentPlayer:
            return blackCheckerImage
        return redCheckerImage
        
    def dropInColumn(self, num):
        if 0 > num or 6 < num: return False
        row = self.board.availableRowInCol(num)
        if 0 > row: return False
        x = redCheckerImage.width * (num + 0.5)
        y = redCheckerImage.height * (row + 0.5)
        
        newPiece = cocos.sprite.Sprite(self.imageForCurrentPlayer(),
            (x, wHeight))
        self.add(newPiece)
        newPiece.do(GravityAction(newPiece.position, (x,y), -5))
        self.do(Delay(1.1)+CallFuncS(GameBoard.waitForMove))
        self.pieces[(num, row)] = newPiece
        return self.board.drop(num, self.currentPlayer)

    def waitForMove(self):
        if None != self.subprocess:
            self.subprocess.join()
            col = self.subprocess.exitcode
            self.subprocess = None
            if col >= 0:
                self.dropInColumn(col)
                self.currentPlayer *= -1.0
            
            if self.board.isOver():
                self.onGameOver()
        else:
            self.isReadyForNextMove = True

    def getComputerMove(self):
        if not self.shouldUseSubprocess:
            abresult = alphabeta(self.board, 11, -10, 10, False)
            if abresult[1] != None:
                self.dropInColumn(abresult[1])
                self.currentPlayer *= -1.0
    
        elif None == self.subprocess:
            self.subprocess = multiprocessing.Process(
                target=findComputerMove, args=(self.board, 7))
            self.subprocess.start()
            self.isReadyForNextMove = False

    def onGameOver(self):
        self.gameOverSprite.do(FadeIn(1))
        self.gameOverSprite.do(RotateBy(700, 2))
        self.add(self.gameOverSprite)
        for key in self.pieces:
            self.pieces[key].do(FadeTo(76, .5))
        
        scoreInfo = self.board.score();
        if 4 == scoreInfo[0] or -4 == scoreInfo[0]:
            for pos in scoreInfo[1]:
                self.pieces[pos].do(FadeTo(255, 0.75))

    def on_key_press(self, symbol, modifiers):
        if not self.board.isOver():
            if self.isReadyForNextMove:
                if 1 == self.currentPlayer or self.isTwoPlayer:
                    if self.dropInColumn(symbol - pyglet.window.key.A):
                       self.currentPlayer *= -1.0
                
                if -1 == self.currentPlayer and \
                        not self.isTwoPlayer and \
                        not self.board.isOver():
                    self.getComputerMove()
            
                if self.isReadyForNextMove and self.board.isOver():
                    self.onGameOver()
        else:
            self.restart()


if __name__ == '__main__':
    # Create a window by initializing the Director:
    cocos.director.director.init(wWidth, wHeight, caption="C Four")
    cocos.director.director.run (cocos.scene.Scene(GameBoard()))
