// GrocerTracker.cpp
/*
 * Implements all GrocerTracker member funcitons.
 */

#include "GrocerTracker.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <sstream>


// Constructor
GrocerTracker::GrocerTracker(const std::string& inputFile) {
	LoadFromFile(inputFile);
}

// Private Helper
void GrocerTracker::LoadFromFile(const std::string& filename) {
	namespace fs = std::filesystem;
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::ostringstream oss;
		oss << "Error: Could not open input file '" << filename << "'.\n";
		oss << "Current working directory: " << fs::current_path() << "\n";
		if (!fs::exists(filename)) oss << "Reason: file does not exist.\n";
		else oss << "Reason: file exists but could not be opened (permissions or locked).\n";
		throw std::runtime_error(oss.str());
	}

	std::string item;
	while (inFile >> item) {
		++m_FrequencyMap[item];
	}

	inFile.close();
}

// Menu Option 1
int GrocerTracker::GetFrequency(const std::string& item) const {
	// Convert serach term to lowercase for case insensitivity
	std::string lowerSearch = item;
	std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), 
		[](unsigned char c) { return std::tolower(c); });

	for (const auto& pair : m_FrequencyMap) {
		std::string lowerKey = pair.first;
		std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), 
			[](unsigned char c) { return std::tolower(c); });
	
		if (lowerKey == lowerSearch) {
			return pair.second;
		}
	}
	return 0;			// item not found
}

// Menu Option 2
void GrocerTracker::PrintAllFrequencies() const {
	const int COL_WIDTH = 16;		// left align item name in a fixed column

	std::cout << "\n";
	std::cout << " ------------------------\n";
	std::cout << "     Item Frequencies    \n";
	std::cout << " ------------------------\n";

	for (const auto& pair : m_FrequencyMap) {
		std::cout << " | " << std::left << std::setw(COL_WIDTH) << pair.first 
			<< std::right << std::setw(4) << pair.second << " |\n";
	}

	std::cout << " ------------------------\n\n";
}

// Menu Option 3
void GrocerTracker::PrintHistogram() const {
	const int COL_WIDTH = 14;

	std::cout << "\n";
	std::cout << " ------------------------\n";
	std::cout << " Item Frequency Histogram\n";
	std::cout << " ------------------------\n";

	for (const auto& pair : m_FrequencyMap) {
		std::cout << " " << std::left << std::setw(COL_WIDTH) << pair.first;
		for (int i = 0; i < pair.second; ++i) {
			std::cout << '*';
		}
		std::cout << '\n';
	}

	std::cout << " ------------------------\n\n";
}

// Backup: write frequency map to frenquency.dat
void GrocerTracker::BackupToFile(const std::string& outputFile) const {
	std::ofstream outFile(outputFile);
	if (!outFile.is_open()) {
		throw std::runtime_error(
			"Error: Could not create backup file '" + outputFile + "'."
		);
	}

	for (const auto& pair : m_FrequencyMap) {
		outFile << pair.first << " " << pair.second << "\n";
	}

	outFile.close();
}