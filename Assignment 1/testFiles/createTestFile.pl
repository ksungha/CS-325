#!/usr/bin/perl -w
#use strict;
#use POSIX qw(ceil floor);
#use Storable qw(dclone);
#use Getopt::Long;
#use Data::Dumper;


int $n = 100000; #change this value for different file sizes

my $fh;
my $i;
my $j;
for($i = 0; $i < 10; $i++)
{
	open($fh,'>',"10ktestfile$i")
		or die "could not open srry\n";
	for($j = 0; $j < $n; $j++)
	{
		my $temp = int rand($n);
		my $temp2 = int rand($n);
		print $fh "$temp $temp2\n";
	}
	close $fh;
}
