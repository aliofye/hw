#include <iostream>
#include "a1.hpp"

using std::cout;
using std::endl;


int main() {
   //////////////////////////////////////////////
   // Change these values to get a new test case.
   int numCust = 10;
   int maxBandwidth = 150;
   int maintenanceCost = 100;
   int reqBand[] = {151,151,50,151,50,151,50,151,151,151};
   int reqPrice[] = {100,100,30,100,30,100,40,100,100,100};
   bool chosenCust[10];
   double partialCust[10];
   //////////////////////////////////////////////
   
   // Check if neighboorhood is viable.
   bool isViable = neighborhoodIsViable(numCust, maxBandwidth, maintenanceCost, reqBand, reqPrice, chosenCust);
   
   int bandwidthUsed = 0;
   int moneyCharged = 0;
   
   if(isViable) {
      cout << "Viable venture. A set of customers that works: " << endl;
      cout << "{" << chosenCust[0];
      for(int i=1; i< numCust; i++) {
         cout << ", " << chosenCust[i];
      }
      cout << "}" << endl;
      
      for(int i=0; i<numCust; i++) {
         if(chosenCust[i]) {
            bandwidthUsed += reqBand[i];
            moneyCharged += reqPrice[i];
         }
      }
      cout << "Bandwidth used by customers: " << bandwidthUsed << ", money paid by customers: " << moneyCharged << endl;
   }
   else {
      cout << "Not viable." << endl;
   }
   
   /*
   bool isViableMax = neighborhoodIsViableMaxProfit(numCust, maxBandwidth, maintenanceCost, reqBand, reqPrice, chosenCust);
   
   bandwidthUsed = 0;
   moneyCharged = 0;
   
   if(isViableMax) {
      cout << "Max income venture customers: " << endl;
      cout << "{" << chosenCust[0];
      for(int i=1; i<numCust; i++) {
         cout << ", " << chosenCust[i];
      }
      cout << "}" << endl;
      
      for(int i=0; i<numCust; i++) {
         if(chosenCust[i]) {
            bandwidthUsed += reqBand[i];
            moneyCharged += reqPrice[i];
         }
      }
      cout << "Bandwidth used by customers: " << bandwidthUsed << ", money paid by customers: " << moneyCharged << endl;
   }
   else {
      cout << "Not viable." << endl;
   }
   */
   
   /*
   bool isViablePartial = neighborhoodIsViablePartialBand(numCust, maxBandwidth, maintenanceCost, reqBand, reqPrice, partialCust);
   
   double bandwidthUsedPartials = 0;
   double moneyChargedPartials = 0;
   if(isViableMax) {
      cout << "Max income venture customers: " << endl;
      cout << "{" << partialCust[0];
      for(int i=1; i<numCust; i++) {
         cout << ", " << partialCust[i];
      }
      cout << "}" << endl;
      
      for(int i=0; i<numCust; i++) {
         bandwidthUsedPartials += partialCust[i]*reqBand[i];
         moneyChargedPartials += partialCust[i]*reqPrice[i];
      }
      cout << "Bandwidth used by customers: " << bandwidthUsedPartials << ", money paid by customers: " << moneyChargedPartials << endl;
   }
   else {
      cout << "Not viable." << endl;
   }
   */

}