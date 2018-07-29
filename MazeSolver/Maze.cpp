//
//  Maze.cpp
//  MazeSolver
//
//

#include "Maze.h"
#include <stdlib.h>


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
class ConcreteMaze : public Maze
{
protected:
   const uint8_t *data;
   uint16_t width;
   uint16_t length;
   
public:
   
   ConcreteMaze(size_t index = 0);
   
   uint16_t getWidth() const {return this->width;};
   uint16_t getLength() const {return this->length;};
   Location startLocation() const;
   bool isOpenAt(const Location &aLocation) const;
   bool isInside(const Location &aLocation) const;
};


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray0[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X X  X XX          X                   X\
X       X XXXXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXX X   X      X X                 X\
X       X X X XXXXXX X XXXXXXXXXXXXXXX X\
X XXXXXXX X X      X X                 X\
X       XXX XXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXXXX X      X                   X\
X           XXXXXX X XXXXXXXXX XXXXXXXXX\
X X XXXXXXXXX   X  X X       X         X\
X X X         X   XX X XXXXX XXXXXXXXX X\
X X XXXXXXXXXXXXXXXXXX X             XXX\
X X            X   X   X X X X X X X    \
X XXXXXXXXXXXX X X X XXXXXXXXXXXXXXXXXXX\
X            X X X X                   X\
X XXXXXXXXXXXX   X X XXXXXXXXXXXXX XXXXX\
X X XX   XXXXXXXXXXX                   X\
X    XXX           XXXXXXXXXXXXXXXXXXX X\
X XX     X X X X X                     X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray1[801] = "\
X XXXXXXX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X X  X XX          X                   X\
X       X XXXXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXX X   X      X X                 X\
X       X X X XXXXXX X XXXXXXXXXXXXXXX X\
X XXXXXXX X X      X X                 X\
X       XXX XXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXXXX X      X                   X\
X           XXXXXX X XXXXXXXXX XXXXXXXXX\
X X XXXXXXXXX   X  X X       X         X\
X X X         X   XX   XXXXX XXXXXXXXX X\
X X XXXXXXXXXXXXXXXXXX X             XXX\
X X            X   X   X X X X X X X    \
X XXXXXXXXXXXX X X X XXXXXXXXXXXXXXXXXXX\
X            X X X X                   X\
X XXXXXXXXXXXX   X X XXXXXXXXXXXXX XXXXX\
X X XX   XXXXXXXXXXX                   X\
X    XXX           XXXXXXXXXXXXXXXXXXX X\
X XX     X X X X X                     X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray2[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray3[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                       \
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray4[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
XXXXXXXXXXXXXXX                        X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                      X\
X                                       \
XXXXXXXXX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray5[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X X  X XX          X                   X\
X       X XXXXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXX X   X      X X                 X\
X         X X XXXXXX X XXXXXXXXXXXXXXX X\
X XXXXXXX X X      X X                 X\
X       XXX XXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXXXX X      X                   X\
X           XXXXXX X XXXXXXXXX XXXXXXXXX\
X X XXXXXXXXX   X  X X       X         X\
X X X         X   XX X XXXXX X XXXXXXX X\
X X XXXXXXXXXXXXXXXXXX X             XXX\
X X            X   X   X X X X X X X    \
X XXXXXXXXXXXX X X X XXXXXXXXXXXXXXXXXXX\
X            X X X X                   X\
X XXXXXXXXXXXX   X X XXXXXXXXXXXXX XXXXX\
X X XX   XXXXXXXXXXX                   X\
X    XXX           XXXXXXXXXXXXXXXXXXX X\
X XX     X X X X X                     X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray6[801] = "\
X XXXXXXXX XXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X X  X XX          X                   X\
X       X XXXXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXX   X      X X                 X\
X         X X XXXXXX X XXXXXXXXXXXXXXX X\
X XXXXXXX X X      X X                 X\
X       XXX XXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXXXX X      X                   X\
X           XXXXXX X XXXXXXXXX XXXXXXXXX\
X X XXXXXXXXX   X  X X       X         X\
X X X         X   XX X XXXXX X XXXXXXX X\
X X XXXXXXXXXXXXXXXXXX X             XXX\
X X            X   X   X X X X X X X    \
X XXXXXXXXXXXX X X X XXXXXXXXXXXXXXXXXXX\
X            X X X X                   X\
X XXXXXXXXXXXX   X X XXXXXXXXXXXXX XXXXX\
X X XX   XXXXXXXXXXX                   X\
X    XXX           XXXXXXXXXXXXXXXXXXX X\
X XX     X X X X X                     X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t defaultMazeArray7[801] = "\
X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\
X X  X XX          X                   X\
X       X XXXXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXX   X      X X                 X\
X         X X XXXXXX X XXXXXXXXXXXXXXX X\
X XXXXXXX X X      X X                 X\
X       XXX XXXXXX   XXXXXXXXXXXXXXXXX X\
X XXXXXXXXX X      X                   X\
X           XXXXXX X XXXXXXXXX XXXXXXXXX\
X X XXXXXXXXX   X  X X       X         X\
X X X         X   XX X XXXXX X XXXXXXX X\
X X XXXXXXXXXXXXXXXXXX X             XXX\
X X            X   X   X X X X X X X   X\
X XXXXXXXXXXXX X X X XXXXXXXXXXXXXXXXXXX\
X            X X X X                   X\
X XXXXXXXXXXXX   X X XXXXXXXXXXXXX XXXXX\
X X XX   XXXXXXXXXXX                   X\
X    XXX           XXXXXXXXXXXXXXXXXXX X\
X XX     X X X X X                     X\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
static const uint8_t *defaultMazeArrayArray[] =
{
   defaultMazeArray0,
   defaultMazeArray1,
   defaultMazeArray2,
   defaultMazeArray3,
   defaultMazeArray4,
   defaultMazeArray5,
   defaultMazeArray6,
   defaultMazeArray7,
};


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
ConcreteMaze::ConcreteMaze(size_t index)
{   
   if(0 < index &&
      index < (sizeof(defaultMazeArrayArray) / sizeof(uint8_t *)))
   {
      this->data = defaultMazeArrayArray[index];
   }
   else
   {
      this->data = defaultMazeArray0;
   }
   
   this->width = 40;
   this->length = 20;
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
Maze::Location ConcreteMaze::startLocation() const
{
   Maze::Location result = {1, 0};
   
   return result;
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
bool ConcreteMaze::isOpenAt(const Maze::Location &aLocation) const
{
   bool result = true;
   
   if(this->isInside(aLocation))
   {
      size_t index = (aLocation.y * this->getWidth()) + aLocation.x;
      
      result = (this->data[index] == ' ');
   }
   
   return result;
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
bool ConcreteMaze::isInside(const Location &aLocation) const
{
   return (aLocation.x < this->getWidth() && aLocation.y < this->getLength());
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
const Maze *MakeMaze(size_t index)
{
   return new ConcreteMaze(index);
}
