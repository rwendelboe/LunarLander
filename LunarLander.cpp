#include <iostream>
#include "lunarLander.h"

using namespace std;


Lander::Lander(){
	G.x = -1.622; 
	G.y = 0;
	angle = PI/2; 
	velocity.x= 0 ;
	velocity.y = 0;
	fuel= 1500;
	position.x=0 ;
	position.y=0;
	maxTouchdownVelocity= 5 ;
	crashed= false;
	landed= false;
	fuelBurnedThisTurn=0;
	rotatedThisTurn=0;

}
Lander::Lander(Vect iG, double iangle, Vect ivelocity, double ifuel,
               Vect iposition, double imax, bool icrashed, bool landed){
				   G.x = iG.x;
				   G.y = iG.y;
				   if (angle <0) angle = 0;
				   else if (angle >= PI/12) angle = PI/12;
				   else{
					   angle= iangle;}
				   velocity.x = ivelocity.x;
				   velocity.y = ivelocity.y;
				   if (fuel <0) fuel = 0;
				   else {
					   fuel = ifuel;}
				   position.x = iposition.x;
				   if(position.y <0) position.y = 0;
				   else{
				   position.y = iposition.y;
				   }
				   maxTouchdownVelocity = imax;
				   crashed = icrashed;
				   landed = landed;
				   fuelBurnedThisTurn=0;
				   rotatedThisTurn=0;


   
}
double Lander::getAngle(){
	return angle;
}
Vect Lander::getVelocity(){
	return velocity;
}
double Lander::getFuel(){
	return fuel;
}
Vect Lander::getPosition(){
	return position;
}
double Lander::getMTV(){
	return maxTouchdownVelocity;
}
bool Lander::getCrashed(){
	return crashed;
}
bool Lander::getLanded(){
	return landed;
}

void Lander::rotateLeft(double rotateAngle){
	
	if(rotatedThisTurn < PI/12){
		rotatedThisTurn +=rotateAngle;}
		else rotatedThisTurn = PI/12;
		angle = rotatedThisTurn;

}//max rotation per sec is pi/12

void Lander::rotateRight(double rotateAngle){
	
	if(rotatedThisTurn < PI/12)
	{
		rotatedThisTurn -= rotateAngle;
	}
		else rotatedThisTurn = PI/12;
		angle = rotatedThisTurn;
}//max rotation per sec is pi/12

void Lander::burn(double fuelAmount){
	if (fuel < fuelAmount )
	{
		fuelAmount= fuel;
	}
	
	fuelBurnedThisTurn = fuelAmount;
	if (fuelBurnedThisTurn >50) fuelBurnedThisTurn = 50;
	fuel -= fuelBurnedThisTurn;
}//max fuelBurn per sec is 50;

void Lander::timeUpdate(){
	if (crashed) return;
	thrust.x = fuelBurnedThisTurn*sin(angle);
	thrust.y = fuelBurnedThisTurn*cos(angle);
	velocity.x = velocity.x + thrust.x + G.x;
	velocity.y = velocity.y + thrust.y + G.y;
	position.x = position.x + velocity.x;
	position.y = position.y + velocity.y;
	 if (position.x <= 0)
	 {
		 if (maxTouchdownVelocity>= abs(velocity.x))
			 landed = true;
		 else
			 crashed = true;
	 }
	
	




	//check on fuel, check on crashed/landing, 1 rotate the lander,2 burn fuel, 3 calculate new velocity , 4 cal new position,
}
// right triaangle
// t= t.x + t.y
// t.x= b*cos0
// t.y= b *sin0
// V'= V + t + G
// P'= P + V'
//
//
