#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<math.h>

double focalLengthComp(double dist, int method);
double objectHeight(double dist, int pixelHeight, double sensorHeight, double fLenEff, double subHeight);
double objectWidth(double dist, int pixelWidth, double sensorWidth, double fLenEff, double subWidth);


int main()
{

	double dist; 		 							//distance from sensor to in-focus subject (m)
	double sensorHeight = 15.6; 					//height of image sensor (mm)
	double sensorWidth = 23.5;	 					//width of image sensor (mm)
	double fLenEff; 	 							//effective focal length (mm)
	int pixelHeight = 4000;	 						//vertical pixel height (px)
	int pixelWidth = 6000;							//horizontal pixel width (px)
	double subHeight;								//subject height (px)
	double subWidth;	 							//subject width (px)
	double objHeight;	 							//subject height (m)
	double objWidth;	 							//subject width (m)
	int ch;				 							//buffer clear

	printf("\nEnter distance to focal plane (subject) (meters): ");
	scanf("%lf[^\n]", &dist);
	while ((ch =getchar()) != EOF && ch != '\n'); //input buffer clear

	printf("\nEnter subject height (pixels): ");
	scanf("%lf[^\n]", &subHeight);
	while ((ch =getchar()) != EOF && ch != '\n'); //input buffer clear

	printf("\nEnter subject width (pixels): ");
	scanf("%lf[^\n]", &subWidth);
	while ((ch =getchar()) != EOF && ch != '\n'); //input buffer clear

	fLenEff = focalLengthComp(dist, 3); //defines the effective focal length, compensated for focal distance.

	objHeight = objectHeight(dist, pixelHeight, sensorHeight, fLenEff, subHeight); //finds the estimated actual object height, prints
	printf("ObjectHeight is: %f meters\n",objHeight);

	objWidth = objectWidth(dist, pixelWidth, sensorWidth, fLenEff, subWidth); //finds the estimated actual object width, prints
	printf("ObjectWidth is: %f meters\n",objWidth);


}

/* focalLengthComp
Focal length varies with focus distance.  This function attempts to compensate based on focal distance.
*/

double focalLengthComp(double dist, int method)
{ 
	/*
	Note that these cases are LENS SPECIFIC. Estimated compensations here are for the Nikon 50mm F/1.8G Prime on a DX body. 
	A focal length corrective curve can be found by measuring the lens angle of view (alpha) over a wide range of focal distances -
	ideally from the near-focus point to the far focus (infinity) point - and then creating a fit equation.  
	*/ 

	double fLenCor = 50.0; 
	switch(method){
		case 0:
			fLenCor = (-0.1668*dist + 50.075);
			break;
		case 1:
			fLenCor = (21.315*(pow(dist,2.0))-(48.979*dist)+64.797);
			break;
		case 2:
			fLenCor = (49.4115 - 1.98574*log(dist));
			break;
		case 3:
			fLenCor = (2.004*(pow(dist,4.0))-(21.875*(pow(dist,3.0)))+(78.249*(pow(dist,2.0)))-(115.936 * dist) + 111.396);
			break;
	
		default:
			fLenCor = 50.0;	
	}

	return fLenCor;
}

/* objectHeight
Calculates the real height of specific in-focus subject given other parameters.  Returns value in meters.
*/

double objectHeight(double dist, int pixelHeight, double sensorHeight, double fLenEff, double subHeight)
{

	//printf("Effective Flen is: %f mm\n",fLenEff);

	double focusAngle = ((2.0 * atan((sensorHeight / (2.0 * fLenEff)))));

	//printf("Angle is: %f\n",focusAngle);

	double halfHeight = (2.0 * tan((focusAngle)/2.0));

	//printf("HalfHeight is: %f\n",halfHeight);

	double planeHeight = ((halfHeight * dist) / pixelHeight);

	//printf("PlaneHeight is: %f\n",planeHeight);

	double objHeight = (planeHeight * subHeight);

	return objHeight;



}

/* objectWidth
Calculates the real width of specific in-focus subject given other parameters.  Returns value in meters.  
*/

double objectWidth(double dist, int pixelWidth, double sensorWidth, double fLenEff, double subWidth)
{


	double focusAngle = ((2.0 * atan((sensorWidth / (2.0 * fLenEff)))));

	double halfWidth = (2.0 * tan((focusAngle)/2.0));
	
	double planeWidth = ((halfWidth * dist) / pixelWidth);
	
	double objWidth = (planeWidth * subWidth);

	return objWidth;

}
