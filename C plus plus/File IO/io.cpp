/**
 * Written By Prashant Thirumal
 * 
 * First part uses open, read and write
 * Second part uses fopen fread and fwrite
 * Third part uses memory mapped file (MMF)
 * 
 **/


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;



// Helper method to parse the file content
// Essentially swaps the case of a character
char upper_to_lower(char c){
    if (islower(c)) {
        return (toupper(c));
    }
	if (isupper(c)) {
         return (tolower(c));
    }      
    else {
        return c;
    }
}

// Helper method to get user input
int choice(){
    int input;
    cout << "Which File I/O method would you like to use?" << endl;
    cout << "1. open, read and write" << endl;
    cout << "2. fopen, fread, fwrite" << endl;
    cout << "3. Memory mapped file" << endl;
    cout << "ENTER THE CORRESSPONDING NUMBER" << endl;
    cin >> input;
   
    if(!cin){
        cin.clear();
		cout << "Invalid input!!! Please try again\n\n";
        choice();
    }

    return input;
}

// Part 1 using open, read and write
int open_read_write(char* filename) {
    cout << "==========================================================" << endl;
    cout << "\nUSING OPEN READ AND WRITE\n" << endl;
    
    // Open the input file
    int src = open(filename, O_RDWR | O_LARGEFILE);

    if (src < 0){
        cout << "ERROR OPENING FILE (open)" << endl;
    }

    // Get size of file and create buffer
    size_t filesize = lseek(src, 0, SEEK_END);
    char *buffer = (char*)malloc(sizeof(char) * filesize);
    
    // Read from file and into buffer
    cout << "Reading in the file\n" << endl;
    lseek(src, 0, SEEK_SET);
    size_t retr = read(src, (char*)buffer, sizeof(char) * filesize);
   
    if (retr < 0){
        cout << "ERROR READING FROM FILE (open_read_write)" << endl;
    }

    // Reset the seek pointer to the beginning of the file
    lseek(src, 0, SEEK_SET);

    // Parse buffer
    for (int i =0; i < sizeof(char) * filesize; i++ ){
        buffer[i] = upper_to_lower(buffer[i]);
    }

    // Clear and write back to the output file
    ftruncate(src, 0);
    size_t ret = write(src, buffer, sizeof(char) * filesize);
    if (ret < 0){
        cout << "ERROR WRITING TO FILE (open_read_write)" << endl;
    }
    
    // Close file and free buffer
    close(src);
    free(buffer);

    cout << "Finshed writing to the file\n" << endl;
    cout << "==========================================================" << endl;
    return 0;

}

// Part 2 using fopen, fread and fwrite
int fopen_fread_fwrite(char* filename){
    cout << "==========================================================" << endl;
    cout << "\nUSING FOPEN FREAD AND FWRITE\n" << endl;

    // Open the input file
    cout << "Reading in the file\n" << endl;

    FILE *fp = fopen(filename, "r+");
    
    if (fp == NULL){
        cout << "Could not open file (fread)" << endl;
        exit(0);
    }

    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    long lSize = ftell (fp);
    rewind (fp);

    // allocate memory to contain the whole file:
    char *buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        cout << "Malloc error (fread)" << endl; 
        exit (2);
    }

    // copy the file into the buffer:
    size_t result = fread (buffer,1,lSize,fp);
    if (result != lSize) {
        cout << "Reading Error (fread)" << endl; 
        exit (3);
    }

    // Parse the buffer
    for(int i = 0; i < lSize; i++){
        buffer[i] = upper_to_lower(buffer[i]);
    }

    // Clear the contents of the file and write to it
    fp = freopen(filename, "w", fp);
    fwrite(buffer, sizeof(buffer[0]), lSize, fp);
    cout << "Wrote to the file\n" << endl;

    // Close the file and free the buffer
    fclose(fp);
    free(buffer);
    cout << "==========================================================" << endl;
    return 0;
}

// Part 3 using memory mapped
int memory_mapped_file(char* filename){
    cout << "==========================================================" << endl;
    cout << "\nUSING MEMORY MAPPED FILE\n" << endl;

    cout << "Reading in File\n" << endl;

    int src = open(filename, O_RDWR | O_LARGEFILE);
    
    if (src < 0){
        cout << "Could not open source file (mmap)" << endl;
        exit(0);
    }
    
    // obtain file size:
    struct stat filestat{};
    if(fstat(src, &filestat)){
        cout << "ERROR OBTAINING FILESIZE (MMAP)" << endl;
        exit(0);
    }

    off_t filesize = filestat.st_size;

    // memory map the file
    char *buffer = (char*) mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_SHARED, src, 0);
    if (buffer == MAP_FAILED){
        cout << "MMAP FAILED" << endl;
        exit(0);
    } 
    cout << "Memory mapped the file\n" << endl;

    // Close source file
    close(src);

    // Parse the memory mapped file
    for(off_t i = 0; i < filesize; i++){
        buffer[i] = upper_to_lower(buffer[i]);
    }


    cout <<"Wrote to the file\n" << endl;

    // Free the mapped memory
    munmap(buffer, filesize);

    cout << "==========================================================" << endl;

    return 0;
}

// Main methood
int main(int argc, char **argv){
    // Get filename from user
    if (argc != 2){
        cout << "Usage: <filename>" << endl;
        exit(0);
    }

    char* filename = argv[1];
    int input = choice();

    if (input == 1){
        open_read_write(filename);
    }
    else if(input == 2){
        fopen_fread_fwrite(filename);
    }
    else if(input == 3){
        memory_mapped_file(filename);
    }

    else {
        cout << "Invalid number chosen. Exiting program now" << endl;
        exit(0);
    }

    

    return 0;
}
