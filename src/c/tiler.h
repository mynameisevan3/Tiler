
/*================
    tiler.h
    Tiler Header
  ================*/


// Include Guard
#ifndef TILER_H
#define TILER_H


// Inclusions
#include <stdint.h>


// Function Prototypes
uint8_t** tilerSerial( uint8_t *input, uint16_t width, uint16_t height,
                         uint16_t tileWidth, uint16_t tileHeight );
uint8_t** tilerOMP( uint8_t *input, uint16_t width, uint16_t height,
                         uint16_t tileWidth, uint16_t tileHeight, uint8_t cores );


// End Include Guard
#endif



// END tiler.h  - EWG SDG
