#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Example usage:

//  makes a pixel rectangle of size defined, scaled up
//  rows = num rows in block pixel image
//  cols = num cols in block pxel image
//  colors = array of color values in bytes (char) from left to right starting from top pixel
//  fname = specify filename, NULL if writing to stdout
//
void ppm_blocks(int rows, int cols, unsigned char colors[], char *fname)
{
    ppm a = ppm_new(rows,cols);
    int k = 0;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < cols; ++j, k+=3)
        {
            a.r[i][j] = colors[k];
            a.g[i][j] = colors[k+1];
            a.b[i][j] = colors[k+2]; //fill this pixel with the values from the in-order color array
        }
    }
    if(fname) // ==1, set, write to file
        ppm_writef(ppm_scale(a,100),fname);
    else
        ppm_write(ppm_scale(a,100));
}

// make a fun intersecting circles image
// fname = specify filename, NULL if writing to stdout
//
void ppm_circles(char *fname)
{
    typedef struct { int x,y; } Circle;
    Circle r,g,b;

    r.x=180; r.y=180;
    g.x=360; g.y=180;
    b.x=270; b.y=360;

    int rad=150;

    ppm a = ppm_new(545,545);

    for(int i=0; i<a.rows; ++i)
    {
        for(int j=0; j<a.cols; ++j)
        {
            a.r[i][j]=a.b[i][j]=a.g[i][j]=255;
            if((sqrt((i-r.y)*(i-r.y) + (j-r.x)*(j-r.x)))<rad)
                a.r[i][j]=0;
            if((sqrt((i-g.y)*(i-g.y) + (j-g.x)*(j-g.x)))<rad)
                a.g[i][j]=0;
            if((sqrt((i-b.y)*(i-b.y) + (j-b.x)*(j-b.x)))<rad)
                a.b[i][j]=0;
        }
        for(int j=0; j<a.cols; ++j)
        {
            if((a.r[i][j])&&(!a.b[i][j]&&!a.g[i][j]))
                a.r[i][j]=255;
            if((a.g[i][j])&&(!a.r[i][j]&&!a.b[i][j]))
                a.g[i][j]=255;
            if((a.b[i][j])&&(!a.r[i][j]&&!a.g[i][j]))
                a.b[i][j]=255;
        }
    }
    if(fname)
        ppm_writef(a,fname);
    else
        ppm_write(a);
}

static double v(double a)
{
    double t = fabs(tan(a));  
    return pow(t,1/t);
}

// make a fun heart using a velocity function
// some credit for implementation to R. Perry, Villanova University
// fname = specify filename, NULL if writing to stdout
//
void ppm_heart(char *fname)       
{

    ppm a = ppm_new(600,600);
    double xc = 600/2.0,yc = 600-1,scale = 600/1.6;
    for(int i=0; i<a.rows; ++i)
    {
        for(int j=0; j<a.cols; ++j)
        {
            double dy = i-yc,dx = j-xc,ang = atan2(dy,dx),r = scale*v(ang);
            double d = hypot(dy,dx);
            if(d < r)
            {
                a.r[i][j] = (unsigned char) (i+j*6);
                a.g[i][j] = (unsigned char) ((j*500)/i);
                a.b[i][j] = (unsigned char) (i+j*4);
            } // heart inside
            else
            {
                a.r[i][j] = a.g[i][j] = a.b[i][j] = 255;
            } // white outside
        }
    }
    if(fname)
        ppm_writef(a,fname);
    else
        ppm_write(a);
}
