/**
 * AVLNode.cpp
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Implementation of AVLNode class methods.
 */

#include "AVLNode.h"

// Constructor
AVLNode::AVLNode(int id, const std::string &n, const std::string &c, float g,
                 float gpa)
    : student_ID(id), name(n), course(c), grade(g), GPA(gpa), height(1),
      left(nullptr), right(nullptr) {}

// Getters
int AVLNode::getStudentID() const { return student_ID; }

std::string AVLNode::getName() const { return name; }

std::string AVLNode::getCourse() const { return course; }

float AVLNode::getGrade() const { return grade; }

float AVLNode::getGPA() const { return GPA; }

int AVLNode::getHeight() const { return height; }

AVLNode *AVLNode::getLeft() const { return left; }

AVLNode *AVLNode::getRight() const { return right; }

// Setters
void AVLNode::setGrade(float g) { grade = g; }

void AVLNode::setGPA(float gp) { GPA = gp; }

void AVLNode::setHeight(int h) { height = h; }

void AVLNode::setLeft(AVLNode *l) { left = l; }

void AVLNode::setRight(AVLNode *r) { right = r; }
