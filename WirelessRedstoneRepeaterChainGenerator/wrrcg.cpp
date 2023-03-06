
#define _CRT_SECURE_NO_WARNINGS

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>

using namespace std;

string printList(byte** repeaterConfigurations, const int repeaterCount, const int configurationCount) {

	stringstream output;

	for (int i = 0; i < configurationCount; i++) {
		output << setw(3) << setfill('0') << i + 1;
		for (int r = 0; r < repeaterCount; r++) {
			output << " | " << (int)repeaterConfigurations[i][r] + 1;
		}
		output << " |" << endl;
	}

	return output.str();
}

void generate(int repeaterCount) {

	// Calculate total possible combinations of the repeaters and optimal delay (= most combinations with same total delay)
	int combinationCount = pow(repeaterCount, 4);
	int optimalDelay = repeaterCount + (repeaterCount * 3 / 2);

	// Generate list with all configurations on the optimal delay
	byte** configurations = new byte * [combinationCount];
	int configurationCount = 0;
	for (int i = 0; i < combinationCount; i++) {

		configurations[configurationCount] = new byte[repeaterCount];
		int delay = 0;
		for (int r = 0; r < repeaterCount; r++) {
			configurations[configurationCount][r] = (byte)((i >> (r * 2)) & 3);
			delay += (int)configurations[configurationCount][r] + 1;
		}

		if (delay != optimalDelay) {
			delete[] configurations[configurationCount];
			configurations[configurationCount] = 0;
		}
		else {
			configurationCount++;
		}

	}

	// Create virtual queue to simmulate configuration order
	byte** virtualQueue = new byte * [configurationCount];

	for (int i = 0; i < configurationCount; i++) {
		virtualQueue[i] = configurations[i];
	}

	// Order the configurations after the final queue-priority by simulating queue-processing
	for (int d = 1; d <= optimalDelay; d++) {

		// Iterate over queue
		int queuePointer = 0;
		for (int i = 0; i < configurationCount; i++) {

			byte* configuration = virtualQueue[queuePointer];

			// Check if configuration triggered at current delay
			int delay = 0;
			for (int r = 0; r < repeaterCount; r++) {
				delay += (int)configuration[r] + 1;
				if (delay > d) break;
				if (delay == d) {

					// Remove from queue
					for (int i2 = queuePointer; i2 < configurationCount - 1; i2++) virtualQueue[i2] = virtualQueue[i2 + 1];

					// Add at the end of the queue
					virtualQueue[configurationCount - 1] = configuration;

					// Step back one element to keep correct order
					queuePointer--;

				}
			}

			// Step forward to next element in queue
			queuePointer++;

		}

	}

	string output = printList(virtualQueue, repeaterCount, (size_t)configurationCount);

	// Cleanup memory
	for (int i = 0; i < configurationCount; i++) {
		delete[] virtualQueue[i];
	}
	delete[] configurations;
	delete[] virtualQueue;

	cout << output << endl;
	cout << "At delay " << optimalDelay << " with " << repeaterCount << " repeaters are " << configurationCount << " combinations possible" << endl;

}

int main() {

	locale::global(locale("German_germany.UTF-8"));
	cout << "##################################################" << endl;
	cout << "# Wireless-Redstone Repeater-Chain-Generator     #" << endl;
	cout << "# By M_Marvin (Marvin Köhler) 06.03.2023         #" << endl;
	cout << "##################################################" << endl;
	cout << endl << "Type help to see commands" << endl;

	char input[128];
	while (true) {

		cout << "> ";
		cin.getline(input, 128);

		char* command = strtok(input, " ");

		if (command != NULL) {
			if (strcmp(command, "exit") == 0) {
				break;
			}
			else if (strcmp(command, "gen") == 0) {
				int repeaterCount = atoi(strtok(NULL, " "));
				cout << "Generate priority map for " << repeaterCount << " repeaters ..." << endl;
				generate(repeaterCount);
			}
			else if (strcmp(command, "help") == 0) {
				cout << "Type 'gen *repeater count*' to generate a prioritiy list, type 'exit' to close the programm." << endl;
			}
		}

	}

	return 0;

}
