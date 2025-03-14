#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
using namespace std;

// Abstract Base Class for Employees
class Employee {
protected:
    string id;
    string name;
public:
    Employee(string empId, string empName) : id(empId), name(empName) {}
    virtual void displaySalary() const = 0; // Pure virtual function (abstraction)
    string getId() const { return id; }
    string getName() const { return name; }
};

// Full-time Employee Class
class FullTimeEmployee : public Employee {
    double salary;
public:
    FullTimeEmployee(string empId, string empName, double empSalary)
        : Employee(empId, empName), salary(empSalary) {}
    void displaySalary() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

// Part-time Employee Class
class PartTimeEmployee : public Employee {
    double hourlyWage;
    int hoursWorked;
public:
    PartTimeEmployee(string empId, string empName, double wage, int hours)
        : Employee(empId, empName), hourlyWage(wage), hoursWorked(hours) {}
    void displaySalary() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Hourly Wage: $" << hourlyWage << "\nHours Worked: " << hoursWorked << "\n";
        cout << "Total Salary: $" << hourlyWage * hoursWorked << "\n\n";
    }
};

// Contractual Employee Class
class ContractualEmployee : public Employee {
    double paymentPerProject;
    int projectsCompleted;
public:
    ContractualEmployee(string empId, string empName, double payPerProject, int projects)
        : Employee(empId, empName), paymentPerProject(payPerProject), projectsCompleted(projects) {}
    void displaySalary() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n";
        cout << "Contract Payment Per Project: $" << paymentPerProject << "\nProjects Completed: " << projectsCompleted << "\n";
        cout << "Total Salary: $" << paymentPerProject * projectsCompleted << "\n\n";
    }
};

// Function to check if ID already exists
bool idExists(const vector<Employee*>& employees, string id) {
    return any_of(employees.begin(), employees.end(), [id](Employee* emp) {
        return emp->getId() == id;
    });
}

// Function to check if Name already exists
bool nameExists(const vector<Employee*>& employees, string name) {
    return any_of(employees.begin(), employees.end(), [name](Employee* emp) {
        return emp->getName() == name;
    });
}

// Function to validate menu choice (accepts number optionally followed by a space)
bool isValidMenuChoice(const string& input) {
    string trimmedInput = input;
    trimmedInput.erase(trimmedInput.find_last_not_of(" ") + 1); // Trim trailing spaces
    return !trimmedInput.empty() && all_of(trimmedInput.begin(), trimmedInput.end(), ::isdigit);
}

int main() {
    vector<Employee*> employees;
    string choiceInput;
    int choice;

    do {
        cout << "\nMenu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        cout << "Enter your choice: ";
        cin >> ws; // Trim leading whitespace
        getline(cin, choiceInput);

        if (!isValidMenuChoice(choiceInput)) {
            cout << "Invalid input. Please enter again.\n";
            continue;
        }

        choice = stoi(choiceInput);

        if (choice == 1 || choice == 2 || choice == 3) {
            string id, name;
            double salary;

            do {
                cout << "Enter ID: ";
                cin >> id;

                if (idExists(employees, id)) {
                    cout << "Error: ID already exists! Please use a unique ID.\n";
                }
            } while (idExists(employees, id));

            do {
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);

                if (nameExists(employees, name)) {
                    cout << "Error: Name already exists! Please use a unique name.\n";
                }
            } while (nameExists(employees, name));

            if (choice == 1) {
                cout << "Enter Fixed Monthly Salary: ";
                cin >> salary;
                employees.push_back(new FullTimeEmployee(id, name, salary));
            } else if (choice == 2) {
                int hours;
                cout << "Enter Hourly Wage: ";
                cin >> salary;
                cout << "Enter Number of Hours Worked: ";
                cin >> hours;
                employees.push_back(new PartTimeEmployee(id, name, salary, hours));
            } else if (choice == 3) {
                int projects;
                cout << "Enter Payment Per Project: ";
                cin >> salary;
                cout << "Enter Number of Projects Completed: ";
                cin >> projects;
                employees.push_back(new ContractualEmployee(id, name, salary, projects));
            }
        } else if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------\n";
            for (const auto& emp : employees) {
                emp->displaySalary();
            }
        } else if (choice == 5) {
            cout << "Exiting program. Goodbye!\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    // Clean up allocated memory
    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
