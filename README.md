# flittergraph

### Problem Scenario:
There are problems at the U.S. Embassy in Flovania, a small land-locked country situated between the nations of Trium to the north and east, Posana to the west, and the Republic of Transak to the southwest.  
The network security team recently found irregularities while reviewing Embassy network traffic logs.  Finding no security issues that could explain the anomalies, they notified the Embassy Counterintelligence Officer.  Upon further investigation, the CI officer identified certain espionage red flags.  You have been requested to help him with the investigation.  
The 60 Embassy employees have 24x7 access to the facility, with access to the classified information room.   
Attached you'll find the following datasets:
1.  Badge and Computer Network Traffic
2.  Social Network and Geospatial
3.  Video 
These datasets may help identify possible suspects, accomplices and evidence that could help the CI Office with their investigation.
For each of these datasets (i.e. for each of the mini challenge) you are asked to answer specific questions that can be deduced strictly from the data provided. You will also be asked to provide a process description highlighting your visualizations and interactions used to arrive at your conclusions. Please see the task description page on the Challenge website.  
For the Grand Challenge, you are asked to integrate the analysis results of the 3 Mini Challenges to provide insight to the overall situation and to prepare a debrief document describing the situation, providing the who, what, when, where and why according to your analysis.

#### Social Net and Geo Problem Definition:
Reference: IEEE VAST mini challenge 2009
		
We believe an employee communicated with his/her handler(s) (a contact from the criminal network) through Flitter, however we do not know the Flitter name of the handler nor of the espionage organization. We believe that the associated network may take one of two forms of social structures:

1. The employee has about 40 Flitter contacts. Three of these contacts are his handlers, people in the criminal organization assigned to obtain his cooperation. Each of the handlers probably has between 30 to 40 Flitter contacts and share a common middle man in the organization, who we have code-named Boris. Boris maintains contact with the handlers, but does not allow them to communicate among themselves using Flitter. Boris communicates with one or two others in the organization and no one else. One of these contacts is his likely boss, who we've code­named Fearless Leader. Fearless Leader probably has a broad Flitter network (well over 100 links), including international contacts.

2. The employee has about 40 Flitter contacts. Three of these contacts are his handlers, people in the organization assigned to obtain his cooperation. Each of the handlers likely has between 30 to 40 Flitter contacts, and each probably has his or her own middle man in the organization, who we've code-named Boris, Morris and Horace. It is probable the middle men will not allow the handlers to communicate among themselves using Flitter. Each of the middle men probably communicate with one or two others in the organization, and no one else. One of the contacts for all of the middle men is the head of the organization, Fearless Leader. Fearless Leader has a broad Flitter network (well over 100 links) including international contacts.

In addition to the above, the two social structures have geospatial implications. While a target and handler may be in a large city, a middleman might be in nearby smaller locations. A leadership role, such as the one of Fearless Leader, would likely require a presence in a larger city.


### Notes on files in data folder:
* Treating files as though they are .csv as they are tab (`\t`) delimited values
* Flitter Names associates name with numeric ID
* People Cities associates numeric ID with City
* Links_Table associates numeric IDs with whom they have contact with (by reference of numeric ID)

### Project Notes:
* A key component to this challenge is parsing the input data (talked this through \
with Kijowski).  This can be done in c++ OR in bash.  I'm going to try to improve \
my skills parsing csv is bash before exploring C++ libraries to assist
  * `$ cat Links_Table.txt | awk '{print $1}' | sort | uniq -c`
  * Truncated Links_Table.txt by removing IDs not associated with the other files
  * 

* vtkTableToGraph
* visualize directed graph?
* Selected Graph IDs?

### Resources:
* English overview of what functionality vtkDelimitedTextReader has
  * https://vtk.org/pipermail/vtk-developers/2017-July/035282.html
  * vtkDelimitedTextReader example (using old to show correct input file sample):
  * https://vtk.org/Wiki/VTK/Examples/Cxx/InfoVis/DelimitedTextReader#Please_try_the_new_VTKExamples_website
  * Python example - super duper useful:
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/delimited_text_reader2.py
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/authors.csv
* vtk Table To Graph - reference to link friends?
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/csv_to_graph.py
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/nodes.csv
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/edges.csv
* TableToTree - GroupLeafVertices
  * https://github.com/Kitware/VTK/blob/master/Infovis/Layout/Testing/Cxx/TestGroupLeafVertices.cxx
* vtkTable - how to manipulate tables
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/tables_adv.py
* vtkStringToCategory - this link works, Google search didn't - Look at Description for use?
  * https://vtk.org/doc/nightly/html/classvtkStringToCategory.html
* Selection Domain - Python - great example of what I think I'm trying to do
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/selection_domain.py
* Extract selected graph - maybe do something like this to pull Flitter IDs?
  * https://github.com/Kitware/VTK/blob/master/Examples/Infovis/Python/selection.py
* How to get how many vertices:
  * https://vtk.org/gitweb?p=VTK.git;a=blob;f=Infovis/Core/Testing/Cxx/TestTableToGraph.cxx
