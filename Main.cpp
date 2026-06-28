// Main
/*
 * Menu driven driver
 * Uses do-while loop so the menu is always displayed at least once before evaluating exit.
 * GetValidMenuChoice() protects against two categories of bad input: non integer characters
 * and out of range integers. 
 */

#include "GrocerTracker.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

// Helpers

// Print the menu options
void DisplayMenu() {
	std::cout << "1. Search for an Item\n";				 
	std::cout << "2. Display All Frequencies\n";
	std::cout << "3. Display Histogram\n";
	std::cout << "4. Exit\n\n";
}

/*
 * Read and validate an integer menu choice from the user. 
 * Clear any bad input state before returning
 */
int GetValidMenuChoice() {
	int choice;

	while (true) {
		if (std::cin >> choice && choice >= 1 && choice <= 4) {
			// Consume line so later getline calls work correctly
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return choice;
		}

		// Bad input: clears error state, discards bad characters, reprompts
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\nInvalid choice. Please enter a number between 1 and 4: ";
	}
}

// Main
int main() {
	const std::string INPUT_FILE = "CS210_Project_Three_Input.txt";
	const std::string BACKUP_FILE = "frequency.dat";

	// Load data and create backup, automatic process
	GrocerTracker tracker(INPUT_FILE);		// Throws if file not found

	tracker.BackupToFile(BACKUP_FILE);
	std::cout << " [Backup] '" << BACKUP_FILE << "' created successfully..\n";

	// Menu Loop
	int choice = 0;

	do {
		DisplayMenu();
		choice = GetValidMenuChoice();

		switch (choice) {
			
			// Option 1: Search for a single item
			case 1: {
				std::cout << "\n Enter item name to search: ";
				std::string item;
				std::cin >> item;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				int freq = tracker.GetFrequency(item);
				if (freq > 0) {
					std::cout << "\n '" << item << "' was purchased " << freq << " time(s). \n\n";
				} else {
					std::cout << "\n " << item << "' was not found in today's records.\n\n";
				}
				break;
			}

			// Option 2: Print all items with numeric frequencies
			case 2: 
				tracker.PrintAllFrequencies();
				break;
			
			// Option 3: Print histogram
			case 3:
				tracker.PrintHistogram();
				break;

			// Option 4: exit
			case 4:
				std::cout << "\n Exiting\n";
				break;
		}

	} while (choice != 4);

	return 0;
}


