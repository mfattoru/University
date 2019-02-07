#/usr/bin/perl

@L = qw \ this is a list of values \;

@L2 = reverse(@L);
print "@L\n";
print "@L2\n";

@L = qw \ 2 3 5 7 23 123 9876\;

@L2 = reverse(@L);
print "@L\n";
print "@L2\n";

$x = reverse @L2;
print $x,"\n";

@L3 = sort @L;
print "@L3\n";
print "\n";

@L4 = reverse sort @L;
@L5 = sort reverse @L;

print "@L4 - @L5\n\n";

($x,$y) = splice @L ,2,2;
print "$x . $y - @L\n";

splice @L,scalar(@L),0,12;
print "\n@L\n";

print scalar(@L)," - ",$#L,"\n";
