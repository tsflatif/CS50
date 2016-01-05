/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    FILE* rawData = fopen("card.raw", "r");
  
    if (rawData == NULL)
    {
        fprintf(stderr, "Could not create card.raw.\n");
        return 3;
    }

    FILE* output = NULL;
    
    int jpgCount = 0;
    
    //read till end of file
    while (!feof(rawData))
    {
        uint8_t buffer[512];
        char jpgName[8];

        //test for start of jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            //close the previous file, if any
            if (output != NULL)
            {
                fclose(output);
            }
            //make new output file
            sprintf(jpgName, "%03d.jpg", jpgCount);
            output = fopen(jpgName, "w");            
            jpgCount++;
            
            //write buffer into new file
            fwrite(buffer, sizeof(buffer), 1, output);
        }
        else
        {
            if (jpgCount > 0) //to skip initial blank space
            {
                //write buffer into new file
                fwrite(buffer, sizeof(buffer), 1, output);            
            }
        }
        
        //read 512 bytes into a buffer
        fread(buffer, sizeof(buffer), 1, rawData);       
    }
    //close last jpeg, if open
    if (jpgCount > 0)
    {
        fclose(output);
    }

    fclose(rawData);

    return 0;
}
