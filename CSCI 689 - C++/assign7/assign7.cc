/*******************************************************************************
 * Read the content of a text file containing data in a the following format:
 *
 *   <int> an identifying number
 *   <string> a two character state abbreviation
 *   <string> a county name
 *   <float> Average January temperature (1941-1970)
 *   <float> Average hours of total January sunlight (1941-1970)
 *   <float> Average July temperature (1941-1970)
 *   <float> Average July humidity (1941-1970)
 *   <int> Average landform topography code (1-21)
 *   <float> Percent of area next to water
 *
 * The program receives in input from the user the name of the file containing
 * the information and it will parse and load it in a vector.
 * the vector is then printed to standard output.
 *
 * @author Michele Fattoruso - z1840898
 * @version 1.0 05/01/2018
 * @return 0 if the program is Successful.
 *         1 Wrong usage
 *         2 for errors in reading the file
 ******************************************************************************/

#include "assign7.h"

int main(int argc, char *argv[]){
    int n_lines = 12;   //number of lines to be printed by the print method
    ifstream file;      //file stream
    string temp_data;   //temporary hold the data read from the file
    vector<Amenity> vector1;
    //Check if the program received the correct number of arguments
    if( argc != 2 ){
        cerr << "Usage: " << argv[0] << " <Filename>" << endl;
        exit(1);
    }
    //open the file, and check that it's been opened correctly
    file.open(argv[1]);
    if( !file ){
        cerr << "Unable to open the file " << argv[1] << endl;
        exit(2);
    }
    //loop and half to read the data from the file, and save it in a set
    while (getline(file,temp_data)){ //read line by line
        //send the read line to the parser, that will return a pointer to an Amenity object
        Amenity* temp = amenityParser(temp_data);
        //add then the object to the vector
        vector1.push_back( *temp );
    }

    //close the file, as we are done reading from it
    file.close();
    //calculate the composite amenity for each object
    compositeAmenity(vector1);

    //declare a functor that will print consider the data of the january temperature
    AmenityFunctor fun1(AmenityFunctor::_JAN_MEAN);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    //declare a functor that will print consider the data of the sunshine value
    fun1.update(AmenityFunctor::_SUN_MEAN);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    //declare a functor that will print consider the data of the july temperature
    fun1.update(AmenityFunctor::_JUL_MEAN);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    //declare a functor that will print consider the data of the humidity
    fun1.update(AmenityFunctor::_HUMIDITY);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    //declare a functor that will print consider the data of the landform
    fun1.update(AmenityFunctor::_LAND_FORM);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    //declare a functor that will print consider the data of the water area
    fun1.update(AmenityFunctor::_WATER_AREA);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    //declare a functor that will print consider the data of the composite amenity
    fun1.update(AmenityFunctor::_COMP_AMENITY);
    //print n elements at the beginning and at the end of the vector
    print_top_bottom_n(vector1,n_lines,fun1);

    return 0;
}


/*******************************************************************************
 *
 * Parse a comma delimited string and return a pointer to Amenity
 *
 * This function will take as input a string, and will parse the data contained
 * in the string, create an amenity object, and return a pointer to it to the
 * caller
 *
 ******************************************************************************/
Amenity* amenityParser(string s){
    //delcaration of default values of the read variables
    int id=0, landForm=0;
    string state="", city="", delimiter = ",";
    float janMean=0.0, sunMean=0.0, julMean=0.0, humidity=0.0, waterArea=0.0;

    //indexes used to keep track of the starting and ending point of the current
    //value to be extracted from the string
    size_t begin = 0, end=0;

    /***************************************************************************
     * parse the data from the string.
     *
     * find the location of the next comma delimiter, get it's position, and
     * consider it as the end value of the current substring. Then extract the
     * substring, convert it to the correct value, in this case an integer, and
     * then assign it to the id variable. This operation gets executed for all
     * the content of the string, updating accordingly the starting and end value
     * of the substring, and performing the necessary conversion.
     **************************************************************************/

    //parsing the ID
    end = s.find(delimiter,begin);
    id = stoi( s.substr(begin,end) ); //cast string to int

    //parse the state
    begin=end+1;
    end = s.find(delimiter,begin);
    state = s.substr(begin,end-begin);

    //parse the city
    begin=end+1;
    end = s.find(delimiter,begin);
    city = s.substr(begin,end-begin);

    //parse the january mean
    begin=end+1;
    end = s.find(delimiter,begin);
    janMean = stof(s.substr(begin,end-begin)); //cast string to float

    //parse the sun mean
    begin=end+1;
    end = s.find(delimiter,begin);
    sunMean = stof(s.substr(begin,end-begin)); //cast string to float

    //parse the july mean
    begin=end+1;
    end = s.find(delimiter,begin);
    julMean = stof(s.substr(begin,end-begin)); //cast string to float

    //parse the humidity
    begin=end+1;
    end = s.find(delimiter,begin);
    humidity = stof(s.substr(begin,end-begin)); //cast string to float

    //parse the landform
    begin=end+1;
    end = s.find(delimiter,begin);
    landForm = stoi(s.substr(begin,end-begin)); //cast string to int

    //parse the water area
    begin=end+1;
    end = s.find(delimiter,begin);
    waterArea = stof(s.substr(begin,end-begin)); //cast string to float

    //return a new instance to an Amenity, calling the class constructor, with the value just extracted
    return new Amenity(id,state,city,janMean,sunMean,julMean,humidity,landForm,waterArea);
}


/*******************************************************************************
 *
 * Calculate the composite amenity of each Amenity object
 *
 * This function will take as input a string, and will parse the data contained
 * in the string, create an amenity object, and return a pointer to it to the
 * caller
 *
 ******************************************************************************/
void compositeAmenity(vector<Amenity> & vec){
    //Variables used to temporarily store the all the value necessary for thre computation
    //vectors to store all the value separated by category
    vector<float> allJanMean, allSunMean, allJulMean, allHumidity, allLandForm, allWaterArea;
    //floats used to temporarily store the calculated average value for each category
    float avgJanMean=0.0, avgSunMean=0.0, avgJulMean=0.0, avgHumidity=0.0, avgLandForm=0.0, avgWaterArea=0.0;
    //floats used to temporarily store the calculated standard deviation value for each category
    float stdJanMean=0.0, stdSunMean=0.0, stdJulMean=0.0, stdHumidity=0.0, stdLandForm=0.0, stdWaterArea=0.0;
    //floats used to temporarily store the calculated zIndex value for each category
    float zJanMean=0.0,zSunMean=0.0,zJulMean=0.0,zHumidity=0.0,zLandForm=0.0,zWaterArea=0.0;

    //store the vector size in a variable, as we don't want to call this method 2*n times, with n the number
    //of elements in the vector
    int vector_size=vec.size();

    //Extract all the value from the amenity object, by storing them in vectors separated by category
    for(int i=0;i<vector_size;i++){
        allJanMean.push_back(vec[i].getJanMean());
        allSunMean.push_back(vec[i].getSunMean());
        allJulMean.push_back(vec[i].getJulMean());
        allHumidity.push_back(vec[i].getHumidity());
        allLandForm.push_back(vec[i].getLandForm());
        //convert the percent in normal value
        allWaterArea.push_back( log( vec[i].getWaterArea()*100 ) );
    }

    //calculate the average value of all the values contained in the vectors
    avgJanMean=average(allJanMean);
    avgSunMean=average(allSunMean);
    avgJulMean=average(allJulMean);
    avgHumidity=average(allHumidity);
    avgLandForm=average(allLandForm);
    avgWaterArea=average(allWaterArea);

    //calculate the standard deviation value of all the values contained in the vectors

    stdJanMean=std_deviation(allJanMean,avgJanMean);
    stdSunMean=std_deviation(allSunMean,avgSunMean);
    stdJulMean=std_deviation(allJulMean,avgJulMean);
    stdHumidity=std_deviation(allHumidity,avgHumidity);
    stdLandForm=std_deviation(allLandForm,avgLandForm);
    stdWaterArea=std_deviation(allWaterArea,avgWaterArea);

    //loop over all the elements in the object vector, calculating the composite amenity value,
    //and then assigning the value to the object
    for(int i=0;i<vector_size;i++){
        //calculating the z index for each element in the amenity class
        zJanMean=(allJanMean[i] - avgJanMean)/stdJanMean;
        zSunMean=(allSunMean[i] - avgSunMean)/stdSunMean;
        zJulMean=(allJulMean[i] - avgJulMean)/stdJulMean;
        zHumidity=(allHumidity[i] - avgHumidity)/stdHumidity;
        zLandForm=(allLandForm[i] - avgLandForm)/stdLandForm;
        zWaterArea=(allWaterArea[i] - avgWaterArea)/stdWaterArea;

        //computing the composite amenity value, and then assigning it to the proper object
        vec[i].setAmenityValue(zJanMean+zSunMean-zJulMean-zHumidity+zLandForm+zWaterArea);
    }

}
