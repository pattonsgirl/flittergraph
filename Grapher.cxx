//needed for pipline
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <vtkDelimitedTextReader.h>
#include <vtkTableToGraph.h>
#include <vtkTable.h>
#include <vtkVariant.h>
#include <vtkGraphLayout.h>
#include <vtkGraphLayoutView.h>
#include <vtkViewTheme.h>
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
    flitter_names->SetHaveHeaders(1);
    flitter_names->SetFieldDelimiterCharacters("\t");
    flitter_names->Update();

    //formatted as numeric id (0), friend ID (1)
    //These are the vertex edges
    auto *people_cities = vtkDelimitedTextReader::New();
    people_cities->SetFileName("../data/People-Cities.txt");
    people_cities->SetHaveHeaders(1);
    people_cities->SetFieldDelimiterCharacters("\t");
    people_cities->Update();

    //formatted as numeric id (0), City (1)
    //These are the vertex edges
    //IDS are NOT equal to IDs of users
    //subract by 12 - found by Kijowski
    auto *links_users = vtkDelimitedTextReader::New();
    links_users->SetFileName("../data/Links_Table.txt");
    links_users->SetHaveHeaders(1);
    links_users->SetFieldDelimiterCharacters("\t");
    links_users->Update();

    /* *** Code to play with Tables - checking data reading
    //Output number of rows and columns for files
    vtkTable* flitter_table = flitter_names->GetOutput();
    vtkTable* cities_table = people_cities->GetOutput();
    vtkTable* links_table = links_users->GetOutput();

    cout << "Table has " << cities_table->GetNumberOfRows() << " rows." << endl;
    cout << "Table has " << cities_table->GetNumberOfColumns() << " columns." << endl;
    //this will return a pointer, I think, to the array
    cout << "Cities are:\n " << cities_table->GetColumn(0) << std::endl;
    //Get value in format row, col - type is variant, so we need to cast as needed
    //.GetTypeAsString will return the TYPE as a STRING, NOT the value
    cout << "City for user 4:\n " << (cities_table->GetValue(5,1)).ToString() << endl;
    //formatted dump of table - it's loaded properly!
    links_table->Dump();
    */
    
    
    auto *links_t2g = vtkTableToGraph::New();
    links_t2g->AddInputConnection(links_users->GetOutputPort());
    links_t2g->AddLinkVertex("ID", "ID1", 0);
    links_t2g->AddLinkVertex("ID2", "ID2", 0);
    links_t2g->AddLinkEdge("ID", "ID2");

    auto *cities_t2g = vtkTableToGraph::New();
    cities_t2g->AddInputConnection(people_cities->GetOutputPort());
    cities_t2g->AddLinkVertex("ID", "ID1", 0);
    cities_t2g->AddLinkVertex("City", "ID2", 0);
    cities_t2g->AddLinkEdge("ID", "City");

    auto *layout = vtkGraphLayout::New();


    auto *graph_layout = vtkGraphLayoutView::New();
    graph_layout->AddRepresentationFromInputConnection(cities_t2g->GetOutputPort());
    graph_layout->SetLayoutStrategyToFast2D();

    auto *view_theme = vtkViewTheme::New();

    graph_layout->ApplyViewTheme(view_theme);
    view_theme->FastDelete();

    graph_layout->GetRenderWindow();
    graph_layout->ResetCamera();
    graph_layout->Render();
    graph_layout->GetInteractor()->Start();
    

}