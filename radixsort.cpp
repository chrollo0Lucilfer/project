// #include <iostream>
// #include <algorithm>
// using namespace std;

// // A utility function to get the maximum value in an array
// int getMax(int arr[], int n)
// {
//     int max = arr[0];
//     for (int i = 1; i < n; i++)
//     {
//         if (arr[i] > max)
//         {
//             max = arr[i];
//         }
//     }
//     return max;
// }

// // A function to do counting sort of arr[] according to the digit represented by exp
// void countingSort(int arr[], int n, int exp)
// {
//     int output[n];       // Output array
//     int count[10] = {0}; // Count array to store the count of digits (0-9)

//     // Store the count of occurrences of each digit
//     for (int i = 0; i < n; i++)
//     {
//         count[(arr[i] / exp) % 10]++;
//     }

//     // Change count[i] so that count[i] contains the actual position of this digit in output[]
//     for (int i = 1; i < 10; i++)
//     {
//         count[i] += count[i - 1];
//     }

//     // Build the output array
//     for (int i = n - 1; i >= 0; i--)
//     {
//         output[count[(arr[i] / exp) % 10] - 1] = arr[i];
//         count[(arr[i] / exp) % 10]--;
//     }

//     // Copy the output array to arr[], so that arr[] now contains sorted numbers according to the current digit
//     for (int i = 0; i < n; i++)
//     {
//         arr[i] = output[i];
//     }
// }

// // The main function to that sorts arr[] of size n using Radix Sort
// void radixSort(int arr[], int n)
// {
//     int max = getMax(arr, n); // Find the maximum number to know the number of digits

//     // Do counting sort for every digit, starting with the least significant digit
//     for (int exp = 1; max / exp > 0; exp *= 10)
//     {
//         countingSort(arr, n, exp);
//     }
// }

// int main()
// {
//     int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     radixSort(arr, n);

//     cout << "Sorted array: ";
//     for (int i = 0; i < n; i++)
//     {
//         cout << arr[i] << " ";
//     }
//     cout << endl;

//     return 0;
// }
#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
};

void traverse(struct node *ptr)
{

    while (ptr != NULL)
    {
        cout << ptr->data << "->";
        ptr = ptr->next;
    }

    if (ptr == NULL)
    {
        cout << "NULL";
    }
}

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *second = (struct node *)malloc(sizeof(struct node));

    struct node *third = (struct node *)malloc(sizeof(struct node));

    struct node *fourth = (struct node *)malloc(sizeof(struct node));

    head->data = 24;
    head->next = second;

    second->data = 45;
    second->next = third;

    third->data = 11;
    third->next = fourth;

    fourth->data = 67;
    fourth->next = NULL;

    traverse(head);
}