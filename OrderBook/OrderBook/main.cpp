#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "CsvFile.h"
#include "OrderBook.h"

using namespace std;

istream& operator>>(istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
} 

void UpdateOrderBook(){}


int main ()
{
	vector<vector<string>> quoteLines;
	int numColumns = 6; // Time, OrderId, Type, Side, Price, Size 
	ifstream file("C:/coding/ABC/OrderBook/Debug/quotes.csv");
	CSVRow row;

	if (file.is_open())
	{
		while (file >> row)
		{
			quoteLines.push_back(row.getData());
		}
	}
	else 
	{
		cout << "cannot open the file" << endl;
	}

	OrderBook book(quoteLines);

	getchar();
	return 0;
}