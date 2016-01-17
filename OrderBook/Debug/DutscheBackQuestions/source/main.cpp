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

int main ()
{
	vector<vector<string>> quoteLines;
	ifstream file("C:/coding/ABC/OrderBook/Debug/quotes.csv");
	file.ignore(100000, '\n');		// ignore the header line
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

	cout << "Please enter a timestamp between " 
		 << quoteLines[0][0] << " and " 
		 << quoteLines[quoteLines.size()-1][0] << endl
		 << "or type 0 to exit" << endl;
	
	while(true)
	{
		uint32_t t;
		cin >> t;
		if (t == 0)
			break;
		OrderBook book(quoteLines);
		book.PrintOrderBook(t);
	}
	return 0;
}