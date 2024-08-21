/**************************************************************************************************
 Name        : main.c
 Author      : Atif Ehab
 Description : Student Management System
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

// structure to be used in code
struct student
{
	char name[50];
	int ID;
	int age;
	float GPA;
};

struct node
{
	struct student data;
	struct node *next;
};

// initialization of the some addresses that will be used in the code
struct node *head = NULL;
struct node *current = NULL;
struct node *previous = NULL;

// functions prototype
void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

int main()
{
	struct student newStudent;
	int choice;
	int ID;
	float average;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	// Main menu loop
	while(1)
	{
		printf("\n----- Student Management System -----\n"
				"1. Add new student.\n"
				"2. Display all students.\n"
				"3. Search for a student by ID.\n"
				"4. Update the student information.\n"
				"5. Delete a student.\n"
				"6. Calculate the average GPA.\n"
				"7. Search for student with the highest GPA.\n"
				"8. Exit the program.\n"
				"Enter your choice: ");
		scanf("%d", &choice);
		// According to the number user enter it will go and execute specific operation
		switch (choice)
		{
		case 1:
			printf ("Enter student information\n");
			printf("Student Name:");
			scanf(" %[^\n]", newStudent.name);
			printf("Student ID: ");
			scanf("%d", &newStudent.ID);
			printf("Student age: ");
			scanf("%d", &newStudent.age);
			printf("Student GPA: ");
			scanf("%f", &newStudent.GPA);
			addStudent(&newStudent);
			break;
		case 2:
			displayStudents();
			break;
		case 3:
			printf("Enter student ID to search: ");
			scanf("%d",&ID);
			searchStudentByID(ID);
			break;
		case 4:
			printf("Enter student ID to update information: ");
			scanf("%d",&ID);
			updateStudent(ID);
			break;
		case 5:
			printf("Enter student ID to delete information: ");
			scanf("%d",&ID);
			deleteStudent(ID);
			break;
		case 6:
			average = calculateAverageGPA();
			printf("The average GPA for students: %.2f", average);
			break;
		case 7:
			searchHighestGPA();
			break;
		case 8:
			printf("Exiting the program");
			return 0;
		default:
			printf("Invalid choice, please try again\n");
			break;
		}
	}
}

// Function to create linked list
void addStudent(const struct student *const ptr)
{
	// Allocate memory for new student
	struct node *newStudent = (struct node*) malloc (sizeof(struct node));
	struct node *ID_ptr = head;
	// Check if there is a location for new student
	if (newStudent == NULL)
	{
		printf("memory allocation failed.\n");
		return;
	}
	newStudent->data = *ptr;
	newStudent->next = NULL;
	// Check if the entered ID already exists
	while(ID_ptr != NULL)
	{
		if(ID_ptr->data.ID == newStudent->data.ID)
		{
			printf("There is a student with same ID please try with another ID");
			free(newStudent);
			return;
		}
		ID_ptr = ID_ptr->next;
	}
	// If the list is empty, add the new student as the head
	if(head == NULL)
	{
		head = newStudent;
		return;
	}
	current = head;
	// This loop is until reach the last node in the list to add new one
	while(current->next != NULL)
	{
		current = current->next;
	}
	// Making the last node in the old list point to new node
	current->next = newStudent;
	printf("The student added successfully.");
}

// Function to display the list
void displayStudents(void)
{
	struct node *ptr = head;
	// Check if head is empty it return nothing
	if (head == NULL)
	{
		printf("There are no students to show.\n");
		return;
	}
	printf("	--- List of student. ---\n");
	printf("***************************************\n");
	// Cross the list and display each student's information
	while (ptr != NULL)
	{
		printf("Student Name: %s\n", ptr->data.name);
		printf("Student ID: %d\n", ptr->data.ID);
		printf("Student age: %d\n", ptr->data.age);
		printf("Student GPA: %.2f\n",ptr->data.GPA);
		printf("***************************************\n");
		ptr = ptr->next;
	}
}

// This function is to search for student by using ID
void searchStudentByID(int id)
{
	struct node *ID_ptr = head;
	/* Check if the location is empty if not, it loops until reach
	the student with the same ID and print student information*/
	while(ID_ptr != NULL)
	{
		if(ID_ptr->data.ID == id)
		{
			printf ("--- Student found ---\n");
			printf("***************************************\n");
			printf("Student Name: %s\n", ID_ptr->data.name);
			printf("Student ID: %d\n", ID_ptr->data.ID);
			printf("Student age: %d\n", ID_ptr->data.age);
			printf("Student GPA: %.2f\n", ID_ptr->data.GPA);
			printf("***************************************\n");
			return;
		}
		ID_ptr = ID_ptr->next;
	}
	// If the id not found it print this
	printf("The student with ID %d is not found\n",id);
}

// This function allow you to update the student information
void updateStudent(int id)
{
	struct node *ID_ptr = head;
	/* Check if the location is empty if not, it loops until it reach the student with
	the target id and you can change all the information or keep them and change one of them*/
	while(ID_ptr != NULL)
	{
		if(ID_ptr->data.ID == id)
		{
			printf ("update the information for student with ID: %d\n",id);
			printf("Student Name:");
			scanf(" %[^\n]", ID_ptr->data.name);
			printf("Student age: ");
			scanf("%d", &ID_ptr->data.age);
			printf("Student GPA: ");
			scanf("%f", &ID_ptr->data.GPA);
			printf("Information updated successfully");
			return;
		}
		ID_ptr = ID_ptr->next;
	}
	// if the student is not found it will print this
	printf("Student with ID %d is not found.",id);
}

// This Function is to calculate the average GPA
float calculateAverageGPA(void)
{
	float average;
	float sumGPA = 0.0;
	int studentNumber = 0;
	struct node *avg_ptr = head;
	// Check if head is empty it return 0
	if (head == NULL)
	{
		return 0.0;
	}
	/* Check if the location is empty if not, it loops until reach
	the last student and read it's GPA and know the number of students*/
	while(avg_ptr != NULL)
	{
		sumGPA += avg_ptr->data.GPA;
		studentNumber++;
		avg_ptr = avg_ptr->next;
	}
	average = sumGPA / studentNumber;
	return average;
}

// This function search for the student with the highest GPA
void searchHighestGPA(void)
{
	struct node *loop_ptr = head;
	// Check if head is empty it return nothing
	if (head == NULL)
	{
		printf("There are no students.\n");
		return;
	}
	current = head;
	/* This loop Check if the location is empty if not,
	it loops until reach the student with the highest GPA*/
	while(loop_ptr != NULL)
	{
		if(loop_ptr->data.GPA > current->data.GPA)
		{
			current = loop_ptr;
		}
		loop_ptr = loop_ptr->next;
	}
	// It print the student information
	printf("--- Student with the highest GPA ---\n");
	printf("***************************************\n");
	printf("Student Name: %s\n", current->data.name);
	printf("Student ID: %d\n", current->data.ID);
	printf("Student age: %d\n", current->data.age);
	printf("Student GPA: %.2f\n", current->data.GPA);
	printf("***************************************\n");
}

// This function is for deleting the student information from the list
void deleteStudent(int id)
{
	struct node *ID_ptr = head;
	// Check if head is empty it return nothing
	if(head == NULL)
	{
		printf("There are no students.\n");
		return;
	}
	current = head;
	previous = head;
	/* Check if the location is empty if not, it loops until reach the student with
	target id and delete the student information from list and link new list again*/
	while(ID_ptr != NULL)
	{
		if(ID_ptr->data.ID == id)
		{
			current = ID_ptr;
			previous->next = current->next;
			printf("The student with following information:\n");
			printf("Student Name: %s\n", current->data.name);
			printf("Student ID: %d\n", current->data.ID);
			printf("Student age: %d\n", current->data.age);
			printf("Student GPA: %.2f\n", current->data.GPA);
			free(current);
			printf("is successfully removed\n");
			return;
		}
		previous = ID_ptr;
		ID_ptr = ID_ptr->next;
	}
	// If the student is not found it prints this
	printf("There is no student with this ID: %d\n",id);
}
