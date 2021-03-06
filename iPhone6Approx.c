#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<math.h>

double focalLengthComp(double dist);
double objectHeight(double dist, int pixelHeight, double sensorHeight, double fLenEff, double subHeight);
double objectWidth(double dist, int pixelWidth, double sensorWidth, double fLenEff, double subWidth);
double lensToDist(double lensPos);

int main()
{

	double dist; 		 							//distance from sensor to in-focus subject (m)
	double sensorHeight = 0.00276; 					//height of image sensor (m)
	double sensorWidth = 0.00368;	 				//width of image sensor (m)
	double fLenEff; 	 							//effective focal length (mm)
	int pixelHeight = 2448;	 						//vertical pixel height (px)
	int pixelWidth = 3264;							//horizontal pixel width (px)
	double subHeight;								//subject height (px)
	double subWidth;	 							//subject width (px)
	double objHeight;	 							//subject height (m)
	double objWidth;	 							//subject width (m)
	double lensPos;
	int ch;				 							//buffer clear

	printf("\nEnter Lens Position (0 - 1): ");
	scanf("%lf[^\n]", &lensPos);
	while ((ch =getchar()) != EOF && ch != '\n'); //input buffer clear

	printf("\nEnter subject height (pixels): ");
	scanf("%lf[^\n]", &subHeight);
	while ((ch =getchar()) != EOF && ch != '\n'); //input buffer clear

	printf("\nEnter subject width (pixels): ");
	scanf("%lf[^\n]", &subWidth);
	while ((ch =getchar()) != EOF && ch != '\n'); //input buffer clear

	dist = lensToDist(lensPos); //Calculates dist based on the lens position
	fLenEff = focalLengthComp(dist); //defines the effective focal length, compensated for focal distance.

	objHeight = objectHeight(dist, pixelHeight, sensorHeight, fLenEff, subHeight); //finds the estimated actual object height, prints
	printf("ObjectHeight is: %f meters\n",objHeight);

	objWidth = objectWidth(dist, pixelWidth, sensorWidth, fLenEff, subWidth); //finds the estimated actual object width, prints
	printf("ObjectWidth is: %f meters\n",objWidth);


}

double lensToDist(double lensPos)
{
	if(lensPos <= 0.69){
		return (((5868*(pow(lensPos,5.0)))-(8131*(pow(lensPos,4.0)))+(4139*(pow(lensPos,3.0)))-(860.4*(pow(lensPos,2.0)))+(80.56 * lensPos) + 7.717)/100);
	}
	else{
		return (0.002405* (pow(M_E , (9.012* lensPos))));
	}
}

/* focalLengthComp
Focal length varies with focus distance.  This function attempts to compensate based on focal distance.
*/

double focalLengthComp(double dist)
{ 
	/*
	Note that these cases are LENS SPECIFIC. Estimated compensations here are for the iPhone 6 (Sony Exmor ISX014). 
	A focal length corrective curve can be found by measuring the lens angle of view (alpha) over a wide range of focal distances -
	ideally from the near-focus point to the far focus (infinity) point - and then creating a fit equation.  
	*/ 
	if(dist <= .175){
		return ((-657.274*(pow(dist,4.0))+(254.198*(pow(dist,3.0)))+(21.39*(pow(dist,2.0)))-(16.748 * dist) + 4.739)/1000);
	}
	else
		return (-0.008143*dist + 3.201)/1000;
		
			
}

/* objectHeight
Calculates the real height of specific in-focus subject given other parameters.  Returns value in meters.
*/

double objectHeight(double dist, int pixelHeight, double sensorHeight, double fLenEff, double subHeight)
{
	return (sensorHeight * dist * subHeight) / (fLenEff * pixelHeight);
}

/* objectWidth
Calculates the real width of specific in-focus subject given other parameters.  Returns value in meters.  
*/

double objectWidth(double dist, int pixelWidth, double sensorWidth, double fLenEff, double subWidth)
{
	return (sensorWidth * dist * subWidth) / (fLenEff * pixelWidth);
}


