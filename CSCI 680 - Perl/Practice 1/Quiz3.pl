#usr/bin/perl

use warnings;

# while($x = <STDIN>){
#     chomp($x);
#     $x = "\L$x";
#     $x = "\u$x";
#     push(@list,$x);
# }
# print "@list\n";

#print (25..15);

@names = <STDIN>;

chomp @names;

$i = 0;

while ($i <= $#names) {
    $names[i] = "\L\u$names[i]";
    $i+=1;
}

print "@names";
