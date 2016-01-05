/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n < 1 || n > 100)
    {
        printf("\"n\" must be between 2 and 100\n");
        return 1;
    }   

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, new_bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    new_bf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, new_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    new_bi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int oldWidth = bi.biWidth;
    int oldHeight = abs(bi.biHeight);
    
    new_bi.biWidth =  bi.biWidth * n;          
    new_bi.biHeight = bi.biHeight * n;
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    int newPadding =  (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //change image and file size
    new_bi.biSizeImage = (new_bi.biWidth * sizeof(RGBTRIPLE) + newPadding) * abs(new_bi.biHeight);
    new_bf.bfSize = bf.bfSize - bi.biSizeImage + new_bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //iterate over scanlines
    for (int i = 0; i < oldHeight; i++)
    {
        // Read each scanline n times
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < oldWidth; k++)
            {
                RGBTRIPLE triple;
                
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int l = 0; l < n; l++)
                    fwrite(&triple,sizeof(RGBTRIPLE), 1, outptr);
            }
            
            //add new padding
            for (int l = 0; l < newPadding; l++)
                fputc(0x00, outptr);
            
            // go back to beginning of a scanline
            if (j < n-1)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);    
        }
        
        //skip any old padding
        fseek(inptr, padding, SEEK_CUR);
    }

    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
