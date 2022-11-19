#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

#define NUM_REPORTS 10
#define NUM_GRADES_PER_SUBJECT 100

using namespace std;

class student {
 public:
	student(string _name, string _surname)
	:name(_name), surname(_surname) {
	}
	void addGrade(string subject, int grade) {
		grades[subject].push_back(grade);
	}

	const map < string, vector < int >>&getGrades() const {
		return grades;
	}
	const vector < int >&getSubjectGrades(const string & subject) const {
		return grades.find(subject)->second;
	}
	double getGPA(const string & subject) const {
		int num = 0;
		double gpa = 0.0;

		for (vector < int >::const_iterator i =
		     getSubjectGrades(subject).begin();
		     i != getSubjectGrades(subject).end(); i++)
			if (*i > 5) {
				gpa += *i;
				num++;
			}

		return num > 0.0 ? gpa / num : 0.0;
	}

	double getGPA() const {
		int num = 0;
		double gpa = 0.0;

		for (map < string, vector < int > >::const_iterator k =
		     grades.begin(); k != grades.end(); k++) {
			double got = getGPA(k->first);
			if (got > 0.0) {
				gpa += got;
				num++;
			}
		}
		return num > 0.0 ? gpa / num : 0.0;
	}

	const string getName() const {
		return name;
	}
	const string getSurname() const {
		return surname;
	}
	bool operator ==(const student & other) const {
		return (name == other.name) && (surname == other.surname);
	}
 private:

	 string name;
	string surname;
	map < string, vector < int >>grades;
};

void printClassNames(const vector < student > Class)
{

	for (unsigned i = 0; i < Class.size(); i++)
		cout << Class[i].
		    getName() << " " << Class[i].getSurname() << endl;
}

void printStudentGrades(vector < student > Class, const string name,
			const string surname)
{
	vector < student >::iterator i =
	    find(Class.begin(), Class.end(), student(name, surname));
	if (i == Class.end())
		return;

	for (map < string, vector < int > >::const_iterator kv =
	     i->getGrades().begin(); kv != i->getGrades().end(); kv++) {
		cout << kv->first << " : ";
		for (vector < int >::const_iterator ocena = kv->second.begin();
		     ocena != kv->second.end(); ocena++)
			cout << *ocena << " ";
		cout << "\t\t" << i->getGPA(kv->first) << endl;
	}
}

void printStudent(vector < student > Class, const string name,
		  const string surname)
{
	vector < student >::iterator i =
	    find(Class.begin(), Class.end(), student(name, surname));
	if (i != Class.end()) {
		cout << i->getName() << " " << i->getSurname() << endl;
		printStudentGrades(Class, name, surname);
	}

	cout << "GPA: " << i->getGPA() << endl << endl;

}

void printClass(vector < student > Class)
{
	printClassNames(Class);

	cout << endl << endl;

	for (vector < student >::iterator i = Class.begin(); i != Class.end();
	     i++)
		printStudent(Class, i->getName(), i->getSurname());

}

int main()
{
	vector < student > Class;

	vector < string > subjects;
	ifstream file("subjects.txt");

	string subject;
	while (getline(file, subject))
		subjects.push_back(subject);

	file.close();

	file.open("students.txt");

	string name, surname;
	while (file >> name >> surname)
		Class.push_back(student(name, surname));

	file.close();

	for (unsigned i = 0; i < Class.size(); i++) {
		for (unsigned j = 0; j < subjects.size(); j++) {
			for (int k = 0; k < NUM_GRADES_PER_SUBJECT; k++) {
				int grade = rand() % 6 + 5;
				Class[i].addGrade(subjects[j], grade);
			}
		}
	}

	int num_reports = NUM_REPORTS;

	while (num_reports) {
		cout << "==================REPORT " << num_reports <<
		    "===================\n";
		printClass(Class);
		cout << "==================REPORT " << num_reports <<
		    "===================\n";
		num_reports--;
	}

	return 0;
}
