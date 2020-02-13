#include <iostream>//for input/output to user
#include <cstdlib>//loading c standard library functions and data types
#include <fstream>//for input/output to file
#include <vector>//because not included in c standard library
#include <sstream>//for splitting string into ints
#include <string>
#include <cmath>
#include <time.h>

using namespace std;

int nbvar, nbclauses, fit = 0;


//this function updates global var to update fitness rating but returns
//vector of indices(line numbers starting at 0) of the clauses that are
//unsatisfied currently
vector<int> fitness(vector< vector<int> > bf, string lit){
	bool clauseSat = false;
	vector<int> unsat;
	int litInd;
	fit = 0;
	string truthVal;
	for(int i=0; i<bf.size(); i++){
		clauseSat = false; //reset to false, will remain until proven otherwise
		for(int j=0; j<bf[i].size(); j++){
			if(bf[i][j]!=0){//if last arg of clause is always 0, this is a 3-SAT problem, dont worry about last arg
				litInd = (abs(bf[i][j])-1);//gets index of corresponding digit in literal
				truthVal = lit.at(litInd);//0 or 1?
				if(bf[i][j]<0 && truthVal == "0")
					clauseSat = true;
				if(bf[i][j]>0 && truthVal == "1")
					clauseSat = true;
			}
		}
		if(clauseSat == true){
			fit++;
		}
		else
			unsat.push_back(i);
	}
	return unsat;
}

void algDPLL(vector< vector<int> > bf, string lit){//tests DPLL on boolean formula

}

void algWalkSAT(vector< vector<int> > bf, string lit){
	vector<int> uns = fitness(bf, lit);
	int iterations = 0;
	while(fit != nbclauses){
		//first step: pick random unsatisfied clause
		srand(time(NULL));
		int r = rand() % uns.size();
		cout << "random unsat clause picked: " << (uns[r]+1) << endl;
	//go through every variable in this clause and see which one
	//can be flipped without making previously sat clauses unsat

	//make vector to represent new-fitness calculation corresponding to
	//variable being flipped
		vector<int> newfit;
		string templit = lit;
		int tempfit = fit;
		for(int t=0; t<nbvar; t++){
			lit = templit;
			if(lit[t]=='0')
				lit[t] = '1';//change to "1"
			else
				lit[t] = '0';//change to "0"
			fitness(bf, lit);
			newfit.push_back(fit);
		}
		cout << "new fitnesses from var flips:" << endl;
		for(int h=0; h<newfit.size(); h++)
			cout << newfit[h] << " ";
		cout << " " << endl;

		//now find largest fitness in this vector
		int max = 0;
		for(int u=1; u<newfit.size(); u++)
			if(newfit[u]>newfit[max])
				max = u;
		cout << "max fitness index = " << max << endl;
		cout << "lit[max] = " << lit[max] << endl;
		if(lit[max]=='0')
			lit[max] = '1';//change to "1"
		else
			lit[max] = '0';//change to "0"	
		cout << "lit[max] = " << lit[max] << endl;
		if(iterations>100){
			for(int g=0; g<nbvar; g++){
				srand(time(NULL));
				int ra = rand()%2;
				if(ra==0)
					lit[g] = '0';
				else
					lit[g] = '1';
			}
			iterations = 0; //random assignment given if stuck
			cout << "RESETTING!!!" << endl;
		}
		uns = fitness(bf, lit);
		iterations++;
	}
	//if all clauses are satisfied
	cout << "Satisfiable with literal: " << lit << endl;
	cout << "Now terminating WalkSAT." << endl;
	//because WalkSAT terminates as soon as one solution is found
}

void algHillClimbing(vector< vector<int> > bf, string lit){

}


int main(int argc, char* argv[]){
	if(argc == 2){//making sure there are exactly 2 command line arguments
		vector< vector<int> > lines;//creating a vector of strings to store each line in
		string l, literal = "";
//		int nbvar, nbclauses;
		int linenum = 0;
		ifstream myfile(argv[1]);
		if(myfile.is_open()){//reading in file of test boolean formulas
			while(getline(myfile, l)){
				vector<int> nums(4);
				istringstream is(l);
				int n, m=0;
				int j=0;
				string sub;
				if(linenum>0){
					while(is>>n){
						nums[j] = n;
						j++;
					}
					lines.push_back(nums);//then storing in vector
				}
				else{
					while(is>>sub){
						if(m==2){
							nbvar = atoi(sub.c_str());
						}
						if(m==3){
							nbclauses = atoi(sub.c_str());
						}
						m++;
					}
				}
				linenum++;
			}
			myfile.close();
		}//end if for reading in

		for(int i=0; i<nbvar; i++){
			literal += "0";
		}

		cout << "vector contains: " << endl;
		for(int t=0; t<lines.size(); t++){
			for(int u=0; u<4; u++){
				cout << lines[t][u] << " ";
			}
			cout << endl;
		}
		cout << "Number of variables: " << nbvar << endl;
		cout << "Number of  clauses: " << nbclauses << endl;
		cout << "Starting literal: " << literal << endl;
		vector<int> u = fitness(lines, literal);
		cout << "Number of clauses satisfied by literal: " << fit << endl;
		cout << "Clauses not satisfied:" << endl << "#";
		for(int t=0; t<u.size()-1; t++){
			cout << (u[t]+1) << ", ";
		}
		cout << (u[u.size()-1]+1) << endl << endl;
		string userin = "";
		while(userin!="4"){
			cout << "Please enter in the number corresponding with what you want to do." << endl;
			cout << "1 - WalkSAT Algorithm" << endl;
			cout << "2 - DPLL Algorithm" << endl;
			cout << "3 - Hill Climbing Algorithm" << endl;
			cout << "4 - Quit" << endl << endl;
			cin >> userin;
			if(userin == "1"){
				cout << "Running WalkSAT Algorithm." << endl;
				algWalkSAT(lines,literal);
			}
			else if(userin == "2"){
				cout << "Running DPLL Algorithm." << endl;
				algDPLL(lines, literal);
			}
			else if(userin == "3"){
				cout << "Running Hill Climbing Algorithm." << endl;
				algHillClimbing(lines, literal);
			}

//			algWalkSAT(lines, literal);
		}

	}//end if for argc
	else{//wont do anything unless it gets correct number of arguments
		cout << "Incorrect number of command line arguments." << endl;
		cout << "Exiting now." << endl;
	}
	return 0;
}
