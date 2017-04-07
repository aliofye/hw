#include <iostream>
#include <cmath>
#include <string>

using std::cout;
using std::endl;
using std::pow;
using std::string;


string convert(unsigned int val)
{
   unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);

   string str;

   for(unsigned int i = 0; i < sizeof(unsigned int) * 8; i++)
   {
      if( (val & mask) == 0 )
         str += '0' ;
      else
         str += '1' ;

      mask  >>= 1;
   }
   
   return str;
}

void reset(unsigned int limit, bool* const chosenCust){
  for (unsigned int i = 0; i < limit; i++){
    chosenCust[i] = false;
  }
}

bool neighborhoodIsViable(const int& numCust,
                          const int& maxBandwidth,
                          const int& maintenanceCost,
                          const int* const reqBand,
                          const int* const reqPrice,
                          bool* const chosenCust) {
  
  unsigned int limit = pow(2, numCust);
  //cout << limit << endl;
  
  bool isValid = false;


  for(unsigned int i = 0; i < limit; ++i){

    string str = convert(i);
    str = str.substr(str.length() - numCust, str.length());
    //cout << str << endl;

    unsigned int totalBand = 0;
    unsigned int totalPrice = 0;

    for (unsigned int j = 0; j < str.length(); ++j){
      
      if(str[j] == '1'){
        totalBand += reqBand[j];
        totalPrice += reqPrice[j];
        chosenCust[j] = true;

        if(totalBand <= maxBandwidth && totalPrice >= maintenanceCost){
          isValid = true;
          break;
        } 
      }
    }


    if(isValid){
      break;
    } else {
      reset(numCust, chosenCust);
    }
  }

  return isValid;

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