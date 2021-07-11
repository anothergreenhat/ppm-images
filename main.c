/*
 *  Joseph Madera
 *  Generates a ppm image of your choosing
 *  netpbm's "pnmtopng" command can be used to convert the .ppm file to a .png
 *
 *  Sample runs on the command line could be: 
 *      
 *   $ ./main 1 colors.txt blocks.ppm
 *   $ pnmtopng blocks.ppm > blocks.png
 *   $ open blocks.png
 *   ...
 *   $ ./main 2 | pnmtopng > circles.png
 *   ...
 *   $ ./main 3 | pnmtopng > heart.png && open heart.png
 *
 *  Expected format for input colors_file:
 *
 *   the first line has a single value which is the number of rows
 *   the second line has a single value and is the number of cols
 *   a number in the range [0..255] on each line
 *   total number of lines in file MUST be exactly divisible by 3
 *  
 *  NOTE: building this program with $ gcc -Wall will reveal a warning when attempting to fscanf()
 *  into the clrs[] array due to an implicit conversion from &i (int) when storing that value in the 
 *  unsigned char array clrs[]. this is expected.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "fun.h"

int main(int argc, char *argv[])
{
    if(argc >= 2)
    {
        switch(atoi(argv[1]))
        {
            case 1:
            { 
                // The array below creates an image with six pixels
                // RED   GREEN BLUE
                // WHITE BLACK GREY
                // 255,0,0,      0,255,0,    0,0,255,
                // 255,255,255,  0,0,0,      85,85,85

                FILE *colors_file = fopen(argv[2],"rb");
                if(!colors_file) {fprintf(stderr,"could not open file. aborting.\n"); exit(1);}

                int rows, cols, i = 0;
                fscanf(colors_file, "%i%i",&rows, &cols);
                unsigned char clrs[rows*cols*3];

                while(EOF != fscanf(colors_file,"%i",&clrs[i])) ++i;

                if((i%3) || ((i/3) < rows*cols) || ((i/3) > rows*cols))
                {
                    fprintf(stderr,"input color array with incorrect number of elements or triplet RGB values. aborting\n");
                    exit(1);
                }
                ppm_blocks(rows,cols,clrs,argv[3]);
                break;
            }
            case 2:
                ppm_circles(argv[2]);
                break;
            case 3:
                ppm_heart(argv[2]);
                break;
            default:
                fprintf(stderr,"not a valid ppm choice arg\n");
                return 1;
                break;
        }
        // if the argument intended to be used as the filename is not NULL, print a friendly message revealing success
        // otherwise do nothing so as to properly write the file to stdout as intended
        if(argv[3] || ((atoi(argv[1]) == 1) && argv[3])) printf("output file %s successfully generated\n",argv[argc-1]);
    }
    else
    {
        fprintf(stderr,"no args passed\narg options are:\n\t./main <1,2,3> <blocks input filename (optional)> <output filename (optional)>\n\t1- ppm_blocks()\n\t2- ppm_circles()\n\t3- ppm_heart()\nif no output filename argument is passed, ppm image is passed to stdout\n");
        return 1;
    }
    return 0;
}

/*  else if (argc == 2) //writing to stdout
    {
        switch(atoi(argv[1]))
        {
            case 1:
            { 
                char clrs[] = {255,0,0,      0,255,0,    0,0,255,
                               255,255,255,  0,0,0,      85,85,85};
                ppm_blocks(2,3,clrs,NULL);
                break;
            }
            case 2:
                ppm_circles(0,NULL);
                break;
            case 3:
                ppm_heart(0,NULL);
                break;
            default:
                fprintf(stderr,"not a valid ppm choice arg\n");
                return 1;
                break;
        }
    }
*/
