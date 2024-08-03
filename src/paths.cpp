/**
 * @file paths.cpp
 * @author Griffin Nye
 * @brief CSC402 Dr. Spiegel Spring 2020- Determines all paths and their corresponding 
 *  costs from a user-provided starting vertex to a user-provided destination index.
 * Due Date: 2/19/20
 * Assignment: #1
 */

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

/**Node:
 * @brief A structure that contains a vertex identifier and the cost to travel
 *        to said vertex from a previous vertex
 */
struct Node {
	public:
	
		/**getVal:
		 * @brief Retrieves the value of Node.val
		 * @return val the value stored in Node.val
		 */
		int getVal() const{
			return val;
		}//end getVal
		
		/**getCost:
		 * @brief Retrieves the value of Node.cost
		 * @return cost the value stored in Node.cost
		 */
		int getCost() const{
			return cost;
		}//end getCost
		
		/**setVal:
		 * @brief Sets the identifier for the recipient vertex of a directed edge
		 * @param vertex identifier for the recipient vertex of a directed edge
		 */
		void setVal(int vertex) {
			val = vertex;
		}//end setVal
		
		/**setCost:
		 * @brief Sets the cost to traverse edge directed to Node.val
		 * @param weight the cost/weight to traverse edge directed to Node.val
		 */
		int setCost(int weight) {
			cost = weight;
		}//end setCost
		
	private:
		int val;
		int cost;
};//end Node

//Function Prototypes
/**clearScreen: 
 * @brief Clears the contents of the screen for improved readability.
 */
void clearScreen();

/**openFile:
 * @brief Prompts the user for the filename and attempts to open it, returning an 
 *        error message if needed.
 * @param file used to open the file- INPUT/OUTPUT
 * @return fileOpen true = success, false = failure
 */
bool openFile(ifstream & file);

/**fillAdjList:
 * @brief Fills the adjacency list using the input text file
 * @param file the input stream for the file- INPUT/OUTPUT
 * @param adj the adjacency list- OUTPUT
 */
void fillAdjList(ifstream & file, vector<vector<Node> > & adj);

/**printAdjList:
 * @brief Prints the contents of the adjacency list
 * @param adj the adjacency list- INPUT
 */
void printAdjList(const vector<vector<Node> > & adj);

/**getStartNode:
 * @brief Prompts the user for the starting vertex
 * @param len the length of the adjacency list- INPUT
 * @return start the starting vertex, -1 quits
 */
int getStartNode(int len);

/**getDestNode:
 * @brief Prompts the user for the destination vertex
 * @param len the length of the adjacency list- INPUT
 * @param start the starting vertex- INPUT
 * @return dest the destination vertex
 */
int getDestNode(int len, int start);

/**findEdgeCost:
 * @brief Determines the cost to traverse edge from start to dest
 * @param start the start vertex- INPUT
 * @param dest the destination vertex- INPUT
 * @param adj the adjacency list- INPUT
 * @return adj[start][i].getCost() the cost to traverse edge from start to dest
 *         -1 if vertices not connected
 */
int findEdgeCost(int start, int dest, const vector< vector<Node> > & adj);

/**findPaths:
 * @brief Prepares the data structures for finding all possible paths.
 *        All paths found upon completion.
 * @param start the starting vertex- INPUT
 * @param dest the destination vertex- INPUT
 * @param adj the adjacency list- INPUT
 * @param pathMap map for storing totalCost and succesful paths- OUTPUT
 */
void findPaths(int start, int dest, const vector< vector<Node> > & adj,
							 map<int, vector<string> > & pathMap);
							 
/**recursiveFind:
 * @brief Recursively finds all possible paths from the starting vertex to the 
 *        destination vertex
 * @param start the starting vertex- INPUT
 * @param dest the destination vertex- INPUT
 * @param marked array for marking visited vertices- INPUT/OUTPUT
 * @param path vector for storing current path- INPUT/OUTPUT
 * @param idx index for storing length of current path- INPUT/OUTPUT
 * @param adj the adjacency list- INPUT
 * @param totalCost the totalCost of the current traversed path- INPUT/OUTPUT
 * @param pathMap map for storing successful paths and their total costs- INPUT/OUTPUT
 */
void recursiveFind(int start, int dest, bool marked[], vector<int> path, 
									 int & idx, const vector< vector<Node> > & adj, int totalCost, 
									 map<int, vector<string> > & pathMap);

/**pathToString:
 * @brief Converts path into a string for insertion into pathMap
 * @param path a successful path- INPUT
 * @param idx length of the path- INPUT
 * @return ss.str() string form of the path vector
 */
string pathToString(const vector<int> & path, int idx);

/**savePath:
 * @brief Saves a successful path and its totalCost
 * @param totalCost the totalCost of the path- INPUT
 * @param path successful path string- INPUT
 * @param pathMap map for storing successful paths and their total costs- INPUT/OUTPUT
 */
void savePath(int totalCost, const string path, map<int, vector<string> > & pathMap);

/**printPaths:
 * @brief Prints all successful paths
 * @param pathMap map containing all successful paths and their total costs- INPUT
 */
void printPaths(const map<int, vector<string> > & pathMap);


/**main:
 * @brief Makes function calls to open file, create adjacency list, prompt and 
 *        retrieve start and dest vertices, and find and print all paths until
 *        indicated exit.
 * @return 0 successful -1 failure
 */
int main() {
	ifstream input;                  
	vector<vector<Node> > adjList;		 
	 
	int startVertex;
	int destVertex; 
	
	clearScreen(); //clear the screen
	
	//if opening file failed
	if (openFile(input) == false) {
		return -1; //EXIT_FAILURE
	}//end if
	
	//Populate the adjacency list
	fillAdjList(input, adjList);     
	
	//printAdjList(adjList);

	//Retrieve start vertex
	startVertex = getStartNode( adjList.size() ); 
	
	//Continue until negative input
	while (startVertex >= 0) {
		map<int, vector<string> > pathMap;
		
		//Retrieve destination vertex
		destVertex = getDestNode( adjList.size(), startVertex);
		//Find all paths from start vertex to destination vertex
		findPaths(startVertex, destVertex, adjList, pathMap);
		//Print all successful paths
		printPaths(pathMap);
		//Retrieve start vertex or exit message
		startVertex = getStartNode( adjList.size() );
	}//end while
	
	return 0; //EXIT_SUCCESS
}//end main

//Clears the contents of the screen for improved readability.
void clearScreen() {
	system("clear");
}//end clearScreen

//Prompts the user for the filename and attempts to open it, returning an error message if needed.                                                                                                                                                                   
bool openFile(ifstream & file) {
	bool fileOpen = true;
	string filename;
	
	//Prompt for filename
	cout << "Please enter the name of the file you wish to open: ";
	cin >> filename;
	
	//Open file
  file.open( filename.c_str() );
	
	//If failure, display error message
  if (file.fail()) {
		cout << "There was an error when trying to open the file '" << filename << "'." << endl;
	  cout << "Please make sure the file exists and is placed in the proper directory." << endl;
		fileOpen= false;
	}//end if

  return fileOpen;
}//end openFile


//Fills the adjacency list using the input text file
void fillAdjList(ifstream & file, vector< vector<Node> > & adj) {
	string line;
	
	//Read file line by line
	while (getline(file, line)) {
		vector<Node> inner;
		
		//Check if vertex has at least one neighbor
		if (line.length() >= 5) {
			
			//Traverse through all neighbors on the line
			for (int i = 2; i < line.length(); i+=4) {
				Node n;
				n.setVal(line[i] - '0');
				n.setCost(line[i+2] - '0');
				
				//Insert node into inner vector
				inner.push_back(n);
			}//end for
		}//end if
		
		//Insert vector into adjacency list
		adj.push_back(inner);
	}//end while
	
	file.close();
}//end fillAdjList

//Prints the contents of the adjacency list
void printAdjList(const vector< vector<Node> > & adj) {
	//get number of vertices
	int size = adj.size();
	
	//Traverse through vertices
	for (int i = 0; i < size; i++) {
		
		//Print header
		cout << "Adjacency list of vertex " << i << ": " << endl;
		
		//Traverse through neighbors
		for (int j = 0; j < adj[i].size(); j++) {
			cout << "Vertex: " << adj[i][j].getVal() << endl;
			cout << "Cost: " << adj[i][j].getCost() << endl;
		}//end for
		
	}//end for
}//end printAdjList

//Prompts the user for the starting vertex
int getStartNode(int len) {
	int start;
	bool valid = false;
	
	//Prompt until valid vertex provided
	while (!valid) {
		//Prompt for start vertex
		cout << "Enter start vertex between 0 and " << len - 1 << ". Negative input quits >";
		cin >> start;

		if ((start >= 0) && (start < len)) { //IN RANGE CASE 
			valid = true; 
		} else if (start < 0) { //QUIT CASE
			break;        
		} else { //OUT OF RANGE CASE
			cout << endl; 
			cout << "Vertex must be between 0 and " << len - 1 << "." << endl;
		}//end if
		
	}//end while

	return start;
}//end getStartNode

//Prompts the user for the destination vertex
int getDestNode(int len, int start) {
	int dest;
	bool valid = false;
	
	//Prompt until valid vertex provided
	while (!valid) {
		//Prompt for dest vertex
		cout << "Enter destination vertex between 0 and " << len - 1 << ", but not " << start << ">";
		cin >> dest;
		
		if ((dest >= 0) && (dest < len) && (dest != start)) { //IN RANGE & NOT START CASE
			valid = true;
		} else if (dest == start) { //SAME AS START CASE
			cout << endl;
			cout << "Destination vertex cannot be the same as start vertex(" << start << ")." << endl;
		} else if ((dest < 0) || (dest >= len)) { //OUT OF RANGE CASE
			cout << endl;
			cout << "Vertex must be between 0 and " << len - 1 << "." << endl;
		}//end if
		
	}//end while
	
	return dest;
}//end getDestNode

//Determines the cost to traverse edge from start to dest
int findEdgeCost(int start, int dest, const vector< vector<Node> > & adj) {
		//Traverse start's neighbors
		for (int i = 0; i < adj[start].size(); i++) {
			//Check if start and dest are neighbors
			if (adj[start][i].getVal() == dest) {
				return adj[start][i].getCost(); //NEIGHBORS CASE
			}//end if
		}//end for
		
		return -1;//NOT NEIGHBORS CASE
}//end findCost

//Prepares the data structures for finding all paths. All paths found upon completion
void findPaths(int start, int dest, const vector< vector<Node> > & adj,
							 map<int, vector<string> > & pathMap) {
	bool marked[adj.size()];            //array for marking visited vertices
	vector<int> path( adj.size() );      //vector for storing current traversed path
	int idx = 0;                        //index for storing current path length
	int totalCost = 0;									//counter for total cost of current path
	
	//Mark all vertices as unvisited
	for (int i = 0; i < adj.size(); i++) {
		marked[i] = false;
	}//end for
	
	//Begin recursive pathfinding
	recursiveFind(start, dest, marked, path, idx, adj, totalCost, pathMap);
}//end findPaths

//Recursively finds all possible paths from the starting vertex to the destination vertex
void recursiveFind(int start, int dest, bool marked[], vector<int>  path, int & idx, 
									 const vector< vector<Node> > & adj, int totalCost, 
									 map<int, vector<string> > & pathMap) {
										 
	marked[start] = true; //mark vertex as visited
	path[idx] = start;    //insert vertex into current path
	idx++;								//increase path length
	
	//Check if reached destination
	if (start == dest) {
		savePath(totalCost, pathToString(path, idx), pathMap); //Save path in pathMap
	} else {
		//Traverse start's neighbors 
		for (int i = 0; i < adj[start].size(); i++) {
			int curr = adj[start][i].getVal(); 
			
			//Check if vertex is unvisited
			if (!marked[curr]) {
				int currCost = findEdgeCost(start, curr, adj); //calculate cost
				totalCost += currCost; 												 //increase total cost
				//Traverse neighbor
				recursiveFind(curr, dest, marked, path, idx, adj, totalCost, pathMap);
				totalCost -= currCost;												 //decrease cost
			}//end if
		}//end for
	}//end if
	
	idx--; //decrease path length (by doing so, same as remove last vertex)
	marked[start] = false; //unvisit node
}//end recursiveFind

//Converts path into a string for insertion into pathMap
string pathToString(const vector<int> & path, int idx) {
	stringstream ss;
	
	//Read each element in the path
	for (int i = 0; i < idx; i++) {
		ss << path[i];      //add element into string
		
		if (i < idx - 1) {  //if not last element
			ss << " ";				//print a space
		}//end if
		
	}//end for
	
	return ss.str();
}//end pathToString

//Saves a successful path and its totalCost
void savePath(int totalCost, const string path, map<int, vector<string> > & pathMap) {
	//Search map for key totalCost, point iterator at result
	map<int, vector<string> >::iterator itr = pathMap.find(totalCost); //map iterator 
	
	//If totalCost already exists as a key
	if ( itr != pathMap.end() ) {
		//Insert the path into the map at key totalCost
		itr->second.push_back(path);
		
	} else { //totalCost does not exist as a key
		vector<string> temp;                         //create vector of strings
		temp.push_back(path);												 //insert path into vector
		pathMap.insert(make_pair(totalCost, temp)); //insert totalCost and vector into map
	}//end if
	
}//end savePath

//Prints all successful paths
void printPaths(const map<int, vector<string> > & pathMap) {
	//map iterator
	map<int, vector<string> >::const_iterator itr;
	
	//Check pathMap has at least one element
	if (!pathMap.empty()) {
		//Traverse each pair in the map
		for (itr = pathMap.begin(); itr != pathMap.end(); itr++) {
			//Print cost header
			cout << "Paths with cost " << itr->first << ":" << endl;
			
			for (int i = 0; i < itr->second.size(); i++) {
				//Print all paths with above cost
				cout << itr->second[i] << endl;
			}//end for
		}//end for
		
		cout << endl;	
	} else { //pathMap is empty 
		cout << "No paths exist for these vertices." << endl;
		cout << endl;
	}//end if
}//end printPaths