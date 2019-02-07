#!/usr/bin/perl

use utf8;
#use warnings;

# print "Hello, World\n";
# print 'Hello\nWorld';
# print "\n\N{SNOWMAN}\n";
# print "pippo" * 2;
# print "\n";
#
# print 1 + ("barney " x 4);
# print "\n";
# print "barney " x 4 +1;
# print "\n";
# print ("barney " x 4) +1;
# print "\n";
#
# print "first: ", "14.9x" % "0.32e1y","\n";
# print "second: " , (0xff % 0b11) + 012 , "\n";
# print "third " , 0xff ," ", 0b11 ," ", 012, "\n";
# print "forth ", "14.9x" ," ", "0.32e1y", "\n";

print "fred" eq 'fred', "\n";
print 35 eq 35.0,"\n";
print '35' eq '35.0',"\n";
print '35' == "35.0", "\n";
$x = 10;
print "'$x'", "\n";
print '"$x"' , "\n";

$str1 = 'Hello\t';
$str2 = "World\n";

print "$str1$str2"x2;

foreach (<STDIN>){
    print "$_ , ";
}
