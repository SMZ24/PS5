/**
 * main.cpp
 * Student Grade Monitoring System - PS5 (Multi-Course Version)
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Team Members:
 * - Prashant Chand
 * - Sambhav Pyakurel
 * - Sujal Maharjan
 *
 * Main program with support for multiple courses per student.
 * GPA is automatically calculated from all courses.
 */

#include "AVLTree.h"
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Function prototypes
void displayMenu();
void addGrade(AVLTree &tree);
void searchStudent(AVLTree &tree);
void updateGrade(AVLTree &tree);
void deleteRecord(AVLTree &tree);
void displayAll(AVLTree &tree);
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
  cout << "     STUDENT GRADE MONITORING SYSTEM - PS5 (Multi-Course Version)  "
          "    \n";
  cout << "           CSC 307 Data Structures and Algorithm Analysis           "
          "   \n";
  cout << "===================================================================="
          "====\n";
  cout << "\nWelcome to the Student Grade Monitoring System!\n";
  cout << "✓ Supports multiple courses per student\n";
  cout << "✓ Automatic GPA calculation from all courses\n";
  cout << "✓ AVL Tree for O(log n) operations\n";

  // Attempt to load existing data at startup
  cout << "\nAttempting to load existing data from '" << DEFAULT_FILENAME
       << "'...\n";
  loadData(gradeTree);

  while (running) {
    displayMenu();
    cout << "\nEnter your choice (1-8): ";

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
      searchStudent(gradeTree);
      break;
    case 3:
      updateGrade(gradeTree);
      break;
    case 4:
      deleteRecord(gradeTree);
      break;
    case 5:
      displayAll(gradeTree);
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

void displayMenu() {
  cout << "\n";
  cout << "========================================\n";
  cout << "          MAIN MENU                    \n";
  cout << "========================================\n";
  cout << "1. Add Grade (New Student/Course)\n";
  cout << "2. Search Student\n";
  cout << "3. Update Course Grade\n";
  cout << "4. Delete Record\n";
  cout << "5. Display All Students\n";
  cout << "6. Save Data to File\n";
  cout << "7. Load Data from File\n";
  cout << "8. Exit\n";
  cout << "========================================\n";
}

void addGrade(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "ADD STUDENT/COURSE GRADE\n";
  cout << "========================================\n";

  int studentID;
  string name, course;
  float grade;

  cout << "Enter Student ID: ";
  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // Check if student exists
  AVLNode *existing = tree.search(studentID);

  if (existing != nullptr) {
    cout << "\n✓ Student ID " << studentID
         << " already exists: " << existing->getName() << endl;
    cout << "Current courses: " << existing->getCourseCount() << endl;
    cout << "Current GPA: " << fixed << setprecision(2) << existing->getGPA()
         << endl;
    cout << "\nAdding a new course for this student...\n\n";
    name = existing->getName(); // Use existing name
  } else {
    cout << "Enter Student Name: ";
    getline(cin, name);
  }

  cout << "Enter Course Name: ";
  getline(cin, course);

  cout << "Enter Grade (0-100): ";
  while (!(cin >> grade) || grade < 0 || grade > 100) {
    cout << "Invalid input! Please enter a grade between 0 and 100: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  // Insert (will add course if student exists, create new if doesn't)
  tree.insert(studentID, name, course, grade);

  if (existing == nullptr) {
    cout << "\n✓ New student record created successfully!\n";
  }

  // Show updated info
  AVLNode *student = tree.search(studentID);
  if (student != nullptr) {
    cout << "Updated GPA: " << fixed << setprecision(2) << student->getGPA()
         << endl;
    cout << "Total courses: " << student->getCourseCount() << endl;
  }
}

void searchStudent(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "SEARCH STUDENT\n";
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
    cout << string(70, '-') << endl;
    cout << left << setw(20) << "Student ID:" << result->getStudentID() << endl
         << setw(20) << "Name:" << result->getName() << endl
         << setw(20) << "Overall GPA:" << fixed << setprecision(2)
         << result->getGPA() << endl
         << setw(20) << "Total Courses:" << result->getCourseCount() << endl;
    cout << string(70, '-') << endl;

    cout << "\nCourses:\n";
    cout << left << setw(40) << "  Course Name" << setw(15) << "Grade"
         << setw(15) << "Letter" << endl;
    cout << "  " << string(65, '-') << endl;

    for (const auto &course : result->getCourses()) {
      string letter;
      if (course.grade >= 90)
        letter = "A";
      else if (course.grade >= 80)
        letter = "B";
      else if (course.grade >= 70)
        letter = "C";
      else if (course.grade >= 60)
        letter = "D";
      else
        letter = "F";

      cout << "  " << left << setw(40) << course.courseName << setw(15) << fixed
           << setprecision(2) << course.grade << setw(15) << letter << endl;
    }
    cout << string(70, '-') << endl;
  } else {
    cout << "\n✗ Student with ID " << studentID << " not found.\n";
  }
}

void updateGrade(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "UPDATE COURSE GRADE\n";
  cout << "========================================\n";

  int studentID;
  cout << "Enter Student ID: ";
  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  AVLNode *student = tree.search(studentID);
  if (student == nullptr) {
    cout << "\n✗ Student with ID " << studentID << " not found.\n";
    return;
  }

  // Display student's courses
  cout << "\nStudent: " << student->getName() << endl;
  cout << "Current GPA: " << fixed << setprecision(2) << student->getGPA()
       << endl;
  cout << "\nCurrent Courses:\n";
  int i = 1;
  for (const auto &course : student->getCourses()) {
    cout << "  " << i++ << ". " << course.courseName << " - " << fixed
         << setprecision(2) << course.grade << endl;
  }

  string courseName;
  cout << "\nEnter Course Name to update: ";
  getline(cin, courseName);

  if (!student->hasCourse(courseName)) {
    cout << "\n✗ Course '" << courseName << "' not found for this student.\n";
    cout << "Tip: Course names are case-sensitive.\n";
    return;
  }

  float newGrade;
  cout << "Enter New Grade (0-100): ";
  while (!(cin >> newGrade) || newGrade < 0 || newGrade > 100) {
    cout << "Invalid input! Please enter a grade between 0 and 100: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  if (tree.updateCourse(studentID, courseName, newGrade)) {
    cout << "\n✓ Course grade updated successfully!\n";
    cout << "Updated GPA: " << fixed << setprecision(2) << student->getGPA()
         << endl;
  } else {
    cout << "\n✗ Update failed.\n";
  }
}

void deleteRecord(AVLTree &tree) {
  cout << "\n========================================\n";
  cout << "DELETE RECORD\n";
  cout << "========================================\n";

  int studentID;
  cout << "Enter Student ID: ";

  while (!(cin >> studentID) || studentID <= 0) {
    cout << "Invalid input! Please enter a positive integer: ";
    clearInputBuffer();
  }
  clearInputBuffer();

  AVLNode *student = tree.search(studentID);
  if (student == nullptr) {
    cout << "\n✗ Student with ID " << studentID << " not found.\n";
    return;
  }

  cout << "\nStudent: " << student->getName() << endl;
  cout << "Total Courses: " << student->getCourseCount() << endl;

  cout << "\nWhat would you like to delete?\n";
  cout << "1. Delete a specific course\n";
  cout << "2. Delete entire student record\n";
  cout << "Enter choice (1-2): ";

  int choice;
  if (!(cin >> choice)) {
    cout << "Invalid input!\n";
    clearInputBuffer();
    return;
  }
  clearInputBuffer();

  if (choice == 1) {
    // Delete a specific course
    if (student->getCourseCount() == 1) {
      cout << "\n✗ Cannot delete the only course. Delete the entire student "
              "record instead.\n";
      return;
    }

    cout << "\nCurrent Courses:\n";
    int i = 1;
    for (const auto &course : student->getCourses()) {
      cout << "  " << i++ << ". " << course.courseName << endl;
    }

    string courseName;
    cout << "\nEnter Course Name to delete: ";
    getline(cin, courseName);

    char confirm;
    cout << "Are you sure you want to delete course '" << courseName
         << "'? (y/n): ";
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
      if (tree.deleteCourse(studentID, courseName)) {
        cout << "\n✓ Course deleted successfully!\n";
        cout << "Updated GPA: " << fixed << setprecision(2) << student->getGPA()
             << endl;
      } else {
        cout << "\n✗ Course deletion failed.\n";
      }
    } else {
      cout << "\n✗ Deletion cancelled.\n";
    }

  } else if (choice == 2) {
    // Delete entire student
    char confirm;
    cout << "\nAre you sure you want to delete the entire student record? "
            "(y/n): ";
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
      tree.deleteStudent(studentID);
      cout << "\n✓ Student record deleted successfully!\n";
    } else {
      cout << "\n✗ Deletion cancelled.\n";
    }
  } else {
    cout << "\nInvalid choice!\n";
  }
}

void displayAll(AVLTree &tree) { tree.display(); }

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

void clearInputBuffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
