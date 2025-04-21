//Restaurant‑Ranker
//COP3530 Project 3b
//Team: Nicholas Santarsiero, Kai Steckley, Nicholas Borden

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <chrono>
#include <algorithm>

using namespace std;

//Nick Santarsiero – JSON parsing and dataset filtering

//parses the string to get the correct parts of the string
string parseString(string key, string line){
    string pattern = "\"" + key + "\":\"";
    size_t pos = line.find(pattern);
    if(pos == string::npos){
        return "";
    }


    pos += pattern.length();
    size_t end = line.find('"', pos);
    return line.substr(pos, end - pos);
}




//gets the numbers from the string
string parseNumber(string key, string line){
    string pattern = "\"" + key + "\":";
    size_t pos = line.find(pattern);
    if (pos == string::npos){
        return "";
    }


    pos += pattern.length();
    while (isspace(line[pos])){
        ++pos;
    }


    size_t end = pos;
    while(end < line.size() && (isdigit(line[end]) || line[end] == '.' || line[end] == '-')){
        ++end;
    }


    return line.substr(pos, end - pos);
}




//struct to parse data and store aspects of a restaurant
struct Restaurant{
    //variables to store data
    string business_id;
    string name;
    string city;
    string state;
    int review_count;
    double stars;
    int line_length;


    //constructor to assign data
    Restaurant(string line){
        line_length = (int)line.length();
        business_id = parseString("business_id", line);
        name = parseString("name", line);
        city = parseString("city", line);
        state = parseString("state", line);
        review_count = stoi(parseNumber("review_count", line));
        stars = stod(parseNumber("stars", line));
    }
};




//compares the number of characteristics of a restaurents (length of inputted string) to break ties
bool better(Restaurant& a, Restaurant& b){
    if (a.stars != b.stars){
        return a.stars > b.stars;
    }


    return a.line_length < b.line_length;
}


//Nicholas Borden – Merge Sort with runtime

//goes through both halves of vector and merges them in sorted order
void mergeVec(vector<Restaurant>& restaurants, int left, int mid, int right)
{
    //splits vector into left and right halves
    vector<Restaurant> leftVec(restaurants.begin() + left, restaurants.begin() + mid + 1);
    vector<Restaurant> rightVec(restaurants.begin() + mid + 1, restaurants.begin() + right + 1);

    int i = 0;
    int j = 0;
    int k = left;

    //compares values from both halves and places them into main vector
    while (i < (int)leftVec.size() && j < (int)rightVec.size())
    {
        if (better(leftVec[i], rightVec[j]))
        {
            restaurants[k] = leftVec[i];
            i++;
        }
        else
        {
            restaurants[k] = rightVec[j];
            j++;
        }
        k++;
    }

    //adds any remaining values from left half
    while (i < (int)leftVec.size())
    {
        restaurants[k] = leftVec[i];
        i++;
        k++;
    }

    //adds any remaining values from right half
    while (j < (int)rightVec.size())
    {
        restaurants[k] = rightVec[j];
        j++;
        k++;
    }
}

//splits vector into halves and recursively calls merge until sorted
void mergeSortRec(vector<Restaurant>& restaurants, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSortRec(restaurants, left, mid);
        mergeSortRec(restaurants, mid + 1, right);
        mergeVec(restaurants, left, mid, right);
    }
}

//checks size of vector and calls recursive merge sort function
void mergeSort(vector<Restaurant>& restaurants)
{
    if (restaurants.size() > 1)
    {
        mergeSortRec(restaurants, 0, restaurants.size() - 1);
    }
}

//calculates runtime or merge sort and returns result in ms
double timeMerge(vector<Restaurant> restaurants)
{
    auto start = chrono::high_resolution_clock::now();
    mergeSort(restaurants);
    auto end = chrono::high_resolution_clock::now();

    return chrono::duration<double, milli>(end - start).count();
}

//Kai Steckley - Heap Sort with runtime

void heapify(vector<Restaurant>& restaurants, int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if (left < n && better(restaurants[left], restaurants[largest])){
        largest = left;	// set largest to left
    }


    if (right < n && better(restaurants[right], restaurants[largest])){
        largest = right;	// Set largest to right
    }


    if (largest != i){
        swap(restaurants[i], restaurants[largest]);	// Swap their positions
        heapify(restaurants, n, largest);
    }
}


void heapSort(vector<Restaurant>& restaurants){	// takes in restaurants vector
    int n = restaurants.size();		// Size of restaurants vector


    for (int i = n / 2 - 1; i >= 0; i--){	// first half
        heapify(restaurants, n, i);
    }


    for (int i = n - 1; i > 0; i--){
        swap(restaurants[0], restaurants[i]);
        heapify(restaurants, i, 0);
    }


    reverse(restaurants.begin(), restaurants.end()); // Reverse the order from ascending to descending.
}


double timeHeap(vector<Restaurant> restaurants){		// This will return the runtime.
    auto start = chrono::high_resolution_clock::now();
    heapSort(restaurants);	// Call sorting algorithm
    auto end = chrono::high_resolution_clock::now();


    return chrono::duration<double, milli>(end - start).count();	// Runtime will be in milliseconds
}


/*─────────────── Main – runs the program ───────────────*/

int main(){
    //Nicholas Santarsiero

    //variables for user input
    string state;
    cout << "State (e.g., FL): ";
    cin >> state;

    cout << "Review-count range  1) 0–49  2) 50–99  3) 100+: ";
    int range;
    cin >> range;

    int minReviews = 0;
    int maxReviews = numeric_limits<int>::max();


    if(range == 1){
        maxReviews = 49;
    }
    else if(range == 2){
        minReviews = 50;
        maxReviews = 99;
    }
    else if (range == 3){
        minReviews = 100;
    }
    else{
        cout << "Invalid.\n";
        return 1;
    }


    //input to see what part to test
    cout << "Choose algorithm  1) Merge  2) Heap  3) Compare both: ";
    int alg;
    cin >> alg;

    if (alg < 1 || alg > 3){
        cout << "Invalid.\n";
        return 1;
    }

    //datafile
    ifstream file("/Users/nicksantarsiero/Desktop/yelp_academic_dataset_business.json");




    if(!file){
        cerr << "File not found.\n";
        return 1;
    }


    //vector to store different restuarents
    vector<Restaurant> data;
    string line;


    //checks if a resturant is correct based on the user inputs, then enters it into the vector if correct
    while(getline(file, line)){
        if (line.find("restaurant") == string::npos && line.find("Restaurant") == string::npos){
            continue;
        }

        if(line.find("\"state\":\"" + state + "\"") == string::npos){
            continue;
        }

        int rc = stoi(parseNumber("review_count", line));
        if (rc < minReviews || rc > maxReviews){
            continue;
        }

        data.push_back(Restaurant(line));
    }

    file.close();

    //Nicholas Borden

    //prints how many restaurants matched the filters
    cout << "\nMatched " << data.size() << " restaurants.\n\n";

    if (alg == 1 || alg == 3)
    {
        vector<Restaurant> copy = data;

        //run merge sort and track time
        double ms = timeMerge(copy);

        cout << "Merge Sort runtime: " << ms << " ms\n";
        cout << "\nTop 10 Restaurants (Merge):\n";

        for (int i = 0; i < copy.size() && i < 10; i++)
        {
            cout << i + 1 << ". " << copy[i].name
                 << " | " << copy[i].stars << "* | "
                 << copy[i].review_count << " reviews\n";
        }

        cout << endl;
    }

    if (alg == 2 || alg == 3)
    {
        vector<Restaurant> copy = data;

        //run heap sort and track time
        double ms = timeHeap(copy);

        cout << "Heap Sort runtime: " << ms << " ms\n";
        cout << "\nTop 10 Restaurants (Heap):\n";

        for (int i = 0; i < copy.size() && i < 10; i++)
        {
            cout << i + 1 << ". " << copy[i].name
                 << " | " << copy[i].stars << "* | "
                 << copy[i].review_count << " reviews\n";
        }

        cout << endl;
    }

    return 0;
}


