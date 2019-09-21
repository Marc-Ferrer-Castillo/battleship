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
		FACIL = 70, // EASY MODE MAX ATTEMPTS
		MODERAT = 50, // MODERATE MODE MAX ATTEMPTS
		DIFICIL = 2, // HARD MODE MAX ATTEMPTS
		NUM_MAX = 10, // MAX NUMBER FOR ARRAY HORIZONTAL/VERTICAL LIMITS
		NUM_MIN = 1, // MINIMUM NUMBER FOR ARRAY HORIZONTAL/VERTICAL LIMITS
		FLOTA_MAX = 2, // USED TO GENERATE 1 COORDINATE IN THE X / Y AXLE MADE OF 2 NUMBERS (a,b)
		LLETRA_MAX = 'J', // LAST CHAR THAT CAN BE ENTERED BY USER
		LLETRA_MIN = 'A';// FIRST CHAR THAT CAN BE ENTERED BY USER


	int
		x, // Used to store user x coordinate
		y, // Used to store user y coordinate
		barcos_hundidos = 0, // Number of ships sinked
		opcio, // Stores the difficulty selected by the user
		exit, // Stores values 1 or 0 selected by the user in order to exit or continue.
		intents = 1, // Number of attempts, starts by 1 to discard 0
		f = 0, // Used in a while loop to generate the fleet
		a, // Stores a randomly generated number between 1 and 10 (X axis) 
		b, // Stores a randomly generated number between 1 and 10 (Y axis) 
		dificultat = 0; // Stores easy/moderate/hard difficulty selected by the user. Set to 0 in order to check if an option has been selected

	bool b_exit = false; // Used to continue/finish the game

	char lletra; // Saves char A-J that will be converted to 1-10 respectively and used for the user to select X axis

	string panell[10][10]; // Used to show a visual panel on the screen

	bool flota[10][10]; // Used to store "0" (water) or "1" ship


	//system("color B1"); // Opcional: Change console background and letter colors




	// Starts the game as long as "b_exit" is false
	do
	{
		// Fills fleet panel with "0" value
		for (int k = 0; k < NUM_MAX; k++)
		{
			for (int l = 0; l < NUM_MAX; l++)
			{
				flota[k][l] = 0;
			}
		}

		// Generates 8 ships randomly into the fleet panel.
		while (f < FLOTA_MAX)
		{
			a = rand() % 10;
			b = rand() % 10;

			// Only fills with a ship if there is no other ship around
			if (flota[a][b] != 1 && flota[a - 1][b] != 1 && flota[a + 1][b] != 1 && flota[a][b - 1] != 1 && flota[a][b + 1] != 1 && flota[a + 1][b + 1] != 1 && flota[a + 1][b - 1] != 1 && flota[a - 1][b + 1] != 1 && flota[a - 1][b - 1] != 1)
			{				
				flota[a][b] = 1;
				f++;
			}
		}


		do // Iterates until user selects valid option
		{
			// Asks user for difficulty and stores it into "option"
			cout << "Escoge la dificultad: [1] FACIL  [2] MODERADO  [3] DIFICIL\n";
			cin >> opcio;

			// Difficulty menu
			switch (opcio)
			{
			case 1:
				dificultat = FACIL; // Difficulty now is easy
				break;

			case 2:
				dificultat = MODERAT; // Difficulty now is moderate
				break;

			case 3:
				dificultat = DIFICIL; // Difficulty now is hard
				break;

			default:
				cout << "Introduce una de las siguientes opciones: [1-2-3]\n"; // Difficulty error
				break;
			}

		} while (dificultat == 0); 


		// Fills the visual panel
		for (int k = 0; k < NUM_MAX; k++)
		{
			for (int l = 0; l < NUM_MAX; l++)
			{
				panell[k][l] = "|___|";
			}
		}

		// Iterates while attempts have not been exhausted or the fleet have not been sinked
		while (intents <= dificultat && barcos_hundidos != FLOTA_MAX)
		{
			// Shows visual panel
			cout << "  A    B    C    D    E    F    G    H    I    J" << endl
				<< "__________________________________________________" << endl;
			for (int j = 0; j < NUM_MAX; j++)
			{
				for (int k = 0; k < NUM_MAX; k++)
				{
					cout << panell[j][k];
				}
				cout << "  " << j + 1 << endl;
			}

			/*
			//Decomment to tell ship positions visually
			for (int k1 = 0; k1 < NUM_MAX; k1++)
			{
				for (int l1 = 0; l1 < NUM_MAX; l1++)
				{
					cout << flota[k1][l1];
				}
				cout << endl;
			}
			*/

			
			do // Iterates until a valid coordinate has been entered by the user
			{
				cout << endl << "\nIntroduce la posición X [A-J]: "; // Asks for X axis 
				cin >> lletra;

				lletra = toupper(lletra); // Transform to mayus

				x = lletra - 65; // Transforms to number

				cout << "Introduece la posición y [1-10]: "; // Asks for Y axis 
				cin >> y;

				// If one of the values are not valid
				if (lletra > LLETRA_MAX || lletra < LLETRA_MIN || y > NUM_MAX || y < NUM_MIN)
				{
					cout << "\nIntroduce numeros entre 1 y 10 y letras entre A y J\n"; // Error message
				}

				
			} while (((lletra > LLETRA_MAX || lletra < LLETRA_MIN) || (y > NUM_MAX || y < NUM_MIN)) && intents != dificultat - 1);


			system("cls"); // Clean screen CMD command


			/* 
			If the selected position matches that of a ship, adds 1 to the number of sinked ships variable "sinked" and replaces
			the position from the visual panel with a cross
			*/
			if (flota[y - 1][x] == 1 && panell[y - 1][x] != "|_X_|")
			{
				barcos_hundidos++;
				cout << "\nTocado y hundido!" << endl << endl;
				panell[y - 1][x] = "|_X_|";
				intents++;
			}

			// If in the position (visual panel) there is a cross or a round does not count the shot
			else if (panell[y - 1][x] == "|_O_|" || panell[y - 1][x] == "|_X_|")
			{
				cout << "\n\aAgua!." << endl << endl;
				intents++;
			}
			else
			{
				cout << "Agua!" << endl << endl;
				panell[y - 1][x] = "|_O_|";
				intents++;
			}
		}

		// If attempts have been achieved (lost)
		if (intents == dificultat + 1)
		{
			cout << endl << "Has agotado el numero de intentos, you lose!\a\n\n";
		}

		// If all the fleet is sinked (Won)
		else if (barcos_hundidos == FLOTA_MAX)
		{
			cout << "Has hundido la flota, eres el ganador. Has empleado " << intents - 1 << " intentos para conseguirlo.\nTu porcentaje de aciertos es de "
				<< (float)barcos_hundidos / (intents - 1) * 100 << "% \n\n\n\n";
		}


		do
		{
			// Asks to play again
			cout << "Quieres volver a intentarlo?  [0]SI [1]NO :\t";
			cin >> exit;

			switch (exit)
			{
			case 0:
				intents = 1;
				barcos_hundidos = 0;
				f = 0;
				break;

			case 1:
				b_exit = true;
				break;

			default:
				cout << "Introduce una opción de las siguientes: [0] o [1].\n";
				break;
			}

		} while (exit != 0 && exit != 1);

	} while (b_exit == false);

	return 0;
}

