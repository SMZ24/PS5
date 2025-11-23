/**
 * AVLTree.h
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Defines the AVLTree class - a self-balancing binary search tree
 * for efficient student grade management. Supports multiple courses per
 * student.
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
                        const std::string &course, float grade);
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
   * Insert a new course for a student
   * If student exists, adds course to their record
   * If student doesn't exist, creates new student with this course
   * Time Complexity: O(log n)
   */
  void insert(int student_ID, const std::string &name,
              const std::string &course, float grade);

  /**
   * Search for a student record by ID
   * Time Complexity: O(log n)
   * @return Pointer to the node if found, nullptr otherwise
   */
  AVLNode *search(int student_ID);

  /**
   * Update a specific course grade for a student
   * Time Complexity: O(log n)
   * @return true if update successful, false if student or course not found
   */
  bool updateCourse(int student_ID, const std::string &courseName,
                    float newGrade);

  /**
   * Add a new course to an existing student
   * Time Complexity: O(log n)
   * @return true if successful, false if student not found or course exists
   */
  bool addCourseToStudent(int student_ID, const std::string &courseName,
                          float grade);

  /**
   * Delete a specific course from a student
   * Time Complexity: O(log n)
   * @return true if successful, false otherwise
   */
  bool deleteCourse(int student_ID, const std::string &courseName);

  /**
   * Delete an entire student record
   * Time Complexity: O(log n)
   */
  void deleteStudent(int student_ID);

  /**
   * Display all student records in sorted order (by student ID)
   * Shows all courses for each student
   * Time Complexity: O(n * m) where m is avg courses per student
   */
  void display();

  /**
   * Save all student records to a CSV file
   * Time Complexity: O(n * m)
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
