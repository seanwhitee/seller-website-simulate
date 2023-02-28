#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// struct data type define
typedef struct SELLER_TYPE
{
    char SID[30];
    int PRICE;
} SELLER_TYPE;

// heap start
typedef struct SELLER_HEAP
{
    SELLER_TYPE *arr;
    // Current Size of the Heap
    int size;
    // Maximum capacity of the heap
    int capacity;
} SELLER_HEAP;

typedef struct ITEM_TYPE
{
    char ITEM_NAME[30];
    SELLER_HEAP *heap;
    struct ITEM_TYPE *LCHILD;
    struct ITEM_TYPE *RCHILD;
} ITEM_TYPE;
int parent(int i)
{
    // Get the index of the parent
    return (i - 1) / 2;
}

int left_child(int i)
{
    return (2 * i + 1);
}

int right_child(int i)
{
    return (2 * i + 2);
}

SELLER_HEAP *init_minheap(int capacity)
{
    SELLER_HEAP *minheap = (SELLER_HEAP *)calloc(1, sizeof(SELLER_HEAP));
    minheap->arr = (SELLER_TYPE *)calloc(capacity, sizeof(SELLER_TYPE));
    minheap->capacity = capacity;
    minheap->size = 0;
    return minheap;
}

// Get the minimum element in the min heap.
SELLER_TYPE *get_min(SELLER_HEAP *heap)
{
    // Return the root node element,
    // since that's the minimum
    return &heap->arr[0];
}

SELLER_HEAP *insert_minheap(SELLER_HEAP *heap, SELLER_TYPE *element)
{
    // Inserts an element to the min heap
    // We first add it to the bottom (last level)
    // of the tree, and keep swapping with it's parent
    // if it is lesser than it. We keep doing that until
    // we reach the root node. So, we will have inserted the
    // element in it's proper position to preserve the min heap property
    if (heap->size == heap->capacity)
    {
        fprintf(stderr, "Cannot insert %d. Heap is already full!\n", element->PRICE);
        return heap;
    }
    // We can add it. Increase the size and add it to the end
    heap->size++;

    strcpy(heap->arr[(heap->size) - 1].SID, element->SID);

    heap->arr[(heap->size) - 1].PRICE = element->PRICE;
    // Keep swapping until we reach the root
    int curr = (heap->size) - 1;
    // As long as you aren't in the root node, and while the
    // parent of the last element is greater than it
    while (curr > 0 && heap->arr[parent(curr)].PRICE > heap->arr[curr].PRICE)
    {
        // Swap
        // swap price
        int temp = heap->arr[parent(curr)].PRICE;
        heap->arr[parent(curr)].PRICE = heap->arr[curr].PRICE;
        heap->arr[curr].PRICE = temp;
        // swap id
        char temp1[30];
        strcpy(temp1, heap->arr[parent(curr)].SID);
        strcpy(heap->arr[parent(curr)].SID, heap->arr[curr].SID);
        strcpy(heap->arr[curr].SID, temp1);

        // Update the current index of element
        curr = parent(curr);
    }
    return heap;
}

SELLER_HEAP *heapify(SELLER_HEAP *heap, int index)
{
    // Rearranges the heap as to maintain
    // the min-heap property
    if (heap->size <= 1)
        return heap;

    int left = left_child(index);
    int right = right_child(index);

    // Variable to get the smallest element of the subtree
    // of an element an index
    int smallest = index;

    // If the left child is smaller than this element, it is
    // the smallest
    if (left < heap->size && heap->arr[left].PRICE < heap->arr[index].PRICE)
        smallest = left;

    // Similarly for the right, but we are updating the smallest element
    // so that it will definitely give the least element of the subtree
    if (right < heap->size && heap->arr[right].PRICE < heap->arr[smallest].PRICE)
        smallest = right;

    // Now if the current element is not the smallest,
    // swap with the current element. The min heap property
    // is now satisfied for this subtree. We now need to
    // recursively keep doing this until we reach the root node,
    // the point at which there will be no change!
    if (smallest != index)
    {
        // swap price
        int temp = heap->arr[index].PRICE;
        heap->arr[index].PRICE = heap->arr[smallest].PRICE;
        heap->arr[smallest].PRICE = temp;
        // swap id
        char temp1[30];
        strcpy(temp1, heap->arr[index].SID);
        strcpy(heap->arr[index].SID, heap->arr[smallest].SID);
        strcpy(heap->arr[smallest].SID, temp1);

        heap = heapify(heap, smallest);
    }

    return heap;
}

// Delete the minimum element from the min heap
// return the new heap after deletion
SELLER_HEAP *delete_minimum(SELLER_HEAP *heap)
{
    // Deletes the minimum element, at the root
    if (!heap || heap->size == 0)
        return heap;

    int size = heap->size;
    SELLER_TYPE last_element;
    last_element.PRICE = heap->arr[size - 1].PRICE;
    strcpy(last_element.SID, heap->arr[size - 1].SID);

    // Update root value with the last element

    heap->arr[0].PRICE = last_element.PRICE;
    strcpy(heap->arr[0].SID, last_element.SID);

    // Now remove the last element, by decreasing the size
    heap->size--;
    size--;

    // We need to call heapify(), to maintain the min-heap
    // property
    heap = heapify(heap, 0);
    return heap;
}
ITEM_TYPE *newItem(char *name)
{
    ITEM_TYPE *newNode = (ITEM_TYPE *)malloc(sizeof(ITEM_TYPE));
    strcpy(newNode->ITEM_NAME, name);
    newNode->LCHILD = NULL;
    newNode->RCHILD = NULL;
    return newNode;
}

// Insert a node
ITEM_TYPE *bstInsert(ITEM_TYPE *head, char *name)
{
    // Return a new node if the tree is empty
    if (head == NULL)
        return newItem(name);

    // Traverse to the right place and insert the node
    if (strcmp(name, head->ITEM_NAME) < 0)
    {
        head->LCHILD = bstInsert(head->LCHILD, name);
    }
    else if ((strcmp(name, head->ITEM_NAME) > 0))
    {
        head->RCHILD = bstInsert(head->RCHILD, name);
    }

    return head;
}

ITEM_TYPE *minValueNode(ITEM_TYPE *node)
{
    ITEM_TYPE *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->LCHILD != NULL)
        current = current->LCHILD;

    return current;
}

void swapNode(ITEM_TYPE *node1, ITEM_TYPE *node2)
{
    // swap name
    char temp[30];
    strcpy(temp, node1->ITEM_NAME);
    strcpy(node1->ITEM_NAME, node2->ITEM_NAME);
    strcpy(node2->ITEM_NAME, temp);

    // swap heap
    SELLER_HEAP *heapHoder;
    heapHoder = node1->heap;
    node1->heap = node2->heap;
    node2->heap = heapHoder;
}

ITEM_TYPE *deleteNode(ITEM_TYPE *root, char *name)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (strcmp(root->ITEM_NAME, name) > 0)
        root->LCHILD = deleteNode(root->LCHILD, name);

    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(root->ITEM_NAME, name) < 0)
        root->RCHILD = deleteNode(root->RCHILD, name);

    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->LCHILD == NULL)
        {
            ITEM_TYPE *temp = root->RCHILD;
            free(root);
            return temp;
        }
        else if (root->RCHILD == NULL)
        {
            ITEM_TYPE *temp = root->LCHILD;
            free(root);
            return temp;
        }

        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        ITEM_TYPE *temp = minValueNode(root->RCHILD);

        // Copy the inorder
        // successor's content to this node
        swapNode(root, temp);

        // Delete the inorder successor
        root->RCHILD = deleteNode(root->RCHILD, temp->ITEM_NAME);
    }
    return root;
}

ITEM_TYPE *bstSearch(ITEM_TYPE *root, char *name)
{

    if (root == NULL)
    {
        return NULL;
    }
    while (root)
    {
        if (strcmp(root->ITEM_NAME, name) < 0)
        {
            root = root->RCHILD;
        }
        else if (strcmp(root->ITEM_NAME, name) > 0)
        {
            root = root->LCHILD;
        }
        else
        {
            return root;
        }
    }
    return root;
}

int maxNum(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}   

int countTreeHeight(ITEM_TYPE *root)
{
    if (root == NULL) {
        return 0;

    }
    int leftHeight = countTreeHeight(root->LCHILD);
    int rightHeight = countTreeHeight(root->RCHILD);

    return maxNum(leftHeight, rightHeight) + 1;
}

void Inorder(ITEM_TYPE *root, FILE *sortTable)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        Inorder(root->LCHILD, sortTable);
        fprintf(sortTable, "%s\n", root->ITEM_NAME);
        Inorder(root->RCHILD, sortTable);
    }
}
int main()
{

    // result variable initialization
    int search_fail = 0;
    int buy_fail = 0;
    int treeHeight = 0;
    int totalNodeNum = 0;
    int insert_time = 0;
    int search_time = 0;
    int buy_time = 0;

    // variable to hold the name of input file
    char inputFileBuffer[100];
    printf("Your input file: ");
    scanf("%s", inputFileBuffer);

    // pointer to read input file
    FILE *fptr = fopen(inputFileBuffer, "r");

    // pointer to write output file
    FILE *search = fopen("SearchTable.txt", "w+");
    FILE *buy = fopen("BuyTable.txt", "w+");
    FILE *sortTable = fopen("SortTable.txt", "w+");
    FILE *log = fopen("LogTable.txt", "w+");

    ITEM_TYPE *treeHead = NULL;

    char token[100]; // command token
    while (fscanf(fptr, "%s", token) != EOF)
    {
        
        if (strcmp(token, "insert") == 0)
        { // insert command processing

            insert_time++;
            char itemName[30];
            char sID[30];
            int price = 0;
            fscanf(fptr, "%s %s %d\n", itemName, sID, &price);
            ITEM_TYPE *temp = bstSearch(treeHead, itemName);
            // search BST for item name
            // if item name not found, insert new item into BST
            if (temp == NULL)
            {
                totalNodeNum++;
                treeHead = bstInsert(treeHead, itemName);
                ITEM_TYPE *item = bstSearch(treeHead, itemName);

                SELLER_TYPE *seller = (SELLER_TYPE *)malloc(sizeof(SELLER_TYPE));
                seller->PRICE = price;
                strcpy(seller->SID, sID);
                item->heap = init_minheap(7);
                item->heap = insert_minheap(item->heap, seller);
            }
            else
            {
                SELLER_TYPE *seller = (SELLER_TYPE *)malloc(sizeof(SELLER_TYPE));
                seller->PRICE = price;
                strcpy(seller->SID, sID);

                temp->heap = insert_minheap(temp->heap, seller);
            }
        }
        else if (strcmp(token, "search") == 0)
        { // search command processing
            search_time++;
            char itemName[30];
            fscanf(fptr, "%s\n", itemName);
            // printf("%s\n", itemName);
            ITEM_TYPE *temp = bstSearch(treeHead, itemName);

            if (!temp)
            {
                search_fail++;
                fprintf(search, "%s doesn’t exist!\n", itemName);
                fprintf(search, "----------------------------\n");
            }
            else
            {

                fprintf(search, "%s\n", temp->ITEM_NAME);
                for (int i = 0; i < temp->heap->size; i++)
                {
                    fprintf(search, "%s %d\n", temp->heap->arr[i].SID, temp->heap->arr[i].PRICE);
                }

                fprintf(search, "----------------------------\n");
            }
        }
        else if (strcmp(token, "buy") == 0)
        { // buy command processing
            buy_time++;
            char itemName[30];
            fscanf(fptr, "%s\n", itemName);
            // printf("%s\n", itemName);
            ITEM_TYPE *temp = bstSearch(treeHead, itemName);
            if (!temp)
            {
                buy_fail++;
                fprintf(buy, "%s doesn’t exist!\n", itemName);
            }
            else
            {

                SELLER_TYPE *sellerInfo = (SELLER_TYPE *)malloc(sizeof(SELLER_TYPE));
                sellerInfo = get_min(temp->heap);
                fprintf(buy, "%s %s %d\n", temp->ITEM_NAME, sellerInfo->SID, sellerInfo->PRICE);
                temp->heap = delete_minimum(temp->heap);
                if (temp->heap->size == 0)
                {

                    treeHead = deleteNode(treeHead, itemName);
                    totalNodeNum--;
                }
            }
        }
        else if (strcmp(token, "sort") == 0)
        { // sort command processing
            Inorder(treeHead, sortTable);
            fprintf(sortTable, "----------------------------\n");
        }
        else if (strcmp(token, "report") == 0)
        { // report command processing
            fprintf(log, "insert %d\n", insert_time);
            fprintf(log, "search %d %d\n", search_time, search_fail);
            fprintf(log, "buy %d %d\n", buy_time, buy_fail);
            fprintf(log, "node_num %d\n", totalNodeNum);
            treeHeight = countTreeHeight(treeHead);
            fprintf(log, "height %d\n", treeHeight);
        }

    } // end of EOF while loop

} // end of main