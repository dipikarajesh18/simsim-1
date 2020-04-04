//simulation for the SIM living in a build house
//code by Milk
#include "includes/class_def.h"

float calculateFitness(Sim* s);
void fulfillNeed(House* house, int needIndex);


// ----- REMEMBER -----
//needs: hunger, hygeine, bladder, energy, social, fun


//simulates a sim living in a house
//input: 
//	Sim* sims 					: array of sims to simulate on
//  int numSims					: number of sims in the array [sims]
//	House house 				: the house to simulate in
//	int maxTicks 				: the number of ticks to simulate for - at the end returns the end state of the sim
//	vector<int> rate			: how often to decrease the energy levels ( applies to the vector needs accordingly )
//	int threshold				: the value sim starts to attend to needs (i.e. when bladder reaches 3 - search for toilet)
//  vector<int> needsRanking	: how to rank the priority of the needs when looking for an object to fulfill it

//output:
//	float fitness	: evaluation of the Sim's end condition (see calculateFitness)
float simulate(Sim* simChar, int maxTicks, vector<int> rate, int threshold, vector<int> needsRanking){
	int tick;
	for(tick=0;tick<maxTicks;tick++){

		//1. check if dead
		if(simChar->isDead())		//miss keisha? Miss Keeisshaaa? MISS KEISHA! 
			break;

		//2. check if at the target object (if has one) - and use the object if so
		simChar->atTarget();

		//3. apply the needs decrement
		int n;
		for(n=0;n<rate.size();n++){
			if(tick == 0)				//skip the first iteration
				break;

			if(rate[n] % tick == 0)		//if the rate matches - decrement a need
				simChar->alterNeed(n, -1);
		}

		//4. find next need to fulfill
		for(n=0;n<needsRanking.size();n++){
			int needIndex = needsRanking[n];
			vector<int> simNeeds = simChar->getNeeds();
			if(simNeeds[needIndex] < threshold){
				fulfillNeed(simChar->getHouse(), needIndex);
			}
		}
		
	}

	return calculateFitness(simChar);
}

/*

//simulates multiple sims living in a house
//input: 
//	Sim* sims 					: array of sims to simulate on
//  int numSims					: number of sims in the array [sims]
//	House house 				: the house to simulate in
//	int maxTicks 				: the number of ticks to simulate for - at the end returns the end state of the sim
//	vector<int> rate			: how often to decrease the energy levels ( applies to the vector needs accordingly )
//	int threshold				: the value sim starts to attend to needs (i.e. when bladder reaches 3 - search for toilet)
//  vector<int> needsRanking	: how to rank the priority of the needs when looking for an object to fulfill it

//output:
//	float fitness	: evaluation of the Sim's end condition (see calculateFitness)
float* multiSimulate(Sim* sims, int numSims, int maxTicks, vector<int> rate, int threshold, vector<int> needsRanking){
	int tick;
	for(tick=0;tick<maxTicks;tick++){
		int s;
		for(s=0;s<numSims;s++){
			Sim simChar = sims[s];		//current sim

			//1. check if dead
			if(simChar.isDead())		//miss keisha? Miss Keeisshaaa? MISS KEISHA! 
				break;

			//2. check if at the target object (if has one) - and use the object if so
			simChar.atTarget();

			//3. apply the needs decrement
			int n;
			for(n=0;n<rate.size();n++){
				if(tick == 0)				//skip the first iteration
					break;

				if(rate[n] % tick == 0)		//if the rate matches - decrement a need
					simChar.alterNeed(n, -1);
			}

			//4. find next need to fulfill
			for(n=0;n<needsRanking.size();n++){
				int needIndex = needsRanking[n];
				vector<int> simNeeds = simChar.getNeeds();
				if(simNeeds[needIndex] < threshold){
					fulfillNeed(simChar.getHouse(), needIndex);
				}
			}
		}
	}

	//calculate all of the fitnesses for the sims
	float* fitnesses = new float[numSims];
	int f;
	for(f=0;f<numSims;f++){
		fitnesses[f] = calculateFitness(&sims[f]);
	}

	return fitnesses;
}

*/


//calculates a fitness value based on the Sim's end condition
//1 = best fitness + health | 0 = dead
float calculateFitness(Sim* s){
	//if the sim died - it's the worst fitness
	if(s->isDead())
		return 0;

	//tally all of the needs and divide them by 60 (needs [6] * maximum value [10])
	int n;
	float avg = 0;
	vector<int> needs = s->getNeeds();
	for(n=0;n<needs.size();n++){
		avg += needs[n];
	}
	avg /= 60;

	return avg;
}

//fulfills a need by identifying the closest object in the house that 
// can satisfy the particular need and setting it as the Sim's target object to navigate to
void fulfillNeed(House* house, int needIndex){

	return;
}


int main(){return 0;}




