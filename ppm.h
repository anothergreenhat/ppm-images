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

/*
 * Example usage:
 *  allocate new ppm and set values on your own. write to stdout as a scaled version
            ppm a = ppm_new(2,3);

            a.r[0][0]=255;  a.r[0][1]=0;    a.r[0][2]=0;
            a.g[0][0]=0;    a.g[0][1]=255;  a.g[0][2]=0;
            a.b[0][0]=0;    a.b[0][1]=0;    a.b[0][2]=255;

            a.r[1][0]=255;  a.r[1][1]=0;    a.r[1][2]=85;
            a.g[1][0]=255;  a.g[1][1]=0;    a.g[1][2]=85;
            a.b[1][0]=255;  a.b[1][1]=0;    a.b[1][2]=85;
            
            ppm_write(ppm_scale(a,100));

 *  make a fun intersecting circles image using stdout
 *              
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
            ppm_write(a);
 *           
 *   read from file fname and write to file "out.ppm"
            ppm_writef(ppm_readf(fname),"out.ppm");
 *
 *   make a fun heart using a velocity function
            
            double v(double a)
            {
                double t = fabs(tan(a));  
                return pow(t,1/t);
            }
            
            ...

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
            ppm_write(a);
 *
 *
 */ 
