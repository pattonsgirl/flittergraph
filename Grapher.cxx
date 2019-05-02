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
#include <vtkDataRepresentation.h>
#include <vtkOutEdgeIterator.h>
#include <vtkGraph.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkIntArray.h>
//#include <vtkIdType.h> - not a thing
//includes for C++
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
    
    //TODO: This method is losing the reverse connection - only looking at col 2
    auto *links_t2g = vtkTableToGraph::New();
    links_t2g->AddInputConnection(links_users->GetOutputPort());
    links_t2g->AddLinkVertex("ID2", "ID", 0);
    //don't need or want vertexes duplicated?
    //links_t2g->AddLinkVertex("ID2", "ID2", 0);
    //TODO: would like to only add edges IF count is greater than threshold
    links_t2g->AddLinkEdge("ID", "ID2");
    //links_t2g->AddLinkEdge("ID2", "ID");
    links_t2g->Update();

    int num_link_vertices = links_t2g->GetOutput()->GetNumberOfVertices();
    //create a new graph that will contain bosses (99+ links)
    auto *bosses_graph = vtkMutableDirectedGraph::New();
    //handlers - between 30 and 40 links
    auto *handler_graph = vtkMutableDirectedGraph::New();
    //middlemen - between 4 and 5 links
    auto *middleman_graph = vtkMutableDirectedGraph::New();
    //bosses_graph->DeepCopy(links_t2g->GetOutput());
    for(int i = 0; i < num_link_vertices; i++){
        int degree = links_t2g->GetOutput()->GetDegree(i);
        auto *link_edge_iterator = vtkOutEdgeIterator::New();
        if(100 <= degree){
            //then it's a boss candidate
            vtkIdType a = bosses_graph->AddVertex();
            links_t2g->GetOutput()->GetOutEdges(i, link_edge_iterator);
            while(link_edge_iterator->HasNext()) { 
                vtkOutEdgeType edge = link_edge_iterator->Next();
                //std::cout << "Source: " << i << " Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
                edge.Target = bosses_graph->AddChild(a);
            }
        }
        
        else if(30 <= degree && 40 >= degree) {
            //then it's a handler OR employee candidate
            vtkIdType a = handler_graph->AddVertex();
            links_t2g->GetOutput()->GetOutEdges(i, link_edge_iterator);
            while(link_edge_iterator->HasNext()) { 
                vtkOutEdgeType edge = link_edge_iterator->Next();
                //std::cout << "Source: " << i << " Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
                edge.Target = handler_graph->AddChild(a);
            }
        }
        else if(4 <= degree && 5 >= degree){
            //then it's a middleman candidate
            vtkIdType a = middleman_graph->AddVertex();
            links_t2g->GetOutput()->GetOutEdges(i, link_edge_iterator);
            while(link_edge_iterator->HasNext()) { 
                vtkOutEdgeType edge = link_edge_iterator->Next();
                //std::cout << "Source: " << i << " Edge id: " << edge.Id << " Target: " << edge.Target << std::endl;
                edge.Target = middleman_graph->AddChild(a);
            }
        }
        //else we don't care, they aren't the droids we are looking for
    }


    auto *cities_t2g = vtkTableToGraph::New();
    cities_t2g->AddInputConnection(people_cities->GetOutputPort());
    //cities_t2g->AddInputConnection(links_users->GetOutputPort());
    cities_t2g->AddLinkVertex("ID", "ID", 0);
    cities_t2g->AddLinkVertex("City", "City", 0);
    cities_t2g->AddLinkEdge("ID", "City");
    //need to call update OR vertices is not populated
    cities_t2g->Update();

    auto *cities_layout = vtkGraphLayoutView::New();
    cities_layout->AddRepresentationFromInputConnection(cities_t2g->GetOutputPort());
    //cities_layout->SetVertexLabelArrayName("ID");
    cities_layout->SetVertexLabelArrayName("City");
    cities_layout->SetVertexLabelVisibility(1);
    cities_layout->GetRenderWindow()->SetSize(600,600);
    cities_layout->GetRenderWindow()->SetWindowName("Users in Cities");
    cities_layout->SetLayoutStrategyToFast2D();

    auto *links_layout = vtkGraphLayoutView::New();
    links_layout->AddRepresentationFromInputConnection(links_t2g->GetOutputPort());
    links_layout->SetVertexLabelArrayName("ID");
    links_layout->SetVertexLabelVisibility(1);
    links_layout->GetRenderWindow()->SetSize(600,600);
    links_layout->GetRenderWindow()->SetWindowName("Links - All");
    links_layout->SetLayoutStrategyToClustering2D();

    auto *boss_layout = vtkGraphLayoutView::New();
    boss_layout->SetRepresentationFromInput(bosses_graph);
    //boss_layout->GetVertexLabelArrayName();
    boss_layout->SetVertexLabelVisibility(1);
    boss_layout->GetRenderWindow()->SetSize(600,600);
    boss_layout->GetRenderWindow()->SetWindowName("Boss Candidates");
    boss_layout->SetLayoutStrategyToFast2D();

    auto *handler_layout = vtkGraphLayoutView::New();
    handler_layout->SetRepresentationFromInput(handler_graph);
    //handler_layout->SetVertexLabelArrayName("ID");
    handler_layout->SetVertexLabelVisibility(1);
    handler_layout->GetRenderWindow()->SetSize(600,600);
    handler_layout->GetRenderWindow()->SetWindowName("Handler Candidates");
    handler_layout->SetLayoutStrategyToFast2D();

    auto *middleman_layout = vtkGraphLayoutView::New();
    middleman_layout->SetRepresentationFromInput(middleman_graph);
    //middleman_layout->SetVertexLabelArrayName("ID");
    middleman_layout->SetVertexLabelVisibility(1);
    middleman_layout->GetRenderWindow()->SetSize(600,600);
    middleman_layout->GetRenderWindow()->SetWindowName("Middleman Candidates");
    middleman_layout->SetLayoutStrategyToFast2D();

    auto *view_theme = vtkViewTheme::New()->CreateMellowTheme();
    view_theme->SetSelectedCellColor(1,0,1);
    view_theme->SetSelectedPointColor(1,0,1);
    //TODO: Play with colors

    cities_layout->ApplyViewTheme(view_theme);
    links_layout->ApplyViewTheme(view_theme);
    boss_layout->ApplyViewTheme(view_theme);
    handler_layout->ApplyViewTheme(view_theme);
    middleman_layout->ApplyViewTheme(view_theme);
    view_theme->FastDelete();

    //set up multiple render windows
    cities_layout->GetRenderWindow();
    cities_layout->ResetCamera();
    cities_layout->Render();

    links_layout->GetRenderWindow();
    links_layout->ResetCamera();
    links_layout->Render();

    boss_layout->GetRenderWindow();
    boss_layout->ResetCamera();
    boss_layout->Render();

    handler_layout->GetRenderWindow();
    handler_layout->ResetCamera();
    handler_layout->Render();

    middleman_layout->GetRenderWindow();
    middleman_layout->ResetCamera();
    middleman_layout->Render();

    cities_layout->GetRepresentation(0)->SetAnnotationLink(anno_link);
    links_layout->GetRepresentation(0)->SetAnnotationLink(anno_link);
    boss_layout->GetRepresentation(0)->SetAnnotationLink(anno_link);
    handler_layout->GetRepresentation(0)->SetAnnotationLink(anno_link);
    middleman_layout->GetRepresentation(0)->SetAnnotationLink(anno_link);
    //this is to update view windows with our link?
    auto updater = vtkViewUpdater::New();
    updater->AddAnnotationLink(anno_link);
    updater->AddView(cities_layout);
    updater->AddView(links_layout);
    updater->AddView(boss_layout);
    updater->AddView(handler_layout);
    updater->AddView(middleman_layout);

    //only need to call one to get the party started?
    cities_layout->GetInteractor()->Start();
    //links_layout->GetInteractor()->Start();
    
}