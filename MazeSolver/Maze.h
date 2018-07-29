//
//  Maze.h
//  MazeSolver
//
//

#ifndef __MazeSolver__Maze__
#define __MazeSolver__Maze__

#include <stdint.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
/// This class encapsulates a maze with positions identified by integer x and y
/// coordinates. Each position within the maze is "open" if a person could walk
/// through that position. A position that is not open cannot be occupied by a
/// person.  Each maze has a start position that a person can occupy. The maze
/// is solved if a continuous sequence of open positions starting with the start
/// position and ending with any open position other than the start position
/// along an outside edge of the maze.
///
/// Example maze:
/// start
///  |
///  |
/// # ######################################
/// # ## # ##          #                   #
/// # #     # ########   ################# #
/// # ##### #   #      # #                 #
/// #       # # # ###### # ###############  
/// # ####### # #      # #                 #
/// #         # ######   ################# #
/// # ######### #      # #                 #
/// # #         ###### # ######### #########
/// # # #########   #  # #       #         #
/// # # #         #   ## # ##### ######### #
/// # # ################ # #             # #
/// # #            #   #   # # # # # # # # #
/// # ############ # # # ################# #
/// #            # # # #                   #
/// # ############   # # ###################
/// ### ##   ###########                   #
/// #    ###           ################### #
/// # ##     # # # # #                     #
/// ########################################///
///
/// In the example maze, '#' indicates a blocked position and ' ' indicates an
/// open position.
class Maze
{
protected:
   Maze() {};
   
public:

   ///
   /// Type used to identify positions within a maze
   typedef struct
   {
      int x;
      int y;
   }
   Location;
   
   ///
   /// Virtual destructor
   virtual ~Maze() {};
   
   ///
   /// Returns the width of the maze. All open positions within the maze have
   /// X coordinate in the range 0 to width-1.
   virtual uint16_t getWidth() const = 0;
   
   ///
   /// Returns the length of the maze. All open positions within the maze have
   /// Y coordinate in the range 0 to length-1.
   virtual uint16_t getLength() const = 0;
   
   ///
   /// Returns the location of the start position in the maze.  The start
   /// position is always open.
   virtual Location startLocation() const = 0;
   
   ///
   /// Returns true if and only if the specified location identifies and open
   /// position in the maze. It is an error to specify a location outside the
   /// maze.
   virtual bool isOpenAt(const Location &aLocation) const = 0;
   
   ///
   /// Returns true if and only if the specified location identifies a
   /// position inside the maze.
   virtual bool isInside(const Location &aLocation) const = 0;
};


////////////////////////////////////////////////////////////////////////////////
/// This function returns a pointer to a newly allocated Maze instance. The
/// caller is responsible for deleting the returned Maze instance.
extern const Maze *MakeMaze(size_t index);

#endif /* defined(__MazeSolver__Maze__) */
