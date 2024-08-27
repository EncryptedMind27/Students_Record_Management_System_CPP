#include <iostream>
#include <dirent.h>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <vector>

#include "header.hpp"

using namespace std;

void createRecord();
void deleteRecord(const string& fileName);
void updateRecord(const string& fileName);
void readRecord(const string& fileName, bool flag, bool sortFlag,int delNum, int ediNum);


int main() {

    system("color a");

    do{
        string folderPath = "records";
        DIR *dir;

        struct dirent *entry;

        // Open the directory
        if ((dir = opendir(folderPath.c_str())) == NULL) {
            system("cls");
            cerr << "THERE WAS AN ERROR OPENING THE FOLDER! " << "\nFILE DIRECTORY: " << folderPath << endl;
            return 1;
        }

        system("cls");
        headerDisplay();
        cout << "File Directory: " << folderPath << endl;
        cout << "Status: Showing All Records" << endl;
        cout << "***************************************************************************\n" << endl;

        // Iterate through directory entries
        int ctr = 0;
        while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file
        if (entry->d_type == DT_REG) {
            ctr++;
            cout << "[" << ctr << "] " << entry->d_name << endl;
            }
        }

        cout << endl;
        cout << "***************************************************************************" << endl;  
        cout << "[C] Create\t" << "[R] Read\t" << "[U] Update\t" << "[D] Delete\t" << "[E] Exit" << endl;
        cout << "***************************************************************************" << endl;

        char ch = _getch();

        switch(ch){
            case 'c':
                // code here
                createRecord();
                break;
            case 'r':
                {
                    // code here
                    int fileNo;
                    string fileFolder = "records/";
                    string fileName, filePath;
                    cout << "Reading File Number: ";
                    cin >> fileNo;

                    rewinddir(dir);

                    int ctr = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (entry->d_type == DT_REG) {
                            ctr++;
                            if(ctr == fileNo){
                                filePath = entry->d_name;
                                fileName = fileFolder+filePath;
                                readRecord(fileName,false,false,0,0);
                            }
                        }
                    }
                }
                break;
            case 'u':
                {
                    // code here
                    int fileNo;
                    string fileFolder = "records/";
                    string fileName, filePath;
                    cout << "Updating File Number: ";

                    cin >> fileNo;

                    rewinddir(dir);

                    int ctr = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (entry->d_type == DT_REG) {
                            ctr++;
                            if(ctr == fileNo){
                                filePath = entry->d_name;
                                fileName = fileFolder+filePath;
                                updateRecord(fileName);
                            }
                        }
                    }
                }
                break;
            case 'd':
                {
                    // code here
                    int fileNo;
                    string fileName;
                    cout << "Deleting File Number: ";
                    cin >> fileNo;

                    rewinddir(dir);

                    int ctr = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (entry->d_type == DT_REG) {
                            ctr++;
                            if(ctr == fileNo){
                                fileName = entry->d_name;
                                deleteRecord(fileName);
                            }
                        }
                    }
                }
                break;
            case 'e':
                closedir(dir);
                system("cls");
                cout << "Leaving";
                for(int i=0;i<3;i++){
                    //Sleep(1000);
                    cout << "."; 
                }
                system("cls");
                return 0;
        }

    } while(true);
    return 0;
}


void createRecord(){
    system("cls");
    string fileStr;
    string fileFolder = "records/";
    headerDisplay();
    cout << "File Directory: " << fileFolder << endl;
    cout << "Status: Creating New Record" << endl;
    cout << "***************************************************************************" << endl;
    cout << "File Name: ";
    getline(cin,fileStr);

    string filePath = fileFolder+fileStr;

    ofstream file(filePath);
    if(!file.is_open()){    
        cerr << "THERE WAS AN ERROR WITH FILE PROCESSING!\nFile Name: " << fileStr << endl;
        return;
    }

    // write contents in here
    //cout << endl;
    file.close();
    updateRecord(filePath);
    //close file
    return;
}

void deleteRecord(const string& fileName){
    string fileFolder = "records/";
    string filePath = fileFolder+fileName;

    cout << "Deleting: " << filePath << endl;

    if (remove(filePath.c_str()) != 0) {
        cerr << "Error deleting file: " << filePath << endl;
    }
    return;
}

void updateRecord(const string& fileName){
    cin.ignore();
    fstream file(fileName,ios::out|ios::in|ios::app);

    if(!file.is_open()){
        cerr << "THERE WAS AN ERROR WITH FILE PROCESSING!\nFile Name: " << fileName << endl;
        return;
    }
    bool sFlag = false;
    do{
        readRecord(fileName,true,sFlag,0,0);
        cout << "\n***************************************************************************" << endl;
        cout <<"[A] Add\t\t" << "[E] Edit\t" << "[D] Delete\t" << "[S] Sort A-Z\t" << "[B] Back" << endl;
        cout << "***************************************************************************" << endl;
    
        char ch = _getch();
        int delNum = 0;
        int ediNum = 0;
        switch(ch){
            case 'a':
                addStudent(fileName);
            break;

            case 'e':
                cout << "Editing File Number: ";
                cin >> ediNum;
                readRecord(fileName,true,sFlag,0,ediNum);
            break;

            case 'd':
                cout << "Deleting File Number: ";
                cin >> delNum;
                readRecord(fileName,true,sFlag,delNum,0);
            break;

            case 's':
                // code here
                sFlag = !sFlag;
            break;

            case 'b':
                return;
            break;
        } 

    }while(true);
}

void readRecord(const string& fileName,bool flag, bool sortFlag, int delNum, int ediNum){
    ifstream file(fileName);
    if(!file.is_open()){
        cerr << "THERE WAS AN ERROR WITH FILE PROCESSING!\nFile Directory: " << fileName << endl;
        return;
    }
    system("cls");

    do{
        string line;
        int ctr = 0;
        headerDisplay();
        cout << "File Directory: "<< fileName << endl;
        cout << "Status: File Active" << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        cout << setw(5) << left << "No.";
        cout << setw(12) << left << "School ID";
        cout << setw(20) << left << "Surname";
        cout << setw(20) << left << "First Name";
        cout << setw(12) << left << "Birth Date";
        cout << setw(6) << left << "Gender" << endl;
        cout << "---------------------------------------------------------------------------" << endl;

        vector<Student> students;

        while(getline(file,line)){
            stringstream ss(line);
            Student temp_Student;

            getline(ss, temp_Student.student_Id, ',');
            getline(ss, temp_Student.surname, ',');
            getline(ss, temp_Student.firstName, ',');
            getline(ss, temp_Student.birthDate, ',');
            getline(ss, temp_Student.gender, ',');

            students.push_back(temp_Student);

            ctr++;
        }
        
        if(sortFlag){
            students = sortStudents(students);
        }

        if(delNum != 0 && delNum <= students.size()){
            deleteStudent(fileName,students,students[delNum-1]);
        }

        if(ediNum != 0 && ediNum <= students.size()){
            editStudent(fileName,students,students[ediNum-1]);
        }

        for(int j=0;j<ctr;j++){
            cout << setw(5) << left    << j+1;
            cout << setw(12) << left << students[j].student_Id;
            cout << setw(20) << left << students[j].surname;
            cout << setw(20) << left << students[j].firstName;
            cout << setw(12) << left << students[j].birthDate;
            cout << setw(6) << left << students[j].gender << endl;
        }

        if(flag){
            return;
        }
        cout << "\n***************************************************************************" << endl;
        cout << "[E] Exit" << endl;
        cout << "***************************************************************************" << endl;
        char ch;   

        while(ch != 'e'){
            ch = _getch();
        }
        return;
    }while(true);
}