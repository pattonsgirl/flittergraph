//needed for pipline
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
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
    flitter_names->SetFileName("data/Flitter Names.txt");
    //flitter_names->DetectNumericColumnsOn();
    flitter_names->SetFieldDelimiterCharacters("\t");
    //flitter_names->Update();

    auto *people_cities = vtkDelimitedTextReader::New();
    people_cities->SetFileName("data/People-Cities.txt");
    people_cities->SetFieldDelimiterCharacters("\t");
    //people_cities->Update();

    auto *links_table = vtkDelimitedTextReader::New();
    links_table->SetFileName("data/Links_Table.txt");
    links_table->SetFieldDelimiterCharacters("\t");
    //links_table->Update();


}