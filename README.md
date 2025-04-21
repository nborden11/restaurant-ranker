Heapin’ Helpings
COP3530 Project 3b – Spring 2025
Team Members:
Nicholas Santarsiero (@santarsiero)
Kai Steckley (@KaiS987)
Nicholas Borden (@nborden11)


Project Overview
Heapin’ Helpings is a C++ program that analyzes restaurant data from the Yelp Academic Dataset. Users can filter restaurants by state and review count, and compare two sorting algorithms, Merge Sort and Heap Sort, on runtime performance. The program outputs the top 10 restaurants by rating and displays the time taken by each algorithm.
Dataset Used
File: yelp_academic_dataset_business.json
 Source: https://www.yelp.com/dataset
We filter only businesses with the word “restaurant” in their category.
Features
Menu-based CLI to select state, review range, and sorting algorithm

Filters restaurants by review count and state

Sorts by rating, with line length used as a tie-breaker

Compares Merge Sort vs Heap Sort using runtime (in milliseconds)

Displays top 10 results per selected sort


How to Run
Clone this repository
 git clone https://github.com/nborden11/restaurant-ranker.git
 cd restaurant-ranker


Open the project in CLion or another C++ IDE.


Build and run the program.
 Make sure the file yelp_academic_dataset_business.json is placed in the correct path.
 (You may need to adjust the file path in main.cpp depending on your system.)


Follow the CLI prompts:

Enter a state (e.g., FL, CA, NY)

Choose a review-count range (0–49, 50–99, or 100+)

Choose a sorting algorithm: Merge, Heap, or Compare Both

Tools & Technologies
Language: C++


IDE: CLion

Libraries:
iostream
fstream
vector
string
chrono
algorithm


Dataset: Yelp Academic Dataset


Demo Video
(https://youtu.be/ZaNrysMWr6c)
Contributors
Name: Nicholas Santarsiero
 GitHub: @santarsiero
 Role: JSON parsing and filtering logic, contributed to final integration and documentation
Name: Kai Steckley
 GitHub: @KaiS987
 Role: Implemented Heap Sort, helped with CLI design and testing
Name: Nicholas Borden
 GitHub: @nborden11
 Role: Implemented Merge Sort, handled performance timing, integrated filtering logic
