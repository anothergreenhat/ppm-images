// read/write PPM (Portable Pixel Map) files
// CREDIT: R. Perry, Villanova University
// assumes 8-bit data with max 255
//
#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

// print error message and exit
//
static void error(const char *msg)
{
    fprintf(stderr,"ppm: %s\n",msg);
    exit(1);
}

// create a 2D array of unsigned char
//
static unsigned char **amalloc(int rows,int cols)
{
    unsigned char **a;

    if((a = malloc(rows*sizeof(char *))) == NULL || (a[0] = malloc(rows*cols)) == NULL)
        error("malloc failed.");

    for(int i = 1; i < rows; ++i) // set the row pointers
        a[i] = a[i-1] + cols;

    return a;
}

// create a new ppm structure
//
// initializes the ppm rows and cols fields,
// allocates but does not initialize the RGB data fields
//
ppm ppm_new(int rows,int cols)
{
    ppm p;

    p.rows = rows;
    p.cols = cols;

    p.r = amalloc(rows,cols);
    p.g = amalloc(rows,cols);
    p.b = amalloc(rows,cols);
    return p;
}

// read PPM data from stdin
//
ppm ppm_read(void)
{
    ppm p;  int rows,cols,max,r,g,b;

    if(getchar() != 'P' || getchar() != '6')
        error("input is not P6 PPM format");

    if(scanf("%i%i%i",&cols,&rows,&max) != 3)
        error("scanf() failed.");

    getchar(); // skip newline

    p = ppm_new(rows,cols);

    for(int i = 0; i < p.rows; ++i)
        for(int j = 0; j < p.cols; ++j)
        {
            r = getchar(); g = getchar(); b = getchar();
            if(b < 0) error("getchar() failed."); // getchar() is negative on EOF
            p.r[i][j] = r; p.g[i][j] = g; p.b[i][j] = b;
        }

    return p;
}

// write PPM data to stdout
//
void ppm_write(ppm p)
{
    printf("P6 %i %i 255\n",p.cols,p.rows);

    for(int i = 0; i < p.rows; ++i)
        for(int j = 0; j < p.cols; ++j)
        {
            putchar(p.r[i][j]); //for some reason, rgb is shifted left > gbr
            putchar(p.g[i][j]);
            putchar(p.b[i][j]);
        }
    free(p.r); free(p.g); free(p.b);
}

// Below adapted from above R. Perry work
// CREDIT: Joseph Madera
//

//read PPM data from file
//
ppm ppm_readf(const char *fname)
{
    FILE *infile = fopen(fname,"rb");
    ppm p;  int rows,cols,max,r,g,b;
    if(getc(infile) != 'P' || getc(infile) != '6')
        error("input is not P6 PPM format");

    if(fscanf(infile,"%i%i%i",&cols,&rows,&max) != 3)
        error("scanf() failed.");

    getc(infile); // skip newline

    p = ppm_new(rows,cols);

    for(int i = 0; i < p.rows; ++i)
        for(int j = 0; j < p.cols; ++j)
        {
            r = getc(infile); g = getc(infile); b = getc(infile);
            if(b < 0) error("getc() failed."); // getc() returns a negative value on EOF
            p.r[i][j] = r; p.g[i][j] = g; p.b[i][j] = b;
        }

    return p;

}

//write PPM data to file
//
void ppm_writef(ppm p, const char *fname)
{
    FILE *outfile = fopen(fname, "wb+");
    fprintf(outfile,"P6 %i %i 255\n",p.cols,p.rows);

    for(int i = 0; i < p.rows; ++i)
        for(int j = 0; j < p.cols; ++j)
        {
            putc(p.r[i][j],outfile); //for some reason, rgb is shifted left > gbr
            putc(p.g[i][j],outfile);
            putc(p.b[i][j],outfile);
        }
    free(p.r); free(p.g); free(p.b);
}

//make new PPM as a scale version of an existing PPM
//
ppm ppm_scale( ppm a,int scale)
{
    int row_scale=0,col_scale=0; 
    row_scale = col_scale = scale;
    ppm b = ppm_new(a.rows*row_scale,a.cols*col_scale);
    for(int i=0; i<b.rows; ++i)
    {
        for(int j=0; j<b.cols; ++j)
        {
            b.r[i][j] = a.r[i/row_scale][j/col_scale];
            b.g[i][j] = a.g[i/row_scale][j/col_scale];
            b.b[i][j] = a.b[i/row_scale][j/col_scale];
        }
    }
    return b;
}
