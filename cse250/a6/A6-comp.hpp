int getHammingWeight(int num){
	if(num < 0){
		return 0; //doesn't accept neg numbers
	}

	int w = 0;
	while(num){
		num &= (num - 1);
		w += 1;
	}

	return w;	
}


class CompareBits {
public:
   bool operator() (const int& lhs, const int& rhs) {
      if(getHammingWeight(lhs) < getHammingWeight(rhs)){
      	return true;
      } else {
      	return false;
      }
   }
};
