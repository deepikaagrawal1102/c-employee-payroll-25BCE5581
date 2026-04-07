/*
Project Title: Employee Payroll System
Student Name: 
Register No:
*/

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Employee {
private:
    int empID;
    string name;
    double basicPay;
    int otHours;

public:
    Employee(int id, string n, double bp, int ot) {
        empID = id;
        name = n;
        basicPay = bp;
        otHours = ot;
    }

    int getID() { return empID; }
    string getName() { return name; }

    void updateOT(int ot) {
        if (ot >= 0)
            otHours = ot;
        else
            cout << "Invalid OT hours!\n";
    }

    double calculateGross() {
        return basicPay + (otHours * 200);
    }

    double calculateTax() {
        double gross = calculateGross();
        if (gross < 30000) return 0;
        else if (gross <= 50000) return gross * 0.1;
        else return gross * 0.2;
    }

    double calculateNet() {
        return calculateGross() - calculateTax();
    }

    void displayPayslip() {
        cout << "\n--- Payslip ---\n";
        cout << "ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Gross: " << calculateGross() << endl;
        cout << "Tax: " << calculateTax() << endl;
        cout << "Net Salary: " << calculateNet() << endl;
    }

    string toFileString() {
        return to_string(empID) + "," + name + "," +
               to_string(basicPay) + "," + to_string(otHours);
    }
};

class PayrollSystem {
private:
    vector<Employee> employees;

public:
    void addEmployee() {
        int id, ot;
        string name;
        double basic;

        cout << "Enter ID: ";
        cin >> id;

        // Check duplicate ID
        for (auto &e : employees) {
            if (e.getID() == id) {
                cout << "Duplicate ID!\n";
                return;
            }
        }

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Basic Pay: ";
        cin >> basic;

        cout << "Enter OT Hours: ";
        cin >> ot;

        if (basic < 0 || ot < 0) {
            cout << "Invalid input!\n";
            return;
        }

        employees.push_back(Employee(id, name, basic, ot));
        cout << "Employee added successfully!\n";
    }

    void updateOT() {
        int id, ot;
        cout << "Enter ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getID() == id) {
                cout << "Enter new OT: ";
                cin >> ot;
                e.updateOT(ot);
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    void generatePayslip() {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.getID() == id) {
                e.displayPayslip();
                return;
            }
        }

        cout << "Employee not found!\n";
    }

    void totalPayout() {
        double total = 0;
        for (auto &e : employees) {
            total += e.calculateNet();
        }
        cout << "Total Salary Payout: " << total << endl;
    }

    void highestPaid() {
        if (employees.empty()) return;

        Employee *maxEmp = &employees[0];

        for (auto &e : employees) {
            if (e.calculateNet() > maxEmp->calculateNet()) {
                maxEmp = &e;
            }
        }

        cout << "Highest Paid Employee:\n";
        maxEmp->displayPayslip();
    }

    void saveToFile() {
        ofstream file("employees.txt");
        for (auto &e : employees) {
            file << e.toFileString() << endl;
        }
        file.close();
    }
};

int main() {
    PayrollSystem ps;
    int choice;

    do {
        cout << "\n1. Add Employee\n2. Update OT\n3. Payslip\n4. Total Payout\n5. Highest Paid\n6. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: ps.addEmployee(); break;
            case 2: ps.updateOT(); break;
            case 3: ps.generatePayslip(); break;
            case 4: ps.totalPayout(); break;
            case 5: ps.highestPaid(); break;
        }

    } while (choice != 6);

    ps.saveToFile();
    return 0;
}