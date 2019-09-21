/*
SINK THE FLEET C++
AUTHOR: MARC FERRER CASTILLO
*/


// Includes
#include <iostream>
#include <string>
#include <ctype.h>
#include <time.h>

// Namespace
using namespace std;

// Main
int main()
{
	/*
	Makes use of the computer's internal clock to control the choice of the seed.  Since time is continually changing, the seed is forever changing.
	Remember: If the seed number remains the same, the sequence of numbers will be repeated for each run of the program.
	*/
	srand(time(NULL));

	// Constant values
	const int
		HARD = 70, // EASY MODE MAX ATTEMPTS
		MODERATE = 50, // MODERATE MODE MAX ATTEMPTS
		HARD = 30,// HARD MODE MAX ATTEMPTS
		NUM_MAX = 10, // MAX NUMBER FOR ARRAY HORIZONTAL/VERTICAL LIMITS
		NUM_MIN = 1, // MINIMUM NUMBER FOR ARRAY HORIZONTAL/VERTICAL LIMITS
		MAX_FLEET = 2, // USED TO GENERATE 1 COORDINATE IN THE X / Y AXLE MADE OF 2 NUMBERS (a,b)
		MAX_CHAR = 'J', // LAST CHAR THAT CAN BE ENTERED BY USER
		MIN_CHAR = 'A';// FIRST CHAR THAT CAN BE ENTERED BY USER


	int
		x, // Used to store user x coordinate
		y, // Used to store user y coordinate
		sinked = 0, // Number of ships sinked
		diff_option, // Stores the difficulty selected by the user
		exit, // Stores values 1 or 0 selected by the user in order to exit or continue.
		attempts = 1, // Number of attempts, starts by 1 to discard 0
		f = 0, // Used in a while loop to generate the fleet
		a, // Stores a randomly generated number between 1 and 10 (X axis) 
		b, // Stores a randomly generated number between 1 and 10 (Y axis) 
		difficulty = 0; // Stores easy/moderate/hard difficulty selected by the user. Set to 0 in order to check if an option has been selected

	bool b_exit = false; // Used to continue/finish the game

	char x_axis; // Saves char A-J that will be converted to 1-10 respectively and used for the user to select X axis

	string visual_panel[10][10]; // Used to show a visual panel on the screen

	bool fleet_panel[10][10]; // Used to store "0" (water) or "1" ship


	//system("color B1"); // Optional: Change console background and letter colors




	// Starts the game as long as "b_exit" is false
	do
	{
		// Fills fleet panel with "0" value
		for (int k = 0; k < NUM_MAX; k++)
		{
			for (int l = 0; l < NUM_MAX; l++)
			{
				fleet_panel[k][l] = 0;
			}
		}

		// Generates 8 ships randomly into the fleet panel.
		while (f < MAX_FLEET)
		{
			a = rand() % 10;
			b = rand() % 10;

			// Only fills with a ship if there is no other ship around
			if (fleet_panel[a][b] != 1 && fleet_panel[a - 1][b] != 1 && fleet_panel[a + 1][b] != 1 && fleet_panel[a][b - 1] != 1 && fleet_panel[a][b + 1] != 1 && fleet_panel[a + 1][b + 1] != 1 && fleet_panel[a + 1][b - 1] != 1 && fleet_panel[a - 1][b + 1] != 1 && fleet_panel[a - 1][b - 1] != 1)
			{				
				fleet_panel[a][b] = 1;
				f++;
			}
		}


		do // Iterates until user selects valid option
		{
			// Asks user for difficulty and stores it into "option"
			cout << "Choose difficulty: [1] Easy  [2] Moderate  [3] Hard\n";
			cin >> diff_option;

			// Difficulty menu
			switch (diff_option)
			{
			case 1:
				difficulty = HARD; // Difficulty now is easy
				break;

			case 2:
				difficulty = MODERATE; // Difficulty now is moderate
				break;

			case 3:
				difficulty = HARD; // Difficulty now is hard
				break;

			default:
				cout << "Enter one of the following options: [1, 2 or 3]\n"; // Difficulty error
				break;
			}

		} while (difficulty == 0); 


		// Fills the visual panel
		for (int k = 0; k < NUM_MAX; k++)
		{
			for (int l = 0; l < NUM_MAX; l++)
			{
				visual_panel[k][l] = "|___|";
			}
		}

		// Iterates while attempts have not been exhausted or the fleet have not been sinked
		while (attempts <= difficulty && sinked != MAX_FLEET)
		{
			// Shows visual panel
			cout << "  A    B    C    D    E    F    G    H    I    J" << endl
				<< "__________________________________________________" << endl;
			for (int j = 0; j < NUM_MAX; j++)
			{
				for (int k = 0; k < NUM_MAX; k++)
				{
					cout << visual_panel[j][k];
				}
				cout << "  " << j + 1 << endl;
			}

			/*
			//Decomment to tell ship positions visually
			for (int k1 = 0; k1 < NUM_MAX; k1++)
			{
				for (int l1 = 0; l1 < NUM_MAX; l1++)
				{
					cout << fleet_panel[k1][l1];
				}
				cout << endl;
			}
			*/

			
			do // Iterates until a valid coordinate has been entered by the user
			{
				cout << endl << "\nEnter the X position [A-J]: "; // Asks for X axis 
				cin >> x_axis;

				x_axis = toupper(x_axis); // Transform to mayus

				x = x_axis - 65; // Transforms to number

				cout << "Enter the Y position [1-10]: "; // Asks for Y axis 
				cin >> y;

				// If one of the values are not valid
				if (x_axis > MAX_CHAR || x_axis < MIN_CHAR || y > NUM_MAX || y < NUM_MIN)
				{
					cout << "\nEnter numbers between 1 and 10 and letters between A and J\n"; // Error message
				}

				
			} while (((x_axis > MAX_CHAR || x_axis < MIN_CHAR) || (y > NUM_MAX || y < NUM_MIN)) && attempts != difficulty - 1);


			system("cls"); // Clean screen CMD command


			/* 
			If the selected position matches that of a ship, adds 1 to the number of sinked ships variable "sinked" and replaces
			the position from the visual panel with a cross
			*/
			if (fleet_panel[y - 1][x] == 1 && visual_panel[y - 1][x] != "|_X_|")
			{
				sinked++;
				cout << "\nTouched and sunk!" << endl << endl;
				visual_panel[y - 1][x] = "|_X_|";
				attempts++;
			}
			// If in the position (visual panel) there is a cross or a round does not count the shot
			else if (visual_panel[y - 1][x] == "|_O_|" || visual_panel[y - 1][x] == "|_X_|")
			{
				cout << "\n\aWater!." << endl << endl;
				attempts++;
			}
			else // Counts the shot
			{
				cout << "Water!" << endl << endl;
				visual_panel[y - 1][x] = "|_O_|";
				attempts++;
			}
		}

		// If attempts have been achieved (lost)
		if (attempts == difficulty + 1)
		{
			cout << endl << "You have exhausted the number of attempts, you lose!\a\n\n";
		}

		// If all the fleet is sinked (Won)
		else if (sinked == MAX_FLEET)
		{
			cout << "You have sunk the fleet, you are the winner. You have used " << attempts - 1 << " attempts to get it.\nYour success rate is "
				<< (float)sinked / (attempts - 1) * 100 << "% \n\n\n\n";
		}


		do
		{
			// Asks to play again
			cout << "Do you want to try again?  [0]SI [1]NO :\t";
			cin >> exit;

			switch (exit)
			{
			case 0:
				attempts = 1;
				sinked = 0;
				f = 0;
				break;

			case 1:
				b_exit = true;
				break;

			default:
				cout << "Enter an option of the following: [0] o [1].\n";
				break;
			}

		} while (exit != 0 && exit != 1);

	} while (b_exit == false);

	return 0;
}
