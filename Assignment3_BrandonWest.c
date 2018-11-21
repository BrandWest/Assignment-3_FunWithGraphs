/*
====================================================
Author: Brandon West, Christopher Brennen
Class: PROG 20025
Assignemnt 2: Fun with Graphs!
Date: December 3, 2018
Description:

====================================================
*/
/*
    This assignment focuses on graphs and thier implementation in c.
    They will use an adjacenty matric data structure and output the information in matrix
     information in matrix form O(n^2)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function prototypes
int numberOfRows ( FILE *filePtr );
void printMatrix ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
void createAdjMatrix ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
void allPairShortestPath ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );

int main (void)
{
     // variables
     // cols will always be 3.
     int numberOfNodes = 0, rows = 0, cols = 3,
         origin = 0, destination = 0, edgeWeight = 0;
     // file pointer position
     FILE *filePtr;

     // attempts to open file pointer for textGraph text
     filePtr = fopen ( "testGraph.txt", "r" );
     // if the filePtr is null the file didnt open, closes and exits.
     if ( filePtr == NULL )
     {
          printf ( "Error Opening File, try again." );
          fclose ( filePtr );
          exit ( 1 );
     }
     // file pointer successful, reading the file.
     else
          puts ( "Reading file..." );
     // check the number of rows in the matrix while the filePtr doesnt have end of file marker
     rows = numberOfRows ( filePtr );
     // rewinds the filePtr to beginning of the file after getting the number of rows and cols
     rewind ( filePtr );
     // initalize the array to be variable from file
     int storageArray[ rows ][ cols ];
     // removes the first number (number of nodes in the graph -- allows for varilbe input)
     fscanf ( filePtr, "%d", &numberOfNodes );
     // initalizes the adjacencyMatrix
     int adjacencyMatrix [ numberOfNodes ][ numberOfNodes ];

     // initalizes the adjacencyMatrix values to 0
     for ( int row = 0; row < numberOfNodes; row++ )
     {
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               adjacencyMatrix[ row ][ col ] = 0;
          }
     }
     // for loop to control the removal from the file, the origin, destination, and edge weight
     for ( int index = 0; index < rows; index++ )
     {
          fscanf ( filePtr, "%d", &origin );
          fscanf ( filePtr, "%d", &destination );
          fscanf ( filePtr, "%d", &edgeWeight );
          // creates the adj matrix
          createAdjMatrix( origin, destination, edgeWeight, numberOfNodes, adjacencyMatrix );
          printMatrix( numberOfNodes, adjacencyMatrix );
          puts ( "" );
     }

     allPairShortestPath ( origin, destination, edgeWeight, numberOfNodes, adjacencyMatrix );
     // close file pointer
     fclose ( filePtr );
     return 0;
}

/*
     Method numberOfRows calculates how many rows in the file there are
     Parameters:
          - FILE *filePtr -> file pointer for the position of the file.
*/
int numberOfRows ( FILE *filePtr )
{
     // variables
     char characters;
     int counter = 0, rows = 0;

     // while not at the end of the pointer file
     while ( !feof ( filePtr ) )
     {
          // checks the character if its not \n continue checking to see number of rows in the file
          characters = fgetc( filePtr );
          if ( characters == '\n' )
               rows++;
     }
     // returnts the value calculated from the rows
     return rows;
}// end of numberOfRows function

/*
     Method creates the adjacencyMatrix
     Parameters:
          - origin -> The first coloum of the text file
          - destination -> the second column of the text file
          - edgeWeight -> The weight of the edge between the nodes
          - numberOfNodes -> the size of the matrix (first value in the file)
          - adjacencyMatrix[][ numberOfNodes ] -> the adjacencyMatrix showing what is connected

*/
void createAdjMatrix ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     printf ( "Inserting edge between %d & %d, %d & %d\n", origin, destination, destination, origin );
     // changed the values @origin and @destination to 1 if there is an edge
     // adjacencyMatrix [ origin ][ destination ] = 1;
     // adjacencyMatrix [ destination ][ origin ] = 1;
     // if we use edge weight as the number in the matrix, can we use that?
     adjacencyMatrix [ origin ][ destination ] = edgeWeight;
     adjacencyMatrix [ destination ][ origin ] = edgeWeight;
}// end of createdAdjMatrix

/*
     Method prints out the matrix
     Parameters:
          - numberOfNodes -> The size of the adjacencyMatrix
          - adjacencyMatrix[][ numberOfNodes ] -> the adjacencyMatrix showing what is connected
*/
void printMatrix( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     char space = ' ';
     // space for formatting
     printf ( "%6c", space );
     // for loop to create the column numbers
     for ( int index = 0; index < numberOfNodes; index++ )
          printf ( "[,%d]%4c", index, space );
     puts( "" );
     // prints the matrix
     for (int row = 0; row < numberOfNodes; row++ )
     {
          // prints the row numberss
          printf ( "[%d,]\t", row );
          // prints the adjacencyMatrix
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               printf ( "%d\t", adjacencyMatrix [ row ][ col ] );
          }
          puts ( "" );
     }
}// end of printMatrix Function

/*
     Method allPairsShortestPath finds shortest path in the graph
     Parameters:
          - origin -> The first coloum of the text file
          - destination -> the second column of the text file
          - edgeWeight -> The weight of the edge between the nodes
          - numberOfNodes -> the size of the matrix (first value in the file)
          - adjacencyMatrix[][ numberOfNodes ] -> the adjacencyMatrix showing what is connected
*/
// will an edge weight ever be 0 in dijkstras?
void allPairShortestPath ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     //set all 0's to 200 (infinity)
     // may change 200 for the other graphs (must be a large number)
     for ( int row = 0; row < numberOfNodes; row++ )
     {
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               if ( adjacencyMatrix [ row ][ col ] == 0 )
                    adjacencyMatrix [ row ][ col ] = 200 ;
               else
                    continue;
          }
     }
     printMatrix( numberOfNodes, adjacencyMatrix );

     for ( int index = 0; index < numberOfNodes; index++ )
     {
          for ( int row = 0; row < numberOfNodes; row++ )
          {
               for ( int col = 0; col < numberOfNodes; col++ )
               {
                    adjacencyMatrix [ index ] ;
               }
          }
     }
}
