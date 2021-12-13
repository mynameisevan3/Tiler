
/*==================================
    tiler.c
    Tiler Function Implementations
  ==================================*/


// Inclusions
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiler.h"


// Function Implementations

// tilerSerial - given an input image file and desired tile widths and heights, this function
//   will break the image into tiles.  Leftover edges that do not fit into tiles are discarded.
// TODO: Expand for overlapping.
uint8_t** tilerSerial( uint8_t *input, uint16_t width, uint16_t height,
                         uint16_t tileWidth, uint16_t tileHeight ) {

  uint8_t **tiles       = NULL;  // Return Container for All Tiles
  uint8_t  *tile        = NULL;  // Construction Container for One Tile
  uint16_t  i           = 0;     // Tile Height Iterator
  uint16_t  j           = 0;     // Tile Width Iterator
  uint16_t  m           = 0;     // Image Pixel X Iterator
  uint16_t  n           = 0;     // Image Pixel Y Iterator
  uint16_t  x           = 0;     // Tile Pixel X Iterator
  uint16_t  y           = 0;     // Tile Pixel Y Iterator
  uint16_t  startXPixel = 0;     // Tile X Minimum Bound
  uint16_t  endXPixel   = 0;     // Tile X Maximum Bound
  uint16_t  startYPixel = 0;     // Tile Y Minimum Bound
  uint16_t  endYPixel   = 0;     // Tile Y Maximum Bound
  uint32_t  imagePixel  = 0;     // Pixel Location in Image
  uint32_t  tilePixel   = 0;     // Pixel Location in Tile
  // Preliminary Calculations
  uint16_t  tilesWide   = width / tileWidth;
  uint16_t  tilesHigh   = height / tileHeight;

  // Allocate Space for Tiles in Return Container
  tiles                 = malloc( tilesWide * tilesHigh * sizeof( uint8_t* ) );

  // Break Up by Tiles in X and Y Direction
  for( i = 0; i < tilesHigh; i++ ) {
    for( j = 0; j < tilesWide; j++ ) {

      // Allocate Memory for this Tile
      tile        = malloc( 3 * tileWidth * tileHeight * sizeof( uint8_t ) );
      if( !tile ) {
        fprintf( stderr, "\nERROR: Tiler memory allocation failure!\n" );
      }

      // Tile Pixel Calculations
      startXPixel = j * tileWidth;
      endXPixel   = startXPixel + tileHeight;
      startYPixel = i * tileHeight;
      endYPixel   = startYPixel + tileHeight;

      // Fill this Tile with the Proper Contents
      for( m = startYPixel, y = 0; m < endYPixel; m++, y++ ) {
        for( n = startXPixel, x = 0; n < endXPixel; n++, x++ ) {

          // Locate Image Source Pixel and Tile Destination Pixel
          imagePixel            = ( m * width + n ) * 3;
          tilePixel             = ( y * tileWidth + x ) * 3;

          // Transfer Data
          tile[ tilePixel + 0 ] = input[ imagePixel + 0 ];  // Red Component
          tile[ tilePixel + 1 ] = input[ imagePixel + 1 ];  // Green Component
          tile[ tilePixel + 2 ] = input[ imagePixel + 2 ];  // Blue Component

        }
      }

      // Place this Tile into Tiles Container
      tiles[ i * tilesWide + j ] = tile;

    }
  }

  return tiles;

}


// tilerOMP - same as above, parallelized with OpenMP.
uint8_t** tilerOMP( uint8_t *input, uint16_t width, uint16_t height,
                         uint16_t tileWidth, uint16_t tileHeight, uint8_t cores ) {

  uint8_t **tiles       = NULL;  // Return Container for All Tiles
  uint8_t  *tile        = NULL;  // Construction Container for One Tile
  uint16_t  i           = 0;     // Tile Height Iterator
  uint16_t  j           = 0;     // Tile Width Iterator
  uint16_t  m           = 0;     // Image Pixel X Iterator
  uint16_t  n           = 0;     // Image Pixel Y Iterator
  uint16_t  x           = 0;     // Tile Pixel X Iterator
  uint16_t  y           = 0;     // Tile Pixel Y Iterator
  uint16_t  startXPixel = 0;     // Tile X Minimum Bound
  uint16_t  endXPixel   = 0;     // Tile X Maximum Bound
  uint16_t  startYPixel = 0;     // Tile Y Minimum Bound
  uint16_t  endYPixel   = 0;     // Tile Y Maximum Bound
  uint32_t  imagePixel  = 0;     // Pixel Location in Image
  uint32_t  tilePixel   = 0;     // Pixel Location in Tile
  // Preliminary Calculations
  uint16_t  tilesWide   = width / tileWidth;
  uint16_t  tilesHigh   = height / tileHeight;

  // Allocate Space for Tiles in Return Container
  tiles                 = malloc( tilesWide * tilesHigh * sizeof( uint8_t* ) );

  #pragma omp parallel for default( none ) num_threads( cores )               \
            shared( input, width, height, tileWidth, tileHeight, tiles,       \
                    tilesWide, tilesHigh )                                    \
            private( i, j, m, n, x, y, startXPixel, endXPixel, startYPixel,   \
                     endYPixel, imagePixel, tile, tilePixel )

  // Break Up by Tiles in X and Y Direction
  for( i = 0; i < tilesHigh; i++ ) {
    for( j = 0; j < tilesWide; j++ ) {

      // Allocate Memory for this Tile
      tile        = malloc( 3 * tileWidth * tileHeight * sizeof( uint8_t ) );
      if( !tile ) {
        printf( "\nERROR: Tiler memory allocation failure!\n" );
      }

      // Tile Pixel Calculations
      startXPixel = j * tileWidth;
      endXPixel   = startXPixel + tileHeight;
      startYPixel = i * tileHeight;
      endYPixel   = startYPixel + tileHeight;

      // Fill this Tile with the Proper Contents
      for( m = startYPixel, y = 0; m < endYPixel; m++, y++ ) {
        for( n = startXPixel, x = 0; n < endXPixel; n++, x++ ) {

          // Locate Image Source Pixel and Tile Destination Pixel
          imagePixel            = ( m * width + n ) * 3;
          tilePixel             = ( y * tileWidth + x ) * 3;

          // Transfer Data
          tile[ tilePixel + 0 ] = input[ imagePixel + 0 ];  // Red Component
          tile[ tilePixel + 1 ] = input[ imagePixel + 1 ];  // Green Component
          tile[ tilePixel + 2 ] = input[ imagePixel + 2 ];  // Blue Component

        }
      }

      // Place this Tile into Tiles Container
      tiles[ i * tilesWide + j ] = tile;

    }
  }

  return tiles;

}



// END tiler.c  - EWG SDG
