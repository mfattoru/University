#!/usr/bin/perl -w

use strict;

my $file = <>;
chomp $file;

my @stats = stat $file;

# print "stat: @stats\n";
print "Device Number: $stats[0]\n";
print "INode: $stats[1]\n";
printf "AccessMode: %o\n",$stats[2];
print "Hard Link: $stats[3]\n";
print "UserID: $stats[4]\n";
print "GroupD: $stats[5]\n";
print "rdev: $stats[6]\n";
print "Size: $stats[7]\n";
my $time = localtime $stats[8];
printf "Atime: %s\n", $time;
$time = localtime $stats[9];
printf "Mtime: %s\n", $time;
$time = localtime $stats[10];
printf "Ctime: %s\n", $time;
print "BlockSize: $stats[11]\n";
print "blocks: $stats[12]\n";
