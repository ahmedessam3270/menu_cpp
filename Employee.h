#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

struct BD {
    int day;
    int month;
    int year;
};

class Employee {
public:
    Employee();
    Employee(const std::string& name, int emp_id, int age, int salary, const BD& bd);

    std::string getName() const;
    int getId() const;
    int getAge() const;
    int getSalary() const;
    BD getBirthDate() const;

private:
    std::string name;
    int emp_id;
    int age;
    int salary;
    BD bd;
};

#endif // EMPLOYEE_H