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
void setInfinity ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
int numberOfRows ( FILE *filePtr );
void printMatrix ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
void createAdjMatrix ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
void allPairShortestPath ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );
int findCentralNode ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] );


int main (void)
{
     // variables
     // cols will always be 3.
     int numberOfNodes = 0, rows = 0, cols = 3,
         origin = 0, destination = 0, edgeWeight = 0,
         centralNode = 0;
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

     //sets the nodes 1,1, 2,2, 3,3,... N,N to infinity (currently 900 because edge weights wont be this high)
     setInfinity ( numberOfNodes, adjacencyMatrix );
     // performs the all pairs shortest path passing : origin, destination, weight, number of nodes, and the matrix
     allPairShortestPath ( origin, destination, edgeWeight, numberOfNodes, adjacencyMatrix );

     // finds central node (the least maximum row value)
     centralNode = findCentralNode ( numberOfNodes, adjacencyMatrix );

     if ( centralNode == -1 )
          puts ( "Graph is not connected" );
          // printf ( "This graph is not connected. %d", centralNode );
     else
          printf( "Central Node is: %d\n", centralNode );


     // close file pointer
     fclose ( filePtr );
     return 0;
}

/*
     Sets the 0 values that aren't 1,1, 2,2, 3,3, ..., N,N, too infinity (900)
     Parameters:
          - numberOfNodes -> the size of the matrix (first value in the file)
          - adjacencyMatrix[][ numberOfNodes ] -> the adjacencyMatrix showing what is connected
*/
void setInfinity ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     //set all 0's to 900 (infinity)
     // may change 200 for the other graphs (must be a large number)
     for ( int row = 0; row < numberOfNodes; row++ )
     {
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               if ( row == col )
                    adjacencyMatrix [ row ][ col ] = 0;
               else if ( row != col && adjacencyMatrix [ row ][ col ] == 0 )
                    adjacencyMatrix [ row ][ col ] = 900 ;
               else
                    continue;

          }
     }
     puts ( "After infinity" );
     printMatrix( numberOfNodes, adjacencyMatrix );

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
     //sets the edge weight where there are connections between origin and destination and destination and origin (undirected graph)
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
void allPairShortestPath ( int origin, int destination, int edgeWeight, int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     int currentWeight = 0, counter = 0;

     printf ( "Counter in while loop = %d\n Number of nodes = %d", counter, numberOfNodes );
     //n^3 for loops to run ovr the adj matrix and find shortest path
     for ( int index = 0; index < numberOfNodes; index++ )
     {
     	for ( int row = 0; row < numberOfNodes; row++ )
        {
	    for ( int col = 0; col < numberOfNodes; col++ )
            {
               // if the row is not 1,1, 2,2, 3,3,....,n,n
               if ( adjacencyMatrix [ row ][ col ] != 0 )
               {
                  // adds the values for the matrix and sets the currentWeight value
                  currentWeight = adjacencyMatrix[  index ][ row ] + adjacencyMatrix[ index ][ col ];
                  // if currentWeight is less than adjacencyMatrix
                  if ( adjacencyMatrix[ row ][ col ] > currentWeight )
                  {
                      // records values of edge weight, currentWeight and the row/col location
                      printf ( "Weight of edge: %d\nCurrent Weight: %d\nIndex: [%d,%d]\n", adjacencyMatrix[ row ][ col ], currentWeight, row, col );
                      // sets the row col location on the matrix to currentWeight
                      adjacencyMatrix[ row ][ col ] = currentWeight;
                      // prints matrix after change
                      printMatrix ( numberOfNodes, adjacencyMatrix );
                  }// end of if
               }// controls if it is not zero
            }// end of col for loop
        }// end of row for loop
     }// end of index for loop
}//end of allPairShortestPath function


int findCentralNode ( int numberOfNodes, int adjacencyMatrix[][ numberOfNodes ] )
{
     int minNode = 0, maxNode = 0, centralNode = 0;

     for (int row = 0; row < numberOfNodes; row++ )
     {
          for ( int col = 0; col < numberOfNodes; col++ )
          {
               if ( maxNode <= adjacencyMatrix[ row ][ col ] && row == 0 )
               {
                    maxNode = adjacencyMatrix[ row ][ col ];
                    minNode = adjacencyMatrix[ row ][ col ];
               }
               else if ( maxNode <= adjacencyMatrix[ row ][ col ] )
                    maxNode = adjacencyMatrix[ row ][ col ];
          }

          // go through each row, get max of the row, and figure out the min.
          if ( maxNode <=  minNode )
          {
               minNode = maxNode;
               centralNode = row;
          }
          maxNode = 0;
     }

     if ( minNode == 900 )
          return -1;
     else
          return centralNode;
}
