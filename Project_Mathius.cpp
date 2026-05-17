/*
 * ============================================================
 *  PROJECT MATHIUS
 *  Smart Classroom Seating and Attendance Simulator
 *  Language : C++ (OOP)
 *  Modules  : Student Management | Seating Arrangement |
 *             Attendance Recording | Report Generation |
 *             File Storage
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <map>
#include <ctime>

using namespace std;


// ============================================================
// MODULE 1 — STUDENT MANAGEMENT
// CLASS: Student
// Encapsulates all data and behaviour for a single student.
// ============================================================
class Student {
private:
    string regNumber;       // Unique registration number (used as key & sort field)
    string name;            // Full student name
    int totalLessons;       // Total lessons held so far
    int lessonsAttended;    // How many of those the student attended

public:
    // Default constructor – required when students are loaded from a file
    Student() : totalLessons(0), lessonsAttended(0) {}

    // Parameterised constructor – used when registering a new student
    Student(string reg, string n)
        : regNumber(reg), name(n), totalLessons(0), lessonsAttended(0) {}

    // ── Getters ──────────────────────────────────────────────
    string getRegNumber()      const { return regNumber; }
    string getName()           const { return name; }
    int    getTotalLessons()   const { return totalLessons; }
    int    getLessonsAttended()const { return lessonsAttended; }

    // ── Setters ──────────────────────────────────────────────
    void setRegNumber(string reg) { regNumber = reg; }
    void setName(string n)        { name = n; }

    // Called when a new lesson is held and the student was present
    void markPresent() { lessonsAttended++; totalLessons++; }

    // Called when a new lesson is held and the student was absent
    void markAbsent()  { totalLessons++; }

    // Calculates attendance percentage for reporting
    double getAttendancePercentage() const {
        if (totalLessons == 0) return 0.0;
        return (double)lessonsAttended / totalLessons * 100.0;
    }

    // Overloaded < operator — enables std::sort to sort students by reg number
    bool operator<(const Student& other) const {
        return regNumber < other.regNumber;
    }

    // Prints a single student row in a formatted table
    void display() const {
        cout << left
             << setw(15) << regNumber
             << setw(25) << name
             << setw(10) << lessonsAttended
             << setw(10) << totalLessons
             << fixed << setprecision(1)
             << getAttendancePercentage() << "%" << endl;
    }

    // ── File Serialisation ────────────────────────────────────
    // Converts a Student object to a CSV line for file storage
    string serialize() const {
        return regNumber + "," + name + "," +
               to_string(lessonsAttended) + "," + to_string(totalLessons);
    }

    // Reconstructs a Student object from a CSV line read from file
    static Student deserialize(const string& line) {
        stringstream ss(line);
        string reg, n, attended, total;
        getline(ss, reg,      ',');
        getline(ss, n,        ',');
        getline(ss, attended, ',');
        getline(ss, total,    ',');
        Student s(reg, n);
        s.lessonsAttended = stoi(attended);
        s.totalLessons    = stoi(total);
        return s;
    }
};


// ============================================================
// MODULE 1 — STUDENT MANAGEMENT (continued)
// CLASS: AttendanceRecord
// Stores the attendance snapshot for ONE lesson session.
// Each entry maps a registration number to a present/absent flag.
// ============================================================
class AttendanceRecord {
private:
    string date;                  // Date the lesson was held
    string lessonNumber;          // Sequential lesson identifier
    map<string, bool> attendance; // regNumber → true (present) / false (absent)

public:
    AttendanceRecord() {}
    AttendanceRecord(string d, string lesson) : date(d), lessonNumber(lesson) {}

    string getDate()        const { return date; }
    string getLessonNumber()const { return lessonNumber; }

    // Records one student's status for this lesson
    void markStudent(string regNumber, bool present) {
        attendance[regNumber] = present;
    }

    // Returns true if the student was present in this lesson
    bool isPresent(string regNumber) const {
        auto it = attendance.find(regNumber);
        return (it != attendance.end()) ? it->second : false;
    }

    map<string, bool> getAttendance() const { return attendance; }

    // Prints this lesson's attendance list to the console
    void displayRecord() const {
        cout << "\n--- Lesson " << lessonNumber << " | Date: " << date << " ---\n";
        cout << left << setw(15) << "Reg Number" << setw(10) << "Status" << endl;
        cout << string(25, '-') << endl;
        for (const auto& entry : attendance) {
            cout << left << setw(15) << entry.first
                 << (entry.second ? "Present" : "Absent") << endl;
        }
    }

    // Produces a multi-line string suitable for appending to the attendance log file
    string serialize() const {
        string result = "LESSON," + lessonNumber + "," + date + "\n";
        for (const auto& entry : attendance) {
            result += entry.first + "," + (entry.second ? "1" : "0") + "\n";
        }
        result += "END_LESSON\n";
        return result;
    }
};


// ============================================================
// MODULE 2 — SEATING ARRANGEMENT
// CLASS: SeatingArrangement
// Maps students (sorted by reg number) onto a grid of seats
// and displays the layout as a visual classroom map.
// ============================================================
class SeatingArrangement {
private:
    int rows;                         // Number of seat rows
    int cols;                         // Number of seats per row
    vector<vector<string>> seats;     // 2-D grid: each cell holds a reg number

public:
    // Default: 5 rows × 6 columns = 30 seats
    SeatingArrangement(int r = 5, int c = 6) : rows(r), cols(c) {
        seats.assign(rows, vector<string>(cols, "EMPTY"));
    }

    // Fills the seat grid row-by-row with students already sorted by reg number
    void arrangeStudents(const vector<Student>& students) {
        int idx = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                seats[r][c] = (idx < (int)students.size())
                              ? students[idx++].getRegNumber()
                              : "EMPTY";
            }
        }
    }

    // Renders the seating grid with a lecturer-front label
    void display() const {
        cout << "\n========== CLASSROOM SEATING ARRANGEMENT ==========\n";
        cout << "                  [FRONT / LECTURER]\n\n";
        for (int r = 0; r < rows; r++) {
            cout << "Row " << r + 1 << ": ";
            for (int c = 0; c < cols; c++) {
                cout << "[" << left << setw(12) << seats[r][c] << "] ";
            }
            cout << "\n";
        }
        cout << "\n===================================================\n";
    }
};


// ============================================================
// MODULE 5 — FILE STORAGE
// CLASS: FileManager
// Handles all reading and writing of persistent data files.
// Uses static methods so no instance is needed — acts as a
// utility/service layer.
// ============================================================
class FileManager {
public:
    // File names used across the system
    static const string STUDENTS_FILE;
    static const string ATTENDANCE_FILE;
    static const string REPORTS_FILE;

    // Writes all students to students.csv (overwrites previous data)
    static void saveStudents(const vector<Student>& students) {
        ofstream file(STUDENTS_FILE);
        if (!file.is_open()) {
            cerr << "Error: Cannot open " << STUDENTS_FILE << "\n";
            return;
        }
        for (const auto& s : students) file << s.serialize() << "\n";
        file.close();
        cout << "Students saved to " << STUDENTS_FILE << "\n";
    }

    // Reads students.csv and returns a vector of Student objects
    static vector<Student> loadStudents() {
        vector<Student> students;
        ifstream file(STUDENTS_FILE);
        if (!file.is_open()) return students;   // Return empty if file not found
        string line;
        while (getline(file, line)) {
            if (!line.empty()) students.push_back(Student::deserialize(line));
        }
        file.close();
        return students;
    }

    // Appends one lesson's attendance snapshot to attendance.txt
    static void saveAttendanceRecord(const AttendanceRecord& record) {
        ofstream file(ATTENDANCE_FILE, ios::app);
        if (!file.is_open()) {
            cerr << "Error: Cannot open " << ATTENDANCE_FILE << "\n";
            return;
        }
        file << record.serialize();
        file.close();
    }

    // Appends a generated report string to reports.txt
    static void saveReport(const string& report) {
        ofstream file(REPORTS_FILE, ios::app);
        if (!file.is_open()) {
            cerr << "Error: Cannot open " << REPORTS_FILE << "\n";
            return;
        }
        file << report;
        file.close();
    }

    // Returns today's date as YYYY-MM-DD using the system clock
    static string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
           << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
           << setfill('0') << setw(2) << ltm->tm_mday;
        return ss.str();
    }
};

// Static member definitions (required outside the class body in C++)
const string FileManager::STUDENTS_FILE   = "students.csv";
const string FileManager::ATTENDANCE_FILE = "attendance.txt";
const string FileManager::REPORTS_FILE    = "reports.txt";


// ============================================================
// MODULE 4 — REPORT GENERATION
// CLASS: ReportGenerator
// Builds formatted, human-readable report strings from live data.
// Reports are both printed to the console and saved to file.
// ============================================================
class ReportGenerator {
public:
    // Produces the full semester attendance summary table,
    // including a list of students below the 75 % threshold.
    static string generateSemesterReport(const vector<Student>& students,
                                         int totalLessons) {
        stringstream report;
        report << "\n========================================\n"
               << "       SEMESTER ATTENDANCE REPORT       \n"
               << "       Generated: " << FileManager::getCurrentDate() << "\n"
               << "========================================\n"
               << left
               << setw(15) << "Reg Number"
               << setw(25) << "Name"
               << setw(12) << "Attended"
               << setw(10) << "Total"
               << "Percentage\n"
               << string(70, '-') << "\n";

        for (const auto& s : students) {
            report << left
                   << setw(15) << s.getRegNumber()
                   << setw(25) << s.getName()
                   << setw(12) << s.getLessonsAttended()
                   << setw(10) << s.getTotalLessons()
                   << fixed << setprecision(1)
                   << s.getAttendancePercentage() << "%\n";
        }

        report << string(70, '-') << "\n"
               << "Total Lessons Held: " << totalLessons << "\n"
               << "\n--- Students Below 75% Attendance (AT RISK) ---\n";

        bool anyAtRisk = false;
        for (const auto& s : students) {
            if (s.getAttendancePercentage() < 75.0) {
                report << s.getRegNumber() << " - " << s.getName()
                       << " (" << fixed << setprecision(1)
                       << s.getAttendancePercentage() << "%)\n";
                anyAtRisk = true;
            }
        }
        if (!anyAtRisk) report << "None — all students meet the threshold.\n";
        report << "========================================\n";
        return report.str();
    }

    // Produces an attendance list for a single lesson session
    static string generateLessonReport(const AttendanceRecord& record,
                                       const vector<Student>& students) {
        stringstream report;
        report << "\n--- Lesson " << record.getLessonNumber()
               << " | Date: " << record.getDate() << " ---\n"
               << left << setw(15) << "Reg Number"
               << setw(25) << "Name" << "Status\n"
               << string(50, '-') << "\n";

        int presentCount = 0;
        for (const auto& s : students) {
            bool present = record.isPresent(s.getRegNumber());
            if (present) presentCount++;
            report << left << setw(15) << s.getRegNumber()
                   << setw(25) << s.getName()
                   << (present ? "Present" : "Absent") << "\n";
        }
        report << string(50, '-') << "\n"
               << "Present: " << presentCount << " / " << students.size() << "\n";
        return report.str();
    }
};


// ============================================================
// MAIN CONTROLLER
// CLASS: ClassroomManager
// Orchestrates all four modules.  This is the only class the
// main() function talks to directly (Facade pattern).
// ============================================================
class ClassroomManager {
private:
    vector<Student>         students;       // Master student list (sorted)
    vector<AttendanceRecord> sessionHistory;// In-memory lesson history
    SeatingArrangement      seating;        // Current seat grid
    int                     lessonCount;    // Running lesson counter

    // Sorts students vector by registration number (ascending)
    void sortStudents() {
        sort(students.begin(), students.end());
    }

    // Returns the index of a student by reg number, or -1 if not found
    int findStudentIndex(const string& regNumber) const {
        for (int i = 0; i < (int)students.size(); i++) {
            if (students[i].getRegNumber() == regNumber) return i;
        }
        return -1;
    }

public:
    // Constructor: loads saved data from file on startup (persistence)
    ClassroomManager() : lessonCount(0), seating(5, 6) {
        students = FileManager::loadStudents();
        if (!students.empty()) {
            sortStudents();
            seating.arrangeStudents(students);
            lessonCount = students[0].getTotalLessons();
            cout << "Loaded " << students.size() << " student(s) from file.\n";
        }
    }

    // ── Student Management ────────────────────────────────────

    // Registers one new student, re-sorts the list, and refreshes the seating grid
    void addStudent() {
        string reg, name;
        cout << "Enter Registration Number: ";
        cin >> reg;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);

        if (findStudentIndex(reg) != -1) {
            cout << "A student with reg number " << reg << " already exists.\n";
            return;
        }
        students.push_back(Student(reg, name));
        sortStudents();
        seating.arrangeStudents(students);
        FileManager::saveStudents(students);
        cout << "Student added successfully.\n";
    }

    // Convenience wrapper: calls addStudent() n times
    void addMultipleStudents() {
        int n;
        cout << "How many students do you want to add? ";
        cin >> n;
        cin.ignore();
        for (int i = 0; i < n; i++) {
            cout << "\nStudent " << i + 1 << ":\n";
            addStudent();
        }
    }

    // Prints the full student list with attendance stats
    void displayAllStudents() const {
        if (students.empty()) { cout << "No students registered.\n"; return; }
        cout << "\n======= REGISTERED STUDENTS =======\n"
             << left
             << setw(15) << "Reg Number"
             << setw(25) << "Name"
             << setw(10) << "Attended"
             << setw(10) << "Total"
             << "Percentage\n"
             << string(65, '-') << "\n";
        for (const auto& s : students) s.display();
        cout << string(65, '-') << "\n";
    }

    // Delegates to SeatingArrangement::display()
    void displaySeating() const { seating.display(); }

    // ── Attendance Recording ──────────────────────────────────

    // Starts a new lesson: prompts the lecturer to mark each student,
    // updates student objects, saves everything to file, and prints a report.
    void markAttendance() {
        if (students.empty()) { cout << "No students registered.\n"; return; }

        lessonCount++;
        string date      = FileManager::getCurrentDate();
        string lessonNum = to_string(lessonCount);
        AttendanceRecord record(date, lessonNum);

        cout << "\n=== MARKING ATTENDANCE - Lesson " << lessonNum
             << " | " << date << " ===\n"
             << "Enter 1 for Present, 0 for Absent\n\n";

        for (auto& student : students) {
            int status;
            cout << student.getRegNumber() << " - " << student.getName() << ": ";
            cin >> status;
            bool present = (status == 1);
            record.markStudent(student.getRegNumber(), present);
            present ? student.markPresent() : student.markAbsent();
        }

        sessionHistory.push_back(record);
        FileManager::saveStudents(students);         // Persist updated totals
        FileManager::saveAttendanceRecord(record);   // Persist lesson snapshot

        string lessonReport = ReportGenerator::generateLessonReport(record, students);
        cout << lessonReport;
        FileManager::saveReport(lessonReport);

        cout << "\nAttendance saved successfully.\n";
    }

    // ── Reports ───────────────────────────────────────────────

    // Generates and saves the full semester attendance report
    void generateSemesterReport() {
        if (students.empty()) { cout << "No students registered.\n"; return; }
        string report = ReportGenerator::generateSemesterReport(students, lessonCount);
        cout << report;
        FileManager::saveReport(report);
        cout << "Report saved to " << FileManager::REPORTS_FILE << "\n";
    }

    // Looks up and displays a single student's attendance summary
    void viewStudentAttendance() const {
        string reg;
        cout << "Enter Registration Number: ";
        cin >> reg;

        int idx = findStudentIndex(reg);
        if (idx == -1) { cout << "Student not found.\n"; return; }

        const Student& s = students[idx];
        double pct = s.getAttendancePercentage();
        string status = (pct < 75.0) ? "AT RISK"
                      : (pct < 85.0) ? "Satisfactory"
                                     : "Good Standing";

        cout << "\n=== ATTENDANCE FOR " << s.getName() << " ===\n"
             << "Reg Number : " << s.getRegNumber()       << "\n"
             << "Attended   : " << s.getLessonsAttended() << "/"
                                << s.getTotalLessons()    << " lessons\n"
             << "Percentage : " << fixed << setprecision(1) << pct << "%\n"
             << "Status     : " << status                 << "\n";
    }

    // Removes a student from the system and refreshes the seating grid
    void removeStudent() {
        string reg;
        cout << "Enter Registration Number to remove: ";
        cin >> reg;

        int idx = findStudentIndex(reg);
        if (idx == -1) { cout << "Student not found.\n"; return; }

        cout << "Removing " << students[idx].getName() << "...\n";
        students.erase(students.begin() + idx);
        seating.arrangeStudents(students);
        FileManager::saveStudents(students);
        cout << "Student removed.\n";
    }
};


// ============================================================
// ENTRY POINT
// Displays the main menu in a loop; delegates every choice
// to a ClassroomManager method.
// ============================================================
void displayMenu() {
    cout << "\n+========================================+\n"
         << "|           PROJECT MATHIUS              |\n"
         << "|  Smart Classroom Attendance System     |\n"
         << "+========================================+\n"
         << "|  1.  Add Student                       |\n"
         << "|  2.  Add Multiple Students             |\n"
         << "|  3.  View All Students                 |\n"
         << "|  4.  View Seating Arrangement          |\n"
         << "|  5.  Mark Attendance (New Lesson)      |\n"
         << "|  6.  View Student Attendance           |\n"
         << "|  7.  Generate Semester Report          |\n"
         << "|  8.  Remove Student                    |\n"
         << "|  0.  Exit                              |\n"
         << "+========================================+\n"
         << "  Choice: ";
}

int main() {
    cout << "Initialising Project Mathius...\n";
    ClassroomManager manager;

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: manager.addStudent();            break;
            case 2: manager.addMultipleStudents();   break;
            case 3: manager.displayAllStudents();    break;
            case 4: manager.displaySeating();        break;
            case 5: manager.markAttendance();        break;
            case 6: manager.viewStudentAttendance(); break;
            case 7: manager.generateSemesterReport();break;
            case 8: manager.removeStudent();         break;
            case 0: cout << "Exiting Project Mathius. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
