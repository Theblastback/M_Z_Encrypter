#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void Encode(char *); // String is Path to recipient
void Decode(char *); // String is mail/file name

// Argv[1] = Mode selection
// Argv[2] = File name to decode/encode
int main(int argc, char **argv){
        int Mode;

        if (argc < 3) {
                fprintf(stderr, "ERROR: Cannot initialize %s!\n", argv[0]);
                exit(1);
        }
        Mode = atoi(argv[1]);
        if (Mode == 1) // Encrypting message
                Encode(argv[2]);
        else if (Mode == 2) // Decrypting message
                Decode(argv[2]);
        else { // Error in arguement
                fprintf(stderr, "ERROR: Cannot determine mode!\n");
                exit(2);
        }

        return 0;
}

void Encode(char *Path) {
        FILE *Destination;
        char *Message;
        size_t Location;

        unsigned char Byte, Length;
        unsigned long int Letter, Maximum, Index, Token;

        // Assume path is to file. File already created in shell script.
        fclose(fopen(Path, "w"));
        Destination = fopen(Path, "a");
        if ( Destination == NULL ) {
                fprintf(stderr, "ERROR: ENCODE: Invalid Path %s!\n", Path);
                exit(3);
        }
        // Okay, now that the file is all hunky dorry, we can get down to business

        fprintf(stdout, "Restain yourself to only using [?] [,] [.] [!] [SPACE] for punctuation\nPlease type your message now:\n");
        getline(&Message, &Location, stdin);
        system("clear");
        fprintf(stdout, "Computing...\n");

        srand(time(NULL)); // Seed the rand function so that I can get separate random numbers each and every time
        Maximum = strlen(Message);

        for (Index = 0; Index < Maximum; Index++) { // Loops only for as long as length of message
                Token = rand(); // Returns random number size of 4 bytes
                Letter = Message[Index];
                if ( (Letter >= 65) && (Letter <= 90) )
                        Letter = Letter + 32; // Makes this lower case

                if ( (Letter < 48) || (Letter == 63) ) { // Punctuation detected. No need to assign a byte for a letter
                        switch (Letter) {
                                case (32): // Space detected
                                        Letter = 4;
                                        break;

                                case (46): // Period detected
                                        Letter = 5;
                                        break;

                                case (33): // Explamation point detected
                                        Letter = 6;
                                        break;

                                case (63): // Question mark detected
                                        Letter = 7;
                                        break;

                                case (44): // Commas detected
                                        Letter = 8;
                                        break;

                                default:
                                        Letter = 254;
                                        break;
                        }
                        if ( Letter != 254) {
                                Letter = Letter << 4; // Now this won't affect the first 4 bits of the randomized number (Critical)
                                Token = (Token | 240) ^ 240; // Ensures 16, 32, 64 and 128 bits are empty
                                Token = Token | Letter; // Now we have the punctuation token all sorted and created!
                        }
                } else { // Normal letter/number. Assign byte 1-3 and start morse proccess
                        // Assign random byte to number. Skip first bit
                        //0 = dot; 1 = dash
                        Byte = (rand() % 3) + 1; // Will give me byte between 1 - 3
                        Token = ((Token | 254) ^ 254) | (Byte << 4); // Makes bits 2 - 128 a 0, and then replaces the clean slate with the byte the char is in
                        switch (Letter) { // Organized by size, then alphabetically
                                case (101): // E 
                                        Letter = 0;
                                        Length = 1;
                                        break;

                                case (116): // T
                                        Letter = 1;
                                        Length = 1;
                                        break;

                                case (97): // A 
                                        Letter = 2; // Says letter is this in bits
                                        Length = 2;
                                        break;

                                case (105): // I
                                        Letter = 0;
                                        Length = 2;
                                        break;

                                case (109): // M
                                        Letter = 3;
                                        Length = 2;
                                        break;

                                case (110): // N
                                        Letter = 1;
                                        Length = 2;
                                        break;

                                case (100): // D
                                        Letter = 4;
                                        Length = 3;
                                        break;

                                case (103): // G
                                        Letter = 6;
                                        Length = 3;
                                        break;

                                case (107): // K
                                        Letter = 5;
                                        Length = 3;
                                        break;

                                case (111): // O
                                        Letter = 7;
                                        Length = 3;
                                        break;

                                case (114): // R
                                        Letter = 2;
                                        Length = 3;
                                        break;

                                case (115): // S
                                        Letter = 0;
                                        Length = 3;
                                        break;

                                case (117): // U
                                        Letter = 1;
                                        Length = 3;
                                        break;

                                case (119): // W
                                        Letter = 3;
                                        Length = 3;
                                        break;

                                case (98): // B 
                                        Letter = 8;
                                        Length = 4;
                                        break;

                                case (99): // C
                                        Letter = 5;
                                        Length = 4;
                                        break;

                                case (102): // F
                                        Letter = 4;
                                        Length = 4;
                                        break;

                                case (104): // H
                                        Letter = 0;
                                        Length = 4;
                                        break;

                                case (106): // J
                                        Letter = 14;
                                        Length = 4;
                                        break;

                                case (108): // L
                                        Letter = 2;
                                        Length = 4;
                                        break;

                                case (112): // P
                                        Letter = 6;
                                        Length = 4;
                                        break;

                                case (113): // Q
                                        Letter = 11;
                                        Length = 4;
                                        break;

                                case (118): // V
                                        Letter = 1;
                                        Length = 4;
                                        break;

                                case (120): // X
                                        Letter = 9;
                                        Length = 4;
                                        break;

                                case (121): // Y
                                        Letter = 13;
                                        Length = 4;
                                        break;

                                case (122): // Z
                                        Letter = 3;
                                        Length = 4;
                                        break;

                                case (48): // 0
                                        Letter = 31;
                                        Length = 5;
                                        break;

                                case (49): // 1
                                        Letter = 30;
                                        Length = 5;
                                        break;

                                case (50): // 2
                                        Letter = 28;
                                        Length = 5;
                                        break;

                                case (51): // 3
                                        Letter = 24;
                                        Length = 5;
                                        break;

                                case (52): // 4
                                        Letter = 16;
                                        Length = 5;
                                        break;

                                case (53): // 5
                                        Letter = 0;
                                        Length = 5;
                                        break;

                                case (54): // 6
                                        Letter = 1;
                                        Length = 5;
                                        break;

                                case (55): // 7
                                        Letter = 3;
                                        Length = 5;
                                        break;

                                case (56): // 8
                                        Letter = 7;
                                        Length = 5;
                                        break;

                                case (57): // 9
                                        Letter = 15;
                                        Length = 5;
                                        break;

                                default:
                                        Letter = 254;
                                        break;
                        }
                        Token = Token | (Length << 1); // Writes in the length for the character
                        Length--;
                        while ( (Length >= 0) && (Length != 255) ) {
                                Token = (Token | (1 << ((Byte * 8) + Length)) )^ ( 1 << ((Byte * 8) + Length)  ); // Will 0 out bits the character will write over
                                Length--;
                        }
                        Token = Token | (Letter << (Byte * 8)); // Places the letter (in 'binary morse') inside the 0'd out section of the number
                }
                if ( Letter != 254) // Once EOF has been reached, letter defaults to 254
                        fprintf(Destination, "%lu ", Token);

        }
        fprintf(Destination, "0");
        fclose(Destination);
}

void Decode(char *Path) {
        FILE *Input;
        unsigned long int Number;
        char Length, Byte, Letter, Offset; // Length of morse code message, byte it's located in, letter itself, Captitalizing first letter
        Offset = 32; // First letter should be capitalized

        Input = fopen(Path, "r");
        if ( Input == NULL ) {
                fprintf(stderr, "ERROR: Cannot open file %s for reading.\n", Path);
                exit(2);
        }
        fscanf(Input, "%lu", &Number);

        while ( Number != 0 ) {
                Number = Number >> 1; // Now first bit is start of length
                Length = Number & 7; // Gets the length of the letter
                Number = Number >> 3; // Now Byte location is first bit
                Byte = Number & 15; // Gets the byte location of the letter
                Number = Number << 4; // Now first 4 bits are 0, but number is back to where it was

                if ( Byte >= 4 ) { // Punctuation has been detected #####################################
                        switch (Byte) {
                                case (4): // Space
                                        Letter = 32;
                                        break;

                                case (5): // Period
                                        Offset = 32;
                                        Letter = 46;
                                        break;

                                case (6): // Explamation point
                                        Offset = 32;
                                        Letter = 33;
                                        break;

                                case (7): // Question mark
                                        Offset = 32;
                                        Letter = 63;
                                        break;

                                case (8): // Comma
                                        Letter = 44;
                                        break;
                        }

                } else { // Normal Letter detected ####################################################
                        while ( Byte > 0) { // Makes it so the byte the number is in is first
                                Number = Number >> 8;
                                Byte--;
                        }

                        Letter = 0;
                        for (Byte = 0; Byte < Length; Byte++) { // Have to grab bits only used by letter
                                Letter = Letter + ((Number & 1) << Byte); // Grabs the active bit, then shifts it to correct value; Then adds it onto
                                Number = Number >> 1; // Time to move onto the next bit
                        }

                        switch (Length) { // Going by length of message
                                case (1):
                                        switch (Letter) {
                                                case (0): // E
                                                        Letter = 101;
                                                        break;

                                                case (1): // T
                                                        Letter = 116;
                                                        break;

                                        }
                                        break;

                                case (2):
                                        switch (Letter) {
                                                case (0): // I
                                                        Letter = 105;
                                                        break;

                                                case (1): // N
                                                        Letter = 110;
                                                        break;

                                                case (2): // A
                                                        Letter = 97;
                                                        break;

                                                case (3): // M
                                                        Letter = 109;
                                                        break;

                                        }
                                        break;

                                case (3):
                                        switch (Letter) {
                                                case (0): // S
                                                        Letter = 115;
                                                        break;

                                                case (1): // U
                                                        Letter = 117;
                                                        break;

                                                case (2): // R
                                                        Letter = 114;
                                                        break;

                                                case (3): // W
                                                        Letter = 119;
                                                        break;

                                                case (4): // D
                                                        Letter = 100;
                                                        break;

                                                case (5): // K
                                                        Letter = 107;
                                                        break;

                                                case (6): // G
                                                        Letter = 103;
                                                        break;

                                                case (7): // O
                                                        Letter = 111;
                                                        break;

                                        }
                                        break;

                                case (4):
                                        switch (Letter) {
                                                case (0): // H
                                                        Letter = 104;
                                                        break;

                                                case (1): // V
                                                        Letter = 118;
                                                        break;

                                                case (2): // L
                                                        Letter = 108;
                                                        break;

                                                case (3): // Z
                                                        Letter = 122;
                                                        break;

                                                case (4): // F
                                                        Letter = 102;
                                                        break;

                                                case (5): // C
                                                        Letter = 99;
                                                        break;

                                                case (6): // P
                                                        Letter = 112;
                                                        break;

                                                case (8): // B
                                                        Letter = 98;
                                                        break;

                                                case (9): // X
                                                        Letter = 120;
                                                        break;

                                                case (11): // Q
                                                        Letter = 113;
                                                        break;

                                                case (13): // Y
                                                        Letter = 121;
                                                        break;

                                                case (14): // J
                                                        Letter = 106;
                                                        break;

                                        }
                                        break;

                                case (5):
                                        switch (Letter) {
                                                case (31): // 0
                                                        Letter = 48;
                                                        break;

                                                case (30): // 1
                                                        Letter = 49;
                                                        break;

                                                case (28): // 2
                                                        Letter = 50;
                                                        break;

                                                case (24): // 3
                                                        Letter = 51;
                                                        break;

                                                case (16): // 4
                                                        Letter = 52;
                                                        break;

                                                case (0): // 5
                                                        Letter = 53;
                                                        break;

                                                case (1): // 6
                                                        Letter = 54;
                                                        break;

                                                case (3): // 7
                                                        Letter = 55;
                                                        break;

                                                case (7): // 8
                                                        Letter = 56;
                                                        break;

                                                case (15): // 9
                                                        Letter = 57;
                                                        break;

                                        }
                                        break;

                        }
                }
                if ( (Letter >= 97) && (Letter <= 122) ) // Will attempt to captialize the first letter after a '!, ?, .'
                        Letter = Letter - Offset;
                else
                        Offset = Offset << 1;
                Offset = ((Offset >> 1) | 31) ^ 31;
                fprintf(stdout, "%c", Letter); // Print the letter to the screen
                fscanf(Input, "%lu", &Number);
        }
        fprintf(stdout, "\n");
        fclose(Input);
}
