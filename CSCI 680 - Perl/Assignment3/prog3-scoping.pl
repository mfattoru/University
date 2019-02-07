#!/usr/bin/perl -w

use strict;
use List::Util qw ( min max );

{
    #declaring a scoped variable chesssize used to store the size of the chess
    my $chessSize;
    ##declaring a scoped variable used to store the number of times the programName
    #should try to beat the game
    my $numRepetitions;
    #declaring a scoped variable used to store the number of prints that the
    #program should perform while completing all the repetitions
    my $printFrequency;
    #declaring a scoped variable to store the calsulated print frequency, so every
    #how many repetitions the program should print information about the current
    #run
    my $printRate;

    #1-Dimensional array used to hold the information about each cell of the chess
    my @chess;

    #scoped variables used to hold the current position in row and column of the
    #knight
    my $curRow;
    my $curCol;

    #Array used to calculate the knight possible moves around the chess
    #Move number:     0  1  2  3  4  5  6  7
    my @horz  = qw (  2  1 -1 -2 -2 -1  1  2 );
    my @vert  = qw ( -1 -2 -2 -1  1  2  2  1 );

    #function used to round a number, it will be added to decimal numbers,
    #and in case a number is bigger or equal than x.5, it will be rounded
    #to the next number. x=1 ==> 1.56 + 0.5 = 2.06, we then apply int, and it
    #wil truncate it's value to 2.
    sub roundNumber(){
        my ($number) = @_;
        my $ROUND_NUMBER = 0.5;
        int($number + $ROUND_NUMBER);
    }

    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #
    # Driver program, used to get the information from the command line,
    # manipulate it, and perform the right function calls to correctly execute
    # the program.
    #
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sub driver(){
        #get the arguments from the command line arguments
        ($chessSize,$numRepetitions,$printFrequency) = &checkArgs(@ARGV);
        #set the random number generator seed
        srand(1);
        #initialize the trial number to 1
        my $trialNumber = 1;
        #calculate the print rate. every how many repetitions we need to print
        #statistics about the current try.
        #if the total number of repetitions it less than the print frequency, then
        #the print rate is the number of repetitions. so we will have just one
        #single print at the end.
        if($numRepetitions < $printFrequency){
            $printRate = $numRepetitions;
        }else{
            $printRate = &roundNumber($numRepetitions / $printFrequency );
        }
        #print at the beginning an header with the size of the chess
        print "*** size = $chessSize ***\n";
        #declating an array of results, where we can store how many cellsTouched
        #the knight have touched for each trial
        my @results;

        #loop until we completed all the trials
        while($trialNumber <= $numRepetitions){
            #Initialize or reset the chess to have all the cells equal to false,
            #which means that no cell has been visited
            @chess = (0) x $chessSize**2;

            #get a random starting position on the chess
            &getStart($trialNumber);

            #call the moveKnight function and store the result of touched cellsTouched
            #in out result array
            push @results,&mvKnight($trialNumber);

            #increase the number of performed trials
            $trialNumber++;
        }
        #at the end of all the trials, print statistics about all the iterations
        &printResults(@results);
    }

    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #
    # Function in charge of calculating and printing statistics about the
    # performed iterations. it takes as input an array containing the results of
    # each iteration and prints to standard output the calculated statistics
    #
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sub printResults{
        #assigning the result array to the locat variable results
        my @results = @_;
        #declaring a variable used to store the sum of all the trials
        my $sum;
        #loop over the array and sum all the results
        foreach (@results){
            $sum += $_;
        }
        #use the max function to calculate the maximum value inside the array
        my $max = max @results;
        #use the min function to calculate the minimum value inside the array
        my $min = min @results;
        #calculating the average value as the sum of all the results, devided by
        #the number of repetitions performed
        my $avg = $sum / $numRepetitions;

        #print the statistics on standard output
        print "\nTotal number of trials: $numRepetitions\n";
        print "Minimum number of squares touched: $min\n";
        print "Maximum number of squares touched: $max\n";
        print sprintf "Average number of squares touched: %.2f\n\n",$avg;
    }


    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #
    # Function used to allow the knight to move around the chess. this Function
    # will call the nextMove function until there are no more possible moves to
    # be performed. ad the same times it will count the number of cells the
    # knight touched, and return that value to the caller.
    #
    # This function takes as input the current trial number, to know if for the
    # current trial it has to print the total number of swuares touched by the knight
    #
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sub mvKnight{
        #saving the current trial number as a local variable
        my ($trialNumber) = @_;

        #Initializing the number of touched cells to 1, as the starting position
        #already counts as a touched cell
        my $cellsTouched = 1;

        #call in a loop the nextMove function. This function will calculate and
        #if possible perform a move on the chessSize.
        #If a move was made, it will return true, the number of cells touched
        #will be incremented, and a new move will be tried.
        #if a move cannot be made, the function nextMove will return false, and
        #the loop will stop
        while( &nextMove() ){
            $cellsTouched++;
        }

        #once we performed as many movement as possible, if the current trial is
        #one to be printed, then we print the number of squares touched
        if( $trialNumber % $printRate == 0){
            print "\tTotal number of squares touched: $cellsTouched\n";
        }
        #then we return the number of touched cells
        $cellsTouched;
    }


    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #
    # Function used to calculate the possible moves in the chess from the current
    # position, and choose a random movement between all the available ones.
    #
    # If a move was made, it will return true
    # if a move cannot be made, the function nextMove will return false
    #
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sub nextMove{
        #declaring a local variable index, used to loop arounf all the moves,
        my $index=0;

        #declaring an array used to store the index of all the available moves
        #the knight can do around the chess from the current position
        my @availableMoves;

        #loop over all the possible moves to see if a move will put the knight
        #outside of the chess, or in a position already visited. only valid moves
        # will be stored in the available moves array
        foreach $index (0..7){
            #calculating the next row and culumn of the chess once the movement
            #at index $index is performed
            my $nextRow = $curRow + $vert[ $index ];
            my $nextCol = $curCol + $horz[ $index ];

            #translating the row and column of the chess, to index of the
            #1-dimensional array
            my $nextMoveIndex = ($nextRow-1)*$chessSize + $nextCol-1;

            #if the next row, and next column are in the range of the chess, so
            #from row 1 to $chessSize and from column 1 to $chessSize, and if the
            #cell hasn't been visited yet, then we add the move to the list of
            #valid moves
            if( $nextRow > 0 && $nextRow <= $chessSize &&     #if the next move is within the allowed row space
                $nextCol > 0 && $nextCol <= $chessSize &&
                $chess[$nextMoveIndex] == 0){      #and is within the allowed column space
                push @availableMoves,$index;
            }
        }

        #if we have at least one valid move to be made
        if(scalar(@availableMoves)){
            #we select a random move from the available moves
            my $moveIndex = int( rand( scalar(@availableMoves) ) );
            my $nextMove = $availableMoves[$moveIndex];

            #and then we update the current row and column of the knight
            $curRow += $vert[ $nextMove ];
            $curCol += $horz[ $nextMove ];

            #we calculate the index in the chess array of the randomly performed
            #move
            my $nextMoveIndex = ($curRow-1)*$chessSize + $curCol-1;

            #and we mark the cell as visited
            $chess[$nextMoveIndex] = 1;
            #and then we return 1 (true), to tell the caller that a move was made
            return 1;
        }
        #if the array of available moves is empty, it means that the knight
        #can't move from that position, so we return 0 (false), to tell the caller
        #that the current trial can end
        return 0;
    }


    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #
    #This function is used to randomly assign the knight in a cell of the chess
    #
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sub getStart{
        #we store the current trial number to a local vaiable
        my ($trialNumber) = @_;

        #we then calculate a random point where the knight can start, so in our
        #case the chess is represented as a 1-dimensional array, with chessSize^2
        #number of elements
        my $startingPoint = int( rand ( $chessSize**2) );

        #after choosing the random start position, we mark that position as visited
        $chess[$startingPoint] = 1;

        #we then convert the array index value to his value as row and column in
        #the chess
        $curRow = int($startingPoint /  ($chessSize)) +1;
        $curCol = $startingPoint % ( $chessSize ) +1 ;

        #then if the current trial number is one when we have to print information,
        #we print to standard output the current trial number, and the rtarting
        #row and column of the knight
        if( $trialNumber % $printRate == 0){
            print "\nTrial number: $trialNumber\n";
            print "\tRandom starting point: ($curRow,$curCol)\n";
        }
    }

    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    #
    #   Check how many arguments the program received as input.
    #
    #   if the number of input arguments in bigger than 3, print a message on
    #   standard error, and close the program
    #
    #   if only two arguments are given, then consider the print frequency to
    #   be 10. if only one argument is given, then consider the number of trials
    #   to be performed be equal to 1, an if no argument are given, consider
    #   the chess size to be 1
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    sub checkArgs{
        #calculate the number of arguments received as input
        my $argsCount = @_;
        my @args;

        #if the number of arguments is more than the three optional
        if( $argsCount > 3){
            #print a message on stanadrd error and close the program
            die "usage: perl $0 < ChessSize = 1 > < #trials = 1 > < printFrequency = 10>.\n";
        }elsif( $argsCount == 3 ){
            @args = @_;
        }elsif( $argsCount == 2 ){
            #set the print frequancy to 10
            @args = (@_,10);
        }elsif ($argsCount == 1 ){
            #set the number of trials to 1 and the print frequency to 10
            @args = (@_,1,10);
        }else{ #$argsCount == 0
            #set chess size to 1,the number of trials to 1 and the print frequency
            #to 10
            @args = (1,1,10);
        }

        #if the user inputs negative numbers for any of the input values, then exit the program
        #with an error message
        die "usage: the chess size must be a number bigger than zero\n" unless $args[0] > 0;
        die "usage: the number of trials must be a number bigger than zero\n" unless $args[1] > 0;
        die "usage: the print frequency must be a positive number\n" unless $args[2]>=0;

        return @args;
    }

    #execute the driver program
    &driver;

}
