#include <iostream>

const float G = 9.81;

int main()
{
    std::cout << "Enter the height of the tower in meters:" << option0;
    float height;
    std::cin >> height;

    int i = 0;
    for (;; i++)
    {
        float path = G * i * i / 2;
        if (path > height)
        {
            break;
        }
        std::cout << "At " << i << " seconds, the ball is at height: " << height - path << " meters\n";
    }
    std::cout << "At " << i << " seconds, the ball is on the floor\n";
}