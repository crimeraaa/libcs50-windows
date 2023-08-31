#include <stdio.h>

#include <cs50.h>

int main(void)
{
    char *name   = get_string("Enter the student's name: ");
    int age      = get_int("Enter %s's current age: ", name);
    char section = get_char("Enter %s's current section: ", name);
    float gpa    = get_float("Enter %s's current gpa: ", name);

    printf("STUDENT INFORMATION\n");
    printf("Name:    %s\n", name);
    printf("Age:     %i years old\n", age);
    printf("Section: %c\n", section);
    printf("GPA:     %f\n", gpa);
    return 0;
}