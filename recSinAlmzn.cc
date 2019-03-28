#include <iostream>

double sack(
	const vector<double> &v, //Values
	const vector<unsigned> &w, //Weights
	int n,                    //Number of objects
	unsigned W               //sack weight limit
)

 
{
	if( n == 0){        	 //Base case
		return 0;
	}

	double S1 = sack(v, w, n-1, W);  //Try not to put it on

	double S2 = numeric_limit<double>::lowest();

	if(w[n-1] <= W){   //Does it fit in the sack
		S2 = v[n-1]+sack(v,w,n-1,W-w[n-1]); //Try to put it on	
	}


	return max(S1,S2); //Choose the best

}
