Author: Noah Cribelar
Date Completed: 4/7/19

PROGRAM SUMMARY

This program reads in commands from a pre-formatted text file to construct a genelogical graph of people and families, and is able to read this graph to test connections and relate two individuals together through their families.

INVOKING THE PROGRAM

After unzipping the zip file, the program can be run using make commands.

Use "make" to compile the program from the command line, and after running make, use "make run" to execute the program.

The program will ask the user to choose which file they want to use, if what the user types in does not match either of the file names, then an error message will be given asking the user to provide an appropriate file.

Use enter to progress through the program should it seem execution stops, the program will also prompt the user to press enter after they input the text file.

Use "make clean" to remove any object file after one is finished with executing the program. If one wants to execute after running make clean, simply enter "make" again and use "make run" again to execute.


PROGRAM INPUT

The only input necessary is the selection of the text file and pressing enter to advance after that point. Valid text file names are "myData.txt" and "finkelData.txt". It is also described in the program how to input the files.


PROGRAM OUTPUT

Output will be instructions showing the user how to enter in files, prompts to continue, and outputs describing insertion of individuals and families, inconsistencies in the data, and paths of relation between two people. A sample of outputs when run on both files can be found in output1.txt and output2.txt, which are included in the zip file.


ADDITIONAL NOTES

Originally I had every command as a seperate function, but when I went to run it there were many segmentation faults. After I mulled this over a bit and asked other classmates about it, Jackson Danna told me he had done his program in a similar manner as mine (using arrays of family and people instead of making a matrix) and his ran fine when it was all in the main function. I transferred my functions over to the main function and implemented them there, and while that may have been messy I wasn't exact in the mood to start from scratch on the code since I was already behind on turning it in.

In making my Check "function", I received help from classmate Jackson Danna on implementing checking if an indiviudal was being claimed as a child in the family it pointed to as its parents. He reccomended that I use a bool variable to track if there was a child in the family that pointed back, so I implemented that into my code.

For the Relate command, Jackson Danna and I whiteboarded the process that we would need to take in creating the function for it. I specifically reccomended that we use a list data structure since a queue would not be able to fulfil the requirement for our version of BFS. We additionally used several YouTube videos from HackerRank to assist in understanding and building the BFS process we would need to take. While our implementations were seperate, we had essentially detailed every step of the process for Relate exactly so I would assume they both look similar when coded.

Additionally, we found out we had done the BFS in reverse basically, as when it outputted for us originally it would start with the last number first. Think of the command Relate 3 7, it would start with Individual 7 first then go to 3. To fix this I simply reversed which one the program treated as source and destination, but I would like to solve that in the future to see what I did wrong.
