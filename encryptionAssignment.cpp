/*************************************************
* Erica Buchanan           Encryption Assignment *
* ICS4U                                          *
* 24/04/2021                                     *
*                                                *
* This assignment reads in a keyword and message *
* from a file, and encrypts the message using    *
* the keyword.                                   *
*************************************************/

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Prototypes
int read_file(ifstream &inputFile, char key[], char message[]);
void remove_badChars(char inMessage[], char outMessage[]);
void encode_message(char key[], char message[], char encodedMessage[]);

int main(){
    // Declare and Initialize variables
    char keyword[7] = "";
    char message[61] = "";
    char goodMessage[61] = "";
    char encodedMessage[61] = "";

    // Open File
    ifstream inFile("encode.dat");

    // Read data from file after making sure it is open
    if (read_file(inFile, keyword, message) == -1){
        return -1;
    }else{
        // Remove bad characters, encode the message and print both to screen with the keyword
        cout << "The keyword is: " << keyword << endl;
        remove_badChars(message, goodMessage);
        cout << "The message to encode is: " << goodMessage << endl;;
        encode_message(keyword, goodMessage, encodedMessage);
        cout << "The encoded message is: " << encodedMessage << endl;
    }
    return 0;
}

/* This function makes sure the file is open and if it is, it reads the keyword and the message from the file
the key array represents the keyword and the message array is for the message*/
int read_file(ifstream &inputFile, char key[], char message[]){
    // Declare and initialize variable
    int i = 0;
    // Check if file is open
    if (!inputFile.is_open()){
        cout << "Error. Could not open file." << endl;
        return -1;
    }
    // Read key and message from file if it is open
    else{
        inputFile >> key;
        while (!inputFile.eof()){
            inputFile >> message[i];
            i++;
        }
        inputFile.close();
        return 0;
    }
}

/* This function removes any characters other than capital A to Z from the message, inMessage
represents the message with all the original characters and outMessage is the message with only
characters from A to Z.*/
void remove_badChars(char inMessage[], char outMessage[]){
    // Declare and initialize variables
    int i = 0;
    int index = 0;
    // Remove all characters outside of the range from A to Z and put all good characters in outMessage
    for (i; i < strlen(inMessage); i++){
        if (inMessage[i] >= 'A' && inMessage[i] <= 'Z'){
            outMessage[index] = inMessage[i];
            index++;
        }
    }

}

/* This function encodes the message using the key that was read in from the file*/
void encode_message(char key[], char message[], char encodedMessage[]){
    for (int i = 0; i < strlen(message); i++){
        // Encodes message by adding the corresponding keyword value
        encodedMessage[i] = message[i]+(key[i%strlen(key)]-65);
        // If the new value is outside of the range from A to Z, it is brought back within the range
        if (encodedMessage[i] > 90){
            encodedMessage[i] -= 26;
        }
    }
}
