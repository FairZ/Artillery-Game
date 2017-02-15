#include<iostream>													//initialization of necessary libraries for: cout, cin,
#include<stdlib.h>													//srand(), rand(),
#include<Windows.h>													//Sleep(), system("cls"),
#include<time.h>														//time(),
#include<math.h>														//sin() and cos()

#define PI 3.14159265												//sets up PI as a constant value for use in the trig functions

using namespace std;												//tells the computer I am using standard namespace in order to not need to use the std:: prefix

int Difficulty(void);												//prtotypes of the functions I will be using
bool SingleGame(void);
bool MultiGame(void);

int main()
{

	bool exit = 0;														//initialization of variables used in this function
	int menuChoice = 0;
	bool errorCheck = 0;

	do 
	{
		system("cls");

		cout << "Please enter the number corresponding to the option you would like to pick:" << endl;
		cout << "1.Play Singleplayer\n2.Play Multiplayer\n3.Exit" << endl;				//displays a small menu with instructions to the user on how to continue

		do																			//start of do-while loop set up for error checking
		{
			errorCheck = 0;												//zeroes the value of errorCheck to stop an endless loop

			cin >> menuChoice;										//takes the input and applies it to the value of menuChoice for use in the below switch statement

			switch (menuChoice)										//switch statement to run either of the options depending on which is chosen
			{
			case 1:																//option one calls the Game() function and begins the actual game
				exit = SingleGame();
				break;
			case 2:																//option 2 exits the program
				exit = MultiGame();
				break;
			case 3:
				exit = 1;
				break;
			default:															//the default will return an error if any other input is logged other than the number 1 or 2
				cout << "The value you entered was invalid, please enter a valid selection" << endl;
				errorCheck = 1;											//this causes the error checking loop to restart
				break;
			}

		} while (errorCheck == 1);

	} while (exit == 0);											//the menu will repeat until the game is exitted

	return 0;
}


int Difficulty(void)												//function used to select the difficulty of the game
{
	int difficultyChoice = 1;									//initialisation of the variables that will be used in this function
	int choice = 1;
	bool errorCheck = 0;

	cout << "Please Enter a number corresponding to the Difficulty you would like:" << endl;
	cout << "(Difficulty affects how precise you have to be and how much the wind affects the projectile)" << endl;
	cout << "1.Easy(default, no wind, 10000m squared area to hit)\n2.Medium(some wind, 5000m squared area to hit)\n3.Hard(high wind, 1500m squared area to hit)\n";
																						//displays a menu with instructions for the user on how to select a choice

	do
	{
		errorCheck = 0;													//ensures the prevention of an infinite loop by falsifying the boolean variable

		cin >> difficultyChoice;								//gets the decision on which difficulty is chosen and assigns it for the variable for use in the next switch statement
			
		switch (difficultyChoice)								//switch statement to return the correct value for the corresponding difficulty chosen
		{
		case 1:
			choice = 1;
			break;
		case 2:
			choice = 2;
			break;
		case 3:
			choice = 3;
			break;
		default:
			cout << "The value you entered was invalid, please enter a valid selection" << endl;					//returns an error message if the input was invalid
			errorCheck = 1;												//makes the boolean variable true in order to cause the loop to repeat
			break;
		}

	} while (errorCheck);

	return choice;
}

bool SingleGame(void)															//function that runs the game itself and most calculations (calls the Difficulty() function)
{
	
	int quit = 0;															//initialisation of most of the variables used in this function
	bool complete = 0;
	int windSpeed = 0;
	float angle = 0.0f;
	float shotSpeed = 0.0f;
	bool angleErrorCheck = 0;
	bool speedErrorCheck = 0;
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	float timeOfFlight = 0.0f;
	int distance = 0;
	int difference = 0;

	do																				//do-while loop allows the game to be run multiple times with different options selected and random variables set
	{
		complete = 0;														//ensures the prevention of an infinite loop
		int turn = 0;														//resets the turn variable at the start of each game

		srand(time(NULL));											//sets the seed for the random numbers to the current time each time the loop is run in order to stop the repeat of numbers

		system("cls");													//clears the screen of any previous menues and choices

		int difficulty = Difficulty();					//calls the Difficulty() funciton in order to allow the user to decide which difficulty they would like every time a new game is run

		system("cls");													//clears the screen of the difficulty menu and options

		int distanceToEnemy = rand() % 19999 + 10001;			//initialises the distance to the enemy as a random integer between 10000 and 30000

		switch (difficulty)											//switch statement which applies a random level of wind according the difficulty
		{
		case 1:																	//the easy option has no wind involved so the windspeed is set to 0
			windSpeed = 0;
			break;
		case 2:
			windSpeed = rand() % 50 - 25;					//the medium option has some wind so it is set to a random number between -25 and 25
			break;
		case 3:
			windSpeed = rand() % 100 - 50;				//the hard option has a large amount of wind so the value is set to a random number between -50 and 50
			break;
		}

		do
		{
			turn++;																//tracks the turn the game is on in order to display the correct information

			cout << "The enemy approaches, they are " << distanceToEnemy << " meters away" << endl;
																						//displayes the distance to the enemy to the player

			if (difficulty != 1)									//if the difficulty is medium or hard the windspeed is displayed to the player otherwise it will be 0 so doesn't need to be displayed
			{
				cout << "The wind is blowing at " << windSpeed << "m/s (positive is towards the enemy and negative away from them)\n";
			}

			cout << "Set the angle of your shot and it's speed in m/s and try to hit them\n";
																						//informs the player of how to play the game

			do																		//initialises a do-while loop in order to prevent an invalid value entry
			{
				angleErrorCheck = 0;								//ensures the prevention of an infinite loop

				cout << "Enter the angle you want to fire at (must be between 10 and 80 degrees): ";		//asks the player to enter an angle in a range in degrees
				cin >> angle;												//assigns the entered value to the angle varaible

				if ((angle > 80)||(angle < 10))			//if the entered value is invalid angleErrorCheck is set to true in order to run the loop again
				{
					cout << "The value entered is invalid, please enter a valid value\n";		//displays an error message to the user
					angleErrorCheck = 1;
				}

			}while (angleErrorCheck);							//repeats if there is an error

			do																		//initialises a do-while loop in order to prevent an invalid value entry
			{
				speedErrorCheck = 0;								//ensures the prevention of an infinite loop
				cout << "Enter the speed you want to fire at (must be between 200 and 600 meters/second): ";		//asks the player to enter a shot speed in a range in meters per second
				cin >> shotSpeed;										//assigns the entered value to the shotSpeed variable

				if ((shotSpeed > 600)||(shotSpeed < 200))			//if the value entered was invalid an error message is displayed and the do-while loop is made to run again
				{
					cout << "The value entered is invalid, please enter a valid value\n";
					speedErrorCheck = 1;
				}

			}while(speedErrorCheck == true);

			system("cls");													//clears the screen in order to display a short message to make the game more interesting
			cout << "\n... CALIBRATING ANGLE ...";		
			Sleep(3000);														//pauses the flow of the program for 3 seconds to show the message more clearly
			cout << "\n\n... SETTING SHOT POWER ...";
			Sleep(3000);
			cout << "\n\n         FIRE\n\n";
			Beep(500,500);													//plays a series of beeps to improve feedback to the user
			Sleep(450);
			Beep(500,500);
			Sleep(450);
			Beep(500,500);

			xSpeed = (shotSpeed * cos(angle * (PI / 180))) + windSpeed;	//calculates the projectile speed in the x direction, using trigonometry and converting the angle to radians, and adds the wind speed to it
			ySpeed = (shotSpeed * sin(angle * (PI / 180)));							//calculates the projectile speed in the y direction using trigonometry and converting the angle to radians
			timeOfFlight = ((2 * ySpeed) / 9.81);																//uses (time = (final velocity - initial velocity) / acceleration) to calculate how long the projectile will fly for
			distance = (xSpeed * timeOfFlight);																	//uses (distance = (speed * time)) to calculate the distance the projectile travels
			difference = (distance - distanceToEnemy);									//calculates the difference in the distance the shot traveled and the distance to the enemy
	
			switch (difficulty)											//switch statement used to apply the correct ranges for the difference value based on difficulty
			{
			case 1:																	//at difficulty 1 (easy) the range is 10000m^2
				if (difference >= 5000)								//if the difference is over 5000 a message is displayed to tell the player by how much they overshot the target
				{
					cout << "Oh no you overshot by " << difference << " meters.\n";
					cout << "Enter 0 to fight off another attack or any other number to return to the main menu:: ";			//the player is asked if they wish to try again or exit and are told how to choose either option
					cin >> quit;																											//the value entered is assigned to the quit variable
				}
				else if (difference <= -5000)					//if the difference is under -5000 a message is displayed to tell the player by how much they undershot the target
				{
					cout << "Oh no you undershot by " << (difference * -1) << " meters.\n";
					cout << "Enter 0 to fight off another attack or any other number to return to the main menu:: ";			//the player is asked if they wish to try again or exit and are told how to choose either option
					cin >> quit;																											//the value entered is assigned to the quit variable
				}
				else																	//if the difference is in between the previous values a message is displayed telling the player that they hit the target
				{
					cout << "You hit them in " << turn << " turns!! and repelled the attack but they'll be back soon.\n";
					cout << "Enter 0 to fight off another attack or any other number to quit: ";		//the player is asked if they wish to play again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
					complete = 1;												//the complete variable is assigned to true in order to allow the player to start a new game
				}
				break;

			case 2:																	//at difficulty 2 (medium) the range is 5000m^2
				if (difference >= 2500)								//if the difference is over 2500 a message is displayed to tell the player by how much they overshot the target
				{
					cout << "Oh no you overshot by " << difference << " meters.\n";
					cout << "Enter 0 to fight off another attack or any other number to return to the main menu:: ";			//the player is asked if they wish to try again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
				}
				else if (difference <= -2500)					//if the difference is under -2500 a message is displayed to tell the player by how much they undershot the target
				{
					cout << "Oh no you undershot by " << (difference * -1) << " meters.\n";
					cout << "Enter 0 to fight off another attack or any other number to return to the main menu:: ";			//the player is asked if they wish to try again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
				}
				else																	//if the difference is in between the previous values a message is displayed telling the player that they hit the target
				{
					cout << "You hit them in " << turn << " turns!! and repelled the attack but they'll be back soon.\n";
					cout << "Enter 0 to fight off another attack or any other number to quit: ";			//the player is asked if they wish to play again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
					complete = 1;												//the complete variable is assigned to true in order to allow the player to start a new game
				}
				break;

			case 3:																	//at difficulty 3 (hard) the range is 1500m^2
				if (difference >= 750)								//if the difference is over 750 a message is displayed to tell the player by how much they overshot the target
				{
					cout << "Oh no you overshot by " << difference << " meters.\n";		
					cout << "Enter 0 to fight off another attack or any other number to return to the main menu:: ";			//the player is asked if they wish to try again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
				}
				else if (difference <= -750)					//if the difference is under -750 a message is displayed to tell the player by how much they undershot the target
				{
					cout << "Oh no you undershot by " << (difference * -1) << " meters.\n";
					cout << "Enter 0 to fight off another attack or any other number to return to the main menu: to the menu: ";			//the player is asked if they wish to try again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
				}
				else																	//if the difference is in between the previous values a message is displayed telling the player that they hit the target
				{
					cout << "You hit them in " << turn << " turns!! and repelled the attack but they'll be back soon.\n";
					cout << "Enter 0 to fight off another attack or any other number to quit to the menu: ";			//the player is asked if they wish to play again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
					complete = 1;												//the complete variable is assigned to true in order to allow the player to start a new game
				}
				break;

			}

			system("cls");													//clears the screen of previous menus and calculations
			cout << "Your previous angle, speed and difference were " << angle << " degrees, " << shotSpeed << "m/s and " << difference << "m respectively.\n";
																							//displays to the player what their previous choices were

		}while((complete == 0)&&(quit == 0));			//if the player didn't complete the game but doesn't want to quit the loop repeats

	}while (quit == 0);													//if the player has completed the game but wants to play again the loop repeats

	return 0;																		//true is returned for the quit value in order to return to the main menu the game
}

bool MultiGame()
{

	int quit = 0;															//initialisation of most of the variables used in this function
	bool complete = 0;
	int windSpeed = 0;
	float angle = 0.0f;
	float shotSpeed = 0.0f;
	bool angleErrorCheck = 0;
	bool speedErrorCheck = 0;
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	float timeOfFlight = 0.0f;
	int distance = 0;
	int difference = 0;
	int player = 1;
	float playerOneShotSpeed = 0.0f;
	float playerTwoShotSpeed = 0.0f;
	float playerOneAngle = 0.0f;
	float playerTwoAngle = 0.0f;
	float playerOneDifference = 0.0f;
	float playerTwoDifference = 0.0f;


	do																				//do-while loop allows the game to be run multiple times with different random variables set
	{
		complete = 0;														//ensures the loop does not exit incorrectly
		int turn = 0;														//resets the turn variable at the start of each game
		
		srand(time(NULL));											//sets the seed for the random numbers to the current time each time the loop is run in order to stop the repeat of numbers

		system("cls");													//clears the screen of any previous menues and choices

		int distanceToEnemy = rand() % 19999 + 10001;			//initialises the distance to the enemy as a random integer between 10000 and 30000
		

		cout << "In this gamemode you will be a random distance from each other and must adjust your shot to try to hit your opponent.\n";
		cout << "The first one to hit their oponent wins!\nEach round the distance is randomised and each turn the windspeed will be randomised.\n";
																						//description of the gamemode

		Sleep(10000);														//pauses the program for 10 seconds in order to allow the user to read the message

		do
		{
			turn++;																//tracks the turn the game is on in order to display the correct information
			system("cls");												//clears the screen in order to remove unneccessary information
			windSpeed = rand() % 100 - 50;				//sets the windspeed to a random value each turn
			cout << "Player " << player << " it's you turn.\n";																	//informs the users of whos turn it is
			cout << "The distance between you is " << distanceToEnemy << "m.\n";								//informs the users of the distance between them

			if(turn > 2)																																				//if both users have already had one turn display their respective previous inputs and result depending on whos turn it is
			{
				if (player == 1)																																	
				{
					cout << "Your previous shot speed was " << playerOneShotSpeed << "m/s.\n";
					cout << "Your previous angle was " << playerOneAngle << " degrees.\n";
					cout << "Last turn you missed by " << playerOneDifference << "m\n";
				}
				else
				{
					cout << "Your previous shot speed was " << playerTwoShotSpeed << "m/s.\n";
					cout << "Your previous angle was " << playerTwoAngle << " degrees.\n";
					cout << "Last turn you missed by " << playerTwoDifference << "m\n";
				}
			}
			
			do																		//initialises a do-while loop in order to prevent an invalid value entry
			{
				angleErrorCheck = 0;								//ensures the prevention of an infinite loop

				cout << "Enter the angle you want to fire at (must be between 10 and 80 degrees): ";		//asks the player to enter an angle in a range in degrees
				cin >> angle;												//assigns the entered value to the angle varaible

				if (player == 1)										//stores the angle input of whoever is playing
				{
					playerOneAngle = angle;
				}
				else
				{
					playerTwoAngle = angle;
				}

				if ((angle > 80)||(angle < 10))			//if the entered value is invalid angleErrorCheck is set to true in order to run the loop again
				{
					cout << "The value entered is invalid, please enter a valid value\n";		//displays an error message to the user
					angleErrorCheck = 1;
				}

			}while (angleErrorCheck);							//repeats if there is an error

			do																		//initialises a do-while loop in order to prevent an invalid value entry
			{
				speedErrorCheck = 0;								//ensures the prevention of an infinite loop
				cout << "Enter the speed you want to fire at (must be between 200 and 600 meters/second): ";		//asks the player to enter a shot speed in a range in meters per second
				cin >> shotSpeed;										//assigns the entered value to the shotSpeed variable

				if (player == 1)															//stores the shot speed input of whoever is playing
				{
					playerOneShotSpeed = shotSpeed;
				}
				else
				{
					playerTwoShotSpeed = shotSpeed;
				}

				if ((shotSpeed > 600)||(shotSpeed < 200))			//if the value entered was invalid an error message is displayed and the do-while loop is made to run again
				{
					cout << "The value entered is invalid, please enter a valid value\n";			//displays error message
					speedErrorCheck = 1;
				}

			}while(speedErrorCheck == true);

			system("cls");													//clears the screen in order to display a short message to make the game more interesting
			cout << "\n... CALIBRATING ANGLE ...";		
			Sleep(3000);														//pauses the flow of the program for 3 seconds to show the message more clearly
			cout << "\n\n... SETTING SHOT POWER ...";
			Sleep(3000);
			cout << "\n\n         FIRE\n\n";
			Beep(500,500);													//plays a series of beeps to improve feedback to the user
			Sleep(450);
			Beep(500,500);
			Sleep(450);
			Beep(500,500);

			xSpeed = (shotSpeed * cos(angle * (PI / 180))) + windSpeed;	//calculates the projectile speed in the x direction, using trigonometry and converting the angle to radians, and adds the wind speed to it
			ySpeed = (shotSpeed * sin(angle * (PI / 180)));							//calculates the projectile speed in the y direction using trigonometry and converting the angle to radians
			timeOfFlight = ((2 * ySpeed) / 9.81);																//uses (time = (final velocity - initial velocity) / acceleration) to calculate how long the projectile will fly for
			distance = (xSpeed * timeOfFlight);																	//uses (distance = (speed * time)) to calculate the distance the projectile travels
			difference = (distance - distanceToEnemy);									//calculates the difference in the distance the shot traveled and the distance to the enemy

			if(player == 1)												//stores the result of whoever is playing
			{
				playerOneDifference = difference;
			}
			else
			{
				playerTwoDifference = difference;
			}


			if (difference >= 750)								//if the difference is over 750 a message is displayed to tell the player by how much they overshot the target
				{
					cout << "Oh no you overshot by " << difference << " meters.\n";		
					Sleep(4000);
				}
				else if (difference <= -750)					//if the difference is under -750 a message is displayed to tell the player by how much they undershot the target
				{
					cout << "Oh no you undershot by " << (difference * -1) << " meters.\n";
					Sleep(4000);
				}
				else																	//if the difference is in between the previous values a message is displayed telling the player that they hit the target
				{
					cout << "You hit them player " << player << "!! Well done you win!\n";
					cout << "Enter 0 to play again or any other number to quit to the menu: ";			//the player is asked if they wish to play again or exit and are told how to choose either option
					cin >> quit;												//the value entered is assigned to the quit variable
					complete = 1;												//the complete variable is assigned to true in order to allow the player to start a new game
				}

				if (player == 1)											//switches who's turn it is
				{
					player = 2;
				}
				else
				{
					player = 1;
				}

		}while (complete == 0);

	}while(quit == 0);

	return 0;
}