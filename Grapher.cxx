#include <vtkSmartPointer.h>
#include <vtkDelimitedTextReader.h>

//includes for C++
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//int main(int, char* [])
int main(int argc, char* argv[]) {
    //setting up file readers - data can be interpreted as csv files
    auto *flitter_names = vtkDelimitedTextReader::New();
    flitter_names->SetFileName("data/People-Cities.txt");
    //flitter_names->DetectNumericColumnsOn();
    flitter_names->SetFieldDelimiterCharacters(",");

    auto *people_cities = vtkDelimitedTextReader::New();
    people_cities->SetFileName("data/People-Cities.txt");
    people_cities->SetFieldDelimiterCharacters(",");

    auto *links_table = vtkDelimitedTextReader::New();
    links_table->SetFileName("data/Links_Table.txt");
    links_table->SetFieldDelimiterCharacters(",");


}