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

     Graph format: First line contains the number of vertices in the graph, Assume 'n'
     identifed by 1,2,3,...,n-1
     the rest of the lines related to info on the undirected edge, whihc is characterized
     by 3 numbers:
        - ID of source vertex
        - ID of target vertex
        - weight of the edge
        - since undirected, should hold edges that include nodes (a,b) and (b,a)

 */

 // my plan to make this is to use structures and arrays, and when searching through the
 // structures, I'm going to check what it looks like with its degrees of edges


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function prototypes
void printMatrix ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
void createAdjMatrix ( int origin, int destination, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );

int main (void)
{
     int numberOfNodes = 0, rows = 0, cols = 0, counter = 0,
         origin = 0, destination = 0, edgeWeight = 0;
     char characters;
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
     while ( !feof ( filePtr ) )
     {
          // if characters is not the newline and the loop is in its first pass
          if ( characters != '\n' && counter == 0 )
          {
               // checks to see the number of coloums. can be variable
               while ( characters != '\n')
               {
                    // gets the characters from the file to see how many cols there are
                    characters = fgetc( filePtr );
                    cols++;
               }
               printf ( "Number of coloums: = %d\n", cols );
               counter++;
          }
          else if ( characters == '\n' )
               rows++;
          // gets the charcters to see how many rows there are
          characters = fgetc( filePtr );
     }

     // initalize the array to be variable from file
     int storageArray[ rows ][ cols ];

     // rewinds the filePtr to beginning of the file after getting the number of rows and cols
     rewind ( filePtr );
     // removes the first number (number of nodes in the graph -- allows for varilbe input)
     fscanf ( filePtr, "%d", &numberOfNodes );

     int adjacencyMatrix [ numberOfNodes ][ numberOfNodes ];
     for ( int row = 0; row < numberOfNodes; row++ )
     {
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               // initalizes the array to 0
               adjacencyMatrix[ row ][ col ] = 0;
          }
     }

     puts ( "" );
     // inserts the filePtr number into the storageArray at positions in the 2d positions

     for ( int index = 0; index < rows; index++ )
     {
          fscanf ( filePtr, "%d", &origin );
          fscanf ( filePtr, "%d", &destination );
          fscanf ( filePtr, "%d", &edgeWeight );
          createAdjMatrix( origin, destination, numberOfNodes, adjacencyMatrix );
          printMatrix( numberOfNodes, adjacencyMatrix );
          puts ( "" );
     }

     // close file pointer
     fclose ( filePtr );
     return 0;
}

void createAdjMatrix ( int origin, int destination, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     printf ( "Inserting edge between %d & %d, %d & %d\n", origin, destination, destination, origin );
     adjacencyMatrix [ origin ][ destination ] = 1;
     adjacencyMatrix [ destination ][ origin ] = 1;
}

// prints the matrix
void printMatrix( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     // space for formatting
     printf ( "  " );
     for ( int index = 0; index < numberOfNodes; index++ )
          printf ( "%4d", index );
     puts( "\n" );
     // prints the matrix
     for (int row = 0; row < numberOfNodes; row++ )
     {
          printf ( "%d  ", row );
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               printf ( "  %-2d", adjacencyMatrix [ row ][ col ] );
          }
          puts ( "" );
     }
}// end of printMatrix Function
