/**
 * AVLNode.cpp
 * Student Grade Monitoring System - PS5
 * CSC 307 Data Structures and Algorithm Analysis, Fall 2025
 *
 * Implementation of AVLNode class methods supporting multiple courses per
 * student.
 */

#include "AVLNode.h"
#include <algorithm>

// Constructor
AVLNode::AVLNode(int id, const std::string &n, const std::string &c, float g)
    : student_ID(id), name(n), GPA(0.0), height(1), left(nullptr),
      right(nullptr) {
  courses.push_back(CourseRecord(c, g));
  calculateGPA();
}

// Helper function to convert numeric grade to GPA using American letter grade
// system
float gradeToGPA(float grade) {
  if (grade >= 90.0)
    return 4.0; // A
  else if (grade >= 80.0)
    return 3.0; // B
  else if (grade >= 70.0)
    return 2.0; // C
  else if (grade >= 60.0)
    return 1.0; // D
  else
    return 0.0; // F
}

// Calculate GPA from all courses (average of letter grade GPAs using American
// grading system)
void AVLNode::calculateGPA() {
  if (courses.empty()) {
    GPA = 0.0;
    return;
  }

  float totalGradePoints = 0.0;
  for (const auto &course : courses) {
    // Convert grade (0-100) to GPA using letter grade system
    float courseGPA = gradeToGPA(course.grade);
    totalGradePoints += courseGPA;
  }

  GPA = totalGradePoints / courses.size();
}

// Add a new course
void AVLNode::addCourse(const std::string &courseName, float grade) {
  courses.push_back(CourseRecord(courseName, grade));
  calculateGPA();
}

// Update an existing course grade
bool AVLNode::updateCourse(const std::string &courseName, float newGrade) {
  for (auto &course : courses) {
    if (course.courseName == courseName) {
      course.grade = newGrade;
      calculateGPA();
      return true;
    }
  }
  return false;
}

// Delete a course
bool AVLNode::deleteCourse(const std::string &courseName) {
  for (auto it = courses.begin(); it != courses.end(); ++it) {
    if (it->courseName == courseName) {
      courses.erase(it);
      calculateGPA();
      return true;
    }
  }
  return false;
}

// Check if student has a specific course
bool AVLNode::hasCourse(const std::string &courseName) const {
  for (const auto &course : courses) {
    if (course.courseName == courseName) {
      return true;
    }
  }
  return false;
}

// Getters
int AVLNode::getStudentID() const { return student_ID; }

std::string AVLNode::getName() const { return name; }

float AVLNode::getGPA() const { return GPA; }

int AVLNode::getHeight() const { return height; }

AVLNode *AVLNode::getLeft() const { return left; }

AVLNode *AVLNode::getRight() const { return right; }

const std::vector<CourseRecord> &AVLNode::getCourses() const { return courses; }

int AVLNode::getCourseCount() const { return courses.size(); }

// Setters
void AVLNode::setHeight(int h) { height = h; }

void AVLNode::setLeft(AVLNode *l) { left = l; }

void AVLNode::setRight(AVLNode *r) { right = r; }
