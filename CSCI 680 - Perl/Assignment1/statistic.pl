#!/usr/bin/perl -w

use strict;

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#   Application to calculate statistical values from a file
#
#   The following application is ised to calculate statistical values like
#   the minimum, maximum, average and standard deviation of a list of numbers
#   received in input both from a file or from command line.
#
#   Usage: <programName> [file1] [file2] ... [fileN]
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

#get input from the file or command prompt and save it into an array
my @fileLines = <>;
#remove the trailing newline from all the elements of the array
chomp(@fileLines);
#call the print_stat method to calculate and display the statistics
&print_stat(@fileLines);

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Calculate the minimum value in a list
#
#   the current function takes as input a list, and returns the minimum value
#   contained in it.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub low{
    #save the input list as local variable
    my @lowList = @_;
    #initialize to zero the scalar that will containe the minimum
    my $minimum = 0;

    #if we have at least one element, we need to search for the minimum
    if(@lowList > 0){

        #Take the first element in the list as current minimum
        $minimum = shift(@lowList);

        #loop over all the remaining elements of the list
        foreach (@lowList){
            #if the current value is smaller than the minimum, then the current
            #is the new minimum
            if( $_ < $minimum ){
                $minimum = $_;
            }
        }
    }
    #return the minimum value found
    $minimum;
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Calculate the maximum value in a list
#
#   The current function takes as input a list, and returns the maximum value
#   contained in it
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub high{
    #save the input list as local variable
    my @highList = @_;
    #initialize to zero the scalar that will containe the maximum
    my $maximum = 0;

    #if we have at least one element, we need to search for the maximum
    if(@highList > 0){

        #Take the first element in the list as current maximum
        $maximum = shift(@highList);
        #loop over all the remaining elements of the list
        foreach (@highList){
            #if the current value is bigger than the maximum, then the current
            #is the new maximum
            if( $_ > $maximum ){
                $maximum = $_;
            }
        }
    }
    #return the maximum value found
    $maximum;
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Calculate the sum of all the elements contained in a list
#
#   The current function takes as input a list, and returns a value equal to
#   the sum of all the element contained in it
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub total{
    #save the input list as local variable
    my @totalList = @_;
    #initialize to zero the scalar that will containe the total sum
    my $total = 0;

    #loop over all the remaining elements of the list
    foreach(@totalList){
        #add the current value to the total
        $total += $_;
    }
    #return the total
    $total;
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Calculate the average of all the elements contained in a list
#
#   The following function takes as input a list, and returns a value equal to
#   the average of all the elements contained in it.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub average{
    #save the input list as local variable
    my @avgList = @_;
    #initialize to zero the scalar that will containe the average
    my $result = 0;

    #if the list has at least one element, calculat ethe average
    if(@avgList > 0){
        #calculat ethe average and return it
        $result = total(@avgList) / @avgList;
    }else{
        #return the initialized value
        $result;
    }
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Calculate the standard deviation of all the elements in a list
#
#   The following funcsion takes as input a list, and returns a value equal to
#   the standard deviation of all the elements contained in it.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub std_deviation{
    #save the input list as local variable
    my @stdList = @_;
    #initialize to zero the scalar that will containe the standard deviation
    my $result = 0;

    #if the list has at least two elements, we can calculate the standard deviation
    if(@stdList > 1){
        #get the mean value, by calling the average subroutine
        my $mean = &average(@stdList);

        #loop over all the element in the list,
        foreach(@stdList){
            #and perform some calculation for the standard deviation
            $result += ($_ - $mean)**2;
        }
        #other calculation for the standard deviation
        $result /= (@stdList-1);
    }
    #return the result of the standard deviation. the square root of all
    #calculated before
    $result**0.5;
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#   Print on screen the results
#
#   The following funcsion prints on screen all the values returned from the
#   different fstatistics functions. The print are made so that all the values
#   appear as right aligned, and rounded to two decimal points.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub print_stat{
    #save the input list as local variable
    my @statList = @_;
    #print the low with a 5 digit padding and rounded to two decimal points
    print sprintf "Low:\t%5.2f\n", &low( @statList);
    #print the high with a 5 digit padding and rounded to two decimal points
    print sprintf "High:\t%5.2f\n", &high(@statList);
    #print the mean with a 5 digit padding and rounded to two decimal points
    print sprintf "Mean:\t%5.2f\n", &average(@statList);
    #print the standard deviation with a 5 digit padding and rounded to
    #two decimal points
    print sprintf "StdDev:\t%5.2f\n", &std_deviation(@statList);
}
