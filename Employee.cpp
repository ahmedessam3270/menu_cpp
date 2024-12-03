#include "Employee.h"

Employee::Employee() : name(""), emp_id(0), age(0), salary(0), bd{0, 0, 0} {}

Employee::Employee(const std::string& name, int emp_id, int age, int salary, const BD& bd)
    : name(name), emp_id(emp_id), age(age), salary(salary), bd(bd) {}

std::string Employee::getName() const {
    return name;
}

int Employee::getId() const {
    return emp_id;
}

int Employee::getAge() const {
    return age;
}

int Employee::getSalary() const {
    return salary;
}

BD Employee::getBirthDate() const {
    return bd;
}