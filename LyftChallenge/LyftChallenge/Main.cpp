#include <iostream>
#include <math.h>
using namespace std;

#define PI 3.14159265
#define RADIUS 3959  // Assumes miles for the units

struct point {
	double longitude;
	double latitude;

	point(double lon, double lat) : longitude(lon), latitude(lat) {}
};

/* Converts degrees to radians */
double toRadians(double degree)
{
	return degree*PI / 180;
}

/* This function makes use of the Haversine Formula to 
compute the great-circle distance between two points.
For more information visit https://en.wikipedia.org/wiki/Haversine_formula 
*/
double calculateDistance(point *source, point *destination)
{
	double latSource = toRadians(source->latitude);
	double latDestination = toRadians(destination->latitude);
	double latDifference = latDestination - latSource;

	double lonDifference = toRadians(destination->longitude - source->longitude);

	double firstTerm = pow(sin(latDifference / 2), 2);
	double secondTerm = cos(latSource) * cos(latDestination) * pow(sin(lonDifference / 2),2);
	double tangentTerm = atan2(sqrt(firstTerm + secondTerm), sqrt(1 - (firstTerm + secondTerm)));
	double distance = 2 * RADIUS * tangentTerm;

	return distance;
}

/* Assume that we have two drivers. DriverA who has a source A and destination B,
and DriverB, who has source C and destination D. We want to compare the detour distances
for one to pick up the other and drop him/her off at their destination before proceeding to their own.

Normally, DriverA goes from A->B and DriverB goes from C->D

If DriverA is picking up the other driver, the path is then:  A->C->D->B
Similarly, if DriverB is picking up the other driver, the path is: C->A->B->D

To compute the total distance for each of these, we would calculate it as follows..
driverADistance = dist(A->C) + dist(C->D) + dist(D->B)
driverBDistance = dist(C->A) + dist(A->B) + dist(B->D)

Note that distance calculations are the same irrespective of their direction.
So dist(A->C) == dist(C->A), and dist(D->B) == dist(B->D)

Therefore, all we really need to calculate to find the shortest detour is the following:
driverADistance = dist(C->D)
driverBDistance = dist(A->B)
*/
void determineShortestDetour(point *locA, point *locB, point *locC, point *locD)
{
	// Calculate the respective differences using the above method
	double driverADistance = calculateDistance(locC, locD);
	double driverBDistance = calculateDistance(locA, locB);

	// Print out the results
	if (driverADistance < driverBDistance)
		cout << "Shorter path is A->C->D->B for DriverA. " 
		<< driverADistance << " miles < " << driverBDistance << " miles " << endl;
	else if (driverBDistance < driverADistance)
		cout << "Shorter path is C->A->B->D for DriverB. " 
		<< driverBDistance << " miles < " << driverADistance << " miles " << endl;
	else
		cout << "The distances are the same, either one can take the detour. " 
		<< driverADistance << " miles == " << driverBDistance << " miles" << endl;
}

int main()
{
	// Given 4 points consisting of a latitude and longitude
	point *locA = new point(12.39, -9.27);
	point *locB = new point(2.199, 15.9);
	point *locC = new point(-9.0, 13.9);
	point *locD = new point(3.23, 5.0);

	// Determines the shortest detour to take
	determineShortestDetour(locA, locB, locC, locD);

	system("Pause");
	return 0;
}