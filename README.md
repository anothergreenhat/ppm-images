# ppm-images
Generates a ppm image of your choosing
netpbm's "pnmtopng" command can be used to convert the .ppm file to a .png
## Usage
`./main <1,2,3> <colors array filename (optional)> <output filename (optional)>`
Option 1 will create an image with the specifications defined by the colors array filename you input. See below for details.

Option 2 will create an image with three intersecting circles.

Option 3 will create an image with a heart and some cool colors and lines.

Include the optional filename argument to route the output image to that file; otherwise, the program will output the image to stdout.

### Sample runs 
`$ ./main 1 colors.txt blocks.ppm`

`$ pnmtopng blocks.ppm > blocks.png`

`$ open blocks.png`

...


`$ ./main 2 | pnmtopng > circles.png`

...


`$ ./main 3 | pnmtopng > heart.png && open heart.png`

## Specifications
### Input Colors File
The colors array filename referred to above looks for a simple text file in the same folder as the executable that has the number or rows and columns of blocks of solid color being produced, and follows with triplets of RGB color values. 


The first line has a single value which is the number of rows, the second line has a single value and is the number of columns, and the remaining values must be numbers in the range `[0..25]`, and there must be exactly `rows*columns` values remaining in the file. `rows*columns` must be a number divisible by 3. 
## Note
Building this program with $ gcc -Wall will reveal a warning when attempting to fscanf() into the clrs[] array due to an implicit conversion from &i (int) when storing that value in the unsigned char array clrs[]. this is expected
