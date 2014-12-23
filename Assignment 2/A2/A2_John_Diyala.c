#include <stdio.h>
#include <string.h>

#define MAX_STR  32
#define MAX_COMP  50
#define MAX_SCHEME  50

//Data structure that represents course component and weighing scheme info
typedef struct {
  int numComponents;
  int numSchemes;
  char component[MAX_COMP][MAX_STR];
  float scheme[MAX_SCHEME][MAX_COMP];
} MarkingSchemeType;

//Function declarations that are defined after main()
void  getCompData(MarkingSchemeType *crs);
void  getSchemeData(MarkingSchemeType *crs);
void  calculateGrades(MarkingSchemeType *crs);

//As simple as a main() can be
int main()
{
  MarkingSchemeType  course;
  MarkingSchemeType  *coursePtr;

  coursePtr = &course;

  getCompData(coursePtr);
  getSchemeData(coursePtr);
  calculateGrades(coursePtr);

  return 0;
}

//Gets course component data from the user and appropriate stores this data using pointers
void getCompData(MarkingSchemeType *crs)
{
  printf("How many marking components in this course? ");	
  while (scanf("%d",&crs->numComponents)!=1 || crs->numComponents <= 0){
    printf("Please enter a valid number of components: ");
  }

  int i;
  for (i = 0; i < crs->numComponents; i++){
    printf("\tEnter the name of component number %d: ",i+1);
    scanf("%s",crs->component[i]);
  }
}

//Gets course scheme data from the user and appropriately stores this data using pointers
void getSchemeData(MarkingSchemeType *crs)
{
  printf("\nHow many marking schemes? ");	
  while (scanf("%d",&crs->numSchemes)!=1 || crs->numSchemes <= 0){
    printf("Please enter a valid number of schemes: ");
  }

  int i,j;
  int total = 0;


  for (j = 0; j < crs->numSchemes; j++){			//Iterate through each scheme
    printf("\nMarking scheme #%d:\n",j+1);
    for (i = 0; i < crs->numComponents; i++){			//Iterate through each component within a scheme, storing the weight
      printf("\tEnter the weight of %s: ",crs->component[i]);
      while (scanf("%f",&crs->scheme[j][i])!=1 || crs->scheme[j][i] <= 0 || crs->scheme[j][i] > 100)	// error checking
        printf("\tPlease enter a valid weight: ");
    }
    for (i = 0; i < crs->numComponents; i++){			//Make sure all components add up to 100%
      total += crs->scheme[j][i];
    }
    if (total != 100){
       printf("Total of components does not add up to 100. Try again.\n\n");
       j--;
    }
    total = 0;
  }
}

//Gets grades from the user for each component, calculates and outputs the result according to each marking scheme
void calculateGrades(MarkingSchemeType *crs)
{
  float grades[crs->numComponents];
  float finalGrade = 0;
  int i,j;

  printf("\n");
  for (i = 0; i < crs->numComponents; i++){		//Iterate through each course component, storing each grade
    printf("Enter %s mark: ",crs->component[i]);
    while (scanf("%f",&grades[i]) !=1 || grades[i] < 0 || grades[i] > 100)	//Assuming a student can't get bonus marks (>100)
      printf("\tPlease enter a valid mark:%f ",grades[i]);
  }
  for (j = 0; j < crs->numSchemes; j++){		//Iterate through each scheme, calculating according to that scheme
    for (i = 0; i < crs->numComponents; i++)
      finalGrade += grades[i]*crs->scheme[j][i]/100;
  printf ("\nGrade using marking scheme #%d: %.2f",j+1,finalGrade);
  finalGrade = 0;
  }
  printf("\n");
}

