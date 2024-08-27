#ifndef STUDENT_HEADER
#define STUDENT_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
	string student_Id;
	string surname;
	string firstName;
	string birthDate;
	string gender;
};

void addStudent(string filePath);
void editStudent(string fileName, vector<Student> students, Student student);
void deleteStudent(string fileName,vector<Student> students,Student student);
bool compareBySurname(const Student &a, const Student &b);
vector<Student> sortStudents(vector<Student>& students);
void headerDisplay();

#endif