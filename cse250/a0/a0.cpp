#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::invalid_argument;
using std::getline;

int main(int argc, char* argv[]){

	const int MAX_ARGS = 4; //4 because file name is counted as one
	char space = ' ';
	ifstream input_ifs;
	ofstream output_ofs;
	string line;
	int test_int;

	if (argc != MAX_ARGS){
		cout << argc << endl;
		cout << "Error: invalid number of arguments." << endl;
	} else {
		
		string input = argv[1];
		string output = argv[2];
		string id = argv[3];

		try{
			test_int = stoi(id);
		} catch (const invalid_argument& e){
			cout << "Error: invalid id (not an integer)." << endl;
		}


		input_ifs.open(input);
		if(input_ifs.fail()){
			cout << "Error: invalid input file." << endl;
		} else {

			output_ofs.open(output);
			if(output_ofs.fail()){
				cout << "Error: invalid output file." << endl;
			} else {
				getline(input_ifs, line);
				string header = line.substr(line.find(",") + 1, line.length());
				output_ofs << header; 

				while(getline(input_ifs, line)){
					string identifier = line.substr(0, line.find(","));

					if(identifier == id){
						identifier = line.substr(line.find(",") + 1, line.length());
						output_ofs << endl << identifier;
					}
				}
			}
			output_ofs.close();
			input_ifs.close();
		}		
	}

	return 0;
}


