//needed for pipline
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <vtkDelimitedTextReader.h>
#include <vtkTableToGraph.h>
#include <vtkTable.h>


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
    //formatted as numeric id, Flitter handle
    //These are the vertex names
    auto *flitter_names = vtkDelimitedTextReader::New();
    flitter_names->SetFileName("../data/Flitter_Names.txt");
    flitter_names->DetectNumericColumnsOn();
    flitter_names->SetFieldDelimiterCharacters("\t");
    flitter_names->Update();

    //formatted as numeric id, friend ID
    //These are the vertex edges
    auto *people_cities = vtkDelimitedTextReader::New();
    people_cities->SetFileName("../data/People-Cities.txt");
    people_cities->SetFieldDelimiterCharacters("\t");
    people_cities->Update();

    //formatted as numeric id, City
    //Cluster as geo locations?
    auto *links_table = vtkDelimitedTextReader::New();
    links_table->SetFileName("../data/Links_Table.txt");
    links_table->SetFieldDelimiterCharacters("\t");
    links_table->Update();

    vtkTable* table = people_cities->GetOutput();
    std::cout << "Table has " << table->GetNumberOfRows()
            << " rows." << std::endl;
    std::cout << "Table has " << table->GetNumberOfColumns()
            << " columns." << std::endl;

    

}