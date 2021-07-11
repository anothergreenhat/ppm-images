#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// read/write PPM (Portable Pixel Map) files

// r,g,b represent the RGB color planes (red, green, blue)
//
typedef struct
{
  int rows, cols; unsigned char **r, **g, **b;
}
ppm;


// read PPM data from stdin
//
ppm ppm_read( void);

// read PPM data from file
//
ppm ppm_readf( const char *);

// make new PPM as a scale version of an existing PPM
//
ppm ppm_scale( ppm, int);

// write PPM data to stdout
//
void ppm_write( ppm);

//write PPM data to file
//
void ppm_writef( ppm, const char *);


// create a new ppm structure
//
// initializes the ppm rows and cols fields,
// allocates but does not initialize the RGB data fields
//
ppm ppm_new( int rows, int cols);

#ifdef __cplusplus
}
#endif 
