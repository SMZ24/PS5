/**
 * AVLTree.cpp
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Implementation of AVLTree class methods including all critical operations:
 * Insert, Search, Update, Delete, Display, Save, and Load.
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

/**
 * Get the height of a node
 * Returns 0 if node is null
 */
int AVLTree::getHeight(AVLNode *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

/**
 * Get the balance factor of a node
 * Balance Factor = height(left subtree) - height(right subtree)
 * AVL property: balance factor must be -1, 0, or 1
 */
int AVLTree::getBalance(AVLNode *node) {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

/**
 * Perform left rotation
 * Used to fix Right-Right case
 */
AVLNode *AVLTree::rotateLeft(AVLNode *x) {
  AVLNode *y = x->right;
  AVLNode *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
  y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

  return y; // New root
}

/**
 * Perform right rotation
 * Used to fix Left-Left case
 */
AVLNode *AVLTree::rotateRight(AVLNode *y) {
  AVLNode *x = y->left;
  AVLNode *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
  x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

  return x; // New root
}

/**
 * Find the node with minimum value (leftmost node)
 * Used in deletion operation
 */
AVLNode *AVLTree::findMinNode(AVLNode *node) {
  AVLNode *current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

// ==================== DSA1: INSERT OPERATION ====================

/**
 * Public insert function
 */
void AVLTree::insert(int student_ID, const std::string &name,
                     const std::string &course, float grade, float GPA) {
  root = insertHelper(root, student_ID, name, course, grade, GPA);
}

/**
 * Recursive helper function for insertion
 * Inserts a new node and maintains AVL balance property
 * Time Complexity: O(log n)
 */
AVLNode *AVLTree::insertHelper(AVLNode *node, int student_ID,
                               const std::string &name,
                               const std::string &course, float grade,
                               float GPA) {
  // 1. Perform standard BST insertion
  if (node == nullptr) {
    return new AVLNode(student_ID, name, course, grade, GPA);
  }

  if (student_ID < node->student_ID) {
    node->left = insertHelper(node->left, student_ID, name, course, grade, GPA);
  } else if (student_ID > node->student_ID) {
    node->right =
        insertHelper(node->right, student_ID, name, course, grade, GPA);
  } else {
    // Duplicate student_ID not allowed
    std::cout << "Error: Student ID " << student_ID << " already exists!"
              << std::endl;
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

// ==================== DSA2: SEARCH OPERATION ====================

/**
 * Public search function
 */
AVLNode *AVLTree::search(int student_ID) {
  return searchHelper(root, student_ID);
}

/**
 * Recursive helper function for searching
 * Time Complexity: O(log n)
 */
AVLNode *AVLTree::searchHelper(AVLNode *node, int student_ID) {
  // Base cases: node is null or key is found
  if (node == nullptr || node->student_ID == student_ID) {
    return node;
  }

  // Key is smaller, search left subtree
  if (student_ID < node->student_ID) {
    return searchHelper(node->left, student_ID);
  }

  // Key is larger, search right subtree
  return searchHelper(node->right, student_ID);
}

// ==================== DSA3: UPDATE OPERATION ====================

/**
 * Update grade and GPA for an existing student
 * Time Complexity: O(log n) - dominated by search operation
 */
bool AVLTree::update(int student_ID, float grade, float GPA) {
  // 1. Search for the node
  AVLNode *nodeToUpdate = search(student_ID);

  // 2. Check if node was found
  if (nodeToUpdate != nullptr) {
    // 3. Update the fields
    nodeToUpdate->setGrade(grade);
    nodeToUpdate->setGPA(GPA);
    return true; // Update successful
  }

  return false; // Node not found
}

// ==================== DSA4: DELETE OPERATION ====================

/**
 * Public delete function
 */
void AVLTree::deleteNode(int student_ID) {
  root = deleteHelper(root, student_ID);
}

/**
 * Recursive helper function for deletion
 * Deletes a node and maintains AVL balance property
 * Time Complexity: O(log n)
 */
AVLNode *AVLTree::deleteHelper(AVLNode *node, int student_ID) {
  // 1. Perform standard BST deletion
  if (node == nullptr) {
    return node;
  }

  if (student_ID < node->student_ID) {
    node->left = deleteHelper(node->left, student_ID);
  } else if (student_ID > node->student_ID) {
    node->right = deleteHelper(node->right, student_ID);
  } else {
    // Node to be deleted found

    // Case 1 & 2: Node with 0 or 1 child
    if (node->left == nullptr) {
      AVLNode *temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      AVLNode *temp = node->left;
      delete node;
      return temp;
    }

    // Case 3: Node with 2 children
    // Get in-order successor (smallest in right subtree)
    AVLNode *temp = findMinNode(node->right);

    // Copy successor's data to this node
    node->student_ID = temp->student_ID;
    node->name = temp->name;
    node->course = temp->course;
    node->grade = temp->grade;
    node->GPA = temp->GPA;

    // Delete the in-order successor
    node->right = deleteHelper(node->right, temp->student_ID);
  }

  // If tree had only one node
  if (node == nullptr) {
    return node;
  }

  // 2. Update height and get balance
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  int balance = getBalance(node);

  // 3. Perform rotations if unbalanced (4 cases)

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

// ==================== DSA5: DISPLAY OPERATION ====================

/**
 * Public display function
 */
void AVLTree::display() {
  if (isEmpty()) {
    std::cout << "\nNo student records to display." << std::endl;
    return;
  }

  std::cout << "\n" << std::string(80, '=') << std::endl;
  std::cout << "STUDENT GRADE RECORDS (Sorted by Student ID)" << std::endl;
  std::cout << std::string(80, '=') << std::endl;
  std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "Name"
            << std::setw(20) << "Course" << std::setw(10) << "Grade"
            << std::setw(10) << "GPA" << std::endl;
  std::cout << std::string(80, '-') << std::endl;

  inorderTraversal(root);

  std::cout << std::string(80, '=') << std::endl;
}

/**
 * Recursive in-order traversal
 * Visits nodes in sorted order: Left -> Root -> Right
 * Time Complexity: O(n)
 */
void AVLTree::inorderTraversal(AVLNode *node) {
  if (node != nullptr) {
    // 1. Recurse on left subtree (smaller IDs)
    inorderTraversal(node->left);

    // 2. Visit current node (print data)
    std::cout << std::left << std::setw(10) << node->student_ID << std::setw(20)
              << node->name << std::setw(20) << node->course << std::setw(10)
              << std::fixed << std::setprecision(2) << node->grade
              << std::setw(10) << std::fixed << std::setprecision(2)
              << node->GPA << std::endl;

    // 3. Recurse on right subtree (larger IDs)
    inorderTraversal(node->right);
  }
}

// ==================== DSA6: SAVE TO FILE OPERATION ====================

/**
 * Save all records to CSV file
 * Time Complexity: O(n)
 */
void AVLTree::saveToFile(const std::string &filename) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    std::cout << "Error: Could not open file '" << filename << "' for writing."
              << std::endl;
    return;
  }

  // Write CSV header
  file << "StudentID,Name,Course,Grade,GPA" << std::endl;

  // Write all records using in-order traversal
  saveToFileHelper(root, file);

  file.close();
  std::cout << "Data successfully saved to '" << filename << "'." << std::endl;
}

/**
 * Recursive helper for saving to file
 * Performs in-order traversal to write records in sorted order
 */
void AVLTree::saveToFileHelper(AVLNode *node, std::ofstream &file) {
  if (node != nullptr) {
    // Save left subtree
    saveToFileHelper(node->left, file);

    // Write current node data as CSV line
    file << node->student_ID << "," << node->name << "," << node->course << ","
         << std::fixed << std::setprecision(2) << node->grade << ","
         << std::fixed << std::setprecision(2) << node->GPA << std::endl;

    // Save right subtree
    saveToFileHelper(node->right, file);
  }
}

// ==================== DSA7: LOAD FROM FILE OPERATION ====================

/**
 * Load records from CSV file
 * Time Complexity: O(n log n) - n insertions, each taking O(log n)
 */
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
      continue; // Skip empty lines
    }

    // Parse CSV line
    std::stringstream ss(line);
    std::string token;

    int student_ID;
    std::string name, course;
    float grade, GPA;

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

      // Parse GPA
      std::getline(ss, token, ',');
      GPA = std::stof(token);

      // Insert into AVL tree (automatically maintains balance)
      insert(student_ID, name, course, grade, GPA);
      count++;

    } catch (const std::exception &e) {
      std::cout << "Error parsing line: " << line << std::endl;
      continue;
    }
  }

  file.close();
  std::cout << "Successfully loaded " << count << " records from '" << filename
            << "'." << std::endl;
}
