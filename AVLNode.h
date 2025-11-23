/**
 * AVLNode.h
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Defines the AVLNode class representing a single node in the AVL Tree.
 * Each node stores student information: ID, name, and multiple courses with
 * grades. GPA is automatically calculated from all courses.
 */

#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>
#include <utility> // for pair
#include <vector>

// Structure to hold course information
struct CourseRecord {
  std::string courseName;
  float grade;

  CourseRecord(const std::string &name, float g) : courseName(name), grade(g) {}
};

class AVLNode {
private:
  int student_ID;
  std::string name;
  std::vector<CourseRecord> courses; // Multiple courses and grades
  float GPA;
  int height;
  AVLNode *left;
  AVLNode *right;

  // Helper function to calculate GPA from all courses
  void calculateGPA();

public:
  /**
   * Constructor - Creates a new AVL node with student data
   * @param id Student ID (unique identifier)
   * @param n Student name
   * @param c Course name
   * @param g Grade
   */
  AVLNode(int id, const std::string &n, const std::string &c, float g);

  // Getters
  int getStudentID() const;
  std::string getName() const;
  float getGPA() const;
  int getHeight() const;
  AVLNode *getLeft() const;
  AVLNode *getRight() const;
  const std::vector<CourseRecord> &getCourses() const;
  int getCourseCount() const;

  // Course management
  void addCourse(const std::string &courseName, float grade);
  bool updateCourse(const std::string &courseName, float newGrade);
  bool deleteCourse(const std::string &courseName);
  bool hasCourse(const std::string &courseName) const;

  // Setters
  void setHeight(int h);
  void setLeft(AVLNode *l);
  void setRight(AVLNode *r);

  // Friend class to allow AVLTree to access private members
  friend class AVLTree;
};

#endif // AVLNODE_H
