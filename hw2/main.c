#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) { 
    
    FILE *fileToCopy,*fileToWrite;
    char *buffer,*bufferToCopy;
    long filelen;
    int j=0;

    fileToCopy = fopen(argv[1], "rb");         
    fseek(fileToCopy, 0, SEEK_END);          
    filelen = ftell(fileToCopy);            
    rewind(fileToCopy);    
    buffer = (char *)malloc((filelen+1)*sizeof(char));                   
    bufferToCopy = (char *)malloc((2*(filelen))*sizeof(char)); 

     for(int i = 0; i < filelen; i++) {
       fread(buffer+i, 1, 1, fileToCopy); 
    }

    for(int i = 0; i < filelen; i++) {
     	bufferToCopy[j] = buffer[i];
     	bufferToCopy[j+1] = buffer[i];
	j=j+2;    
    }

    fileToWrite=fopen(argv[2], "wb");
    fwrite(bufferToCopy, sizeof(bufferToCopy[0]), (2*(filelen)), fileToWrite);
    fclose(fileToCopy); // Close the file
    fclose(fileToWrite);
    return 0;
}
