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

A. The employee has about 40 Flitter contacts. Three of these contacts are his handlers, people in the criminal organization assigned to obtain his cooperation. Each of the handlers probably has between 30 to 40 Flitter contacts and share a common middle man in the organization, who we have code-named Boris. Boris maintains contact with the handlers, but does not allow them to communicate among themselves using Flitter. Boris communicates with one or two others in the organization and no one else. One of these contacts is his likely boss, who we've code­named Fearless Leader. Fearless Leader probably has a broad Flitter network (well over 100 links), including international contacts.

B. The employee has about 40 Flitter contacts. Three of these contacts are his handlers, people in the organization assigned to obtain his cooperation. Each of the handlers likely has between 30 to 40 Flitter contacts, and each probably has his or her own middle man in the organization, who we've code-named Boris, Morris and Horace. It is probable the middle men will not allow the handlers to communicate among themselves using Flitter. Each of the middle men probably communicate with one or two others in the organization, and no one else. One of the contacts for all of the middle men is the head of the organization, Fearless Leader. Fearless Leader has a broad Flitter network (well over 100 links) including international contacts.

In addition to the above, the two social structures have geospatial implications. While a target and handler may be in a large city, a middleman might be in nearby smaller locations. A leadership role, such as the one of Fearless Leader, would likely require a presence in a larger city.


### Notes on files in data folder:
* Treating files as though they are .csv as they are comma delimited values
* Flitter Names associates name with numeric ID
* People Cities associates numeric ID with City
* Links_Table associates numeric IDs with whom they have contact with (by reference of numeric ID)

### Visualization Goals:
* vtkVariant
* vtkTableToGraph

### Resources:
* English overview of what functionality vtkDelimitedTextReader has
  * https://vtk.org/pipermail/vtk-developers/2017-July/035282.html