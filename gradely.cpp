#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <string>
#include <cstdlib>
using namespace std;


void clearScreen() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}


class Student {
private:
    int rollno;
    char name[50], lastName[50];
    int phyMarks, cheMarks, mathsMarks, engMarks, csMarks;
    float percentage;
    char grade;
    void calculate();

public:
    void getData();
    void showData();
    int getRollnum();
};


void Student::calculate() {
    percentage = (phyMarks + cheMarks + mathsMarks + engMarks + csMarks)/5.0;
    if(percentage >= 80)
        grade = 'A';
    else if(percentage >= 70)
        grade = 'B';
    else if(percentage >= 60)
        grade = 'C';
    else if(percentage >= 50)
        grade = 'D';
    else if(percentage >= 40)
        grade = 'E';
    else if(percentage >= 33)
        grade = 'F';
    else
        grade = 'F';
}


void Student::getData() {
    cout<<"\n\tEnter the Roll number of Student: ";
    cin>>rollno;
    cout<<"\n\tEnter the First Name of Student: ";
    cin>>name;
    cout<<"\n\tEnter the Last Name of Student: ";
    cin>>lastName;
    cout<<"\n\tEnter the Marks in Physics out of 100: ";
    cin>>phyMarks;
    cout<<"\n\tEnter the Marks in Chemistry out of 100: ";
    cin>>cheMarks;
    cout<<"\n\tEnter the Marks in Maths out of 100: ";
    cin>>mathsMarks;
    cout<<"\n\tEnter the Marks in English out of 100: ";
    cin>>engMarks;
    cout<<"\n\tEnter the Marks in Computer Science out of 100: ";
    cin>>csMarks;
    calculate();
}


void Student::showData() {
    clearScreen();
    cout<<"\t------------------------";
    cout<<"\n\tStudent Detail | Gradely\n";
    cout<<"\t------------------------";
    cout<<"\n\n\tRoll No: "<<rollno;
    cout<<"\n\n\tName of Student: "<<name<<" "<<lastName;
    cout<<"\n\n\tMarks in Physics: "<<phyMarks;
    cout<<"\n\n\tMarks in Chemistry: "<<cheMarks;
    cout<<"\n\n\tMarks in Mathematics: "<<mathsMarks;
    cout<<"\n\n\tMarks in English: "<<engMarks;
    cout<<"\n\n\tMarks in Computer Science: "<<csMarks;
    cout<<"\n\n\tPercentage of Student is: "<<percentage;
    cout<<"\n\n\tGrade of Student is: "<<grade<<endl<<endl;
}


int Student::getRollnum() {
    return rollno;
}


void writeStudent() {
    Student st;
    ofstream outfile;
    outfile.open("student.dat", ios::binary | ios::app);
    st.getData();
    outfile.write((char*)&st, sizeof(Student));
    outfile.close();
    cout<<"\n\n\tStudent record has been created!";
    cout<<"\n\tPress any key to continue...";
    cin.get();
    cin.get();
}


void displayStudent(int n) {
    Student st;
    ifstream infile;
    infile.open("student.dat", ios::binary);
    if(!infile){
        cout<<"\n\tFile could not be open!";
        cout<<"\n\tPress any key to continue...";
        cin.get();
        cin.get();
        return;
    }

    int temp = 0;
    while(infile.read((char*)&st, sizeof(Student))){
        if(st.getRollnum() == n){
            st.showData();
            temp = 1;
        }
    }
    infile.close();
    if(temp == 0){
        cout<<"\n\n\tRecord does not exist!";
        cout<<"\n\tPress any key to continue...";
        cin.get();
        cin.get();
    }
}


void modifyStudent(int n) {
    clearScreen();
    int found = 0;
    Student st;
    fstream file;
    file.open("student.dat", ios::binary | ios::in | ios::out);
    if(!file){
        cout<<"\n\n\tFile could not be open!!";
        getch();
        return;
    }
    while(file.read((char*)&st, sizeof(Student)) && found==0){
        if(st.getRollnum() == n){
            st.showData();
            cout<<"\n\n\tPlease Enter the new details of student "<<endl;
            st.getData();
            int pos = (-1)*sizeof(st);
            file.seekp(pos, ios::cur);
            file.write((char*)&st, sizeof(Student));
            cout<<"\n\n\t Record Updated";
            found = 1;
        }
    }
    file.close();
    if(found == 0){
        cout<<"\n\n\tRECORD NOT FOUND!";
    }
    getch();
}


void deleteStudent(int n) {
    Student st;
    ifstream infile;
    infile.open("student.dat", ios::binary);
    if(!infile){
        cout<<"\n\n\tFile could not be open! Press any Key to continue...";
        getch();
        return;
    }
    ofstream outfile;
    outfile.open("temp.dat", ios::out);
    infile.seekg(0, ios::beg);
    while(infile.read((char*)&st, sizeof(Student))){
        if(st.getRollnum() != n){
            outfile.write((char*)&st, sizeof(Student));
        }
    }
    outfile.close();
    infile.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    cout<<"\n\n\tRECORD DELETED...";
    getch();
}


void result() {
    char ch;
    int rollno;

    cout<<"\n\n\t---------------------";
    cout<<"\n\tResult Menu | Gradely\n";
    cout<<"\t---------------------";
    cout<<"\n\n\t1. View Report Card";
    cout<<"\n\n\t2. Back to Main Menu";
    cout<<"\n\n\tPlease Enter Your Choice(1/2): ";
    cin>>ch;
    switch(ch){
    case '1':
        cout<<"\n\tEnter Roll number of Student: ";
        cin>>rollno;
        displayStudent(rollno);
        break;
    case '2':
        break;
    default:
        cout<<"\n\tERROR! Wrong Choice Entered!";
        cout<<"\n\tPress any key to continue...";
        cin.get();
        cin.get();
    }
}


void studentEntryMenu() {
    char ch;
    int num;
    
    cout<<"\n\n\t--------------------";
    cout<<"\n\tManage Menu | Gradely\n";
    cout<<"\t--------------------";
    cout<<"\n\n\t1. Create Student Record";
    cout<<"\n\n\t2. Search Student Record";
    cout<<"\n\n\t3. Modify Student Record";
    cout<<"\n\n\t4. Delete Student Record";
    cout<<"\n\n\t5. Back to Main Menu";
    cout<<"\n\n\tPlease Enter Your Choice(1-5): ";
    cin>>ch;
    switch(ch){
    case '1':
        writeStudent();
        clearScreen();
        break;
    case '2':
        cout<<"\n\n\tPlease Enter the roll number ";
        cin>>num;
        displayStudent(num);
        break;
    case '3':
        cout<<"\n\n\tPlease Enter the roll number ";
        cin>>num;
        modifyStudent(num);
        break;
    case '4':
        cout<<"\n\n\tPlease Enter the roll number ";
        cin>>num;
        deleteStudent(num);
        break;
    case '5':
        clearScreen();
        break;
    default:
        cout<<"\a";
        cout<<"\n\tERROR! Wrong Choice Entered!\n\n";
        studentEntryMenu();
    }
}


int password() {
    string pass = "";
    char ch;
    cout<<"\n\n\t----------------------------";
    cout<<"\n\tGradely | Grading Simplified\n";
    cout<<"\t----------------------------";
    cout<<"\n\n\tEnter Password: ";
    ch = _getch();
    while(ch != 13){
        pass.push_back(ch);
        cout<<'*';
        ch = _getch();
    }
    if(pass == "12345"){
        cout<<"\n\n\tAccess Granted :)\n\n";
    }else{
        cout<<"\n\n\tAccess Denied! Enter Correct Password!\n";
        cout<<"\tPress any key to continue...";
        cin.get();
        clearScreen();
        password();
    }
}


// MAIN FUNCTION

int main() {
    password();
    char ch;
    cout.setf(ios::fixed | ios::showpoint);
    cout<<setprecision(2);
    clearScreen();
    do {
        cout<<"\n\t-------------------";
        cout<<"\n\tMain Menu | Gradely\n";
        cout<<"\t-------------------";
        cout<<"\n\n\t1. Result Menu";
        cout<<"\n\n\t2. Manage Menu";
        cout<<"\n\n\t3. EXIT";
        cout<<"\n\n\tPlease Enter Your Choice: ";
        cin>>ch;
        switch(ch){
            case '1':
                clearScreen();
                result();
                clearScreen();
                break;
            case '2':
                clearScreen();
                studentEntryMenu();
                clearScreen();
                break;
            case '3':
                cout<<"\n\tThank You! Your Session Ended Successfully.";
                cout<<"\n\tGRADELY | Grading Simplified\n\n";
                return 0;
                break;
            default:
                cout<<"\n\tERROR! Wrong Choice Entered!\n\n";
        }
    } while(ch != '3');
}