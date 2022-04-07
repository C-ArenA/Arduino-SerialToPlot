/*
	Helps you plot data in the Arduino plotter
	By Carlos Arena (arenamovediza)
	By VReality (https://vrealitybolivia.com)
*/

#include <Arduino.h>
#include <SerialToPlot.h>

SerialToPlot<int> p;

void setup()
{
	p = SerialToPlot<int>(9600);
	String datasets[] = {"s1", "s2"}; // Array with labels
	p.addDatasets(datasets, 2); // We have 2 datasets
}

void loop()
{
	int points[] = {3,5}; // Array with data
	p.addDatasetsPoints(points); // Add new data
	p.plot(); // Plot data
	delay(100);
}