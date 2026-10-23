#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <string>
#include <sstream>

using namespace std;
/** Moves all zeros to the end of a vector with two passes.
 * @param vec: The vector to be modified in place. 
 */
void move_zeros_two_passes(vector<int>& vec) {
    size_t current = 0; // Points to the current element being checked

    // First pass: Move all non-zero elements to the front of the vector
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec.at(i) != 0) {
            vec.at(current) = vec.at(i); // Move non-zero element to the current position
            ++current; // Point to the next position for the next non-zero element 
        }
    }

    // Second pass: Fill the remaining positions with zeros
    for (size_t i = current; i < vec.size(); ++i) {
        vec.at(i) = 0; // Set the remaining elements to zero
    }
} // Time Complexity: O(n), Space Complexity: O(1)

void move_zeros_single_pass(vector<int>& vec) {
    size_t last_position = 0; // Points to the last position of the non-zero elements

    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec.at(i) != 0) {
            swap(vec.at(last_position), vec.at(i)); // Swap the current non-zero element with the last non-zero position
            ++last_position; // Move the last position pointer to the next index
        }
    }
} // Time Complexity: O(n), Space Complexity: O(1)

vector<int> generate_vector(size_t num_of_elements, size_t num_of_zeros) {
    vector<int> vec;

    random_device rd; // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    uniform_int_distribution<int> distr(1, 99); // Define the range for random numbers

    // Generate n-k random non-zero elements
    for (size_t i = 0; i < num_of_elements - num_of_zeros; ++i) {
        vec.push_back(distr(gen)); // Add random non-zero elements to the vector
    }

    // Add k zeros to the vector
    for (size_t i = 0; i < num_of_zeros; ++i) {
        vec.push_back(0); // Add zeros to the vector
    }

    // Shuffle the vector
    shuffle(vec.begin(), vec.end(), gen);

    return vec;
} // Time Complexity: O(n), Space Complexity: O(n)

void print_vector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec.at(i); // Print each element of the vector
        if (i != vec.size() - 1) {
            cout << ", "; // Add a comma and space between elements
        }
    }
    cout << "]" << endl << endl;;
}

size_t get_nonnegative_integer(const char* prompt) {
    string line;
    while(true) {
        cout << prompt; // Prompt the user for input
        getline(cin, line); // Read a line of input

        // Reject empty input or non digit characters
        if (line.empty() || line.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid input. Please enter a non-negative integer." << endl;
            continue; // Prompt again
        }
        stringstream ss(line);
        size_t value;
        if (ss >> value) {
            return value;
        }
        cout << "Invalid input." << endl;
    }
}

void display_menu() {
    cout << "Choose an option:" << endl;
    cout << "1. Generate a new vector." << endl;
    cout << "2. Move zeros to the end using two passes." << endl;
    cout << "3. Move zeros to the end using a single pass." << endl;
    cout << "4. Exit." << endl;
    cout << "Enter your choice: \n";
}

int main() {
    size_t num_of_elements;
    size_t num_of_zeros;
    int choice;
    vector<int> original_vector = {0, 0, 0, 0, 0};

    
    while (true) {

        display_menu();

        if (!(cin >> choice)) {
            cin.clear(); // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            cout << "Invalid input. Please enter 1, 2, 3, or 4." << endl;
            continue;
        }
        switch (choice) {
            case 1: {
                cout << "\nGenerating a new vector." << endl;
                // Ask the user for vector information
                do {
                    num_of_elements = get_nonnegative_integer("Enter the number of elements: ");

                    if (num_of_elements == 0) {
                        cout << "Vector cannot be empty." << endl;
                    }
                } while (num_of_elements == 0);

                do {
                    num_of_zeros = get_nonnegative_integer("Enter the number of zeros: ");
                    if (num_of_zeros > num_of_elements) {
                        cout << "Number of zeros cannot exceed" << num_of_elements << " the number of elements." << endl;
                    }
                } while (num_of_zeros > num_of_elements);
                original_vector = generate_vector(num_of_elements, num_of_zeros);
                print_vector(original_vector); // Print the new vector
                break;
            }
            case 2: {

                vector<int> vec = original_vector; // Create a copy of the original vector
                cout << "Original vector: ";
                print_vector(vec); // Print the original vector
                cout << "Moving zeros to the end using two passes." << endl;
                move_zeros_two_passes(vec); // Move zeros using two passes
                print_vector(vec); // Print the modified vector
                break;
            }
            case 3: {
                vector<int> vec = original_vector; // Create a copy of the original vector
                cout << "Original vector: ";
                print_vector(vec); // Print the original vector
                cout << "Moving zeros to the end using a single pass." << endl;
                move_zeros_single_pass(vec); // Move zeros using a single pass
                print_vector(vec); // Print the modified vector
                break;
            }
            case 4:
                cout << "Exiting the program." << endl;
                return 0; // Exit the program
        }
    }
    
    
}