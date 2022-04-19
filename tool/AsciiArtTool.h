//
// Created by liorb on 19/04/2022.
//

#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>

/**
* Ascii Art tool
*
* Compresses and decompresses the ascii art pictures
*
* The following functions are available:
*   asciiArtRead	        - Reads a given file and compresses it to an RLE list
*   asciiArtPrint           - Decompresses the RLEList into the requested file
*/


/**
* asciiArtRead: Reads a given file and compresses it to an RLE list
*
* This function receives a file that holds ascii art, reads the file and compresses the information into an RLE list.
*
* @param file - The file that holds the ascii art
* @return
*   NULL argument if there are any issues in the function
* 	The new RLEList that holds the ascii art characters
*/
RLEList asciiArtRead(FILE* in_stream);



/**
*   asciiArtPrint: Decompresses the RLEList into the requested file
*
* @param list - The RLE list that holds the ascii art characters
* @param file - The file that the picture needs to be written to
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater
* 	RLE_LIST_SUCCESS if the decompression was completed successfully
*
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


#endif // HW1_ASCIIARTTOOL_H
