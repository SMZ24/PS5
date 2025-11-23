# Major Update: Multi-Course Support

**Date**: November 19, 2025  
**Team**: PS5 (Prashant Chand, Sambhav Pyakurel, Sujal Maharjan)  
**Version**: 2.0 - Multi-Course Edition

---

## 🎯 What Changed?

The Student Grade Monitoring System has been **completely redesigned** to support **multiple courses per student** with **automatic GPA calculation**.

---

## 🔄 Major Changes

### 1. Data Structure Redesign

**Before (v1.0):**

```cpp
class AVLNode {
    int student_ID;
    string name;
    string course;        // Single course
    float grade;          // Single grade
    float GPA;            // Manually set
};
```

**After (v2.0):**

```cpp
struct CourseRecord {
    string courseName;
    float grade;
};

class AVLNode {
    int student_ID;
    string name;
    vector<CourseRecord> courses;  // Multiple courses!
    float GPA;                      // Auto-calculated!
};
```

### 2. Insert Operation Changes

**Before:**

- Insert with ID that exists → Error (duplicate)

**After:**

- Insert with ID that exists → Adds course to student
- Insert with new ID → Creates new student

**Example:**

```
// First insert
insert(1, "John", "Math", 90)
→ Creates student 1 with Math course, GPA = 3.60

// Second insert (SAME ID!)
insert(1, "John", "Science", 80)
→ Adds Science to student 1, GPA = 3.40 (average)
```

### 3. New Operations

| Operation              | Description                        |
| ---------------------- | ---------------------------------- |
| `addCourseToStudent()` | Add new course to existing student |
| `updateCourse()`       | Update specific course grade       |
| `deleteCourse()`       | Delete specific course             |
| `deleteStudent()`      | Delete entire student record       |
| `getCourses()`         | Get all courses for student        |
| `getCourseCount()`     | Get number of courses              |

### 4. Automatic GPA Calculation

**Formula:**

```
For each course: courseGPA = (grade / 100) * 4.0
Overall GPA = average of all courseGPAs
```

**Example:**

```
Math: 90 → 3.60
Science: 80 → 3.20
History: 95 → 3.80

GPA = (3.60 + 3.20 + 3.80) / 3 = 3.53 ✓
```

### 5. Display Changes

**Before:**

```
ID    Name         Course           Grade    GPA
1     John Doe     Mathematics      90.00    3.60
```

**After:**

```
Student ID: 1 | Name: John Doe | Overall GPA: 3.53 | Courses: 3
----------------------------------------------------------------------
  Course                                  Grade          Letter Grade
  --------------------------------------------------------------------
  Mathematics                             90.00          A
  Science                                 80.00          B
  History                                 95.00          A
```

### 6. CSV Format Changes

**Before (One student = One row):**

```csv
StudentID,Name,Course,Grade,GPA
1,John Doe,Mathematics,90.00,3.60
2,Jane Smith,Science,85.00,3.40
```

**After (One course = One row):**

```csv
StudentID,Name,Course,Grade,GPA
1,John Doe,Mathematics,90.00,3.53
1,John Doe,Science,80.00,3.53
1,John Doe,History,95.00,3.53
2,Jane Smith,Science,85.00,3.40
```

---

## 📊 Impact on Operations

### Time Complexity Changes

| Operation       | Before   | After        | Notes                     |
| --------------- | -------- | ------------ | ------------------------- |
| Insert          | O(log n) | O(log n)     | Same for new student      |
| Insert existing | N/A      | O(log n + m) | m = courses per student   |
| Update          | O(log n) | O(log n + m) | Must find specific course |
| Display         | O(n)     | O(n × m)     | Shows all courses         |

**m is typically small (< 10 courses), so impact is minimal**

---

## 🔧 Implementation Details

### Files Modified

1. **AVLNode.h** → Added CourseRecord struct, vector of courses
2. **AVLNode.cpp** → Implemented course management methods
3. **AVLTree.h** → Updated operation signatures
4. **AVLTree.cpp** → Rewrote insert, update, delete, display
5. **main.cpp** → Updated menu and user interactions

### New Classes/Structures

```cpp
struct CourseRecord {
    string courseName;
    float grade;
    CourseRecord(const string& name, float g);
};
```

### New Methods in AVLNode

```cpp
void calculateGPA();              // Auto-calc GPA from courses
void addCourse(string, float);    // Add new course
bool updateCourse(string, float); // Update course grade
bool deleteCourse(string);        // Remove course
bool hasCourse(string);           // Check if course exists
```

---

## 🎮 User Experience Changes

### Menu Updated

```
1. Add Grade (New Student/Course)     ← Updated description
2. Search Student                     ← Shows all courses now
3. Update Course Grade                ← Must specify course
4. Delete Record                      ← Choose course or student
5. Display All Students               ← Shows all courses
6. Save Data to File
7. Load Data from File
8. Exit
```

### Smart Insert Behavior

When adding a grade:

1. System checks if student ID exists
2. **If YES**: Automatically adds course to existing student
3. **If NO**: Creates new student with this course

**User sees:**

```
✓ Student ID 1 already exists: John Doe
Current courses: 2
Current GPA: 3.40

Adding a new course for this student...

Course Name: History
Grade: 95

Course 'History' added to student ID 1.
GPA updated to 3.53
Total courses: 3
```

---

## 📁 Project Files

### New Files

- `MULTI_COURSE_GUIDE.md` → Complete usage guide
- `CHANGES.md` → This file

### Updated Files

- `AVLNode.h` / `AVLNode.cpp`
- `AVLTree.h` / `AVLTree.cpp`
- `main.cpp`
- `compile.bat`
- `student_grades.csv` (sample data)

---

## ✅ Testing Performed

### Test 1: Multiple Courses

- ✓ Add student with first course
- ✓ Add second course to same student
- ✓ Add third course to same student
- ✓ Verify GPA updates correctly

### Test 2: Course Operations

- ✓ Update specific course grade
- ✓ Delete specific course
- ✓ Verify GPA recalculates
- ✓ Prevent deleting only course

### Test 3: File I/O

- ✓ Save multi-course data to CSV
- ✓ Load multi-course data from CSV
- ✓ Verify courses grouped by student
- ✓ Verify GPA recalculated on load

### Test 4: Display

- ✓ Display shows all courses per student
- ✓ Letter grades calculated correctly
- ✓ Overall GPA displayed
- ✓ Course count shown

---

## 🐛 Known Limitations

1. **Course names are case-sensitive** - "Math" ≠ "math"
2. **Cannot rename courses** - must delete and re-add
3. **Cannot reorder courses** - displayed in insertion order
4. **Minimum 1 course per student** - cannot have 0 courses
5. **Simple GPA calculation** - doesn't account for credit hours

---

## 🚀 Backward Compatibility

### Old CSV Files

Old CSV files (one row per student) will still load, but:

- Each student will have exactly 1 course
- Can add more courses after loading

### Converting Old Data

1. Load old CSV
2. Add additional courses via menu
3. Save to create new multi-course CSV

---

## 📈 Future Enhancements

Possible additions for future versions:

- Credit hours for weighted GPA
- Semester/term organization
- Grade history/transcripts
- Course prerequisites tracking
- Statistical analysis (class averages)
- Export to different formats

---

## 👥 Developer Notes

### For Team Members

Key architectural decisions:

1. Used `vector<CourseRecord>` for simplicity
2. GPA always calculated, never stored in courses
3. Insert behavior changed to auto-add courses
4. CSV format: one row per course (not per student)

### For Future Developers

To add new features:

- Course management is in `AVLNode` class
- Tree operations are in `AVLTree` class
- Always call `calculateGPA()` after course changes
- Maintain AVL balance properties

---

## 📞 Support

For questions or issues:

- **Team**: PS5
- **Course**: CSC 307 - Fall 2025
- **Documentation**: See MULTI_COURSE_GUIDE.md

---

**Version History:**

- v1.0 (Initial) - Single course per student
- v2.0 (Current) - Multiple courses with auto GPA calculation

---

_Last Updated: November 19, 2025_

