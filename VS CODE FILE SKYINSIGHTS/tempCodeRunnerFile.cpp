#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

// Structure for a blood donor
struct Donor {
    string name;
    string bloodGroup;
    int units;
    string contactDetails;
    string email;

    Donor(string n, string bg, int u, string cd, string e)
        : name(n), bloodGroup(bg), units(u), contactDetails(cd), email(e) {}
};

// Node structure for a binary search tree
struct TreeNode {
    Donor donor;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Donor d) : donor(d), left(nullptr), right(nullptr) {}
};

class BloodBank {
private:
    TreeNode* root;

public:
    BloodBank() : root(nullptr) {}

    // Function to convert a string to uppercase
    string toUpperCase(string str) {
        for (char& c : str) {
            c = toupper(c);
        }
        return str;
    }

    // Function to add a donor to the BST
    TreeNode* insert(TreeNode* node, Donor donor) {
        if (node == nullptr) {
            return new TreeNode(donor);
        }

        if (donor.name < node->donor.name) {
            node->left = insert(node->left, donor);
        } else if (donor.name > node->donor.name) {
            node->right = insert(node->right, donor);
        } else {
            cout << "Error: Donor with the same name already exists." << endl;
        }

        return node;
    }

    // Function to add a donor
    void addDonor() {
        string name, bloodGroup, contactDetails, email;
        int units;

        cout << "Enter donor name: ";
        getline(cin, name);

        cout << "Enter blood group: ";
        getline(cin, bloodGroup);
        bloodGroup = toUpperCase(bloodGroup);

        // Validate and get the number of units
        while (true) {
            cout << "Enter units of blood donated: ";
            if (cin >> units && units > 0) {
                break;
            } else {
                cout << "Error: Invalid input. Please enter a positive integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Enter contact details: ";
        getline(cin, contactDetails);

        cout << ("(EMAIL ID): ");
        getline(cin, email);

        Donor newDonor(name, bloodGroup, units, contactDetails, email);
        root = insert(root, newDonor);
        cout << "Donor added successfully." << endl;
    }

    // Function to display donors in-order
    void displayInOrder(TreeNode* node) {
        if (node != nullptr) {
            displayInOrder(node->left);
            displayDonorDetails(node->donor);
            displayInOrder(node->right);
        }
    }

    // Function to display donor details
    void displayDonorDetails(Donor donor) {
        cout << "Donor Name: " << donor.name << endl;
        cout << "Blood Group: " << donor.bloodGroup << endl;
        cout << "Units Donated: " << donor.units << endl;
        cout << "Contact Details: " << donor.contactDetails << endl;
        cout << "Email: " << donor.email << endl;
        cout << "---------------------------" << endl;
    }

    // Function to search for a donor by name
    TreeNode* searchByName(TreeNode* node, const string& name) {
        if (node == nullptr || node->donor.name == name) {
            return node;
        }

        if (name < node->donor.name) {
            return searchByName(node->left, name);
        } else {
            return searchByName(node->right, name);
        }
    }

    // Function to search for a donor by blood group
    TreeNode* searchByBloodGroup(TreeNode* node, const string& bloodGroup) {
        if (node == nullptr || node->donor.bloodGroup == bloodGroup) {
            return node;
        }

        if (bloodGroup < node->donor.bloodGroup) {
            return searchByBloodGroup(node->left, bloodGroup);
        } else {
            return searchByBloodGroup(node->right, bloodGroup);
        }
    }

    // Function to display the main menu
    void displayMainMenu() {
        cout << "\nBlood Bank Management System\n";
        cout << "1. Add Donor\n";
        cout << "2. View Donors\n";
        cout << "3. Search Donor\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
    }

    // Function to handle user input and execute corresponding actions
    void handleUserInput() {
        int choice;
        string searchName, searchBloodGroup;

        do {
            displayMainMenu();
            cin >> choice;
            cin.ignore(); // Consume newline character

            switch (choice) {
                case 1:
                    addDonor();
                    break;
                case 2:
                    cout << "Donors in the Blood Bank:" << endl;
                    displayInOrder(root);
                    break;
                case 3:
                    cout << "1. Search by Name\n";
                    cout << "2. Search by Blood Group\n";
                    cout << "Enter your choice: ";
                    int searchChoice;
                    cin >> searchChoice;
                    cin.ignore(); // Consume newline character
                    switch (searchChoice) {
                        case 1:
                            cout << "Enter donor name to search: ";
                            getline(cin, searchName);
                            searchByNameAndDisplay(searchName);
                            break;
                        case 2:
                            cout << "Enter blood group to search: ";
                            getline(cin, searchBloodGroup);
                            searchByBloodGroupAndDisplay(searchBloodGroup);
                            break;
                        default:
                            cout << "Invalid search choice. Returning to main menu." << endl;
                    }
                    break;
                case 4:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 4.\n";
            }
        } while (choice != 4);
    }

    // Function to search for a donor by name and display details
    void searchByNameAndDisplay(const string& name) {
        TreeNode* result = searchByName(root, name);
        if (result != nullptr) {
            displayDonorDetails(result->donor);
        } else {
            cout << "Donor not available." << endl;
        }
    }

    // Function to search for a donor by blood group and display details
    void searchByBloodGroupAndDisplay(const string& bloodGroup) {
        TreeNode* result = searchByBloodGroup(root, bloodGroup);
        if (result != nullptr) {
            displayDonorDetails(result->donor);
        } else {
            cout << "Donor not available." << endl;
        }
    }
};

int main() {
    BloodBank bloodBank;
    bloodBank.handleUserInput();

    return 0;
}