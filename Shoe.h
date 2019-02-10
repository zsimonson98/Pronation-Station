#ifndef Shoe_h
#define Shoe_h
#include "Arduino.h"
#include "String.h"

class Shoe
{	
  	public:
  		String model;
  		String fxn;
  		int price;
  		double weight;
  		Shoe(String model, String fxn, int price, double weight);
};

#endif
