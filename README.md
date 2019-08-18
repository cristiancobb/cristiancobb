# Completed Projects that exemplifies my coding abilities

## Software Design and Engineering
### The code below is snip for Java class code of a game I created
```
//reset timer
                missileStartTime = System.nanoTime();
            }
            //loop through every missile and check collision and remove
            for(int i = 0; i<missiles.size();i++)
            {
                //update missile
                missiles.get(i).update();

                if(collision(missiles.get(i),player))
                {
                    missiles.remove(i);
                    player.setPlaying(false);
                    break;
                }
```
### 	The artifacts I selected are snips of the code I created to showcase my proficiency in coding. The artifact below shows my ability to make code. The code highlights that I am about to code software such as games. The code is a couple lines of code that shows the use of an animation. This was created on my own time when I decided to make a 2D Android game. The artifact showcases my coding skills and my abilities in software development. The artifact was improved because it has less errors, a better format, and has ample descriptions. I did meet the course objective to enhance the code. I do need to go back and fix the emulator on the game. The purpose of enhancing and modifying the artifact is to improve its function and contexts. I learned to use different methods and approach with specific problems. Some of the challenges I faced it fixing the function of it. The objective of the code was to create a missile animation and remove the missile when it is done serving its purpose. I do plan on publishing my game on Google Play.

## Algorithms and Data Structures
```
#include <isostream>
using namespace std;

int main() {
  int* numItemsPtr = 0;
  int numItems = 99:
  
//Assign the address of the numItems to numItemsPtr

    numItemPtr = &numItems;
    
    //print the output
    
cout << "Items: " << *numItemsPtr << endl;

    system("pause");
    
   return 0;
}    
```
### I picked the code above because it highlights my ability to use pointers effectively. The problem I need to solve is assign numItems' address to numItemsPtr, then print the shown text followed by the value to which numItemsPtr points. End with newline. Items: 99. It was created in another college class where I learned extensively on data structures. I did meet the course objective and I did enhance the code to work. The purpose of enhancing and modifying this code is to make sure the pointers work and effective. I did add the objective of the pointer, so the reader understands what’s going on. The screenshot below shows my work.
## Datebase 
```
../startMongod.sh
```
### After I have started the process, we will now import the database that we will be using for the document found in the files enron.js. As shown in the screenshot below.
```
cd datasets
datasets$ mongoimport --db emails --collection enron ./enron.json
```
### Also, we need to run mongo and use emails to begin to use the database. As shown in the screenshot below. 
```
datasets$ mongo
connection to: test
> use emails 
switch to db emails
```
### Now we have imported the mongo import toll for using the database emails and the collection enron from the file enron.json. We now need to find the document and display it from using the db.enron.findOne() function to find the sender and the email  rosalee_fleming@enron.com.  From using the above query we should have the following function db.enron.findOne({"sender" : "rosalee.fleming@enron.com"}).  After running this command we will now see the results and the sender, and the email document will appear. As shown in the screenshot below. 
```
> db.enron.findOne({"sender" : "rosalee.fleming@enron.com"})
{
  "id" : ObjectId("52sf48b5d55148fa0c199645"),
  "sender" : "rosalee.fleming@enron.com:,
  "recipients" : [
            "rob.bradley@enron.com"
  ],
  "cc" : [ ],
  
```
### The list of database codes below where chosen because it highlights the steps, I took to get the results. I picked this artifact because it is extensive, and it shows several correct steps of how I came up with the solution. I did this in a college class where I learned about data base. I did meet the course objective my showing an artifact that highlights my database skills. I did go back and add descriptions on the steps to narrative the process. For the first step we will be importing the database emails document that is found with the file eron.js for the collection enron. From doing this we will be using the mongo import tool was used in previous assignments. The mongo import tool that we will be using is mongoimport --db emails --collection enron ./enron.json. First before using the mongo import tool we will be starting the mongo shell like we been doing in our previous assignments as shown in the screenshot below. 
