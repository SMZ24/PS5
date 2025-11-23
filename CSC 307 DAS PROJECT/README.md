# Student Grade Monitoring System

**CSC 307 Data Structures and Algorithm Analysis - Fall 2025**  
**Team PS5**

## Team Members

- Prashant Chand
- Sambhav Pyakurel
- Sujal Maharjan

---

## Project Overview

The **Student Grade Monitoring System** is a command-line application designed to efficiently manage and monitor student grades using an **AVL Tree** data structure. The system provides fast operations for adding, searching, updating, deleting, and displaying student grade records while maintaining data integrity through automatic tree balancing.

### Key Features

- ✅ Add new student grade records
- 🔍 Search for student records by ID
- 📝 Update existing grades and GPAs
- 🗑️ Delete student records
- 📊 Display all records in sorted order
- 💾 Save data to CSV file for persistence
- 📂 Load data from CSV file
- ⚖️ Automatic AVL tree balancing for O(log n) performance

---

## Problem Addressed

Manually managing grades for multiple students across various courses can be:

- **Inefficient**: Linear search through unorganized data
- **Error-prone**: Manual tracking and calculations
- **Time-consuming**: Difficult to maintain sorted records

This system solves these problems by:

- Using an **AVL Tree** for automatically balanced, efficient operations
- Providing **O(log n)** time complexity for insert, search, update, and delete
- Maintaining records in **sorted order** by student ID
- Offering **persistent storage** via CSV files

---

## Technical Implementation

### Primary Data Structure: AVL Tree

An **AVL Tree** (Adelson-Velsky and Landis Tree) is a self-balancing binary search tree where the height difference between left and right subtrees is at most 1. This guarantees:

- **Insert**: O(log n)
- **Search**: O(log n)
- **Update**: O(log n)
- **Delete**: O(log n)
- **Display**: O(n) - in-order traversal

#### Why AVL Tree?

Unlike a standard Binary Search Tree (BST) which can degrade to O(n) performance when unbalanced, an AVL Tree maintains balance through **rotations** after insertions and deletions:

- **Left-Left Rotation** (LL)
- **Right-Right Rotation** (RR)
- **Left-Right Rotation** (LR)
- **Right-Left Rotation** (RL)

### Data Structure Components

#### AVLNode Class

Each node contains:

- `student_ID` (int) - Unique identifier
- `name` (string) - Student name
- `course` (string) - Course name
- `grade` (float) - Grade (0-100)
- `GPA` (float) - GPA (0.0-4.0)
- `height` (int) - Height of node for balancing
- `left` (AVLNode\*) - Left child pointer
- `right` (AVLNode\*) - Right child pointer

#### AVLTree Class

Provides operations:

- `insert()` - Add new record with automatic balancing
- `search()` - Find record by student ID
- `update()` - Modify grade and GPA
- `deleteNode()` - Remove record with rebalancing
- `display()` - Show all records in sorted order
- `saveToFile()` - Export data to CSV
- `loadFromFile()` - Import data from CSV

---

## File Structure

```
CSC 307 DAS PROJECT/
│
├── AVLNode.h              # AVLNode class header
├── AVLNode.cpp            # AVLNode implementation
├── AVLTree.h              # AVLTree class header
├── AVLTree.cpp            # AVLTree implementation
├── main.cpp               # Main program with menu interface
├── Makefile               # Build configuration
├── README.md              # This file
└── student_grades.csv     # Sample data file (generated)
```

---

## Compilation and Execution

### Prerequisites

- C++ compiler with C++11 support (g++, clang++, etc.)
- Make (optional, for using Makefile)

### Compilation Options

#### Option 1: Using Makefile (Recommended)

```bash
# Build the program
make

# Run the program
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild
```

#### Option 2: Manual Compilation

```bash
# Compile all source files
g++ -std=c++11 -Wall -Wextra -o GradeSystem main.cpp AVLNode.cpp AVLTree.cpp

# Run the program
./GradeSystem
```

#### Option 3: Windows (Command Prompt)

```cmd
# Compile
g++ -std=c++11 -Wall -Wextra -o GradeSystem.exe main.cpp AVLNode.cpp AVLTree.cpp

# Run
GradeSystem.exe
```

---

## Usage Guide

### Main Menu

When you run the program, you'll see the following menu:

```
========================================
          MAIN MENU
========================================
1. Add Grade
2. Search Grade
3. Update Grade
4. Delete Grade
5. Display All Grades
6. Save Data to File
7. Load Data from File
8. Exit
========================================
```

### 1. Add Grade

Adds a new student record to the system.

**Input:**

- Student ID (positive integer)
- Student Name (string)
- Course Name (string)
- Grade (0-100)
- GPA (0.0-4.0)

**Example:**

```
Enter Student ID: 12345
Enter Student Name: John Doe
Enter Course Name: Data Structures
Enter Grade (0-100): 95.5
Enter GPA (0.0-4.0): 3.8
```

### 2. Search Grade

Search for a student record by ID.

**Input:**

- Student ID

**Output:**

- Complete student information if found
- Error message if not found

### 3. Update Grade

Modify the grade and GPA of an existing student.

**Input:**

- Student ID
- New Grade (0-100)
- New GPA (0.0-4.0)

### 4. Delete Grade

Remove a student record from the system.

**Input:**

- Student ID
- Confirmation (y/n)

### 5. Display All Grades

Shows all student records in sorted order by Student ID.

**Output Format:**

```
================================================================================
STUDENT GRADE RECORDS (Sorted by Student ID)
================================================================================
ID        Name                Course              Grade     GPA
--------------------------------------------------------------------------------
12345     John Doe            Data Structures     95.50     3.80
12346     Jane Smith          Algorithms          92.00     3.90
================================================================================
```

### 6. Save Data to File

Saves all records to a CSV file for persistent storage.

**Input:**

- Filename (or press Enter for default: `student_grades.csv`)

**CSV Format:**

```csv
StudentID,Name,Course,Grade,GPA
12345,John Doe,Data Structures,95.50,3.80
12346,Jane Smith,Algorithms,92.00,3.90
```

### 7. Load Data from File

Loads student records from a CSV file into the AVL tree.

**Input:**

- Filename (or press Enter for default: `student_grades.csv`)

**Note:** The tree is automatically balanced during the loading process.

### 8. Exit

Exits the program with an option to save data before closing.

---

## CSV File Format

The system uses CSV (Comma-Separated Values) format for data persistence:

```csv
StudentID,Name,Course,Grade,GPA
12345,John Doe,Data Structures,95.50,3.80
12346,Jane Smith,Algorithms,92.00,3.90
12347,Bob Johnson,Operating Systems,88.75,3.65
```

**Important Notes:**

- First line is the header (automatically added when saving)
- Student IDs must be unique
- Grades should be between 0-100
- GPAs should be between 0.0-4.0
- No commas allowed in Name or Course fields

---

## Algorithm Complexity Analysis

| Operation | Time Complexity | Space Complexity |
| --------- | --------------- | ---------------- |
| Insert    | O(log n)        | O(1)             |
| Search    | O(log n)        | O(1)             |
| Update    | O(log n)        | O(1)             |
| Delete    | O(log n)        | O(1)             |
| Display   | O(n)            | O(1)             |
| Save      | O(n)            | O(1)             |
| Load      | O(n log n)      | O(n)             |

**Where n = number of student records in the tree**

---

## AVL Tree Operations Explained

### Insert Operation

1. Perform standard BST insertion
2. Update heights of ancestors
3. Check balance factor at each ancestor
4. Perform rotations if needed:
   - **LL Case**: Right rotation
   - **RR Case**: Left rotation
   - **LR Case**: Left rotation on left child, then right rotation
   - **RL Case**: Right rotation on right child, then left rotation

### Delete Operation

1. Perform standard BST deletion (3 cases: 0, 1, or 2 children)
2. Update heights of ancestors
3. Check balance factor and rebalance if necessary

### Balance Factor

```
Balance Factor = Height(Left Subtree) - Height(Right Subtree)
```

- **Balanced**: Balance factor is -1, 0, or 1
- **Left-heavy**: Balance factor > 1
- **Right-heavy**: Balance factor < -1

---

## Sample Data

Here's some sample data you can use to test the system:

```csv
StudentID,Name,Course,Grade,GPA
10001,Alice Johnson,Data Structures,95.50,3.95
10002,Bob Smith,Algorithms,88.00,3.70
10003,Carol White,Operating Systems,92.50,3.85
10004,David Brown,Computer Networks,87.00,3.65
10005,Emily Davis,Database Systems,94.00,3.90
10006,Frank Miller,Software Engineering,89.50,3.75
10007,Grace Lee,Computer Architecture,91.00,3.80
10008,Henry Wilson,Artificial Intelligence,96.00,4.00
10009,Irene Martinez,Web Development,85.50,3.60
10010,Jack Thompson,Mobile Computing,93.50,3.88
```

Save this as `student_grades.csv` and use option 7 to load it into the system.

---

## Testing Guide

### Test Case 1: Basic Operations

1. Add 5 student records with different IDs
2. Display all records (verify sorted order)
3. Search for an existing student
4. Search for a non-existing student
5. Update a student's grade
6. Delete a student
7. Display again to verify deletion

### Test Case 2: AVL Balancing

1. Insert students in ascending order: 1, 2, 3, 4, 5
2. Tree should automatically balance (verify by display order)
3. Insert in descending order: 10, 9, 8, 7, 6
4. Tree should remain balanced

### Test Case 3: File I/O

1. Add several records
2. Save to file
3. Exit program
4. Restart program
5. Load from file
6. Verify all records are restored

### Test Case 4: Edge Cases

1. Try to insert duplicate student ID (should fail)
2. Try to update non-existing student (should fail)
3. Try to delete non-existing student (should fail)
4. Load from non-existing file (should show error)
5. Try invalid inputs (negative IDs, invalid grades)

---

## Error Handling

The system includes robust error handling for:

- ✅ Invalid input types (non-numeric input for numbers)
- ✅ Out-of-range values (negative IDs, grades > 100, GPA > 4.0)
- ✅ Duplicate student IDs
- ✅ Non-existing file operations
- ✅ Empty tree operations
- ✅ Invalid CSV file format

---

## Known Limitations

1. **Student ID must be unique** - No duplicate IDs allowed
2. **Name and Course cannot contain commas** - CSV format limitation
3. **File operations are not atomic** - Partial file corruption possible if interrupted
4. **In-memory only during runtime** - Must explicitly save to persist changes
5. **Single-threaded** - No concurrent access support

---

## Future Enhancements

Possible improvements for future versions:

- 📈 Add statistics (average grade, GPA distribution)
- 🔐 User authentication and access control
- 🔄 Support for updating name and course (currently only grade/GPA)
- 🔍 Search by name in addition to ID
- 📊 Export to other formats (JSON, XML)
- 💾 Database integration (SQLite, MySQL)
- 🖥️ GUI interface
- 📱 Multi-platform support

---

## References

### AVL Tree Implementation

1. "Insertion in an AVL Tree", kartik, GeeksforGeeks, July 23, 2025  
   URL: https://www.geeksforgeeks.org/dsa/insertion-in-an-avl-tree/

2. "Deletion in an AVL Tree", kartik, GeeksforGeeks, June 19, 2025  
   URL: https://www.geeksforgeeks.org/dsa/deletion-in-an-avl-tree/

3. "Inorder Traversal of Binary Tree", animeshdey, GeeksforGeeks, March 3, 2023  
   URL: https://www.geeksforgeeks.org/dsa/inorder-traversal-of-binary-tree/

---

## Troubleshooting

### Compilation Errors

**Problem:** `g++: command not found`  
**Solution:** Install g++ compiler:

- Ubuntu/Debian: `sudo apt-get install g++`
- macOS: `xcode-select --install`
- Windows: Install MinGW or use WSL

**Problem:** `error: 'string' is not a member of 'std'`  
**Solution:** Make sure `#include <string>` is present in header files

### Runtime Errors

**Problem:** Program crashes when loading file  
**Solution:** Check CSV file format, ensure no extra commas or malformed lines

**Problem:** "File not found" error  
**Solution:** Ensure the file is in the same directory as the executable, or provide full path

### Logic Errors

**Problem:** Display shows records in wrong order  
**Solution:** This shouldn't happen with AVL tree; check if data was properly inserted

**Problem:** Can't find recently added student  
**Solution:** Verify the student was successfully added (check for duplicate ID error)

---

## Contact & Support

For questions, issues, or suggestions:

- **Team PS5**
- **Course:** CSC 307 - Data Structures and Algorithm Analysis
- **Semester:** Fall 2025

---

## License

This project is created for educational purposes as part of CSC 307 coursework.

---

## Acknowledgments

- Course Instructor: Prof. Chad McDaniel
- GeeksforGeeks for AVL Tree algorithm references
- Team PS5 members for collaborative design and implementation

---

**End of Documentation**
