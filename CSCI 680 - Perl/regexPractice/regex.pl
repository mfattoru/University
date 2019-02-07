#!/usr/bin/perl -w

use strict;

# $_ = "My name is alfred not frederic, fredfredfred";
#
# if(/([\w\W])/){
#     print "match: $1\n";
# }else{
#     print "no\n";
# }
#
# if(/([^\w\W])/){
#     print "match2: $1\n";
# }else{
#     print "no2\n";
# }
# my $RE = 'fred|barney';
# if(/($RE)\1\1/){
#     print "yes\n";
# }else{
#     print "no\n";
# }
#
# $_ = 'wilma-betty';
# if(/\bwilma[^\w]*betty\b/){
#     print "yes\n";
# }else{
#     print "no\n";
# }

$_ = "xyz&abc\nbinoxyz\n****abc";

s/\b(xyz)\b(\W.*?)\b(abc)\b/$3$2$1/gm;
# print $_;
my @L = split '',$_;
#my @L2 = split '\w',$_;
print "@L\n";

# foreach(@L){
#     if(/abc/){
#         $_ = "xyz";
#     }elsif(/xyz/){
#         $_ = "abc";
#     }
# }

print "@L";
# $res = join
