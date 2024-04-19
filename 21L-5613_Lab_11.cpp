#include<iostream>
#include<vector>
#include<fstream>
#include<climits>
#include <cstdlib>
#include<string>
using namespace std;

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode* left, * right;

};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct node {
    char data;
    int frequency;
    node* left;
    node* right;

    node()
    {
        left = NULL;
        right = NULL;
    }

};

struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)

{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
    struct MinHeapNode* left, * right, * top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {


        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top)

{

    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {

        cout << root->data << ": ";
        printArr(arr, top);
    }
}

void HuffmanCodes(char data[], int freq[], int size)

{
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    int arr[10];
    int top = 0;

    printCodes(root, arr, top);
}


int main()
{


    cout << endl << "File: " << endl;
    string text;
    vector<node*>v;
    ifstream file("abc.txt");

    while (getline(file, text))
    {
        cout << text;
    }
    cout << endl;
    file.close();

    int len = text.length();

    for (int i = 0; i < len; i++)
    {
        bool b = false;
        for (int a = 0; a < v.size(); a++)
        {
            if (v[a]->data == text[i])
            {
                v[a]->frequency++;
                b = true;
            }
        }
        if (b == false)
        {
            node* temp = new node();
            temp->data = text[i];
            temp->frequency = 1;
            v.push_back(temp);
        }
    }
    cout << endl << "Frequency:  " << endl << endl;
    for (int a = 0; a < v.size(); a++)
    {
        cout << v[a]->data << " ";
        cout << v[a]->frequency;
        cout << endl;
    }

    char arr[] = { 'f', 'j', 's', 'b', 'a', 'd' };
    int freq[] = { 56, 52, 77, 28, 24, 24 };

    int size = sizeof(arr) / sizeof(arr[0]);

   // cout << endl << "HuffMan Coding " << endl;
   // HuffmanCodes(arr, freq, size);

    cout << endl;
    cout << endl << "Tree: " << endl << endl;;
    for (int i = 0; i < 6; i++)
    {
        cout << freq[i] << " ";
    }
    int min1 = freq[4];
    int min2 = freq[5];
    int s = min1 + min2;
    cout << endl;
    int freq1[] = { 56, 52, 77, 28, 48 };
    for (int i = 0; i < 5; i++)
    {
        cout << freq1[i] << " ";
    }
    cout << endl;
    int min3 = freq[3];
    int min4 = freq[4];
    int s1 = min3 + min4;
    int freq2[] = { 56, 52, 77, 76 };
    for (int i = 0; i < 4; i++)
    {
        cout << freq2[i] << " ";
    }

    cout << endl;
    int min5 = freq[0];
    int min6 = freq[1];
    int s2 = min5 + min6;
    int freq3[] = { 108, 77, 76 };
    for (int i = 0; i < 3; i++)
    {
        cout << freq3[i] << " ";
    }

    cout << endl;
    int min7 = freq[1];
    int min8 = freq[2];
    int s3 = min7 + min8;
    int freq4[] = { 108, 153 };
    for (int i = 0; i < 2; i++)
    {
        cout << freq4[i] << " ";
    }



    int sum = 0;
    for (int i = 0; i < 6; i++)
    {
        sum += freq[i];
    }
    cout << endl << sum;
    cout << endl << endl;
    return 0;
}