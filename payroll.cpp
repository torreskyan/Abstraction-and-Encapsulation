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
bool idExists(const vector<Employee*>& employees, const string& id) {
    return any_of(employees.begin(), employees.end(), [&id](Employee* emp) {
        return emp->getId() == id;
    });
}

// Function to check if Name already exists
bool nameExists(const vector<Employee*>& employees, const string& name) {
    return any_of(employees.begin(), employees.end(), [&name](Employee* emp) {
        return emp->getName() == name;
    });
}

// Function to validate numeric input
bool isValidNumericInput(const string& input) {
    return !input.empty() && all_of(input.begin(), input.end(), [](char c) {
        return isdigit(c) || c == '.'; // Allows decimal numbers
    });
}

// Function to validate non-empty name with spaces allowed
bool isValidName(const string& name) {
    string trimmedName = name;
    trimmedName.erase(0, trimmedName.find_first_not_of(" ")); // Trim leading spaces
    trimmedName.erase(trimmedName.find_last_not_of(" ") + 1); // Trim trailing spaces
    return !trimmedName.empty();
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
        cin >> ws;
        getline(cin, choiceInput);

        if (!isValidNumericInput(choiceInput)) {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        choice = stoi(choiceInput);

        if (choice == 1 || choice == 2 || choice == 3) {
            string id, name, salaryInput;
            double salary;

            do {
                cout << "Enter ID: ";
                cin >> id;

                if (idExists(employees, id)) {
                    cout << "Error: ID already exists! Please use a unique ID.\n";
                }
            } while (idExists(employees, id));

            cin.ignore();
            do {
                cout << "Enter Name: ";
                getline(cin, name);

                if (!isValidName(name)) {
                    cout << "Error: Name cannot be empty or only spaces. Try again.\n";
                } else if (nameExists(employees, name)) {
                    cout << "Error: Name already exists! Please use a unique name.\n";
                }
            } while (!isValidName(name) || nameExists(employees, name));

            if (choice == 1) {
                do {
                    cout << "Enter Fixed Monthly Salary: ";
                    cin >> salaryInput;

                    if (!isValidNumericInput(salaryInput)) {
                        cout << "Error: Please enter a valid numeric value.\n";
                    }
                } while (!isValidNumericInput(salaryInput));

                salary = stod(salaryInput);
                employees.push_back(new FullTimeEmployee(id, name, salary));

            } else if (choice == 2) {
                string wageInput;
                int hours;

                do {
                    cout << "Enter Hourly Wage: ";
                    cin >> wageInput;

                    if (!isValidNumericInput(wageInput)) {
                        cout << "Error: Please enter a valid numeric value.\n";
                    }
                } while (!isValidNumericInput(wageInput));

                salary = stod(wageInput);

                cout << "Enter Number of Hours Worked: ";
                while (!(cin >> hours) || hours < 0) {
                    cout << "Error: Enter a valid number of hours.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                employees.push_back(new PartTimeEmployee(id, name, salary, hours));

            } else if (choice == 3) {
                string payInput;
                int projects;

                do {
                    cout << "Enter Payment Per Project: ";
                    cin >> payInput;

                    if (!isValidNumericInput(payInput)) {
                        cout << "Error: Please enter a valid numeric value.\n";
                    }
                } while (!isValidNumericInput(payInput));

                salary = stod(payInput);

                cout << "Enter Number of Projects Completed: ";
                while (!(cin >> projects) || projects < 0) {
                    cout << "Error: Enter a valid number of projects.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

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
