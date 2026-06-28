// GrocerTrakcer.h
/*
 * Declares the GrockerTracker class.
 *		- Load item data from an input file into
 *		  an order frequency map.
 *		- Proved search, display, histogram, and
 *		  file-backup functionality. 
 */

#ifndef GROCERTRACKER_H
#define GROCERTRACKER_H

#include <map>
#include <string>

class GrocerTracker {
	public:
		// Constructor
		/*
		 * Reads input file and builds the frequency map.
		 * Throws runtime error if the file cannot be opened.
		 */
		explicit GrocerTracker(const std::string& inputFile);

		// Returns the purchase frequency of a single item, case insensivitve
		int GetFrequency(const std::string& item) const;

		// Prints every item with its numeric frequency (Menu Option 2)
		void PrintAllFrequencies() const;

		// Prints a histogram for every item (Menu Option 3)
		void PrintHistogram() const;

		// Writes the full frequency map to a backup file (frequency.dat)
		/*
		 * Called once at program start without user input.
		 * Throws runtime error if the file cannot be opened.
		 */
		void BackupToFile(const std::string& outputFile) const;

	private:
		// Ordered map: item name -> purchase count.
		/*
		 * Keeps entries sorted alphabetically, which gives consistent,
		 * readable output for options 2 and 3. 
		 */
		std::map<std::string, int>m_FrequencyMap;

		// Helper: reads the input file and populates m_FrequencyMap.
		void LoadFromFile(const std::string& filename);
};

#endif // GROCERTRACKER_H