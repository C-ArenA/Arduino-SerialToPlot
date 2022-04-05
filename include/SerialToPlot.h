#pragma once
#include <Arduino.h>

template <typename T>
struct Dataset
{
	String label;
	T currentValue;
};

template <typename T>
class SerialToPlot
{
private:
	uint8_t datasetsQuantity = 0;
	uint8_t actualDatasetsQuantity = 0;
	Dataset<T> *datasets;
	int testValue = 10;
	int baudrate = 9600;

public:
	SerialToPlot(int baudrate = 9600, uint8_t datasetsNumber = 0);
	~SerialToPlot();
	int addDataset(String label, T initialValue = -1); // Returns the index (ID) of the new dataset
	int addDatasets(String* labels, int datasetsQuantity);
	void addDatasetPoint(int datasetId, T value);
	void addDatasetsPoints(T* values);
	void plot();
	void printTestValue();
};

template <typename T>
SerialToPlot<T>::SerialToPlot(int baudrate, uint8_t datasetsNumber)
{
	this->baudrate = baudrate;
	this->datasetsQuantity = datasetsNumber;
	Serial.begin(this->baudrate);
	Serial.println("Inicializando_Plotter");
	datasets = new Dataset<T>[this->datasetsQuantity];
}

template <typename T>
SerialToPlot<T>::~SerialToPlot()
{
}

template <typename T>
void SerialToPlot<T>::printTestValue()
{
	Serial.println(this->testValue);
}

template <typename T>
int SerialToPlot<T>::addDataset(String label, T initialValue)
{
	if (actualDatasetsQuantity < datasetsQuantity)
	{
		Dataset<T> dp = {label, initialValue};
		datasets[actualDatasetsQuantity] = dp;
		actualDatasetsQuantity++;
	}
	return actualDatasetsQuantity - 1; // returns the index of this dataset
}

template <typename T>
int SerialToPlot<T>::addDatasets(String* labels, int datasetsQuantity)
{
	this->datasetsQuantity = datasetsQuantity;
	
	//delete datasets;
	datasets = new Dataset<T>[this->datasetsQuantity];
	
	for (uint8_t i = 0; i < datasetsQuantity; i++)
	{
		Dataset<T> dp = {labels[i], 0};
		datasets[i] = dp;
	}

	actualDatasetsQuantity = datasetsQuantity;
	return actualDatasetsQuantity - 1; // returns the index of last dataset
}

template <typename T>
void SerialToPlot<T>::addDatasetPoint(int index, T value)
{
	if (index < datasetsQuantity)
	{
		this->datasets[index].currentValue = value;
	}
}

template <typename T>
void SerialToPlot<T>::addDatasetsPoints(T* values)
{
	for (uint8_t i = 0; i < datasetsQuantity; i++)
	{
		this->datasets[i].currentValue = values[i];
	}
}

template <typename T>
void SerialToPlot<T>::plot()
{
	if (datasetsQuantity == 0)
	{
		Serial.print("DEBUG No_hay_valores_que_mostrar");
		Serial.print(":");
		Serial.print(-1);
		Serial.println();
	}
	else
	{
		for (int i = 0; i < datasetsQuantity; i++)
		{

			Serial.print(datasets[i].label);
			Serial.print(":");
			Serial.print(datasets[i].currentValue);
			if (i != datasetsQuantity - 1)
			{
				Serial.print(",");
			}
		}

		Serial.println();
	}
}

