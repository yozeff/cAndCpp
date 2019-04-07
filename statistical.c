//
//  statistical.c
//
//
//  Created by Joseph Harrison on 06/01/2019.
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main()
{
    /*description
     get input filename for data
     get number of items in file
     open file with filename
     unpack data into array
     close input file
     get output filename
     calculate mean
     calculate mode
     sort array
     calculate median
     calculate range, interquartile range
     and standard deviation
     display results
     close output file
    */

    bool search(float array[], float item);
    float mean_average(float array[], int length);
    void mode_average(float array[], int items, FILE *results);
    void bubble_sort(float array[], int length);
    void insertion_sort(float array[], int length);
    float standard_deviation(float array[], int length, float average);
    float interquartile_range(float array[], int length);

    //get filename
    char filename[100];
    printf("input filename: ");
    scanf("%s",filename);

    //get number of items in file
    int items;
    printf("number of items: ");
    scanf("%d",&items);

    //open file
    FILE *data = fopen(filename,"r");

    //declare array
    float dataArray[items];

    //read data file and items to data array
    float item;
    for (int i = 0; i < items; i++){
        fscanf(data,"%f\n",&item);
        dataArray[i] = item;
    }

    //close file
    fclose(data);

    //get output filename
    printf("output filename: ");
    scanf("%s",filename);

    //open results file
    FILE *results = fopen(filename,"w");

    //calculate mean average
    float average = mean_average(dataArray,items);

    //display mean and add to file
    printf("mean: %f\n",average);
    fprintf(results,"mean: %f\n",average);

    //calculate mode
    mode_average(dataArray,items,results);

    //sort data array
    insertion_sort(dataArray,items);
    //print median
    float median = dataArray[items / 2];
    printf("median: %f\n",median);
    fprintf(results,"median: %f\n",median);

    //array is already sorted
    //so range is final minus first elements
    float range = dataArray[items - 1] - dataArray[0];
    printf("range: %f\n",range);
    fprintf(results,"range: %f\n",range);

    //standard deviation and variance
    float stdDev = standard_deviation(dataArray,items,average);
    float variance = pow(stdDev,2);
    printf("standard deviation: %f\nvariance: %f\n",stdDev,variance);
    fprintf(results,"standard deviation: %f\nvariance: %f\n",stdDev,variance);

    //interquartile range
    float intQtlRange = interquartile_range(dataArray,items);
    printf("interquartile range: %f\n",intQtlRange);
    fprintf(results,"interquartile range: %f\n",intQtlRange);

    //close results file
    fclose(results);

}

bool search(float array[], float item)
{
    bool found = false;
    //loop through array searching for item
    for (int i = 0; i < sizeof(&array); i++){
        if (array[i] == item){
            found = true;
        }
    }
    return found;
}

float mean_average(float array[], int length)
{

    //sum all array elements
    float sum = 0;
    for (int i = 0; i < length; i++){
        sum += array[i];
    }

    //calculate mean
    float average = sum / length;

    return average;
}

void mode_average(float array[], int length, FILE *results)
{

    //define structure to store mode
    struct mode{
        float value;
        int occur;
    } ;

    //init current mode struct
    struct mode currentMode;
    currentMode.occur = 0;

    //init modes array
    //use if more than one mode
    float modes[length];
    //mode count for indexing
    int number;

    //loop through each item
    float current;
    int occur;
    for (int i = 0; i < length; i++){

        current = array[i];
        occur = 0;

        //get occurences
        for (int j = 0; j < length; j++){

            if (current == array[j]){
                occur += 1;
            }
        }

        //if more occurences than current mode guess
        //make new mode
        if (occur > currentMode.occur){
            currentMode.value = current;
            currentMode.occur = occur;
            modes[0] = current;
            number = 1;
        }
        //if equal occurences as current mode guess
        //increment number of modes and add current to modes array
        else if (occur == currentMode.occur){
            if (search(modes,current) == false){
                modes[number] = current;
                number += 1;
            }
        }
    }

    //if multiple modes
    if (number > 1 && number != length){
        printf("%d modes occurring %d times:\n",number,currentMode.occur);
        fprintf(results,"modes:\n");

        for (int i = 0; i < number; i++){
            printf("%d : %f\n",i + 1,modes[i]);
            fprintf(results,"%d : %f\n",i + 1,modes[i]);
        }

    }
    else if (number > 1){
        printf("no mode\n");
        fprintf(results,"no mode\n");
    }
    //if one mode
    else{
        printf("mode: %f occurring %d times\n",currentMode.value,currentMode.occur);
        fprintf(results,"mode: %f occurring %d times\n",currentMode.value,currentMode.occur);
    }
}

void bubble_sort(float array[], int length)
{
    bool swaps = true;
    float temp;

    while (swaps == true){

        swaps = false;

        for (int i = 1; i < length; i++){

            if (array[i - 1] > array[i]){

                temp = array[i - 1];
                array[i - 1] = array[i];
                array[i] = temp;
                swaps = true;
            }
        }
    }
}

void insertion_sort(float array[], int length)
{
    float val;
    int j;
    for (int i = 1; i < length; i++){
        val = array[i];
        j = i - 1;
        while (j >= 0 & val < array[j]){
            array[j + 1] = array[j];
            j -= 1;
        }
        array[j + 1] = val;
    }
}

float standard_deviation(float array[], int length, float average)
{
    float stdDev;
    float sum = 0.0;
    for (int i = 0; i < length; i++){
        sum += pow(array[i],2);
    }

    //calculate standard deviation
    stdDev = sqrt((sum / length) - pow(average,2));

    return stdDev;
}

float interquartile_range(float array[], int length)
{
    int q1 = length / 4;
    int q3 = 3 * length / 4;
    float range = array[q3] - array[q1];
    return range;
}
