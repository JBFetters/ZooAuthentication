// ZooAuthentication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
* Main Program:     Zoo Authentication System
* Author:           J. Barrett-Fetters
* Date:             March 22, 2022
* Purpose:          This program the Zoo Authentication System. The program ask user to input valid crendentials to access the correct system per their privilage roles.
Modification History:
*
*
*
*
*
*
*
*
*
*/


#include <iostream>
#include <string>
#include <fstream>

#include "UserInfo.h" //User Information Class
#include "MD5.h" // MD5 Class
using namespace std;


void outputTextFile(string filePathName); // declaring Output Text File Function
string changeString(string change); // declaring changeString Function; takes user ID and converts to lowercase



int main()
{

    UserInfo myUser = UserInfo(); // Instantiation of the UserInfo Class
    int attempts = 0;
    bool numofAttemps = true; // Nunmber of attempts set to true

    //Variables for user inputs
    string userId; // lowercase of user id inputs
    string getUserId;  // gets user id inputs
    string userPassword; // User inputs User Password
    string originalPassword; // original password convered to MD5
    string credentialPassword; // User Credential Password from Credential File
    string credentialId; // Credential ID from Credential File
    string credentialRole; // Crednetial role from the credential file
    bool validCredentials{}; // valid crendentials
    bool userIdValid = false; // UserID is valid set to false
    bool exitProgram = false; // exitProgram set to false

    //Variables for reading credential file
    string row[6]; // row in credential file
    string column[4]; // column in credential file
    string data[6][4]; // data in crednetila file to a 2D Array
    int index = 0; // Index
    int position = 0; // Position
    fstream newFile; // variable for text file
    string passwordHash; // password hashed from credential file


    // Reading Credential file
    newFile.open("Credentials.txt"); // open crendeital file
    if (newFile.is_open()) // if the file is open
    {
        string tp; // variable for string tp
        index = 0; // initilize index
        position = 0; // initilize position

        while (getline(newFile, tp)) // while readline in new file
        {
            row[index] = tp; //set line to row [index = 0] to tp
            data[index][0]; // set data as row and position 0

            for (int x = 0; x < 4; x++) // for x = 0, x less than 4 increment x
            {
                position = tp.find('\t'); // if tab not found return -1, if found returns position of tab
                if (position > 0) // if position great than 0
                {
                    data[index][x] = tp.substr(0, position);
                    position = position + 1;
                    tp.erase(0, (position));
                }
                else
                {
                    data[index][x] = tp.substr(0, tp.length());

                }
                //compare user inputs with credentials

                if (originalPassword == data[index][1])
                {
                    originalPassword = true;
                    myUser.setUserCredPass(passwordHash);
                }

                if (userId == data[index][0])
                {
                    userId = true;
                    myUser.setUserCred(credentialPassword);
                }

            }index++; // increment index
        }newFile.close(); //close file
    }
    else
    {
        cout << "File did not open" << "\n";
    }


    //***Starts Main Program***

    do
    {
        //User Welcome message
        cout << "***WELCOME*** \n";

        cout << "Enter User ID \n";
        cout << " Or exit to leave \n";


        getline(cin, getUserId); ////User ID 

        userId = changeString(getUserId); // Calls changeUserId Fuction to change user id to all lowercase
        myUser.setUserId(userId);

        if (userId != "exit")// if userId does not equal exit
        {
            index = 0; // initialized index to zero

            while (validCredentials != true && index < 6) // searches crendential file verify user name is found
            {
                if (userId == data[index][0])
                {
                    validCredentials = true; //user name was found
                    userIdValid = true;  // user Id was found
                }
                index++; // increments index
            }
            if (validCredentials == true) // if validCrednetials equal to true
            {
                validCredentials = false; // reset to false

                // do-while loop to vaildate password and user crendentials. 
                // If user inputs incorrect password the program will not request to input user ID and Password as the user ID had already been validated.
                do
                {
                    cout << "Enter Password: \n"; // Enter User Password
                        //getline of user input
                        //ws extract all whitepace character
                    getline(cin >> ws, userPassword); //getline of user password input; extract all whitespaces (ws) character
                    myUser.setUserPass(userPassword); // set userpassword in myuser UserInfo class

                    //Hash Password
                    originalPassword = md5(userPassword); // set originalPassword with the MD5 hash from the input from user
                    myUser.setHassPass(originalPassword); // set hassPass from myUser User Info class

                    index = 0;  // initialize index to zero for password
                    validCredentials = false;  // initialize validCredentials to to false for password

                    while (validCredentials != true && index < 6)   //  search credentials to see if password is found
                    {
                        if (originalPassword == data[index][1])
                        {
                            validCredentials = true;        // password was found
                            credentialRole = data[index][3];      // set role equal to the permission for the user
                        }
                        index++; // index until user inputes match credential file
                    }
                    if (validCredentials == true) // if userId is equal to credential file user ID and originalPassword is credential file hashed password
                    {
                        if (validCredentials == true) // if valid crednetials equal to true
                        {
                            // original the credential file password and number of attempts are less than or equal to 3
                            if (credentialRole == ("veterinarian")) // credential role equals vet
                            {
                                outputTextFile("Veterinarian.txt"); // Outputs Veterinarian access priviaged to

                            }
                            if (credentialRole == ("admin")) // credential role equals admin
                            {
                                outputTextFile("Admin.txt"); // Outputs Admin access priviaged to

                            }
                            if (credentialRole == ("zookeeper")) // credentila role equals zookeeper
                            {
                                outputTextFile("Zookeeper.txt"); // Outputs Zookeeper access priviaged to
                            }
                            validCredentials == true;
                            attempts = 0;
                        }
                    }
                    else //else password was incorrect
                    {
                        cout << "Password Incorrect! TRY AGAIN" << endl;
                        attempts++; //increment attempts
                        validCredentials == false; //set validCrednetials to false
                        exitProgram = true; // set exitProgram to true;
                    }
                } while ((!validCredentials) && attempts < 3); // (vaildCred && attempt) || (valid Cre || attempt)
            }
            else // user id incorrect
            {
                if (attempts < 2)
                {
                    cout << "\n";
                    cout << "User Name incorrect! Try Again!" << endl;
                    attempts++;
                }
                else
                {
                    cout << "\n";
                    cout << "User Name incorrect! Try Again!" << endl;
                    exitProgram = true;
                }
            }
        }
        else // User enter exit
        {
            cout << "\n";
            cout << "You have logged out" << endl;
            exitProgram = true;
        }

    } while (exitProgram == false); // while password is correct or user id is correct keep running
}

//Function to opena file, read a file and close a file
void outputTextFile(string filePathName)
{
    fstream outputTextFile; //File variable
    outputTextFile.open(filePathName); // opening the text file
    string line; // line variable

    while (getline(outputTextFile, line)) // while getline in text file
    {

        cout << line << endl; // output the line in text file
    }
    outputTextFile.close(); // close file
}

string changeString(string change) //Function Converts Users Id String to Lowercase

{
    for (int x = 0; x < change.length(); x++) // index x until x less than the length of change

    {
        if (change[x] >= 'A' && change[x] <= 'Z') // if the change[x] greater than ascii A and less than ascii Z
        {
            change[x] = change[x] + 32; // user id array [x],  add 32 (decial); 'A' = 65; 65+32 = 97; '97' = a
        }
    } return change; //returns user id all lowercase

}