#This script is intended to clean data on the hunt for the cyber threat Flitter Network
# The targets we want to look into should have upwards of 30 contacts
import csv
#Give option to enter value for threshold
threshold = raw_input("Enter threshold value for friend connections (default is 15): ")
threshold = threshold or '15'
#print(threshold)

#Links Table will help define how many important nodes we have
# aka. people with more than the threshold of connections
#read in Links_Table
with open('Links_Table.txt', 'r') as csvfile:
    readCSV = csv.reader(csvfile, delimiter='\t')
    for row in readCSV:
        print(row)
        print(row[0],row[1])
#count instances from COL 2 to COL 1 (other way around gets the wrong friendship model)

#keep list of users to be deleted

#remove rows with unimportant IDS from People_Cities and Flitter_Names

