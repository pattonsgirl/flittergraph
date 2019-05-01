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
#include <vtkAnnotationLink.h>
#include <vtkViewUpdater.h>
#include <vtkStringToCategory.h>
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
    
    //basing this off of select-domain.py
    //Annotation Link should help us connect components between view windows
    //testing setting against user IDs / Flitter IDs
    auto *anno_link = vtkAnnotationLink::New();
    anno_link->AddDomainMap(flitter_names->GetOutput());
    
    auto *links_t2g = vtkTableToGraph::New();
    links_t2g->AddInputConnection(links_users->GetOutputPort());
    links_t2g->AddLinkVertex("ID", "ID1", 0);
    //don't need or want vertexes duplicated?
    //links_t2g->AddLinkVertex("ID2", "ID2", 0);
    links_t2g->AddLinkEdge("ID2", "ID");

    auto *cities_t2g = vtkTableToGraph::New();
    cities_t2g->AddInputConnection(people_cities->GetOutputPort());
    //cities_t2g->AddInputConnection(links_users->GetOutputPort());
    cities_t2g->AddLinkVertex("ID", "ID", 0);
    cities_t2g->AddLinkVertex("City", "City", 0);
    cities_t2g->AddLinkEdge("ID", "City");

    auto *cities_layout = vtkGraphLayoutView::New();
    cities_layout->AddRepresentationFromInputConnection(cities_t2g->GetOutputPort());
    //cities_layout->SetVertexLabelArrayName("ID");
    cities_layout->SetVertexLabelArrayName("City");
    cities_layout->SetVertexLabelVisibility(1);
    cities_layout->GetRenderWindow()->SetSize(500,500);
    cities_layout->SetLayoutStrategyToFast2D();

    auto *links_layout = vtkGraphLayoutView::New();
    links_layout->AddRepresentationFromInputConnection(links_t2g->GetOutputPort());
    //links_layout->SetVertexLabelArrayName("ID");
    //links_layout->SetVertexLabelVisibility(1);
    links_layout->GetRenderWindow()->SetSize(500,500);
    links_layout->SetLayoutStrategyToFast2D();

    //NOTE: ONLY DOING FOR LINKS HERE
    //creates a category array from a string array
    auto *str_category = vtkStringToCategory::New();
    str_category->SetInputConnection(cities_t2g->GetOutputPort());
    //TODO: Play with what these variables mean - 3rd was 4 - this seems to be a size parameter?
    str_category->SetInputArrayToProcess(0,0,0,vtkDataObject::FIELD_ASSOCIATION_VERTICES,"domain");

    /*
    auto *rep = cities_layout->AddRepresentationFromInputConnection(str_category->GetOutputPort());
    rep->SetSelectionType(2);
    rep->SetAnnotationLink(anno_link);
    */
    
    auto *view_theme = vtkViewTheme::New()->CreateMellowTheme();
    view_theme->SetSelectedCellColor(1,0,1);
    view_theme->SetSelectedPointColor(1,0,1);
    //TODO: Play with colors

    cities_layout->ApplyViewTheme(view_theme);
    links_layout->ApplyViewTheme(view_theme);
    view_theme->FastDelete();

    //set up multiple render windows
    cities_layout->GetRenderWindow();
    cities_layout->ResetCamera();
    cities_layout->Render();

    links_layout->GetRenderWindow();
    links_layout->ResetCamera();
    links_layout->Render();

    //this is to update view windows with our link?
    auto updater = vtkViewUpdater::New();
    updater->AddAnnotationLink(anno_link);
    updater->AddView(cities_layout);
    updater->AddView(links_layout);

    //only need to call one to get the party started?
    cities_layout->GetInteractor()->Start();
    //links_layout->GetInteractor()->Start();
    
}