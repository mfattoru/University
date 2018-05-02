/*******************************************************************************
 * Display on screen a calendar.
 *
 * The program receives in input from the user two integers, month and year,
 * and display accordingly a calendar.
 * The program takes care of exceptions on number of days, also considering leap
 * years.
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 02/08/2018
 * @return 0 if the program is Successful, -1 for illegal imputs.
 ******************************************************************************/

#include "assign2.h"


int main(){
    int month,year;
    cout << "Month and Year? ";
    cin >> month >> year;

    //printing the header of the calendar
    calendar_header(month,year);
    //printing the body of the calendar
    calendar_body(month,year);

    return 0;
}

/*******************************************************************************
 * This function will print the BODY of the calendar. It will take as input
 * two integers, representing the year and the month, and will print to standard
 * output the days of the month.
 ******************************************************************************/

void calendar_body(int month,int year){
    int day=1; // days of the month start from 1
    //calculating the number of days available in the month.
    int monthDays=days_in_month(month,year);
    //Calculating the starting day of the week.
    int startingDay=starting_day(month,year);

    //Loop for printing the days of the month from zero to monthDays+startingDay
    //the first n=startingDay calendar cells will be empty in case the first day
    //of the month doesn't start at the beginning of the calendar page.
    for(int x=0;x<=monthDays+startingDay;x++){
        if( x<=startingDay ){ //if this is not the starting day
            cout << "   ";
        }
        else{ //print the day in a 2 digit space
            cout << setw(CELL_WIDTH) <<day++ << " ";
        }
        if(x%WEEKDAYS==0){ //if we reached the end of the week, go to the new line
            cout << endl;
        }
    }
    cout << endl;
}

/*******************************************************************************
 * This function is used to verify if an year is a leap year. It will take as
 * input an integer representing the year to analyze and will return a boolean
 * value of true or false if the year is a leap year or not.
 *
 * if (year is not divisible by 4) then (it is a common year)
 * else if (year is not divisible by 100) then (it is a leap year)
 * else if (year is not divisible by 400) then (it is a common year)
 * else (it is a leap year)
 ******************************************************************************/
bool leap_year(int year){
    bool leap_year=false;

    if(year % 4) leap_year=false;
    else if(year % 100) leap_year=true;
    else if(year % 400) leap_year=false;
    else leap_year=true;

    return leap_year;
}

/*******************************************************************************
 * This function will print the header of the calendar. It will take as input
 * two integers, representing the year and the month, and will print to standard
 * output the header of the calendar
 ******************************************************************************/
void calendar_header(int month, int year){
    const char * months[N_MONTHS] = {"January", "February", "March", "April", "May",
                               "June", "July", "August", "September", "October",
                               "November", "December"};
    char days_header[] = " S  M Tu  W Th  F  S";

    if( month < 1 || month > N_MONTHS){
        cerr <<"ERROR: "<< month <<" is not a valid month!"<<endl;
        exit(-1);
    }

    //calculating the length of the string month+year to identify the starting
    //position to center the text in the calendar.
    //this way the text is centered for every year, regardless of the number of
    //digits of the year,or letters of the month.
    int curr_length=strlen(months[month-1]) + num_of_digits(year) + 1;
    int starting_pos=(strlen(days_header)-curr_length)/2;

    //filling the first positions with spaces, to be able to print the text in a
    // centered position
    for(int x=0;x<starting_pos;x++){
        cout << " ";
    }
    cout << months[month-1] << " " << year << endl;
    cout << days_header;
}

/*******************************************************************************
 * This function will calculate the number of digit of the year.
 *
 * It will take as input an integer, and will return the number of digits of
 * that number. This function will be used to return the number of digits of the
 * year, so that the first line of the header can be properly centered
 ******************************************************************************/
int num_of_digits(int number){
    int digits=1;
    while(true){
        if (number > 10){
            digits++;
            number/=10;
        }
        else break;
    }
    return digits;
}


/*******************************************************************************
 * This function will calculate the number of days that are in the month. It
 * will take as input two integers representing the year and the month, and will
 * return an integer, representing the number of days that are in the month
 ******************************************************************************/
int days_in_month(int month, int year){
    int calc;
    if( month == 2 ){
        if(leap_year(year))
            return 29;
        return 28;
    }
    else{
        calc=( ( ( month + 11 ) * 7 ) % 12 );
        if ( calc < 7 )
            return 31;
        return 30;
    }
}

/*******************************************************************************
 * This function will calculate what day is the first day of the input date. It
 * will take as input two integers representing the year and the month, and will
 * return an integer value,representing the starting day of the week.
 * 0 representing Sunday, 1 representing Monday and so on up to 6 representing
 * Saturday
 ******************************************************************************/
int starting_day(int month, int year){
    int reduced_year=year-1;
    int approx1=0,approx2=0; //approximation 1 and 2 for the formula
    int total;

    //formula where the magic happens
    approx1=reduced_year*365 + reduced_year/4 -
            reduced_year/100 + reduced_year/400;

    approx2=(month*367 -362 )/12;

    total=approx1+approx2+1;

    if( month > 2 ){
        if( leap_year(year))
            total-=1;
        else
            total-=2;
    }

    total=total%7;
    return total;
}
