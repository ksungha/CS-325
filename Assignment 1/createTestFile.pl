
my $fh;
for(my $i = 0; $i < 10; $i++)
{
	open($fh,'>',"100testfile$i")
		or die "could not open srry\n";
	for(my $j = 0; $j < 100; $j++)
	{
		my $temp = int rand(100);
		my $temp2 = int rand(100);
		print $fh "$temp\s$temp2\n";
	}
	close $fh;
}
