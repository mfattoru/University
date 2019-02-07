#!/usr/bin/perl -w

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#   Application to calculate the number of repetition of words in a file
#
#   The following application is ised to calculate the number of repetitions
#   of words in a file.
#
#   Usage: <programName> <InputFile> <OutputFile>
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

use strict;

#check the if the number of arguments given in input is correct
checkArgs(@ARGV);

#Open the two files given in input and return the handlers
my( $inputFh, $outputFh) = openFiles(@ARGV);

#read the file, and return a list of read words
my @splitWords = createList($inputFh);

#use the read list to create a hash
my %H1 = createHash(@splitWords);

#print statistic related to the hash
printHash($outputFh,%H1);

#close the file handlers
closeFiles($inputFh,$outputFh);


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#   Check how many arguments the program received as input.
#
#   if the number of input arguments in different than 2, print a message on
#   standard error, and close the program
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub checkArgs{
    #calculate the number of arguments received as input
    my $argsCount = @_;
    #if the number of arguments is different than the two required
    if( $argsCount != 2){
        #print a message on stanadrd error and close the program
        die "usage: perl $0 <input file> <output file>.\n";
    }
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#   Open the files received in input by the user, and return two file handlers
#   for the input and output file
#
#   If the opening of one of the files fails, it prints a message to standard
#   error, and close the program
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub openFiles{
    #get the subroutine input arguments
    my @inputArgs = @_;

    #open the first argument as an input file, so in read mode
    open(my $input, "<", $inputArgs[0])
        or die "Unable to open input file $inputArgs[0]: $!";

    #open the second file as an output file, so in write mode
    open(my $output, ">", $inputArgs[1])
        or die "Unable to open output file > $inputArgs[1]: $!";

    #return a list of two elements, containing the file handler to the input and
    #output file
    ($input, $output);
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#   Close the two files handler related to the files received in input by the
#   user.
#
#   If the closing of one of the file handler fails, it prints a message to
#   standard error, and close the program
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub closeFiles{
    #save the subroutinr input argumet as wto scalar input and output
    my ( $input,$output ) = @_;

    #close the input file, or print a message and close the program if it fails
    close($input)
        or die "Close of input file $input failed: $!";

    #close the output file, or print a message and close the program if it fails
    close($output)
        or die "Close of output file $output failed: $!";
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#   Read from the input file all the lines, and save each read word to a list.
#
#   return the generated list
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub createList{
    #get the subroutine input arguments
    my ( $inputFile) = @_;
    #Array to save the word found in the file
    my @wordList;

    #read from the file one line at a time
    while(my $line = <$inputFile>){
        #remove newlines from the end of the line
        chomp($line);

        #split the line with spaces and dashes as separator, and save the
        #result in a temporary list
        my @tempList = split /(\s|-)/, $line;

        #push the temporary list, generated from the splitting of the current line
        #inside the array that will be returned by the subroutine
        push(@wordList, @tempList);
    }
    #return a list with all the found words
    @wordList;
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#   Received in input an array of words
#
#   Each word is manipulated, so that eventual non-alphabetical characters are
#   removed from the start and end of a word, and also words with middle dashes
#   separator are considered as two different words.
#
#   A word that is separated in the middle by a non-alphabetical character
#   different from a dash, the part after the character is ignored
#
#   return an hash containing the word as key and the occurrence as values
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub createHash{
    #get the subroutine input arguments
    my @wordList = @_;
    #declare the hash where to save the data
    my %hash;

    foreach my $word (@wordList){
        #convert the word to lowercase
        $word = "\L$word";
        #remove beginning and end non alphabetic characters
        $word =~ s/(^[^a-zA-Z]+|[^a-zA-Z]+$)//g;
        #f the word contains non-alphabetical characters in the middle, ignore
        #the alphabetical characters beyond them, but not the dashes

        #TODO: by mistake deleted a char, check if it needs the g as global in the next substitution
        $word =~ s/[^a-zA-Z-].+//;

        #if the resulting word is different from empty string
        if( $word ne ""){
            #add it to the hash map
            $hash{$word} += 1;
        }
    }
    #return the hash
    %hash;
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#
#   Received in input an hash containing words as keys and occurrences as values
#
#   prints to the output file in column of three, the content of the hash in the
#   form of key:value
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sub printHash{
    #get the subroutine input arguments
    my $outFile = shift(@_);
    #convert the array to hash
    my %hash = @_;
    #initialize an index variable so we can separate the output in three columns
    my $index = 0;
    #calculate the size of the hash
    my $size = keys %hash;

    #print to output file the size of the hash
    print $outFile "size = $size\n\n";

    #loop over all the keys of the hash, sorted in alphabetical order
    foreach my $key (sort keys %hash){
        #print the key:value with key padding of 15 and left aligned, and value
        #with a 3 digit padding
        printf $outFile "%-15s :%3d",$key , $hash{$key};
        #increase the index
        $index++;

        #if we reach a third column, or we reached the end of the hash,
        #print a newline
        if( $index % 3 == 0 || $index == $size){
            print $outFile "\n";
        }else{ #if not, separate the column by a tab
            print $outFile "\t";
        }
    }
}
