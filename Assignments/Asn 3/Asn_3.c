// Zaid Kaleem
// 103619897
// Assignment 3
// 60-256
// October 27th, 2014

//Libraries included
#include <stdio.h>
#include <string.h>

/*
 
 Input:
 1) Image file to read from
 2) Image file to write to
 3) Number of columns and rows
 4) Size of the image
 
 Output:
 Image is flipped vertically and then saved into a new image file
 
 */

void flip(FILE *fp_1, FILE *fp_2, int col, int row, long int size) {
    
    int i;
    char pic[col];
    
    fseek(fp_2, size, SEEK_SET);

    for (i = 0; i < row; ++i) {
        
        fread(pic, 1, col, fp_1);
        fseek(fp_2, -col, SEEK_CUR);
        fwrite(pic, 1, col, fp_2);
        fseek(fp_2, -col, SEEK_CUR);
    }
}

int main(int argc, char *argv[]) {
    
    FILE *fp_1, *fp_2;  // fp_1 is the file pointer for the input file and fp_2 is the file pointer for output file
    long int size;
    char temp[100];
    int col, row;
    
    if ((fp_1=fopen(argv[2], "r")) != NULL) { // argv[2] is the input file paremeter
    
        if ((fp_2=fopen(argv[3], "w")) != NULL) { // argv[3] is the output file paremeter
        
            fseek(fp_1, 0, SEEK_END);
            size = ftell(fp_1);
            rewind(fp_1);
                
            fgets(temp, 100, fp_1);
            fputs(temp, fp_2);

            fscanf(fp_1,"%d %d\n", &col, &row);
            fprintf(fp_2,"%d %d\n", col, row);

            fgets(temp, 100, fp_1);
            fputs(temp, fp_2);
                
            flip(fp_1, fp_2, col, row, size);   // Function call to flip the image
            
        }
            else {
                
                fprintf(stderr, "Error - Cannot open file: %s", argv[2]);   // Error displayed if file cannot be opened for writing
            }
    }
    
    else {
        
        fprintf(stderr, "Error - Cannot open file: %s", argv[1]);   // Error displayed if file cannot be opened for reading
    }
    
    fclose(fp_1);   // Closing input file
    fclose(fp_2);   // Closing output file
    
    return 0;
}
