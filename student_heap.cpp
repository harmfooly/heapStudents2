#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// Address class definition
class Address {
  private:
    std::string street;
    std::string city;
    std::string state;
    std::string zip;

  public:
    Address();
    void init(std::string addressString);
    void printAddress() const;
};

// Date class definition
class Date {
  private:
    int month;
    int day;
    int year;

  public:
    Date();
    void init(std::string dateString);
    void printDate() const;
};

// Student class definition
class Student {
  private:
    std::string firstName;
    std::string lastName;
    Address address;
    Date birthDate;
    Date gradDate;
    int creditHours;

  public:
    Student();
    void init(std::string studentString);
    void printStudent() const;
    std::string getFirstName() const;
    std::string getLastName() const;
};

// ----------------------------------------
// Address class
// ----------------------------------------

// Constructor
Address::Address() {
    street = "";
    city = "";
    state = "";
    zip = "";
}

void Address::init(std::string addressString) {
    std::stringstream ss(addressString);

    std::getline(ss, street, ',');
    std::getline(ss, city, ',');
    std::getline(ss, state, ',');
    std::getline(ss, zip, ',');
}

// Print the address
void Address::printAddress() const {
    std::cout << street << std::endl;
    std::cout << city << " " << state << ", " << zip << std::endl;
}

// ----------------------------------------
// Date class
// ----------------------------------------

// Constructor: initialize date fields to zero
Date::Date() {
    month = 0;
    day = 0;
    year = 0;
}

void Date::init(std::string dateString) {
    std::stringstream ss(dateString);
    std::string temp;

    std::getline(ss, temp, '/');
    month = std::stoi(temp);

    std::getline(ss, temp, '/');
    day = std::stoi(temp);

    std::getline(ss, temp, '/');
    year = std::stoi(temp);
}

// Print the date with the full month name
void Date::printDate() const {
    std::string months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    // Only print the date if the month is valid
    if (month >= 1 && month <= 12) {
        std::cout << months[month - 1] << " " << day << ", " << year << std::endl;
    } else {
        std::cout << "Invalid date" << std::endl;
    }
}

// ----------------------------------------
// Student class
// ----------------------------------------

// Constructor
Student::Student() {
    firstName = "";
    lastName = "";
    creditHours = 0;
}

// Initialize a student using a comma-separated CSV row
void Student::init(std::string studentString) {
    std::stringstream ss(studentString);
    std::string temp;

    // Read the student's first and last names
    std::getline(ss, firstName, ',');
    std::getline(ss, lastName, ',');

    // Read the address fields
    std::string street;
    std::string city;
    std::string state;
    std::string zip;

    std::getline(ss, street, ',');
    std::getline(ss, city, ',');
    std::getline(ss, state, ',');
    std::getline(ss, zip, ',');

    address.init(street + "," + city + "," + state + "," + zip);

    // Pick up the birth date, graduation date, and credit hours
    std::getline(ss, temp, ',');
    birthDate.init(temp);

    std::getline(ss, temp, ',');
    gradDate.init(temp);

    std::getline(ss, temp, ',');
    creditHours = std::stoi(temp);
}

// Print all student information
void Student::printStudent() const {
    std::cout << "Name: " << firstName << " " << lastName << std::endl;

    std::cout << "Address: ";
    address.printAddress();

    std::cout << "Birth Date: ";
    birthDate.printDate();

    std::cout << "Graduation Date: ";
    gradDate.printDate();

    std::cout << "Credit Hours: " << creditHours << std::endl;

    std::cout << "----------------------------------------"
              << std::endl;
} // end printStudent

// Return the student's first name
std::string Student::getFirstName() const {
    return firstName;
}

// Return the student's last name
std::string Student::getLastName() const {
    return lastName;
} // end getLastName

// ----------------------------------------
// Menu functions
// ----------------------------------------

// Load students from the file (returns true if it worked)
bool loadStudents(std::vector<Student*>& students) {
    std::ifstream file("students.csv");
    std::string line;

    while (std::getline(file, line)) {
        // Skip blank lines
        if (line.empty() || line == "\r") {
            continue;
        }
        Student* student = new Student();
        student->init(line);
        students.push_back(student);
    }
    file.close();
    return true;
}

// Print all students in the vector
void printStudents(const std::vector<Student*>& students) {
    for (int i = 0; i < students.size(); i++) {
        students[i]->printStudent();
    }
    // Print the total number of students
    std::cout << "Total students: " << students.size() << std::endl;
}

// Search for a student by first and last name
void findStudent(const std::vector<Student*>& students) {
    if (students.empty()) {
        std::cout << "No students loaded. Choose option 1 first.\n";
        return;
    }

    std::string first, last;
    std::cout << "Enter first name: ";
    std::cin >> first;
    std::cout << "Enter last name: ";
    std::cin >> last;

    bool found = false;
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getFirstName() == first && students[i]->getLastName() == last) {
            students[i]->printStudent();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No student named " << first << " " << last << " was found.\n";
    }
}

// Delete a student by first and last name
void delStudents(std::vector<Student*>& students) {
    if (students.empty()) {
        std::cout << "No students loaded. Choose option 1 first.\n";
        return;
    }

    std::string first, last;
    std::cout << "Enter first name: ";
    std::cin >> first;
    std::cout << "Enter last name: ";
    std::cin >> last;

    int deleted = 0;
    int i = 0;
    while (i < students.size()) {
        if (students[i]->getFirstName() == first &&
            students[i]->getLastName() == last) {
            delete students[i];                      // free the memory
            students.erase(students.begin() + i);    // removes the pointer from the vector
            deleted++;                               // the next item goes here, so don't increment i
        } else {
            i++;
        }
    }

    if (deleted == 0) {
        std::cout << "No student named " << first << " " << last << " was found.\n";
    } else {
        std::cout << "Deleted " << deleted << " student(s). " << students.size() << " remaining.\n";
    }
}

// ----------------------------------------
// Main function
// ----------------------------------------

int main() {
    std::vector<Student*> students;
    std::string choice = "";
    bool loaded = false;   // tracks whether the file has been read yet

    // Keep showing the menu until the user picks Exit
    while (choice != "4") {
        std::cout << "\nHello! Select an option from the list:\n";
        std::cout << "[1] Load Student List & Show Students\n";
        std::cout << "[2] Search for Student (firstName, lastName)\n";
        std::cout << "[3] Delete a Student\n";
        std::cout << "[4] Exit\n";

        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            break;  // input stream closed (e.g., Ctrl+D), so stop instead of looping forever
        }

        if (choice == "1") {
            if (!loaded) {
                loaded = loadStudents(students);   // only read the file the first time
            }
            printStudents(students);
        } else if (choice == "2") {
            findStudent(students);
        } else if (choice == "3") {
            delStudents(students);
        } else if (choice == "4") {
            std::cout << "Goodbye!\n";
        } else {
            std::cout << "Invalid option. Please select 1, 2, 3, or 4.\n";
        }
    }

    // Free any remaining students before exiting
    for (int i = 0; i < students.size(); i++) {
        delete students[i];
    }

    return 0;
}
