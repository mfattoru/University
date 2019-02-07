#!/usr/bin/perl

#use warnings;

@array1 = (0,1,2,3,4);
@array2 = ("a","b","c","d","e");

print 'print @array1;',"\n";
print @array1,"\n";

print 'print "@array1";',"\n";
print "@array1","\n";

print 'print array2',"\n";
print @array2,"\n";

print "Swapping now\n";

# (@array2,@array1)=(@array1,@array2);
#
# print 'print "@array1";',"\n";
# print "@array1","\n";
#
# print 'print array2',"\n";
# print "@array2","\n";

($array1[0],$array2[0]) = ($array2[0],$array1[0]);

print 'print "@array1";',"\n";
print "@array1","\n";

print 'print array2',"\n";
print "@array2","\n";

$i = "1*3";
print 'print $array[$i];',"\n";
print $array1[$i],"\n";

@array3 = (5..23);
print 'print "@array3";',"\n";
print "@array3","\n";

print 'print @array4 = (@array1,@array2)',"\n";
print @array4 = (@array1,@array2,7..33),"\n";

($temp1,$temp2,$temp3) = @array1;
print 'print ($temp1,$temp2,$temp3) = @array1',"\n";
print $temp1, $temp2, $temp3, "\n";

print "Arrays before a loop","\n";
print "@array1","\n";
print "@array2", "\n";
print "swapping arrays with a loop\n";

for my $i (0..$#array1){
    ($array1[$i],$array2[$i]) = ($array2[$i],$array1[$i]);
}

print "@array1","\n";
print "@array2", "\n\n";
print $array2[1]," ",$array2[-4],"\n";
print $array2[1] == $array2[-4],"\n";
print $array2[1] eq $array2[-4],"\n";

@array5 = qw(this is a list of values);
print @array5,"\n";
print "$array5[10]","\n";
# print undef;
#
# print (($array2[1] ne $array2[-4]) +2)
# print "\n";

print "Popping elements from the array\n";
print "@array1","\n";
print pop(@array1),"\n";
print "pop(@array1)","\n";
print push(@array1,55),"\n";
print push(@array1,44),"\n";

print "@array1","\n";

print shift(@array1),"\n";
print unshift(@array1,123),"\n";
print "@array1","\n";
print unshift(@array1,0..6),"\n";
print "@array1","\n";
print unshift(@array1,qw(adding few words)),"\n";
print "@array1","\n";
print "current size: ",$#array1,"\n";
$array1[100]="lalalal";
print "After size: ",$#array1,"\n";
print @array1,"\n";
