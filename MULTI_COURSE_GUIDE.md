# Multi-Course Student Grade System - Quick Guide

**CSC 307 Data Structures - Team PS5**

## 🎓 New Features

### ✨ What's Changed?

The system now supports **multiple courses per student** with automatic GPA calculation!

### 📊 Key Features

1. **Multiple Courses Per Student**

   - Each student can have unlimited courses
   - GPA is automatically calculated from all courses
   - Each course stores its own grade

2. **Automatic GPA Calculation**

   - GPA = Average of all course grades converted to 4.0 scale
   - Formula: `(grade / 100) * 4.0` for each course, then averaged
   - Updates automatically when courses are added/updated/deleted

3. **Smart Insert Operation**
   - If student ID exists: Adds new course to existing student
   - If student ID doesn't exist: Creates new student with first course

---

## 📝 Example Usage

### Example 1: Adding Multiple Courses for Same Student

```
Step 1: Add first course
- Student ID: 1
- Name: John Doe
- Course: Mathematics
- Grade: 90
Result: New student created, GPA = 3.60

Step 2: Add second course (same ID)
- Student ID: 1  (already exists!)
- Course: Science
- Grade: 80
Result: Course added to John Doe, GPA = 3.40 (average of 90 and 80)

Step 3: Add third course (same ID)
- Student ID: 1
- Course: History
- Grade: 95
Result: Course added, GPA = 3.53 (average of 90, 80, 95)
```

### Example 2: Display Output

```
Student ID: 1 | Name: John Doe | Overall GPA: 3.53 | Courses: 3
--------------------------------------------------------------------------------
  Course                                  Grade          Letter Grade
  ----------------------------------------------------------------------
  Mathematics                             90.00          A
  Science                                 80.00          B
  History                                 95.00          A
```

---

## 🎮 Menu Options Explained

### 1. Add Grade (New Student/Course)

- **If student ID is NEW**: Creates new student with this course
- **If student ID EXISTS**: Adds this course to the student's record
- GPA recalculates automatically

### 2. Search Student

- Shows ALL courses for the student
- Displays individual grades + letter grades
- Shows overall GPA and course count

### 3. Update Course Grade

- Lists all courses for the student
- Select course to update
- Enter new grade → GPA recalculates automatically

### 4. Delete Record

Two options:

- **Delete specific course**: Removes one course, keeps student
- **Delete entire student**: Removes student and all courses
- Note: Cannot delete a student's only course (must delete student instead)

### 5. Display All Students

- Shows all students in sorted order by ID
- Each student displays ALL their courses
- Shows overall GPA for each student

### 6-7. Save/Load Data

- CSV format: One row per course
- Same student ID appears on multiple rows for multiple courses
- GPA is recalculated on load (stored GPA is for reference only)

---

## 📁 CSV File Format

```csv
StudentID,Name,Course,Grade,GPA
1,John Doe,Mathematics,90.00,3.60
1,John Doe,Science,80.00,3.40
1,John Doe,History,95.00,3.53
2,Jane Smith,Mathematics,85.00,3.40
2,Jane Smith,English,88.00,3.46
```

**Important Notes:**

- Same StudentID can appear multiple times (one per course)
- Name must be identical for all rows of same student
- GPA in file is for display only; actual GPA is recalculated

---

## 🔢 GPA Calculation Details

### Formula

```
For each course:
  course_gpa = (grade / 100) * 4.0

Overall GPA = (sum of all course_gpas) / (number of courses)
```

### Examples

```
Course 1: 90/100 → 3.60
Course 2: 80/100 → 3.20
Course 3: 95/100 → 3.80

Overall GPA = (3.60 + 3.20 + 3.80) / 3 = 3.53
```

### Grade to GPA Conversion

| Grade Range | Letter | GPA (per course) |
| ----------- | ------ | ---------------- |
| 90-100      | A      | 3.60 - 4.00      |
| 80-89       | B      | 3.20 - 3.56      |
| 70-79       | C      | 2.80 - 3.16      |
| 60-69       | D      | 2.40 - 2.76      |
| 0-59        | F      | 0.00 - 2.36      |

---

## ⚠️ Important Notes

1. **Student ID is the unique key** - you cannot have different students with the same ID
2. **Course names are case-sensitive** - "Math" and "math" are different courses
3. **Minimum 1 course per student** - cannot delete a student's only course
4. **GPA updates automatically** - you never manually set GPA
5. **Adding duplicate course** - will show a warning, use Update instead

---

## 🧪 Testing Scenarios

### Scenario 1: New Student with Multiple Courses

1. Add Grade → ID: 100, Name: Test Student, Course: Math, Grade: 90
2. Add Grade → ID: 100, Course: Science, Grade: 85
3. Search → ID: 100 (should show both courses, GPA ~3.50)

### Scenario 2: Update and GPA Recalculation

1. Add three courses for student ID 200
2. Update one course grade
3. Verify GPA changed automatically

### Scenario 3: Delete Course

1. Add multiple courses for student ID 300
2. Delete Record → Option 1 (specific course)
3. Verify course removed and GPA recalculated

### Scenario 4: File Save/Load

1. Add multiple students with multiple courses each
2. Save to file
3. Exit program
4. Restart and load file
5. Verify all courses loaded correctly

---

## 🔧 Technical Details

### Data Structures

- **AVLNode**: Contains `vector<CourseRecord>` for multiple courses
- **CourseRecord**: Struct with `courseName` and `grade`
- **GPA**: Calculated field (not stored for courses, only for student)

### Time Complexity

| Operation                   | Complexity   | Notes                                |
| --------------------------- | ------------ | ------------------------------------ |
| Insert Course (new student) | O(log n)     | Standard AVL insert                  |
| Insert Course (existing)    | O(log n + m) | Find student + add to vector         |
| Update Course               | O(log n + m) | Find student + linear search courses |
| Delete Course               | O(log n + m) | Find student + linear search + erase |
| Delete Student              | O(log n)     | Standard AVL delete                  |
| Display                     | O(n \* m)    | Visit all students and all courses   |

Where: n = number of students, m = average courses per student

---

## 💡 Pro Tips

1. **Use consistent course names** - "Data Structures" not "data structures" or "DS"
2. **Plan your course names** - easier to update if names are consistent
3. **Regular saves** - save after adding multiple courses
4. **Check GPA after updates** - verify calculations are as expected
5. **Use Search before Update** - see what courses exist before updating

---

## 🐛 Common Questions

**Q: Can I change a student's name?**
A: No, names are set when the student is first created. Delete and re-add if needed.

**Q: What if I add the same course twice?**
A: System will warn you and not add duplicate. Use Update instead.

**Q: Can GPA be manually set?**
A: No, GPA is always calculated from course grades. This ensures accuracy.

**Q: Why does file show GPA for each row?**
A: For CSV readability. The actual GPA is recalculated when loading.

**Q: Can a student have zero courses?**
A: No, students must have at least one course. Delete the student if needed.

---

## 📚 Example Test Data

Use this sample data to test:

```csv
StudentID,Name,Course,Grade,GPA
10001,Alice Johnson,Data Structures,95.50,3.78
10001,Alice Johnson,Algorithms,92.00,3.78
10001,Alice Johnson,Operating Systems,85.00,3.78
10002,Bob Smith,Data Structures,88.00,3.52
10002,Bob Smith,Calculus,82.00,3.52
```

---

**Updated by Team PS5 - Fall 2025**

