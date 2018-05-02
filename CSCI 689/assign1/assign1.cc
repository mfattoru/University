/**
 * Calculate the heat index value for a range of temparature (F) and humidity (%)
 *
 * Calculate and print in a table format the heat index value.
 * The program receive as input the starting and ending range of temperature and
 * humidity, plus a step increment for both of the units, and prints to the screen
 * the heat index value for all the possible combination of the values.
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 01/30/2018
 * @return 0 if the programi is Successful, for illegal imputs:
 *          -1: starting range bigger than ending range.
 *          -2: negative increment step.
 *          -3: Humidity not in the 0-100 (%) range.
 *
 * NOTE: I could have inserted fewer if conditions, by letting the user for
 * example insert both minimum and max temperature and check that if the two
 * values were in range, but I preferred to immediatly stop the user as soon as
 * he inserts a wrong value, that's why a check of the value follows
 * immediately after the input of the value itself.
 */

#include "assign1.h"

int main(){
    //deltaT and deltaH represent respectively the step increment of temperature
    //and humidity
    float minTemp,maxTemp,minHumidity,maxHumidity,deltaT,deltaH;

    cout << "This program prints out a table of approximate heat index values\n"
         << endl;

    cout << "Temperature range low value (degrees F) ? ";
    cin >> minTemp;
    cout << "Temperature range high value  (degrees F) ? ";
    cin >> maxTemp;

    if ( minTemp > maxTemp ){
        cerr << "ERROR: The minimum temperature cannot be higher than "
                "the maximum temperature" << endl;
        return -1;
    }

    cout << "Temperature increment (degrees F) ? ";
    cin >> deltaT;

    if ( deltaT <= 0 ){
        cerr << "ERROR: The tempararute increment need to be a value "
                "bigger than zero" << endl;
        return -2;
    }

    cout << "\nRelative humidity low value (%) ? ";
    cin >> minHumidity;

    if ( minHumidity < 0 && minHumidity > 100){
        cerr << "ERROR: The minimum humidity is a value between 0% "
                "and 100% "<< endl;
        return -3;
    }

    cout << "Relative humidity high value(%) ? ";
    cin >> maxHumidity;

    if ( maxHumidity < 0 && maxHumidity > 100){
        cerr << "ERROR: The maximum humidity is a value between 0% "
                "and 100% "<< endl;
        return -3;
    }

    if ( minHumidity > maxHumidity ){
        cerr << "ERROR: The minimum humidity cannot be higher than "
                "the maximum humidity" << endl;
        return -1;
    }

    cout << "Relative humidity increment (%) ? ";
    cin >> deltaH;

    if ( deltaH <= 0 ){
        cerr << "ERROR: The humidity increment need to be a value "
                "bigger than zero" << endl;
        return -2;
    }

    printTable(minTemp,maxTemp,deltaT,minHumidity,maxHumidity,deltaH);

    return 0;
}

/**
 * Calculate heat index value;
 *
 * This function will take as input the air temperature expressed in degrees
 * Fahrenheit as first parameter and the relative humidity in percent
 *
 * Usage: heatIndexValue( float <air Temperature> ,
 *                        float <air Humidity>)
 * @return float containing the heat index value
 */

float heatIndexValue(float airTemperature, float humidity){
    float hiv = - 42.379 + ( 2.04901523 * airTemperature ) + ( 10.1433127 * humidity )
                - ( 0.22475541 * airTemperature * humidity )
                - ( 6.83783 * pow(10,-3) * pow( airTemperature, 2 ) )
                - ( 5.481717 * pow( 10 , -2 ) * pow(humidity,2) )
                + ( 1.22874 * pow(10,-3) * pow( airTemperature, 2 ) * humidity )
                + ( 8.5282 * pow( 10 , -4 ) * airTemperature * pow( humidity , 2 ) )
                - ( 1.99 * pow( 10 , -6 ) * pow(airTemperature,2) * pow(humidity,2) );
    return hiv;
}

/**
 * Print a formatted table containing the estimates of heat index value for
 * a range of temperature (degree F) and humidity (%)
 *
 * Getting in input the starting and ending point range of temperature and humidity,
 * plus the step increment for temperature and increment, the function will
 * print to screen a table containing the heat index value for every combination
 * of humidity and temperature
 *
 * Usage: printTable( float <Temperature starting range> ,
 *                    float <Temperature ending range> ,
 *                    float <Temperature step increment> ,
 *                    float <Humidity starting range> ,
 *                    float <Humidity ending range> ,
 *                    float <Humidity step increment> )
 */

void printTable(float minT,float maxT, float deltaT, float minH, float maxH, float deltaH){
    // column number variable is used to save the number of columns in the table,
    // In this way I'm able to print a separator  line of dashes without the
    // need of looping
    //column number starts from 1 because there will always be a column
    //showing at indexes of the tables
    int column_number = 1;
    cout << "\nHeat Index Table" << endl;
    cout << "\nRelative Humidity" << endl;
    cout << setw(CELL_WIDTH) << "(%)";

    // Set the precision of the cout, this will allow me to print numbers with
    // Two digits after the dot for each floating number
    // fixed force cout to print zeros, to fill the digit number set by
    // setprecision, even for number without decimal part:
    // E.g.   10 --> 10.00
    cout << setprecision(2) << fixed;

    //Print the list of all the humidity range, printing the header of the table
    for ( float curr_humidity=minH; curr_humidity<=maxH ; curr_humidity+=deltaH){
        cout << setw(CELL_WIDTH) << curr_humidity;
        column_number++;
    }
    cout << endl;

    //filling a line with dashes. the amount of dashes will be equal to the
    //CELL_WIDTH, that is the number of characters allowed for each value, multiplied
    //for the number of columns in the table, value calculated before when printing
    //the list of humidity values.
    //setfill will print a dash in every empty digit cell CELL_WIDTH * column_number times
    //setfill is then reset to space character
    cout << setfill('-') << setw(CELL_WIDTH*column_number) << "" <<  setfill(' ');

    cout << "\nAir Temperature\n(deg. F)"<< endl;

    //run the heatIndexValue function for all the combinations of temperature
    // and humidity between the range
    for (float curr_temp=minT; curr_temp<=maxT; curr_temp+=deltaT){
        cout << setw(CELL_WIDTH-1) << curr_temp << "|";
        for (float curr_hum=minH; curr_hum<=maxH; curr_hum+=deltaH){
            cout << setw(CELL_WIDTH) << heatIndexValue(curr_temp,curr_hum);
        }
        cout << endl;
    }
}
