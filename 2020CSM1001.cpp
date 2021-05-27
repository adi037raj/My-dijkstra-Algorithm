/*


    NAME - AADITYA RAJ BARNWAL

    ROLL NO. - 2020CSM1001


*/


#include<bits/stdc++.h>
using namespace std;
#define infinity INT_MAX    // the maximum value so that it is treated like infinity
typedef long long ll;      // it is used many times in program so "ll" means long long
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;   // used in codes

#define N 65915   // maximum number of Nodes (Given in the Question)
vi path[N];                              //To keep track of path
unordered_map<int,ll> key_index_pair;   // for storing the key and value, where key is the NodeID and value is its index of the graph vector
unordered_map<int,ll> index_key_pair;   // This is just the opposite of the above where key is index of graph vector and value is NodeID
vi distance_array(N+1,infinity);        // Its a 1D array which is going to store the Distance(cost), it is initialize to infinity


vector<pi> graph[N+1];                  // Its the graph -> like an adjacancy list and it store the list that which node is connected to which node and by what weight,thats why it is a pair type list

void fetch_nodes_from_file()           // Function Used to Fetch the Nodes from the file Nodes.txt
{
    fstream file;
    string filename="Nodes.txt";
    file.open(filename,ios::in);         // opening the file in read mode
    string word;
    if(!file)
    {
      cout<<"The Nodes.txt file is not found or some error\n";  // make sure that you spell the right file
      exit(0);
      return ;

    }

    int i=1;                    // a variable to keep track of index
    while(file>>word)           // reading line by line
        {
            ll t=stoll(word);       // converting string to long long
            key_index_pair[t]=i;    // storing in key_index_pair(its a hashmap)
            index_key_pair[i]=t;    // storing in index_key_pair(its also a hashmap)
            i++;


        }
        file.close();          // closing the file



}
void fetch_edge_from_file()        // function to fetch the edges from the file
{
    fstream file;
    string filename="Edges.txt";
    file.open(filename,ios::in);   //opening in read mode

    string word;
    if(!file){
            cout<<"Edges.txt file is not found or some other error\n";      // make sure that you spell the right file
          exit(0);
          return ;
    }
    vector <string> tokens;    // variable to store the tokens separated by comma

     while(file>>word)  // reading line by line

     {


      stringstream check(word);
      string intermediate;
    while(getline(check, intermediate, ','))
    {
        tokens.push_back(intermediate);   // extracting each word separated by comma
    }

        ll head=stoll(tokens[0]);                    // the head is the head node
        ll tail=stoll(tokens[1]);                   // the tail node
        int weight=stoll(tokens[2]);                // the weight

        int head_index=key_index_pair[head];        // using the key_index_pair to find out index
        int tail_index=key_index_pair[tail];            // same as above
        graph[head_index].push_back({tail_index,weight});    // graph is list of nodes containing tail node,weight pair
        graph[tail_index].push_back({head_index,weight});
        tokens.clear();                                       // clearing so that it deletes its prev history

     }

   file.close();                                                // closing file

}

int main(){                                                                  // main start
fetch_nodes_from_file();                                                     // fetching the nodes from the file

fetch_edge_from_file();                                                      // fetching the edges from the file

ll source,dest;                                                              // variable to store the current source and destination enter by user


cout<<"Enter your Source Node "<<endl;
cin>>source;
cout<<"enter your destination "<<endl;
cin>>dest;

priority_queue<pi,vector<pi>,greater<pi>> pq;                          //its a priority queue (min heap) contains pair of elements first is distance and second is NodeId, the key is weight that means it is sorted in weights , lower weight is on top of the heap

if(key_index_pair.find(source) ==key_index_pair.end() || key_index_pair.find(dest)==key_index_pair.end())  // Condition checker
{
    cout<<"Invalid Combination of Source and Destination , Please check \n";
    return 0;

}

int t=key_index_pair[source];    // extracting the index of source node
pq.push({0,t});                    // pushing the 0 distance of source to source

distance_array[t]=0;
path[t].push_back(t);              // this is used for path tracking
while(!pq.empty())               // while it is non empty
{
    int curr=pq.top().second;     // it is node with minimum distance from source at that instant
    int curr_d=pq.top().first;     // this is  distance from source of that node
     pq.pop();

    for(auto edge:graph[curr])         // visiting every edge
    {
        if(curr_d+edge.second<distance_array[edge.first])    // Relaxing an edge
        {
            path[edge.first]=path[curr];       // to keep track of node path
            path[edge.first].push_back(edge.first);  // same
            distance_array[edge.first]=curr_d+edge.second;   // updating distance array
            pq.push({distance_array[edge.first],edge.first});   // pushing it again in min heap
        }
    }



}


int d=key_index_pair[dest];     // calculating the index of that Node via Hashmap

if(distance_array[d]==infinity)   // This means that there is no path from source to destination but both nodes are present in the garph
cout<<"Distance is unreachable";
else
    {

        cout<<"The Cost of Path Length is "<<distance_array[d]<<endl;    // distance from source

        cout<<"The Path is "<<endl;
    for(int i=0;i<path[d].size();i++)
       i!=path[d].size()-1? cout<<index_key_pair[path[d][i]]<<"->":cout<<index_key_pair[path[d][i]];         // using opposite of key_index_pair hashmap,as explained above

    }


return 0;
}



/*


 Time Complexity: The time complexity of the above code/algorithm looks O(V^2) as there are two nested while loops. If we take a closer look, we can observe that the statements in inner loop are executed O(V+E) times (similar to BFS).
 The inner loop has decreaseKey() operation which takes O(LogV) time. So overall time complexity is O(E+V)*O(LogV) which is O((E+V)*LogV) = O(E LogV)

*/
