#include <iostream>
#include "int_array.hpp"

int main()
{
    // Declare an array with 10 elements
    IntArray array(10);

    // Fill the array with numbers 1 through 10
    for (int i = 0; i < 10; i++)
        array[i] = i + 1;

    // Resize the array to 8 elements
    array.resize(8);

    // Insert the number 20 before element with index 5
    array.insertBefore(20, 5);

    // Remove the element with index 3
    array.remove(3);

    // Add 30 and 40 to the end and beginning
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    // Print out all the numbers
    for (int j = 0; j < array.getLength(); j++)
        std::cout << array[j] << " ";

    std::cout << std::endl;

    IntArray array2{5, 4, 3, 2, 1}; // initializer list
    for (int count = 0; count < array2.getLength(); ++count)
        std::cout << array2[count] << ' ';
    std::cout << std::endl;

    array2 = {1, 3, 5, 7, 9, 11};

    for (int count = 0; count < array2.getLength(); ++count)
        std::cout << array2[count] << ' ';

    return 0;
}