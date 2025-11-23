/**
 * AVLNode.h
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Defines the AVLNode class representing a single node in the AVL Tree.
 * Each node stores student information: ID, name, course, grade, and GPA.
 */

#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>

class AVLNode {
private:
  int student_ID;
  std::string name;
  std::string course;
  float grade;
  float GPA;
  int height;
  AVLNode *left;
  AVLNode *right;

public:
  /**
   * Constructor - Creates a new AVL node with student data
   * @param id Student ID (unique identifier)
   * @param n Student name
   * @param c Course name
   * @param g Grade
   * @param gpa GPA
   */
  AVLNode(int id, const std::string &n, const std::string &c, float g,
          float gpa);

  // Getters
  int getStudentID() const;
  std::string getName() const;
  std::string getCourse() const;
  float getGrade() const;
  float getGPA() const;
  int getHeight() const;
  AVLNode *getLeft() const;
  AVLNode *getRight() const;

  // Setters
  void setGrade(float g);
  void setGPA(float gp);
  void setHeight(int h);
  void setLeft(AVLNode *l);
  void setRight(AVLNode *r);

  // Friend class to allow AVLTree to access private members
  friend class AVLTree;
};

#endif // AVLNODE_H
