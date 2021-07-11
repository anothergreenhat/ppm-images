//  makes a pixel rectangle of size defined, scaled up
//  rows = num rows in block pixel image
//  cols = num cols in block pxel image
//  colors = array of color values in bytes (char) from left to right starting from top pixel
//  fname = specify filename, NULL if writing to stdout
//
void ppm_blocks(int rows, int cols, unsigned char colors[], char *fname);

// make a fun intersecting circles image
// fname = specify filename, NULL if writing to stdout
//
void ppm_circles(char *fname);

// make a fun heart using a velocity function
// some credit for implementation to R. Perry, Villanova University
// fname = specify filename, NULL if writing to stdout
//
void ppm_heart(char *fname);
