#!/usr/bin/perl -w

use 5.26.0;
use strict;
#
# my %hash = (
#     'one' => 12345,
#     'two' => 2,
#     'three' => 3,
#     'four' => 4,
#     'five' => 5,
# );
# my %hash2;
# $hash2{'fred'} = 'flinstones';
# $hash2{'barney'} = 'rubble';
#
# print $hash2{'fred'}, "\n";
# print $hash2{'barney'}, "\n";
# my @hash_to_array = %hash;
# my @hash_to_array2 = %hash2;
#
# print "@hash_to_array\n";
# print "@hash_to_array2\n";
#
# my @hashKeys =  keys %hash;
# print "@hashKeys\n";
# my @hashValues =  values %hash;
# print "@hashValues\n";
#
# my @hashKeys2  = keys %hash2;
# print "@hashKeys2\n";
# my @hashValues2  = values %hash2;
# print "@hashValues2\n";
#
# my %reversedHash = reverse %hash;
#
# print %reversedHash,"\n";
#
# open(my $myfile, '<', 'temp.txt')
#     or die "can't open the file: $!";
#
# # print FILES1 "test\n";
#
# # while(my $x = <FILES1>){
# #     chomp($x);
# #
# # }
#
# foreach my $x (<$myfile>){
#     chomp($x);
#     say("read line: $x");
# }
#
# print "Print examples1\n";
# print %hash,"\n";
# print "%hash","\n";
# print '%hash',"\n";
#
# # print $hash,"\n";
# # print "$hash","\n";
# # print '$hash',"\n";
#
# print "Print examples2\n";
#
# print $hash{one},"\n";
# print "$hash{one}","\n";
# print '$hash{one}',"\n";
#
# print "Print examples3\n";
#
# print $hash{"one"},"\n";
# print "$hash{'one'}","\n";
# print '$hash{"one"}',"\n";
#
# my $temp = "one";
#
# print "Print examples4\n";
#
# print $hash{$temp},"\n";
# print "$hash{$temp}","\n";
# print '$hash{$temp}',"\n";
#
# while( my ($x,$y) = each %hash){
#     say "key: $x - value: $y";
# }


# sub F2{
#     my $x = @_;
#     $x + 5;
# }
#
# print &F2(1..5);

sub F3 {
    foreach(@_){
        print;
    }
}

print &F3(1..5),"\n";

sub f{
    my $n++;
}

print &f,"\n";

sub g{
    my $m=2;
    print $m;
}

print &g,"\n";

sub h1{
    print 5;
}
sub h2{
    &h1;
}
print &h2
