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
    //setting up file readers
    auto *flitter_names = vtkDelimitedTextReader::New();
    flitter_names->SetFileName('VASTInfo/M2-Social Net and Geo/People-Cities.txt');
    //flitter_names->DetectNumericColumnsOn();
    flitter_names->SetFieldDelimiterCharacters(",");

    auto *people_cities = vtkDelimitedTextReader::New();
    people_cities->SetFileName('People-Cities.txt');
    people_cities->SetFieldDelimiterCharacters(",");

    auto *links_table = vtkDelimitedTextReader::New();
    links_table->SetFileName('VASTInfo/M2-Social Net and Geo/Links_Table.txt');
    links_table->SetFieldDelimiterCharacters(",");


}