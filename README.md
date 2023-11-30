# seller-website-simulate
![Static Badge](https://img.shields.io/badge/c%2Fc%2B%2B-100%25-green)

## Overview

A project use __Binary Search Tree__ and __Heap__ data structure to simulate the sellers and buyers' interaction.

Use __Binary Search Tree__  to store the items seller wanted to sell, and every item (every tree node) has its own __Min Heap__ point to them in order to store the seller's name and price.

Note: An item may have multiple seller, and we use the min heap to store those values.

## Code Structure

The code consists of three main data structures:

1. **SELLER_TYPE**: A structure representing a seller, containing a seller ID (`SID`) and the price of the item (`PRICE`).

2. **SELLER_HEAP**: A min heap structure storing sellers' information. It includes an array of `SELLER_TYPE` elements, the current size, and the maximum capacity of the heap.

3. **ITEM_TYPE**: A structure representing an item in the BST. It contains the item name (`ITEM_NAME`), a pointer to a min heap of sellers (`heap`), and pointers to left and right child nodes.

The code includes functions to perform various operations on these structures, such as initializing a min heap, inserting elements into the heap, getting the minimum element, and deleting the minimum element.

## Operations

The simulation supports the following operations:

1. **Insert**: Add a new item to the BST with its corresponding seller information in the min heap.
2. **Search**: Retrieve information about an item, including its name and the sellers with their prices.
3. **Buy**: Purchase an item, displaying the item name, seller ID, and price. The corresponding seller is removed from the min heap, and if the heap becomes empty, the item is removed from the BST.
4. **Sort**: Display the items in the BST in sorted order.
5. **Report**: Generate a report with statistics about the simulation, including the number of insertions, searches, and purchases, the number of nodes in the BST, and the height of the BST.


## Input

The program reads input from a file specified by the user. Each line in the file contains a command, and the format of each command shawn as follows.
```text
insert CD Mary 280
insert TV John 20000
buy Book
insert Book Jacky08 220
search CD
insert Book Jacky01 200
insert Book GiGi 180
search Book
buy Book
buy Book
search Notebook
sort
buy CD
sort
report
```

## Output

The simulation produces output in the form of three text files:

- **SearchTable.txt**: Information about searched items and their sellers.
```text
CD
Mary 280
----------------------------
Book
GiGi 180
Jacky08 220
Jacky01 200
----------------------------
Notebook doesn’t exist!
----------------------------
```
- **BuyTable.txt**: Information about purchased items and their sellers.
```text
Book doesn’t exist!
Book GiGi 180
Book Jacky01 200
CD Mary 280
```
- **SortTable.txt**: Items sorted in ascending order.
```text
Book
CD
TV
----------------------------
Book
TV
----------------------------
```
- **LogTable.txt**: Statistics and reports about the simulation.
```text
insert 5
search 3 1
buy 4 1
node_num 2
height 2
```

## Conclusion

The Seller-Buyer Interaction Simulation demonstrates the use of __BST__ and __Min Heap__ data structures to model the interaction between sellers and buyers. Users can customize scenarios by providing input files with specific commands, and the program provides detailed information and reports based on these interactions.





