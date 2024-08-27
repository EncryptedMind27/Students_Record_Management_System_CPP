#include "header.hpp"

void headerDisplay(){
    cout << "***************************************************************************" << endl;
    cout << "                   STUDENT RECORD DATA MANAGEMENT SYSTEM                   " << endl;
    cout << "***************************************************************************" << endl;
}

void addStudent(string filePath){

	system("cls");
	headerDisplay();
	cout << "File Directory: " << filePath << endl; 
    	cout << "Status: Adding Student Information"<<endl;
    	cout << "---------------------------------------------------------------------------\n" << endl;
	Student student;

	cout << "School ID: ";
	getline(cin,student.student_Id);
	cout << "Surname: ";
	getline(cin,student.surname);

	cout << "First Name: ";
	getline(cin,student.firstName);

	cout << "Birth Date: ";
	getline(cin,student.birthDate);

	cout << "Gender: ";
	getline(cin,student.gender);

	fstream file(filePath, ios::out|ios::app);
	if(!file.is_open()){
        cerr << "THERE WAS AN ERROR WITH ADDING DATA!\nFile Directory: " << filePath << endl;
        return;
    }

    file << student.student_Id << ","
         << student.surname << ","
         << student.firstName << ","
         << student.birthDate << ","
         << student.gender << endl;
 	file.close();
 	return;
}

bool compareBySurname(const Student &a, const Student &b) {
    return a.surname < b.surname;
}

vector<Student> sortStudents(vector<Student>&students){
	sort(students.begin(), students.end(), compareBySurname);
	return students;
}

void deleteStudent(string filePath, vector<Student> students,Student student){
	ofstream newFile(filePath);


	for(const auto& stdnts : students){
		if(!(stdnts.student_Id == student.student_Id &&
			stdnts.surname == student.surname &&
			stdnts.firstName == student.firstName &&
			stdnts.birthDate == student.birthDate &&
			stdnts.gender == student.gender)){

				newFile << stdnts.student_Id << ","
         			<< stdnts.surname << ","
        			<< stdnts.firstName << ","
        			<< stdnts.birthDate << ","
         			<< stdnts.gender << endl;
		}
	}

	newFile.close();
	cin.ignore();
	return;
}

void editStudent(string filePath, vector<Student> students, Student student) {
    ofstream newFile(filePath);

    system("cls");
    headerDisplay();
    cout << "File Directory: " << filePath << endl;
    cout << "Status: Editing Student Information" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "            " << setw(20) << left << "Old Information" << "New Information\n" << endl; 


    for (auto& stdnts : students) {
        if (!(stdnts.student_Id == student.student_Id &&
              stdnts.surname == student.surname &&
              stdnts.firstName == student.firstName &&
              stdnts.birthDate == student.birthDate &&
              stdnts.gender == student.gender)) {

            // Write the current record as is if it doesn't match
            newFile << stdnts.student_Id << ","
                    << stdnts.surname << ","
                    << stdnts.firstName << ","
                    << stdnts.birthDate << ","
                    << stdnts.gender << endl;
        } else {
            // Allow the user to edit student details
         
        		cout << "Student ID: " << setw(20) << left << stdnts.student_Id;
        		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        		getline(cin,stdnts.student_Id);

        		cout << "Surname:    " << setw(20) << left << stdnts.surname;
        		getline(cin,stdnts.surname);

        		cout << "First Name: " << setw(20) << left << stdnts.firstName;
        		getline(cin,stdnts.firstName);

        		cout << "Birth Date: " << setw(20) << left << stdnts.birthDate;
        		getline(cin,stdnts.birthDate);

        		cout << "Gender:     " << setw(20) << left << stdnts.gender;
        		getline(cin,stdnts.gender);

            newFile << stdnts.student_Id << ","
                    << stdnts.surname << ","
                    << stdnts.firstName << ","
                    << stdnts.birthDate << ","
                    << stdnts.gender << "\n";
        }
    }

    newFile.close();
    
    return;
}

