# Student Grade Monitoring System - Project Summary

**Team PS5**  
**CSC 307 Data Structures and Algorithm Analysis - Fall 2025**

---

## 📋 Quick Start Guide

### Compilation (Choose one method):

#### Windows:

```cmd
# Method 1: Use the batch file (easiest)
compile.bat

# Method 2: Manual compilation
g++ -std=c++11 -Wall -Wextra -o GradeSystem.exe main.cpp AVLNode.cpp AVLTree.cpp

# Run the program
GradeSystem.exe
```

#### Linux/Mac:

```bash
# Method 1: Use Makefile (recommended)
make
./GradeSystem

# Method 2: Manual compilation
g++ -std=c++11 -Wall -Wextra -o GradeSystem main.cpp AVLNode.cpp AVLTree.cpp
./GradeSystem
```

---

## 📁 Project Files

| File                 | Description                              |
| -------------------- | ---------------------------------------- |
| `AVLNode.h`          | AVL Node class header                    |
| `AVLNode.cpp`        | AVL Node implementation                  |
| `AVLTree.h`          | AVL Tree class header                    |
| `AVLTree.cpp`        | AVL Tree implementation (all operations) |
| `main.cpp`           | Main program with menu interface         |
| `Makefile`           | Build configuration for Linux/Mac        |
| `compile.bat`        | Build script for Windows                 |
| `README.md`          | Complete documentation                   |
| `PROJECT_SUMMARY.md` | This file (quick reference)              |
| `student_grades.csv` | Sample data file                         |

---

## 🎯 Implemented Operations

### Core AVL Tree Operations:

1. ✅ **Insert (DSA1)** - O(log n)

   - Standard BST insertion
   - Automatic height updates
   - Self-balancing with rotations (LL, RR, LR, RL)

2. ✅ **Search (DSA2)** - O(log n)

   - Binary search by student ID
   - Returns node pointer or nullptr

3. ✅ **Update (DSA3)** - O(log n)

   - Searches for student
   - Updates grade and GPA fields

4. ✅ **Delete (DSA4)** - O(log n)

   - Handles all 3 BST cases (0, 1, 2 children)
   - Rebalances tree after deletion

5. ✅ **Display (DSA5)** - O(n)

   - In-order traversal
   - Shows records sorted by student ID

6. ✅ **Save to File (DSA6)** - O(n)

   - Exports to CSV format
   - Uses in-order traversal

7. ✅ **Load from File (DSA7)** - O(n log n)
   - Imports from CSV
   - Automatically balances during insertion

---

## 🏗️ Architecture

```
┌─────────────────────────────────────┐
│         Main Program (main.cpp)     │
│  ┌───────────────────────────────┐  │
│  │    Menu-Driven Interface      │  │
│  └───────────────────────────────┘  │
└──────────────┬──────────────────────┘
               │
               ▼
┌─────────────────────────────────────┐
│       AVLTree Class (AVLTree.cpp)   │
│  ┌───────────────────────────────┐  │
│  │  • insert()                   │  │
│  │  • search()                   │  │
│  │  • update()                   │  │
│  │  • deleteNode()               │  │
│  │  • display()                  │  │
│  │  • saveToFile()               │  │
│  │  • loadFromFile()             │  │
│  └───────────────────────────────┘  │
└──────────────┬──────────────────────┘
               │
               ▼
┌─────────────────────────────────────┐
│       AVLNode Class (AVLNode.cpp)   │
│  ┌───────────────────────────────┐  │
│  │  Data:                        │  │
│  │  • student_ID (int)           │  │
│  │  • name (string)              │  │
│  │  • course (string)            │  │
│  │  • grade (float)              │  │
│  │  • GPA (float)                │  │
│  │  • height (int)               │  │
│  │  • left, right (AVLNode*)     │  │
│  └───────────────────────────────┘  │
└─────────────────────────────────────┘
```

---

## 📊 Time Complexity Summary

| Operation | Time Complexity | Why?                    |
| --------- | --------------- | ----------------------- |
| Insert    | O(log n)        | Balanced tree height    |
| Search    | O(log n)        | Binary search           |
| Update    | O(log n)        | Search + O(1) update    |
| Delete    | O(log n)        | Balanced deletion       |
| Display   | O(n)            | Visit all nodes         |
| Save      | O(n)            | Visit all nodes         |
| Load      | O(n log n)      | n insertions × O(log n) |

---

## 🔄 AVL Rotations Implemented

### 1. Left-Left (LL) Case → Right Rotation

```
      y                x
     / \              / \
    x   T3    =>    T1   y
   / \                  / \
  T1  T2               T2  T3
```

### 2. Right-Right (RR) Case → Left Rotation

```
    x                    y
   / \                  / \
  T1  y       =>       x   T3
     / \              / \
    T2  T3           T1  T2
```

### 3. Left-Right (LR) Case → Left + Right Rotation

```
      z                z              y
     / \              / \            / \
    x   T4    =>     y   T4   =>   x   z
   / \              / \            / \ / \
  T1  y            x  T3          T1 T2 T3 T4
     / \          / \
    T2  T3       T1  T2
```

### 4. Right-Left (RL) Case → Right + Left Rotation

```
    x                x                y
   / \              / \              / \
  T1  z     =>     T1  y      =>    x   z
     / \              / \          / \ / \
    y  T4            T2  z        T1 T2 T3 T4
   / \                  / \
  T2  T3               T3  T4
```

---

## 📝 CSV File Format

```csv
StudentID,Name,Course,Grade,GPA
10001,Alice Johnson,Data Structures,95.50,3.95
10002,Bob Smith,Algorithms,88.00,3.70
10003,Carol White,Operating Systems,92.50,3.85
```

**Rules:**

- First line is header (auto-generated)
- Student IDs must be unique positive integers
- Grades: 0-100
- GPA: 0.0-4.0
- No commas in names or course names

---

## 🧪 Testing Checklist

- [ ] **Basic Operations**

  - [ ] Add multiple students
  - [ ] Search existing student
  - [ ] Search non-existing student
  - [ ] Update student grade
  - [ ] Delete student
  - [ ] Display all students

- [ ] **AVL Balancing**

  - [ ] Insert in ascending order (1, 2, 3, 4, 5)
  - [ ] Insert in descending order (10, 9, 8, 7, 6)
  - [ ] Insert randomly
  - [ ] Verify sorted display

- [ ] **File I/O**

  - [ ] Save data to file
  - [ ] Exit and restart program
  - [ ] Load data from file
  - [ ] Verify data integrity

- [ ] **Error Handling**
  - [ ] Duplicate student ID
  - [ ] Invalid input types
  - [ ] Out of range values
  - [ ] Non-existing file
  - [ ] Empty tree operations

---

## 🎓 Key Learning Outcomes

### Data Structures:

- ✅ Implemented self-balancing AVL Tree
- ✅ Understanding of tree rotations
- ✅ Balance factor calculation
- ✅ Recursive tree operations

### Algorithms:

- ✅ BST insertion/deletion
- ✅ Tree balancing algorithms
- ✅ In-order traversal
- ✅ Searching in balanced trees

### Software Engineering:

- ✅ Object-oriented design
- ✅ Class encapsulation
- ✅ File I/O operations
- ✅ Error handling
- ✅ Menu-driven interface
- ✅ Code documentation

---

## 🚀 Running the Program

1. **Compile** using one of the methods above
2. **Run** the executable
3. Program will automatically try to load `student_grades.csv`
4. Use menu options 1-8 to interact
5. Save data before exiting (option 6 or auto-prompt on exit)

---

## 💡 Pro Tips

1. **Always save before exiting** - Data is only in memory until saved
2. **Use unique student IDs** - Duplicates will be rejected
3. **Keep backups of CSV files** - In case of corruption
4. **Test with sample data first** - Use provided student_grades.csv
5. **Check balance after operations** - Display should always show sorted order

---

## 🐛 Common Issues & Solutions

| Problem             | Solution                             |
| ------------------- | ------------------------------------ |
| Compiler not found  | Install g++ (MinGW for Windows)      |
| File not found      | Ensure CSV file is in same directory |
| Compilation errors  | Check C++11 support: `-std=c++11`    |
| Data not persisting | Remember to save before exit         |
| Display not sorted  | Check for insertion errors           |

---

## 📚 References

- Course: CSC 307 - Data Structures and Algorithm Analysis
- Semester: Fall 2025
- Instructor: Prof. Chad McDaniel
- Team: PS5 (Prashant Chand, Sambhav Pyakurel, Sujal Maharjan)

### Algorithm References:

1. GeeksforGeeks - AVL Tree Insertion
2. GeeksforGeeks - AVL Tree Deletion
3. GeeksforGeeks - Binary Tree Traversal

---

## 🏆 Project Completion Status

✅ **Milestone 1**: Requirements and Design - COMPLETE  
✅ **Milestone 2**: Architecture and Pseudocode - COMPLETE  
✅ **Final Implementation**: Full C++ Program - COMPLETE

### Deliverables:

- ✅ Complete source code (7 files)
- ✅ Comprehensive documentation
- ✅ Sample data file
- ✅ Build scripts (Makefile + compile.bat)
- ✅ Test cases and examples
- ✅ Project summary

---

**Project Status: READY FOR SUBMISSION** ✅

All requirements from Milestone 1 and Milestone 2 have been implemented successfully!

---

_End of Summary_
