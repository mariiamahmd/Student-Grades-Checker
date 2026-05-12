# Student Grade Checker

## Team Members
- **Mohamed Amgad** - ID: 2300459
- **Habiba Ahmed**  - ID: 2300086
- **Mariam Ahmed**  - ID: 2300506

---

## Project Description
Student Grade Checker is a robust C++ application designed to seamlessly manage student academic records, course registrations, and faculty assignments. 

Built with a clear separation between backend data structures and a Qt-powered Graphical User Interface (GUI), the system serves two primary users:
- **Instructors/Administrators:** Can manage the student body, assign lecturers to courses, record grades, and generate comprehensive analytical reports (e.g., top students, pass/fail ratios, and grade distributions).
- **Students:** Can log in using their unique ID to review their personal academic history, registered courses, and dynamically calculated cumulative GPAs.

---

## Data Structures Used

The application leverages standard C++ containers optimized for performance and scalability:

### 1. Binary Search Tree (BST)
- **Usage:** Stores the core student database (`TreeNode` containing `Student` objects) indexed by Student ID.
- **Why:** Ensures efficient $O(\log n)$ average time complexity for searching, inserting, and deleting student profiles while inherently keeping records sorted by ID for organized traversal.

### 2. Hash Maps (`std::unordered_map`)
- **Usage:** 
  - `coursesDatabase` and `lecturersDatabase` in the `GradeManager` for instant entity retrieval.
  - `enrolledStudents` inside the `Course` class to map Student IDs directly to their course grades.
- **Why:** Provides fast $O(1)$ constant time lookups, insertions, and updates, which is critical when processing grades for hundreds of enrolled students.

### 3. Ordered Map (`std::map`)
- **Usage:** Calculates and stores the grade distribution histogram data (counting A, B, C, D, F grades).
- **Why:** Automatically keeps the grade categories alphabetically sorted for consistent UI reporting and chart generation.

### 4. Vectors (`std::vector`)
- **Usage:** Stores dynamic lists such as a student's `CourseRecord` history, lists of all available courses/lecturers, and arrays of `Student*` pointers generated via inorder BST traversals for rendering in Qt UI tables.

---

## Implemented Features

### Instructor / Admin Dashboard
1. **Student Management:** Add, update, search, and delete student profiles.
2. **Course & Faculty Management:** Create courses with specific credit hours and assign `Lecturer` profiles to them.
3. **Enrollment & Grading:** Register students for specific courses (with an "In Progress" `-1.0` status) and update final grades.
4. **Analytical Reporting:**
   - **Top Students:** Generate a sorted ranking of top-performing students by CGPA.
   - **Pass/Fail Analysis:** Calculate total passing vs. failing metrics based on a configurable threshold.
   - **Grade Distribution:** Generate data for visual histogram representations of overall performance.

### Student Dashboard
1. **Secure Access:** Retrieve personal records using a unique Student ID.
2. **Academic History:** View all registered courses, completed credits, and grades across Fall, Spring, and Summer terms.
3. **Performance Tracking:** View dynamically calculated Cumulative GPA (CGPA) reflecting all completed coursework.

---

## System Architecture

The project is divided into distinct modular components, separating backend logic (`src`) from frontend presentation (`gui`):

### Core Models (`src/`)
- **`Student`:** Encapsulates ID, name, transferred base credits, and a dynamic vector of `CourseRecord` structs to track semester-by-semester progress.
- **`Course`:** Manages credit hours, course codes, a pointer to an assigned `Lecturer`, and an internal hash map of enrolled students and their scores.
- **`Lecturer`:** Stores faculty details (ID, Name, Department).
- **`Types`:** Defines shared constructs like the `Term` enum and `StudentScore` sorting structs.

### The Controller (`GradeManager`)
Acts as the central backend API. It owns the root of the Student BST and the database hash maps, handling all cross-entity operations (e.g., verifying a course exists before registering a student, calculating aggregate reports, and formatting data lists for the UI).

### Graphical User Interface (`gui/`)
Built using Qt Widgets and Qt Designer, featuring distinct views and navigation flows for Instructors and Students, seamlessly connected to the `GradeManager` via signal/slot mechanisms.

---

## How to Run the Project

1. Open the project folder in **Qt Creator**.
2. Open the `.pro` or `CMakeLists.txt` file to load the project tree.
3. Configure the build kit (Ensure a compatible C++ compiler like MSVC or MinGW is selected).
4. Run **qmake** or **CMake** to generate the makefiles.
5. Build and Run the application.

---

## AI Usage & Academic Integrity

### AI Tools Used
The project utilized AI tools such as Gemini and ChatGPT as educational and debugging assistants during development. It helped with:
1. Designing UI layouts and histogram visualization logic.
2. Explaining the underlying algorithmic differences between `std::map` and `std::unordered_map`.
3. Understanding Qt Designer widget object hierarchy and signal/slot connections.
4. Troubleshooting and debugging C++ compilation errors.

### Modifications and Review
All AI-generated suggestions were strictly treated as drafts. The team reviewed, tested, and heavily modified the code before integration. Several generated solutions required significant structural adjustments to properly fit the custom BST backend architecture and Qt window navigation flow.

### Example of Incorrect/Unsuitable AI Output
During development, a generated solution connected multiple Qt signals to the same button incorrectly, causing duplicate popup message boxes and unexpected window state behavior. The group identified the architecture flaw, debugged the signal connections, and manually rewrote the event handlers for correct implementation.

### Group Implementation & Understanding
The team was solely responsible for the final logic and fully understands the underlying concepts, including:
- Implementing and traversing the Custom Binary Search Tree for student records.
- Cross-referencing pointers and hash maps between the `Course`, `Lecturer`, and `Student` classes.
- Algorithm design for dynamic CGPA calculations and report generation.
- Integrating backend C++ structures with Qt frontend tables and line edits.

All final integration, testing, debugging, and feature implementation were completed manually by the group members.
