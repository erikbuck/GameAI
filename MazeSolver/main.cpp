//
//  main.cpp
//  MazeSolver
//
//
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <algorithm>
#include <queue>
#include <curses.h>
#include "Maze.h"


////////////////////////////////////////////////////////////////////////////////
/// This class encapsulates a modifiable representation of a Maze instance.
class WritableMaze
{
   uint16_t width;
   uint16_t length;
   int32_t *mazeData;
   Maze::Location startLocation;
   int32_t shortestSolution;
   Maze::Location closestExit;
   
public:

   ///
   /// 
   WritableMaze(const Maze &maze)
   {
      width = maze.getWidth();
      length = maze.getLength();
      size_t mazeSize = width * length;
      mazeData = (int32_t *)calloc(mazeSize, sizeof(int32_t));
      startLocation = maze.startLocation();
      shortestSolution = INT32_MAX;
      closestExit = startLocation;
      
      // Fill up our local data structure by copying info in maze
      for(uint16_t j = 0; j < length; j++)
      {
         for(uint16_t i = 0; i < width; i++)
         {
            Maze::Location location = {i, j};
            
            if(!maze.isOpenAt(location))
            {
               this->at(i, j) = INT32_MAX;
            }
            else
            {
               this->at(i, j) = 0;
            }
         }
      }
   };
   
   ///
   /// 
   ~WritableMaze()
   {
      free(mazeData);
   };
   
   ///
   /// 
   bool isIn(uint16_t x, uint16_t y) const
   {
      return (x < width && y < length);
   }
   
   ///
   /// 
   bool isExit(uint16_t x, uint16_t y) const
   {
      return (x == 0 || x == width-1 || y == 0 || y == length-1) &&
             (x != startLocation.x || y != startLocation.y);
   }
   
   ///
   /// 
   int32_t &at(uint16_t x, uint16_t y)
   {
      assert(isIn(x, y));
      return mazeData[y * width + x];
   };
   
   ///
   /// 
   int32_t &at(uint16_t x, uint16_t y) const
   {
      assert(isIn(x, y));
      return mazeData[y * width + x];
   };
   
   ///
   /// This function prints the maze represented by the receiver. If the maze
   /// has been solved, the printed maze includes '.' characters in each
   /// position along a path from the start position to an exit from the maze.
   void print(bool showIntermediate = true) const
   {
      clear();
      
      for(uint16_t j = 0; j < length; j++)
      {
         for(uint16_t i = 0; i < width; i++)
         {
            int32_t block = this->at(i, j);
            
            if(INT32_MAX == block)
            {
               attron(A_STANDOUT);
               attron(COLOR_PAIR(2));
               mvaddch(j+1, i, ' ');
               attroff(COLOR_PAIR(2));
               attroff(A_STANDOUT);
            }
            else if(INT32_MAX-1 == block)
            {
               attron(COLOR_PAIR(1));
               mvaddch(j+1, i, '.');
               attroff(COLOR_PAIR(1));
            }
            else if(0 != block && showIntermediate)
            {
               attron(COLOR_PAIR(2));
               mvaddch(j+1, i, '.');
               attroff(COLOR_PAIR(2));
            }
            else
            {
               mvaddch(j+1, i, ' ');
            }
         }
      }
      refresh();  // curses call to implement all changes since last refresh
   };
   
   ///
   /// 
   int solve();
};


////////////////////////////////////////////////////////////////////////////////
/// This function makes a maze, solves it, and prints the solution.
int main(int argc, const char * argv[])
{
   const Maze *maze = NULL;
   
   if(1 < argc)
   {
      maze = MakeMaze((size_t)atoi(argv[1]));
   }
   else
   {
      maze = MakeMaze(0);
   }
   
   WINDOW *wnd;
   wnd = initscr();  // curses call to initialize window
   start_color();
   init_pair(1, COLOR_GREEN, COLOR_BLACK);
   init_pair(2, COLOR_WHITE, COLOR_BLACK);
   cbreak();  // curses call to set no waiting for Enter key
   noecho();  // curses call to set no echoing
   clear();  // curses call to clear screen, send cursor to position (0,0)
   wrefresh(wnd);  // curses call to implement all changes since last refresh

   WritableMaze writableMaze(*maze);
   int result = writableMaze.solve();
   writableMaze.print(false);

   if(0 > result)
   {
      attron(COLOR_PAIR(1));
      mvprintw(0, 0, "No Solution!");
      attroff(COLOR_PAIR(1));
   }
   else
   {
      attron(COLOR_PAIR(1));
      mvprintw(0, 0, "Shortest path length = %d", result);
      attroff(COLOR_PAIR(1));      
   }
   
   getch();
   
   wrefresh(wnd);  // curses call to implement all changes since last refresh
   endwin();  // curses
   
   return 0;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// This function uses recursion to solve the maze. Rewrite this function without
/// using recursion using a loop and a data structure such as a "stack".
int WritableMaze::solve()
{
   int result = -1;
   std::queue<Maze::Location> queue;
   int32_t distance = 1;
   queue.push(startLocation);
   this->at(startLocation.x, startLocation.y) = distance; // mark path
   
   while(0 < queue.size())
   {
      usleep(5000);
      this->print();
      refresh();
      
      Maze::Location currentLocation = queue.front();
      
      // Distance is teh number of steps from start to get to location
      distance = this->at(currentLocation.x, currentLocation.y);
      
      if(isExit(currentLocation.x, currentLocation.y))
      {  // An exit was found. The maze has been solved.
         break;
      }

      queue.pop();
      
      //
      // enqueue all valid position one step further from start than distance
      //
      if(isIn(currentLocation.x+1, currentLocation.y) &&
         0 == at(currentLocation.x+1, currentLocation.y))
      {
         Maze::Location nextLocation =
            {currentLocation.x+1, currentLocation.y};
         queue.push(nextLocation);
         
         // Store distance traveled to get to next location
         this->at(currentLocation.x+1, currentLocation.y) = distance+1; 
      }
      
      if(isIn(currentLocation.x, currentLocation.y+1) &&
         0 == at(currentLocation.x, currentLocation.y+1))
      {
         Maze::Location nextLocation =
            {currentLocation.x, currentLocation.y+1};
         queue.push(nextLocation);
         
         // Store distance traveled to get to next location
         this->at(currentLocation.x, currentLocation.y+1) = distance+1; 
      }
      
      if(isIn(currentLocation.x, currentLocation.y-1) &&
         0 == at(currentLocation.x, currentLocation.y-1))
      {
         Maze::Location nextLocation =
            {currentLocation.x, currentLocation.y-1};
         queue.push(nextLocation);
         
         // Store distance traveled to get to next location
         this->at(currentLocation.x, currentLocation.y-1) = distance+1; 
      }
      
      if(isIn(currentLocation.x-1, currentLocation.y) &&
         0 == at(currentLocation.x-1, currentLocation.y))
      {
         Maze::Location nextLocation =
            {currentLocation.x-1, currentLocation.y};
         queue.push(nextLocation);
         
         // Store distance traveled to get to next location
         this->at(currentLocation.x-1, currentLocation.y) = distance+1;
      }
   }
   
   if(0 != queue.size())
   {  // A path was found
      Maze::Location currentLocation = queue.front();
      distance = at(currentLocation.x, currentLocation.y);
      at(currentLocation.x, currentLocation.y) = INT32_MAX-1;

      result = distance;
      
      //
      // Find the shortest path back to start by selecting the adjacent
      // location reached by the fewest steps
      //
      while(currentLocation.x != startLocation.x ||
         currentLocation.y != startLocation.y)
      {
         if(isIn(currentLocation.x+1, currentLocation.y) &&
            distance > at(currentLocation.x+1, currentLocation.y))
         {
            Maze::Location nextLocation =
               {currentLocation.x+1, currentLocation.y};
            currentLocation = nextLocation;
         }         
         else if(isIn(currentLocation.x, currentLocation.y+1) &&
            distance > at(currentLocation.x, currentLocation.y+1))
         {
            Maze::Location nextLocation =
               {currentLocation.x, currentLocation.y+1};
            currentLocation = nextLocation;
         }         
         else if(isIn(currentLocation.x, currentLocation.y-1) &&
            distance > at(currentLocation.x, currentLocation.y-1))
         {
            Maze::Location nextLocation =
               {currentLocation.x, currentLocation.y-1};
            currentLocation = nextLocation;
         }         
         else if(isIn(currentLocation.x-1, currentLocation.y) &&
            distance > at(currentLocation.x-1, currentLocation.y))
         {
            Maze::Location nextLocation =
               {currentLocation.x-1, currentLocation.y};
            currentLocation = nextLocation;
         }
         
         distance = at(currentLocation.x, currentLocation.y);
         at(currentLocation.x, currentLocation.y) = INT32_MAX-1;
      
         usleep(5000);
         this->print();
         refresh();
      }
   }
   
   return result;
}
