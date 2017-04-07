#include <iostream>
#include <cmath>
#include <string>
using std::cout;
using std::endl;
using std::pow;
using std::string;



//change all the nums into binary
string intToBinary(unsigned int num){
    string str;
    unsigned int bin = 1 << (sizeof(unsigned int) * 8 - 1);

    for (int i = 0; i < sizeof(unsigned int) * 8; i++) {
        if((num & bin) == 0)
            str += '0';
        else
            str += '1';

        bin >>= 1;
    }

    return str;
}
//power of array into limit

bool neighborhoodIsViable(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          bool* const chosenCust) {

    int max = pow(2,numCust);//power of 2^numcust
    int band = 0;
    int price = 0;
    bool found = false;
//loops thru the elements to find the value
    for (int i = 0; i < max; i++) {
        string str = intToBinary(i);
        str = str.substr(str.length() - numCust, str.length());
        //cout << str << endl;

        band = 0;
        price = 0;

        for (int j = 0; j < str.length(); j++) {
            
            if(str[j] == '1'){
                chosenCust[j] = true;
                band += reqBand[j];
                price += reqPrice[j];

                if(band <= maxBandwidth && price >= maintenanceCost){
                    found = true;
                    break;//end the loop
                }
            } 

        }

        if(found){
          break;
        } else {   
          for (int k = 0; k < numCust; k++) {
            chosenCust[k] = false;
          }
        }


    }
    return found;//return back when found
}

// Bonus function.
/*
bool neighborhoodIsViableMaxProfit(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          bool* const chosenCust) {
   return false;
}
*/


// Bonus function.
/*
bool neighborhoodIsViablePartialBand(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          double* const chosenCust) {
   return false;
}
*/