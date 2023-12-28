#include "enigma.h"

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
// Follow chapter 1 (Read from keyboard and put in array)
// Assume all input is correct
void Get_Message(char msg[]) {
    char c;
    int i = 0;
    while ((c = getchar()) != '\n') {
        msg[i] = c;
        i++;
    }

    // Insert null terminator
    msg[i] = '\0';
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]) {    
    scanf("%4s", which_rotors);
    int numRotors = strlen(which_rotors);

    return numRotors;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
// use scanf (takes care of typecasting for us)
int Get_Rotations() {
    int numRotation = 0;
    scanf("%d", &numRotation);

    return numRotation;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
// Copy from Rotor constants
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]) {
    for (int i = 0; i < strlen(which_rotors); i++) {
        strcpy(encryption_rotors[i] ,ROTOR_CONSTANTS[which_rotors[i] - 48]);
    }

    return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
    if (rotations == 0) {
        return;
    }

    int j = 0;
    for (int i = 0; i < 4; i++) {
        char secondHalf[26];
        char firstHalf[26];

        while (j < (26 - rotations)) {
            secondHalf[j] = encryption_rotors[i][j];
            j++;
        }
        secondHalf[j] = '\0';

        for (int z = 0; z < rotations; z++) {
            firstHalf[z] = encryption_rotors[i][j];
            j++;
        }

        firstHalf[rotations] = '\0';

        j = 0;

        strcpy(encryption_rotors[i], firstHalf);
        strcat(encryption_rotors[i], secondHalf);

        encryption_rotors[i][26] = '\0';
    }

    return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]) {
    int i = 0;

    while (msg[i] != '\0') {
        if (msg[i] == ' ') {
            encrypted_msg[i] = ' ';
            i++;
            continue;
        }

        int originalIndex = (int) msg[i] - 65;
        int nextIndex = originalIndex;
        char nextChar;

        for (int j = 0; j < num_active_rotors; j++) {
            nextChar = encryption_rotors[j][nextIndex];
            nextIndex = (int) nextChar - 65;
        }

        encrypted_msg[i] = nextChar;
        i++;
    }

    encrypted_msg[i] = '\0';
    return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
    int i = 0;

    while (encrypted_msg[i] != '\0') {
        if (encrypted_msg[i] == ' ') {
            decrypted_msg[i] = ' ';
            i++;
            continue;
        }

        char encryptChar = encrypted_msg[i];

        for (int j = num_active_rotors - 1; j >= 0; j--) {
            for (int z = 0; z < 26; z++) {
                if (encryptChar == encryption_rotors[j][z]) {
                    encryptChar = ROTOR_CONSTANTS[0][z];
                    break;
                }
            }
        }

        decrypted_msg[i] = encryptChar;
        i++;
    }

    decrypted_msg[i] = '\0';
    return;
}