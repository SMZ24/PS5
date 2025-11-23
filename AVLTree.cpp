/**
 * AVLTree.cpp
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Implementation supporting multiple courses per student with automatic GPA
 * calculation.
 */

#include "AVLTree.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Destructor
AVLTree::~AVLTree() { destroyTree(root); }

// Helper function to destroy the tree recursively
void AVLTree::destroyTree(AVLNode *node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

// Check if tree is empty
bool AVLTree::isEmpty() const { return root == nullptr; }

// ==================== HELPER FUNCTIONS ====================

int AVLTree::getHeight(AVLNode *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVLTree::getBalance(AVLNode *node) {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

AVLNode *AVLTree::rotateLeft(AVLNode *x) {
  AVLNode *y = x->right;
  AVLNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
  y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

  return y;
}

AVLNode *AVLTree::rotateRight(AVLNode *y) {
  AVLNode *x = y->left;
  AVLNode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
  x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

  return x;
}

AVLNode *AVLTree::findMinNode(AVLNode *node) {
  AVLNode *current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

// ==================== INSERT OPERATION ====================

void AVLTree::insert(int student_ID, const std::string &name,
                     const std::string &course, float grade) {
  root = insertHelper(root, student_ID, name, course, grade);
}

AVLNode *AVLTree::insertHelper(AVLNode *node, int student_ID,
                               const std::string &name,
                               const std::string &course, float grade) {
  // 1. Perform standard BST insertion
  if (node == nullptr) {
    return new AVLNode(student_ID, name, course, grade);
  }

  if (student_ID < node->student_ID) {
    node->left = insertHelper(node->left, student_ID, name, course, grade);
  } else if (student_ID > node->student_ID) {
    node->right = insertHelper(node->right, student_ID, name, course, grade);
  } else {
    // Student ID already exists - add course to existing student
    if (node->hasCourse(course)) {
      std::cout << "Note: Student ID " << student_ID << " already has course '"
                << course << "'. Use Update to modify the grade." << std::endl;
    } else {
      node->addCourse(course, grade);
      std::cout << "Course '" << course << "' added to student ID "
                << student_ID << ". GPA updated to " << std::fixed
                << std::setprecision(2) << node->getGPA() << std::endl;
    }
    return node;
  }

  // 2. Update height of current node
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

  // 3. Get balance factor
  int balance = getBalance(node);

  // 4. Perform rotations if unbalanced (4 cases)

  // Left-Left Case
  if (balance > 1 && student_ID < node->left->student_ID) {
    return rotateRight(node);
  }

  // Right-Right Case
  if (balance < -1 && student_ID > node->right->student_ID) {
    return rotateLeft(node);
  }

  // Left-Right Case
  if (balance > 1 && student_ID > node->left->student_ID) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Right-Left Case
  if (balance < -1 && student_ID < node->right->student_ID) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

// ==================== SEARCH OPERATION ====================

AVLNode *AVLTree::search(int student_ID) {
  return searchHelper(root, student_ID);
}

AVLNode *AVLTree::searchHelper(AVLNode *node, int student_ID) {
  if (node == nullptr || node->student_ID == student_ID) {
    return node;
  }

  if (student_ID < node->student_ID) {
    return searchHelper(node->left, student_ID);
  }

  return searchHelper(node->right, student_ID);
}

// ==================== UPDATE OPERATIONS ====================

bool AVLTree::updateCourse(int student_ID, const std::string &courseName,
                           float newGrade) {
  AVLNode *student = search(student_ID);

  if (student != nullptr) {
    return student->updateCourse(courseName, newGrade);
  }

  return false;
}

bool AVLTree::addCourseToStudent(int student_ID, const std::string &courseName,
                                 float grade) {
  AVLNode *student = search(student_ID);

  if (student == nullptr) {
    return false; // Student not found
  }

  if (student->hasCourse(courseName)) {
    return false; // Course already exists
  }

  student->addCourse(courseName, grade);
  return true;
}

// ==================== DELETE OPERATIONS ====================

bool AVLTree::deleteCourse(int student_ID, const std::string &courseName) {
  AVLNode *student = search(student_ID);

  if (student == nullptr) {
    return false;
  }

  if (student->getCourseCount() == 1) {
    std::cout << "Warning: This is the student's only course. Deleting it will "
                 "remove the student entirely."
              << std::endl;
    std::cout << "Use 'Delete Student' option instead if you want to remove "
                 "the entire student record."
              << std::endl;
    return false;
  }

  return student->deleteCourse(courseName);
}

void AVLTree::deleteStudent(int student_ID) {
  root = deleteHelper(root, student_ID);
}

AVLNode *AVLTree::deleteHelper(AVLNode *node, int student_ID) {
  if (node == nullptr) {
    return node;
  }

  if (student_ID < node->student_ID) {
    node->left = deleteHelper(node->left, student_ID);
  } else if (student_ID > node->student_ID) {
    node->right = deleteHelper(node->right, student_ID);
  } else {
    // Node to be deleted found

    if (node->left == nullptr) {
      AVLNode *temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      AVLNode *temp = node->left;
      delete node;
      return temp;
    }

    // Node with 2 children
    AVLNode *temp = findMinNode(node->right);

    // Copy data
    node->student_ID = temp->student_ID;
    node->name = temp->name;
    node->courses = temp->courses;
    node->GPA = temp->GPA;

    node->right = deleteHelper(node->right, temp->student_ID);
  }

  if (node == nullptr) {
    return node;
  }

  // Update height and balance
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  int balance = getBalance(node);

  // Left-Left Case
  if (balance > 1 && getBalance(node->left) >= 0) {
    return rotateRight(node);
  }

  // Left-Right Case
  if (balance > 1 && getBalance(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Right-Right Case
  if (balance < -1 && getBalance(node->right) <= 0) {
    return rotateLeft(node);
  }

  // Right-Left Case
  if (balance < -1 && getBalance(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

// ==================== DISPLAY OPERATION ====================

void AVLTree::display() {
  if (isEmpty()) {
    std::cout << "\nNo student records to display." << std::endl;
    return;
  }

  std::cout << "\n" << std::string(90, '=') << std::endl;
  std::cout << "STUDENT GRADE RECORDS (Sorted by Student ID)" << std::endl;
  std::cout << std::string(90, '=') << std::endl;

  inorderTraversal(root);

  std::cout << std::string(90, '=') << std::endl;
}

void AVLTree::inorderTraversal(AVLNode *node) {
  if (node != nullptr) {
    inorderTraversal(node->left);

    // Display student header
    std::cout << "\nStudent ID: " << node->student_ID
              << " | Name: " << node->name << " | Overall GPA: " << std::fixed
              << std::setprecision(2) << node->GPA
              << " | Courses: " << node->getCourseCount() << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    // Display all courses
    std::cout << std::left << "  " << std::setw(40) << "Course" << std::setw(15)
              << "Grade" << std::setw(15) << "Letter Grade" << std::endl;
    std::cout << "  " << std::string(70, '-') << std::endl;

    for (const auto &course : node->getCourses()) {
      std::string letterGrade;
      if (course.grade >= 90)
        letterGrade = "A";
      else if (course.grade >= 80)
        letterGrade = "B";
      else if (course.grade >= 70)
        letterGrade = "C";
      else if (course.grade >= 60)
        letterGrade = "D";
      else
        letterGrade = "F";

      std::cout << "  " << std::left << std::setw(40) << course.courseName
                << std::setw(15) << std::fixed << std::setprecision(2)
                << course.grade << std::setw(15) << letterGrade << std::endl;
    }

    inorderTraversal(node->right);
  }
}

// ==================== SAVE TO FILE OPERATION ====================

void AVLTree::saveToFile(const std::string &filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cout << "Error: Could not open file '" << filename << "' for writing."
              << std::endl;
    return;
  }

  // Write CSV header
  file << "StudentID,Name,Course,Grade,GPA" << std::endl;

  saveToFileHelper(root, file);

  file.close();
  std::cout << "Data successfully saved to '" << filename << "'." << std::endl;
}

void AVLTree::saveToFileHelper(AVLNode *node, std::ofstream &file) {
  if (node != nullptr) {
    saveToFileHelper(node->left, file);

    // Write one line per course
    for (const auto &course : node->getCourses()) {
      file << node->student_ID << "," << node->name << "," << course.courseName
           << "," << std::fixed << std::setprecision(2) << course.grade << ","
           << std::fixed << std::setprecision(2) << node->GPA << std::endl;
    }

    saveToFileHelper(node->right, file);
  }
}

// ==================== LOAD FROM FILE OPERATION ====================

void AVLTree::loadFromFile(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Error: Could not open file '" << filename << "' for reading."
              << std::endl;
    return;
  }

  std::string line;
  int count = 0;

  // Skip header line
  std::getline(file, line);

  // Read each line
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    std::stringstream ss(line);
    std::string token;

    int student_ID;
    std::string name, course;
    float grade, gpa;

    try {
      // Parse student_ID
      std::getline(ss, token, ',');
      student_ID = std::stoi(token);

      // Parse name
      std::getline(ss, name, ',');

      // Parse course
      std::getline(ss, course, ',');

      // Parse grade
      std::getline(ss, token, ',');
      grade = std::stof(token);

      // Parse GPA (we recalculate it, but read it for compatibility)
      std::getline(ss, token, ',');
      gpa = std::stof(token);

      // Insert - will automatically add course if student exists
      insert(student_ID, name, course, grade);
      count++;

    } catch (const std::exception &e) {
      std::cout << "Error parsing line: " << line << std::endl;
      continue;
    }
  }

  file.close();
  std::cout << "Successfully loaded " << count << " course records from '"
            << filename << "'." << std::endl;
}
