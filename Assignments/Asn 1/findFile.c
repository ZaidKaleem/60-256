/*
 Zaid Kaleem
 103619897
 60-256
 Assignment 1
 Sep 22, 2014
 
 
 Input: Target directory (optional) and the file name
 Output: Whether or not the searched file is found and also prints if it's a file or a directory
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

// Function to check if the file exists and if it can be opened (to check if it's a file or a directory)
int checkF(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *dirp;
    
    // If no file name is provided
	if (argc == 1){
		printf("No filename given.\n");
		return 0;
	}
	else
		dp = opendir("./");
    //If directory is not empty then program finds the file and checks if it's indeed a file using the checkF function
	while ((dirp=readdir(dp)) != NULL)
		if(checkF(argv[1]) == 1)
            printf("Found and it is a file");
        else
            printf("Not found");
    
	closedir(dp);
	return 0;
}
