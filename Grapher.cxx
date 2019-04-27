//needed for pipline
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <vtkDelimitedTextReader.h>
#include <vtkTableToGraph.h>
#include <vtkTable.h>
#include <vtkVariant.h>
//includes for C++
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//int main(int, char* [])
int main(int argc, char* argv[]) {
    //string inputFilename = "../data/Flitter_Names.txt";

    //setting up file readers - data can be interpreted as csv files
    //formatted as numeric id (0), Flitter handle (1)
    //These are the vertex names
    auto *flitter_names = vtkDelimitedTextReader::New();
    flitter_names->SetFileName("../data/Flitter_Names.txt");
    flitter_names->DetectNumericColumnsOn();
    flitter_names->SetFieldDelimiterCharacters("\t");
    flitter_names->Update();

    //formatted as numeric id (0), friend ID (1)
    //These are the vertex edges
    auto *people_cities = vtkDelimitedTextReader::New();
    people_cities->SetFileName("../data/People-Cities.txt");
    people_cities->SetFieldDelimiterCharacters("\t");
    people_cities->Update();

    //formatted as numeric id (0), City (1)
    //These are the vertex edges
    //IDS are NOT equal to IDs of users
    //subract by 12 - found by Kijowski
    auto *links_table = vtkDelimitedTextReader::New();
    links_table->SetFileName("../data/Links_Table.txt");
    links_table->SetFieldDelimiterCharacters("\t");
    links_table->Update();

    
    //Output number of rows and columns for files
    vtkTable* table = people_cities->GetOutput();
    cout << "Table has " << table->GetNumberOfRows()
            << " rows." << std::endl;
    cout << "Table has " << table->GetNumberOfColumns()
            << " columns." << std::endl;
    //this will return a pointer, I think, to the array
    //std::cout << "Cities are:\n " << table->GetColumn(0) << std::endl;
    //Get value in format row, col - type is variant, so we need to cast as needed
    cout << "City for user 5:\n " << (table->GetValue(5,1)).ToString() << std::endl;
    
    auto *t2g = vtkTableToGraph::New();

    

}