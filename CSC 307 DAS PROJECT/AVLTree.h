/**
 * AVLTree.h
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Defines the AVLTree class - a self-balancing binary search tree
 * for efficient student grade management.
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <string>

class AVLTree {
private:
  AVLNode *root;

  // Helper functions for AVL operations
  int getHeight(AVLNode *node);
  int getBalance(AVLNode *node);
  AVLNode *rotateLeft(AVLNode *node);
  AVLNode *rotateRight(AVLNode *node);
  AVLNode *findMinNode(AVLNode *node);

  // Recursive helper functions
  AVLNode *insertHelper(AVLNode *node, int student_ID, const std::string &name,
                        const std::string &course, float grade, float GPA);
  AVLNode *deleteHelper(AVLNode *node, int student_ID);
  AVLNode *searchHelper(AVLNode *node, int student_ID);
  void inorderTraversal(AVLNode *node);
  void saveToFileHelper(AVLNode *node, std::ofstream &file);
  void destroyTree(AVLNode *node);

public:
  /**
   * Constructor - Creates an empty AVL tree
   */
  AVLTree();

  /**
   * Destructor - Cleans up all nodes in the tree
   */
  ~AVLTree();

  /**
   * Insert a new student grade record into the AVL tree
   * Time Complexity: O(log n)
   */
  void insert(int student_ID, const std::string &name,
              const std::string &course, float grade, float GPA);

  /**
   * Search for a student record by ID
   * Time Complexity: O(log n)
   * @return Pointer to the node if found, nullptr otherwise
   */
  AVLNode *search(int student_ID);

  /**
   * Update the grade and GPA of an existing student record
   * Time Complexity: O(log n)
   * @return true if update successful, false if student not found
   */
  bool update(int student_ID, float grade, float GPA);

  /**
   * Delete a student record by ID
   * Time Complexity: O(log n)
   */
  void deleteNode(int student_ID);

  /**
   * Display all student records in sorted order (by student ID)
   * Time Complexity: O(n)
   */
  void display();

  /**
   * Save all student records to a CSV file
   * Time Complexity: O(n)
   */
  void saveToFile(const std::string &filename);

  /**
   * Load student records from a CSV file
   * Time Complexity: O(n log n)
   */
  void loadFromFile(const std::string &filename);

  /**
   * Check if the tree is empty
   */
  bool isEmpty() const;
};

#endif // AVLTREE_H
