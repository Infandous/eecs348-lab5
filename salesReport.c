#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_MONTHS 12

float *getSalesNums(FILE *file); //function to get the sales numbers from the input file. Returns a pointer to an array of doubles
void salesReport(float *monthlySales,char *months[NUM_MONTHS]); //function to generate sales report 
void salesSummary(float *monthlySales,char *months[NUM_MONTHS]); //function to generate sales summary (min,max,avg)
bool largerSmaller(float num1, float num2); //checks which number is larger, return true if num1, false otherwise
void sixMonthAvg(float *monthlySales, char *months[NUM_MONTHS]); //function to print six-month movine averages
void salesReportDescending(float *monthlySales, char *months[NUM_MONTHS]); //generate a sales report in decending order

int main(int argc, char *argv[]){
  char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  //check to ensure user has input a file as command line argument
  if (argc != 2){
    //if the proper number of arguments is not given, inform the user and exit the program
    printf("The program expects a .txt file to be givven as a command line argument.\n");
    printf("Example: %s inputFile.txt\n", argv[0]);
    return 1;
  }

  //otherwise set the pointer filename equal to the input file
  char *filename = argv[1];
  FILE *file = fopen(filename,"r"); //open file and set to read
  float *salesNums = getSalesNums(file); //get sales numbers from file

  //generate sales report
  salesReport(salesNums,months);
  //generate sales summary
  salesSummary(salesNums,months);
  //create sixe-month moving avg report
  sixMonthAvg(salesNums,months);

  //get descending report
  salesReportDescending(salesNums,months);

  //clean up and exit the program
  fclose(file);
  free(salesNums);
  return 0;
}

//function to get sales numbers from file
float *getSalesNums(FILE *file){
  float *array = (float*) malloc(NUM_MONTHS*sizeof(float)); //used to hold sales report numbers for every month of the year
  float num; //used to hold a number from one months of sales reports
  int counter = 0; //used to index array
  //read in data from file
  while (fscanf(file,"%f",&num)==1){
    array[counter] = num; //add num to array
    counter++; //increment counter
  }
  return array;
}

//function to print out monthly sales report
void salesReport(float *monthlySales,char *months[12]){

  printf("Monthly sales report:\n\n");
  printf("Month      Sales\n");
  int numSpaces = 11;//used as the basis to calculate the number of spaces on each row
  for (int i=0; i<NUM_MONTHS; i++){ //for every month
    printf("%s",months[i]); //print month
    for (int x=0; x<(numSpaces-strlen(months[i])); x++){ //print required number of spaces
      printf(" ");
    }
    printf("%0.2f\n",monthlySales[i]);//print sales for the month
  }
  printf("\n");
}

//function to generate sales summary
void salesSummary(float *monthlySales, char *months[NUM_MONTHS]){
  int min=0,max=0; //used to hold index on min and max months, initially set to index 0
  float sum = 0; //holds the sum of all the months sales
  float minSale = monthlySales[0], maxSale = monthlySales[0]; // declare minSale and maxSale, set initially to index 0
  sum += monthlySales[0]; //add sales from January to sum as initial value
  //loop through every month
  for (int t=1; t<NUM_MONTHS; t++){
    if (!largerSmaller(monthlySales[t],minSale)){ //if monthlySale at t is smaller than minSale
      min = t; //set new min index
      minSale = monthlySales[t]; //set new minimum sale value
    }
    if(largerSmaller(monthlySales[t],maxSale)){ //if monthlySale at t is larger than maxSale
      max=t; //set new max index
      maxSale = monthlySales[t]; //set new max sale value
    }
    sum += monthlySales[t]; //add monthly sale at t to sum
  }

  //print out sales summary
  printf("Sales summary:\n\n");
  printf("Minimum sales: $%0.2f (%s)\n",minSale,months[min]);
  printf("Maximum sales: $%0.2f (%s)\n",maxSale,months[max]);
  printf("Average sales: $%0.2f\n\n",(sum/NUM_MONTHS));
}

//determines which number is larger
bool largerSmaller(float num1, float num2){
  if (num1>num2)
    return true;
  return false;
}


//function to list six month moving averages
void sixMonthAvg(float *monthlySales, char *months[NUM_MONTHS]){
  printf("Six-Month Moving Average Report:\n");
  float sum; //used to hold sum every month over 6 months
  for (int i = 0; i<(NUM_MONTHS-5); i++){ //loop over every month we can calculuate moving average
    sum = 0; //set sum to 0
    for (int t = i; t<(i+6); t++){//for every month from i for 6 months (inclusive)
      sum += monthlySales[t]; //add monthlySales at month t to sum
    }
    printf("%s - %s: $%0.2f\n",months[i],months[i+5],(sum/6)); //print report
  }
  printf("\n");
}

//generate sales report in descending order
void salesReportDescending(float *monthlySales, char *months[NUM_MONTHS]){
    //int i, j;
    float tempSale; //used to hold temporary sale entry
    char *tempMonth; //used to hold temporary month
    int numSpaces = 11;//used as the basis to calculate the number of spaces on each row

    //sort to be in descending order
    for (int i = 0; i < NUM_MONTHS - 1; i++) {
        for (int j = 0; j < NUM_MONTHS - i - 1; j++) {
            if (monthlySales[j] < monthlySales[j + 1]) { //if current sale is less than current sale + 1, swap
                // Swap sales
                tempSale = monthlySales[j];
                monthlySales[j] = monthlySales[j + 1];
                monthlySales[j + 1] = tempSale;
                // Swap months
                tempMonth = months[j];
                months[j] = months[j + 1];
                months[j + 1] = tempMonth;
            }
        }
    }

    //print report
    printf("Sales Report (Highest to Lowest):\n");
    for (int i=0; i<NUM_MONTHS; i++){ //for every month
    printf("%s",months[i]); //print month
    for (int x=0; x<(numSpaces-strlen(months[i])); x++){ //print required number of spaces
      printf(" ");
    }
    printf("%0.2f\n",monthlySales[i]);//print sales for the month
    }
    printf("\n");
}