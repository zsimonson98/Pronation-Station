#include "Arduino.h"
#include "Shoe.h"
#include "String.h"
Shoe::Shoe(String model, String fxn, int price, double weight) 
{
	this->model = model;
  	this->fxn = fxn;
  	this->price = price;
  	this->weight = weight;
}
