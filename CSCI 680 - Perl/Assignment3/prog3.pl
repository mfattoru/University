#!/usr/bin/perl -w

use strict;



# my $m;
# my $curRow += $vert [ $m ];
# my $curCol += $horz [ $m ];

#counter from 1 to n2
# Record the latest count in each square the knight moves to.
my $counter = 1;

#choose a random starting point among n^2 cells and move the knight around until no more move is possible.

#For a given value of n,repeat this experiment for N ≥ 1 times, and enter these values at the command line.

# If the name of your program as prog3, then to test your program for n = 4 and N = 10, execute the command:
# prog3 4 10
# For default value use n = 1 and N = 1

#To generate random numbers, use the Perl function 'rand EXPR'
# This function returns a fractional number greater than or equal to 0 and less than the value of
#EXPR.If EXPR is omitted, the value 1 is used

sub driver(){
    my $ROUND_NUMBER = 0.5;
    #write a Perl program to move the knight around the chessboard of size n
    (my $chessSize,my $numRepetitions,my $printFrequency) = &checkArgs(@ARGV);
    #set the random number generator seed
    srand(1);
    my $trialNumber = 1;
    my $printRate = 0;
    #every how many repetitions we are supposed to print statistics
    if($numRepetitions < $printFrequency){
        $printRate = $numRepetitions;
    }else{
        $printRate = int( $numRepetitions / $printFrequency + $ROUND_NUMBER);
    }
    print "*** size = $chessSize ***\n\n";
    my $min=0;
    my $max=0;
    my $avg=0;

    while($trialNumber <= $numRepetitions){
        #Initialize the chess
        my @chess = (0) x $chessSize**2;

        my ($startRow,$startCol) = &getStart($chessSize,$trialNumber,$printRate,@chess);

        #$chess[$start] = 1;
        my $squaresTouched = &mvKnight($chessSize,$trialNumber,$printRate,$startRow,$startCol,@chess);
        if($squaresTouched > $max){
            $max = $squaresTouched;
        }elsif($squaresTouched < $min){
            $min = $squaresTouched;
        }
        $avg += $squaresTouched;
        # print "my $chessSize,my $numRepetitions,my $printFrequency\n";
        #print "@chess\n";
        #&printChess($chessSize,@chess);
        $trialNumber++;
    }
    $avg /= $numRepetitions;
    &printResults($numRepetitions,$min, $max, $avg);
}

sub printResults{
    my($numRepetitions,$min, $max, $avg) = @_;

    print "\nTotal number of trials: $numRepetitions\n";
    print "Minimum number of squares touched: $min\n";
    print "Maximum number of squares touched: $max\n";
    print "Average number of squares touched: $avg\n";
}

sub mvKnight{
    my $chessSize = shift(@_);
    my $trialNumber = shift(@_);
    my $printRate = shift(@_);
    my $startRow = shift(@_);
    my $startCol = shift(@_);

    # my @localChess = @_;
    my $cellsTouched = 1;
    while(&nextMove($startRow,$startCol,$chessSize,@_)){
        $cellsTouched++;
    }
    if( $trialNumber % $printRate == 0){
        print "\tTotal number of squares touched: $cellsTouched\n";
    }
    #print "Total number of squares touched: $cellsTouched\n";
    #&nextMove($startRow,$startCol,$chessSize,@_);
    #print "@_\n";
    # my $curRow = int($startingPoint /  ($chessSize)) +1;
    # my $curCol = $startingPoint % ( $chessSize ) +1 ;

    # $curRow += $vert [ $m ];
    # $curCol += $horz [ $m ];
    # if( $curRow > 0 && $curRow <= $chessSize &&     #if the next move is within the allowed row space
    #     $curCol > 0 && $curCol <= $chessSize){      #and is within the allowed column space
    #     return 1;
    # }else{
    #     return 0;
    # }
}

sub printChess(){
    my $chessSize = shift(@_);
    my $index=0;
    for($index = 0; $index < scalar(@_);++$index){

        if($index % $chessSize == 0){
            print "\n";
        }
        print "$_[$index] ";
    }
    print "\n";
}

sub nextMove{
    #Move number:     0  1  2  3  4  5  6  7
    my @horz  = qw (  2  1 -1 -2 -2 -1  1  2 );
    my @vert  = qw ( -1 -2 -2 -1  1  2  2  1 );

    my $curRow = shift(@_);
    my $curCol = shift(@_);
    my $chessSize = shift(@_);
    my $index=0;

    my $nextMove = int( rand( 8 ) );

    $curRow += $vert[ $nextMove ];
    $curCol += $horz[ $nextMove ];

    #print "R $curRow C $curCol";
    my $nextMoveIndex = ($curRow-1)*$chessSize + $curCol-1;
    #print "next: $nextMoveIndex\n";
    if( $curRow > 0 && $curRow <= $chessSize &&     #if the next move is within the allowed row space
        $curCol > 0 && $curCol <= $chessSize &&
        $_[$nextMoveIndex] == 0){      #and is within the allowed column space
        $_[$nextMoveIndex] = 1;
        #print "if\n";
        return 1;
    }else{
        #print "else\n";
        return 0;
    }
}

sub getStart{
    my $chessSize = shift(@_);
    my $trialNumber = shift(@_);
    my $printRate = shift(@_);

    my $startingPoint = int( rand ( $chessSize**2) );
    #printf("Starting: $startingPoint Size: $chessSize\n");
    $_[$startingPoint] = 1;
    my $row;
    my $column;
    if( $trialNumber % $printRate == 0){
        print "Trial number: $trialNumber\n";
        $row = int($startingPoint /  ($chessSize)) +1;
        $column = $startingPoint % ( $chessSize ) +1 ;
        print "\tRandom starting point: ($row,$column)\n";
    }
    return ($row,$column);
}

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
    if( $argsCount > 3){
        #print a message on stanadrd error and close the program
        die "usage: perl $0 < ChessSize = 1 > < #Repetitions = 1 > < #OfPartialResults = 10>.\n";
    }elsif( $argsCount == 3 ){
        return @_;
    }elsif( $argsCount == 2 ){
        return (@_,10);
    }elsif ($argsCount == 1 ){
        return (@_,1,10);
    }else{ #$argsCount == 0
        return (1,1,10);
    }
}
sub markCellAsVisited{
    (my $row,my $comuln,my @chess) = @_;
}
&driver;
