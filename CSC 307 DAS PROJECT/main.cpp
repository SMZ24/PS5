/**
 * main.cpp
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Team Members:
 * - Prashant Chand
 * - Sambhav Pyakurel
 * - Sujal Maharjan
 *
 * Main program providing a command-line menu interface for the
 * Student Grade Monitoring System using AVL Tree data structure.
 */

#include "AVLTree.h"
#include <iomanip>
#include <iostream>
#include <limits>


using namespace std;

// Function prototypes
void displayMenu();
void addGrade(AVLTree &tree);
void searchGrade(AVLTree &tree);
void updateGrade(AVLTree &tree);
void deleteGrade(AVLTree &tree);
void displayGrades(AVLTree &tree);
void saveData(AVLTree &tree);
void loadData(AVLTree &tree);
void clearInputBuffer();

// Default CSV filename
const string DEFAULT_FILENAME = "student_grades.csv";

int main() {
  AVLTree gradeTree;
  int choice;
  bool running = true;

  cout << "\n";
  cout << "===================================================================="
          "====\n";
  cout << "           STUDENT GRADE MONITORING SYSTEM - PS5                    "
          "   \n";
  cout << "           CSC 307 Data Structures and Algorithm Analysis           "
          "   \n";
  cout << "===================================================================="
          "====\n";
  cout << "\nWelcome to the Student Grade Monitoring System!\n";
  cout << "This system uses an AVL Tree for efficient grade management.\n";

  // Attempt to load existing data at startup
  cout << "\nAttempting to load existing data from '" << DEFAULT_FILENAME
       << "'...\n";
  loadData(gradeTree);

  while (running) {
    displayMenu();
    cout << "\nEnter your choice (1-8): ";

    // Input validation
    if (!(cin >> choice)) {
      cout << "Invalid input! Please enter a number between 1 and 8.\n";
      clearInputBuffer();
      continue;
    }

    clearInputBuffer();

    switch (choice) {
    case 1:
      addGrade(gradeTree);
      break;
    case 2:
      searchGrade(gradeTree);
      break;
    case 3:
      updateGrade(gradeTree);
      break;
    case 4:
      deleteGrade(gradeTree);
      break;
    case 5:
      displayGrades(gradeTree);
      break;
    case 6:
      saveData(gradeTree);
      break;
    case 7:
      loadData(gradeTree);
      break;
    case 8:
      cout << "\n========================================\n";
      cout << "Exiting Program\n";
      cout << "========================================\n";

      // Prompt to save before exiting
      char saveChoice;
      cout << "Would you like to save data before exiting? (y/n): ";
      cin >> saveChoice;
      clearInputBuffer();

      if (saveChoice == 'y' || saveChoice == 'Y') {
        saveData(gradeTree);
      }

      cout << "\nThank you for using the Student Grade Monitoring System!\n";
      cout << "Goodbye!\n\n";
      running = false;
      break;
    default:
      cout << "\nInvalid choice! Please select a number between 1 and 8.\n";
    }
  }

  return 0;
}

/**
 * Display the main menu
 */
void displayMenu() {
  cout << "\n";
  cout << "========================================\n";
  cout << "          MAIN MENU                    \n";
  cout << "========================================\n";
  cout << "1. Add Grade\n";
  cout << "2. Search Grade\n";
  cout << "3. Update Grade\n";
  cout << "4. Delete Grade\n";
  cout << "5. Display All Grades\n";
  cout << "6. Save Data to File\n";
  cout << "7. Load Data from File\n";
  cout << "8. Exit\n";
  cout << "========================================\n";
}

/**
 * Add a new student grade record
 */
void addGrade(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "ADD NEW STUDENT GRADE\n";
  cout << "========================================\n";

  int studentID;
  string name, course;
  float grade, gpa;

  cout << "Enter Student ID: ";
  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  cout << "Enter Student Name: ";
  getline(cin, name);

  cout << "Enter Course Name: ";
  getline(cin, course);

  cout << "Enter Grade (0-100): ";
  while (!(cin >> grade) || grade < 0 || grade > 100) {
    cout << "Invalid input! Please enter a grade between 0 and 100: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  cout << "Enter GPA (0.0-4.0): ";
  while (!(cin >> gpa) || gpa < 0.0 || gpa > 4.0) {
    cout << "Invalid input! Please enter a GPA between 0.0 and 4.0: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // Insert into AVL tree
  tree.insert(studentID, name, course, grade, gpa);

  cout << "\n✓ Student record added successfully!\n";
}

/**
 * Search for a student grade record by ID
 */
void searchGrade(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "SEARCH STUDENT GRADE\n";
  cout << "========================================\n";

  int studentID;
  cout << "Enter Student ID to search: ";

  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  AVLNode *result = tree.search(studentID);

  if (result != nullptr) {
    cout << "\n✓ Student Found!\n";
    cout << string(60, '-') << endl;
    cout << left << setw(20) << "Student ID:" << result->getStudentID() << endl
         << setw(20) << "Name:" << result->getName() << endl
         << setw(20) << "Course:" << result->getCourse() << endl
         << setw(20) << "Grade:" << fixed << setprecision(2)
         << result->getGrade() << endl
         << setw(20) << "GPA:" << fixed << setprecision(2) << result->getGPA()
         << endl;
    cout << string(60, '-') << endl;
  } else {
    cout << "\n✗ Student with ID " << studentID << " not found.\n";
  }
}

/**
 * Update an existing student's grade and GPA
 */
void updateGrade(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "UPDATE STUDENT GRADE\n";
  cout << "========================================\n";

  int studentID;
  float newGrade, newGPA;

  cout << "Enter Student ID to update: ";
  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // First, check if student exists
  AVLNode *student = tree.search(studentID);
  if (student == nullptr) {
    cout << "\n✗ Student with ID " << studentID << " not found.\n";
    return;
  }

  // Display current information
  cout << "\nCurrent Information:\n";
  cout << "  Name: " << student->getName() << endl;
  cout << "  Course: " << student->getCourse() << endl;
  cout << "  Grade: " << fixed << setprecision(2) << student->getGrade()
       << endl;
  cout << "  GPA: " << fixed << setprecision(2) << student->getGPA() << endl;

  cout << "\nEnter New Grade (0-100): ";
  while (!(cin >> newGrade) || newGrade < 0 || newGrade > 100) {
    cout << "Invalid input! Please enter a grade between 0 and 100: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  cout << "Enter New GPA (0.0-4.0): ";
  while (!(cin >> newGPA) || newGPA < 0.0 || newGPA > 4.0) {
    cout << "Invalid input! Please enter a GPA between 0.0 and 4.0: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // Perform update
  if (tree.update(studentID, newGrade, newGPA)) {
    cout << "\n✓ Student record updated successfully!\n";
  } else {
    cout << "\n✗ Update failed.\n";
  }
}

/**
 * Delete a student grade record
 */
void deleteGrade(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "DELETE STUDENT GRADE\n";
  cout << "========================================\n";

  int studentID;
  cout << "Enter Student ID to delete: ";

  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // Check if student exists before deleting
  AVLNode *student = tree.search(studentID);
  if (student == nullptr) {
    cout << "\n✗ Student with ID " << studentID << " not found.\n";
    return;
  }

  // Display student info and confirm deletion
  cout << "\nStudent to be deleted:\n";
  cout << "  ID: " << student->getStudentID() << endl;
  cout << "  Name: " << student->getName() << endl;
  cout << "  Course: " << student->getCourse() << endl;

  char confirm;
  cout << "\nAre you sure you want to delete this record? (y/n): ";
  cin >> confirm;
  clearInputBuffer();

  if (confirm == 'y' || confirm == 'Y') {
    tree.deleteNode(studentID);
    cout << "\n✓ Student record deleted successfully!\n";
  } else {
    cout << "\n✗ Deletion cancelled.\n";
  }
}

/**
 * Display all student grade records in sorted order
 */
void displayGrades(AVLTree &tree) { tree.display(); }

/**
 * Save all records to CSV file
 */
void saveData(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "SAVE DATA TO FILE\n";
  cout << "========================================\n";

  string filename;
  cout << "Enter filename (or press Enter for default '" << DEFAULT_FILENAME
       << "'): ";
  getline(cin, filename);

  if (filename.empty()) {
    filename = DEFAULT_FILENAME;
  }

  tree.saveToFile(filename);
}

/**
 * Load records from CSV file
 */
void loadData(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "LOAD DATA FROM FILE\n";
  cout << "========================================\n";

  string filename;
  cout << "Enter filename (or press Enter for default '" << DEFAULT_FILENAME
       << "'): ";
  getline(cin, filename);

  if (filename.empty()) {
    filename = DEFAULT_FILENAME;
  }

  tree.loadFromFile(filename);
}

/**
 * Clear input buffer to handle invalid input
 */
void clearInputBuffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
