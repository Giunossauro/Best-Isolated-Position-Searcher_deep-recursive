/*
 * Author: Giuliano Mitteroheffer Morelli
 * Name: Best Isolated Position Searcher
 * Purpose: searches for positions in array that are far away of any other found and that satisfy some condition(s)
 * Language: C
 */

 //headers
#include <stdio.h>
#include <conio.h>

//random data I created
#define T 3000000

//recursion prototype - passed only "level" by value to avoid heap overflow
void bestIsolatedPositionSearcher(unsigned int level, unsigned int& aux, unsigned int& cycle, unsigned short int& condition,
	unsigned int* startPointPosition, unsigned int* positionCounter, unsigned int* aboveLevelCounterReminder,
	unsigned int* belowLevelCounterReminder, unsigned short int* whereToSearchForCondition, bool& found,
	unsigned char& loopRecyclableVariable, bool* positionOfFound);

//function prototype to run the cycle
void runCycle(unsigned int level, unsigned int& aux, unsigned int& cycle, unsigned short int& condition,
	unsigned int* startPointPosition, unsigned int* positionCounter, unsigned int* aboveLevelCounterReminder,
	unsigned int* belowLevelCounterReminder, unsigned short int* whereToSearchForCondition, bool& found,
	unsigned char& loopRecyclableVariable, bool* positionOfFound, unsigned int* positionCounterAux, unsigned int* startPointPositionAux,
	unsigned int& x, unsigned int& y, unsigned int& z);

int main() {

	//STATIC VARIABLES

	//level of recursion - passed by value - first level is 0
	unsigned int level;

	//variable that will return the new found position - passed by reference (to avoid using returnable funcion)
	unsigned int aux;

	//number of stored found positions plus one - passed by reference - initialized with random data - 6 simulate that already have 5 positions found
	unsigned int cycle;

	//condition searched for - passed by reference - initialized with random data - can be any other number, or boolean
	unsigned short int condition;

	//when found, this will stop searching - passed by reference
	bool found;

	//loop variable passed by reference to save memory - passed by reference
	unsigned char loopRecyclableVariable;

	//loop variables - not passed
	unsigned int x, y, z;



	//DINAMIC VARIABLES (all passed by reference, because are all arrays)

	//start point position of the search for conditions - from this will search up and down
	unsigned int* startPointPosition;

	//store searching steps (up and down)
	unsigned int* positionCounter;

	//when program increase recursion level, it have to compare current position counter with above
	unsigned int* aboveLevelCounterReminder;

	//when program reentry any recursion level, it have to remind where (by position counter) it stopped searching
	unsigned int* belowLevelCounterReminder;

	//program will recursively search this array by condition
	unsigned short int* whereToSearchForCondition;

	//this bool array stores position of found best isolated conditions
	bool* positionOfFound;
	
	//aux for sorting positionCounter and startPointPosition
	unsigned int* positionCounterAux;
	unsigned int* startPointPositionAux;



	/*
	INITIALIZING AND POPULATING (most with random data, few just initializing, some already initialized)
	T, cycle, condition, positionOfFound and whereToSearchForCondition
	can be populated with own data, from reading some file, database or other source
	also you can use matrix
	*/

	level = 0;

	cycle = 1;

	condition = 500;

	found = false;

	positionOfFound = new bool[T];

	whereToSearchForCondition = new unsigned short int[T];

	for (x = 0; x < T; x++) {
		positionOfFound[x] = false;
	}

	for (x = 0; x < T; x++) {

		//can be any other number, just habe to be different from condition to prove this algorithim
		whereToSearchForCondition[x] = 499;
	}

	printf("Take note where are the 5 positions of condition:\n");
	//y store seed to put 5 (z) satisfiable conditions
	y = 145857;
	z = 5;
	for (x = 0; x < T; x++) {
		if (y == x) {
			whereToSearchForCondition[x] = 500;
			y += y;
			printf("found condition at: %u position\n", x);
			z--;
		}
	}
	printf("\nType any key to continue...\n");
	//x = _getch();

	//no reason for recursion (will not run, here "x" dont allow, because this part is to you seed with your data) 
	if (cycle == 1 && x == 0) {
		for (x = 0; x < T; x++) {
			if (whereToSearchForCondition[x] == condition) {
				positionOfFound[x] = true;
			}
		}
	}

	//have reason for recursion (same of first if)
	else if (cycle > 1) {


		for (x = 0; x < T; x++) {
			positionOfFound[x] = true ? cycle++ : 0;
		}

		//for a short time, aux take value considering if none or any of both or both extremities is true, because there's no way to search under 0 or above T - 1
		positionOfFound[0] == true ? positionOfFound[T - 1] == true ? aux = cycle - 1 : aux = cycle : positionOfFound[T - 1] == true ? aux = cycle : aux = cycle + 1;

		//alocating memory in heap
		positionCounter = new unsigned int[aux];
		startPointPosition = new unsigned int[aux];
		positionCounterAux = new unsigned int[aux];
		startPointPositionAux = new unsigned int[aux];
		aboveLevelCounterReminder = new unsigned int[aux - 1];
		belowLevelCounterReminder = new unsigned int[aux - 1];

		//the function below will run cycle
		runCycle(0, aux, cycle, condition, startPointPosition, positionCounter, aboveLevelCounterReminder, belowLevelCounterReminder,
			whereToSearchForCondition, found, loopRecyclableVariable, positionOfFound, positionCounterAux, startPointPositionAux, x, y, z);
	}

	//here will run to test this program
	else {

		//where hypothetically other conditions was hypothetically already found
		positionOfFound[0] = true;
		positionOfFound[599999] = true;
		positionOfFound[1599999] = true;
		positionOfFound[1799999] = true;
		positionOfFound[2399999] = true;
		positionOfFound[T - 1] = true;

		for (x = 0; x < T; x++) {
			positionOfFound[x] == true ? cycle++ : 0;
		}

		printf("oi");

		//for a short time, aux take value considering if none or any of both or both extremities is true, because there's no way to search under 0 or above T - 1
		positionOfFound[0] == true ? positionOfFound[T - 1] == true ? aux = cycle - 1 : aux = cycle : positionOfFound[T - 1] == true ? aux = cycle : aux = cycle + 1;

		//alocating memory in heap
		positionCounter = new unsigned int[aux];
		startPointPosition = new unsigned int[aux];
		positionCounterAux = new unsigned int[aux];
		startPointPositionAux = new unsigned int[aux];
		aboveLevelCounterReminder = new unsigned int[aux - 1];
		belowLevelCounterReminder = new unsigned int[aux - 1];

		//as this is the 7th cycle searching for the 7th Best Isolated Position, considering data above
		runCycle(0, aux, cycle, condition, startPointPosition, positionCounter, aboveLevelCounterReminder, belowLevelCounterReminder,
			whereToSearchForCondition, found, loopRecyclableVariable, positionOfFound, positionCounterAux, startPointPositionAux, x, y, z);

	}

	return 0;
}

//Recursion function
void bestIsolatedPositionSearcher(unsigned int level, unsigned int& aux, unsigned int& cycle, unsigned short int& condition,
	unsigned int* startPointPosition, unsigned int* positionCounter, unsigned int* aboveLevelCounterReminder,
	unsigned int* belowLevelCounterReminder, unsigned short int* whereToSearchForCondition, bool& found,
	unsigned char& loopRecyclableVariable, bool* positionOfFound) {

	//Loop variable to this level
	unsigned int* v = new unsigned int;

	//This "if" is for "middle stuff" because it creates variables to check counter of below and above, also remind own counter
	if (level > 0 && level < cycle) {

		//stores last/next below position that will be checked (always increased)
		unsigned int* x = new unsigned int(startPointPosition[level] + 1 + belowLevelCounterReminder[level - 1]);

		//stores last/next above position that will be checked (always decreased)
		unsigned int* y = new unsigned int(startPointPosition[level] - belowLevelCounterReminder[level - 1]);

		//stores above position counter - takes above counter minus itself minus rest of it (its like counter menus counted)
		unsigned int* ct2 = new unsigned int(positionCounter[level - 1] - (positionCounter[level - 1] - aboveLevelCounterReminder[level - 1]));

		//stores below position counter (level + 1 is next level)
		unsigned int* ct3 = new unsigned int(positionCounter[level + 1]);

		//position of "belowLevelCounterReminder" is "level - 1" because the 0 (first) position stores level 1 (second level) counter
		for (v[0] = belowLevelCounterReminder[level - 1]; v[0] < positionCounter[level] && found == false; v[0]++) {

			//this stores this level counter for below levels compare with
			aboveLevelCounterReminder[level] = positionCounter[level] - v[0];

			//condition test for incremented position
			if (whereToSearchForCondition[x[0]] == condition && positionOfFound[x[0]] == false) {

				//store position (of incremented) where condition was found
				aux = x[0];

				//end all recursion
				found = true;
			}

			//condition test for decremented position
			else if (whereToSearchForCondition[y[0]] == condition && positionOfFound[y[0]] == false) {

				//store position (of decremented) where condition was found
				aux = y[0];
				found = true;
			}

			//check if this level counter is less then above and below counter to decide how is bigger if this test is true
			else if (aboveLevelCounterReminder[level] < ct2[0] && aboveLevelCounterReminder[level] < ct3[0]) {

				//then decides if close this level and return to above
				if (ct3[0] <= ct2[0]) {
					belowLevelCounterReminder[level - 1] = v[0] + 1;
					v[0] = positionCounter[level];
					aboveLevelCounterReminder[level]++;
				}

				//or if suspend this level and enter below
				else {
					bestIsolatedPositionSearcher(level + 1, aux, cycle, condition, startPointPosition, positionCounter, aboveLevelCounterReminder,
						belowLevelCounterReminder, whereToSearchForCondition, found, loopRecyclableVariable, positionOfFound);
					ct3[0] -= belowLevelCounterReminder[level];
					x[0] < T - 1 ? x[0]++ : 0;
					y[0] > 0 ? y[0]-- : 0;
				}
			}

			//or if only below is bigger, then just go there
			else if (aboveLevelCounterReminder[level] < ct3[0]) {
				bestIsolatedPositionSearcher(level + 1, aux, cycle, condition, startPointPosition, positionCounter, aboveLevelCounterReminder, belowLevelCounterReminder, whereToSearchForCondition, found, loopRecyclableVariable, positionOfFound);
				ct3[0] -= belowLevelCounterReminder[level];
				x[0] < T - 1 ? x[0]++ : 0;
				y[0] > 0 ? y[0]-- : 0;
			}

			//of if only above is bigger, then just go there
			else if (aboveLevelCounterReminder[level] < ct2[0]) {
				belowLevelCounterReminder[level - 1] = v[0] + 1;
				v[0] = positionCounter[level];
				aboveLevelCounterReminder[level]++;
			}

			//or if none of above tests, then just continue in this level
			else {

				//if incremented position is less than bigger position, increment it, else nothing
				x[0] < T - 1 ? x[0]++ : 0;

				//if decremented position is bigger than smaller position, decrement it, else nothing
				y[0] > 0 ? y[0]-- : 0;
			}
		}

		//clean up
		delete x;
		delete y;
		delete ct2;
		delete ct3;
	}

	//This if is for first level because it never checks counter of above, so dont creates above counter
	else if (level == 0) {
		unsigned int* x = new unsigned int(startPointPosition[level] + 1);
		unsigned int* y = new unsigned int(startPointPosition[level]);
		unsigned int* ct3 = new unsigned int(positionCounter[level + 1]);
		for (v[0] = 0; v[0] < positionCounter[level] && found == false; v[0]++) {
			aboveLevelCounterReminder[level] = positionCounter[level] - v[0];
			if (whereToSearchForCondition[x[0]] == condition && positionOfFound[x[0]] == false) {
				aux = x[0];
				found = true;
			}
			else if (whereToSearchForCondition[y[0]] == condition && positionOfFound[y[0]] == false) {
				aux = y[0];
				found = true;
			}
			else if (aboveLevelCounterReminder[level] < ct3[0]) {
				bestIsolatedPositionSearcher(level + 1, aux, cycle, condition, startPointPosition, positionCounter, aboveLevelCounterReminder, belowLevelCounterReminder, whereToSearchForCondition, found, loopRecyclableVariable, positionOfFound);
				ct3[0] -= belowLevelCounterReminder[level];
				x[0] < T - 1 ? x[0]++ : 0;
				y[0] > 0 ? y[0]-- : 0;
			}
			else {
				x[0] < T - 1 ? x[0]++ : 0;
				y[0] > 0 ? y[0]-- : 0;
			}
		}
		delete x;
		delete y;
		delete ct3;
	}

	//This if is for last level because it never checks counter of below, so dont creates below counter
	else if (level == cycle) {
		unsigned int* x = new unsigned int(startPointPosition[level] + 1 + belowLevelCounterReminder[level - 1]);
		unsigned int* y = new unsigned int(startPointPosition[level] - belowLevelCounterReminder[level - 1]);
		unsigned int* ct2 = new unsigned int(positionCounter[level - 1] - (positionCounter[level - 1] - aboveLevelCounterReminder[level - 1]));
		for (v[0] = belowLevelCounterReminder[level - 1]; v[0] < positionCounter[level] && found == false; v[0]++) {
			aboveLevelCounterReminder[level] = positionCounter[level] - v[0];
			if (whereToSearchForCondition[x[0]] == condition && positionOfFound[x[0]] == false) {
				aux = x[0];
				found = true;
			}
			else if (whereToSearchForCondition[y[0]] == condition && positionOfFound[y[0]] == false) {
				aux = y[0];
				found = true;
			}
			else if (aboveLevelCounterReminder[level] >= ct2[0]) {
				x[0] < T - 1 ? x[0]++ : 0;
				y[0] > 0 ? y[0]-- : 0;
			}
			else {
				belowLevelCounterReminder[level - 1] = v[0] + 1;
				v[0] = positionCounter[level];
				aboveLevelCounterReminder[level]++;
			}
		}
		delete x;
		delete y;
		delete ct2;
	}
	else {
		printf("Whats happened? This level is: %u and this cycle is: %u \n\nmore informations debugging...", level, cycle);
		printf("Type any key, then press ENTER to continue...\n");
		aux = _getch();
		aux = 4000000;
	}

	//clean up
	delete v;
}

void runCycle(unsigned int level, unsigned int& aux, unsigned int& cycle, unsigned short int& condition,
	unsigned int* startPointPosition, unsigned int* positionCounter, unsigned int* aboveLevelCounterReminder,
	unsigned int* belowLevelCounterReminder, unsigned short int* whereToSearchForCondition, bool& found,
	unsigned char& loopRecyclableVariable, bool* positionOfFound, unsigned int* positionCounterAux, unsigned int* startPointPositionAux,
	unsigned int& x, unsigned int& y, unsigned int& z) {

	//initializing
	for (x = 0; x < aux - 1; x++) {
		belowLevelCounterReminder[x] = 0;
		aboveLevelCounterReminder[x] = 0;
	}

	//searching for all startingPointPosition and for all half distances (positionCounter) between positionOfFound (storing in aux versions)
	unsigned int aux1, aux2, aux3;
	aux1 = 0;
	aux2 = 0;
	aux3 = 0;
	for (x = 0; x < T; x++) {
		if (positionOfFound[x] == true) {
			if (x == 0) {
				startPointPositionAux[aux3] = 0;
			}
			else if (x == T - 1) {
				if (aux1 % 2 == 0) {
					aux1--;
				}
			}
			aux2 = aux1 / 2;
			aux1 = 0;
			x == 0 ? 0 : startPointPositionAux[aux3] = x - aux2;
			positionCounterAux[aux3] = aux2;
			aux3++;
		}
		else {
			aux1++;
		}
	}

	//algorithim to consistently sorting positionCounter and startPointPosition (still using aux versions)
	x = 1;
	//aux -= 2;
	while (x < aux) {
		x = 3 * x + 1;
	}
	while (x > 0) {
		for (aux1 = x; aux1 < aux; aux1++) {
			y = positionCounterAux[aux1];
			z = startPointPositionAux[aux1];
			aux2 = aux1;
			while (aux2 > x - 1 && y <= positionCounterAux[aux2 - x]) {
				positionCounterAux[aux2] = positionCounterAux[aux2 - x];
				startPointPositionAux[aux2] = startPointPositionAux[aux2 - x];
				aux2 = aux2 - x;
			}
			positionCounterAux[aux2] = y;
			startPointPositionAux[aux2] = z;
		}
		x = x / 3;
	}
	//aux += 2;

	for (x = 0; x < aux; x++) {
		y = positionCounterAux[x];
		printf("%u\n", y);

		y = startPointPositionAux[x];
		printf("%u\n\n", y);
	}
	printf("\n\n\n");
	//storing in "oficial" version of arrays (reason of use of aux versions)
	for (x = 0, y = aux - 1; x < aux; x++, y--) {
		positionCounter[x] = positionCounterAux[y];
		startPointPosition[x] = startPointPositionAux[y];
		z = positionCounter[x];
		printf("%u\n", z);
		z = startPointPosition[x];
		printf("%u\n\n", z);
	}

	//no more need of aux versions
	delete[] startPointPositionAux;
	delete[] positionCounterAux;

	//here "x" will save cycle
	x = cycle;

	//because...
	cycle = aux - 1;

	//and cycle will fit in the math of recursion! - RECURSION
	printf("Before recursion\n...\n");

	bestIsolatedPositionSearcher(0, aux, cycle, condition, startPointPosition, positionCounter, aboveLevelCounterReminder, belowLevelCounterReminder,
		whereToSearchForCondition, found, loopRecyclableVariable, positionOfFound);

	printf("After recursion.\nCheck if value of \"aux\" match with some condition: %u\n\n", aux);

	printf("Type any key to continue...\n");

	cycle = x;

	x = _getch();

	//do (or not) stuff you need or want with result data
}

//Need it more chewed? If yes, please chew more and return what you chewed!





































/*
some garbage I keep case I need

//first positions to start searching are exactly the middle between next after and before already found
startPointPosition[0] = 300000;
startPointPosition[1] = 900000;
startPointPosition[2] = 1500000;
startPointPosition[3] = 2100000;
startPointPosition[4] = 2700000;

//this will count if reached other found position (can be made by testing for condition with next after and before already found?)
positionCounter[0] = 300000;
positionCounter[1] = 500000;
positionCounter[2] = 100000;
positionCounter[3] = 300000;
positionCounter[4] = 300000;

By: Data Hoarder

*/