#!/usr/bin/perl -w 

use strict;
use utf8;
use LWP::Simple;
use HTML::TokeParser::Simple;

open OUT1, ">", "DATA.dat" or die $!;
open OUT2, ">", "US.dat" or die $!;

my $base = "http://www.datasciencecentral.com";

for my $index (1 .. 84){

    my $url = "http://www.datasciencecentral.com/profiles/friend/listFeatured?page=$index";

    my $parser = HTML::TokeParser::Simple->new(url => $url);
    
    my $flag = 0;
    while(my $anchor = $parser->get_tag('a')){
	my $href = $anchor->get_attr('href'); 
	if($href =~ m/\/profile\/.*?=profiles_featuredList$/){
	    if(($flag%2) == 0){
		my $parser2 = HTML::TokeParser::Simple->new(url => "$base$href");
		while(my $anchor2 = $parser2->get_tag('ul')){
		    next unless defined(my $member = $anchor2->get_attr('class'));
		    if($member =~ /member_detail/){
			my $tmp;
			while(my $t = $parser2->get_token){
			    last if $t->is_end_tag('ul');
			    $tmp .= $t->as_is;
			}
			chomp($tmp);
			$tmp =~ s/^<li>|<\/li><li>|<\/li>$/!/g;
			$tmp =~ s/^!|!$//g;
			print OUT1 $tmp,"\n";
			my @data = split /!/,$tmp;
			if($#data == 2){
			    if($data[2] =~ m/United States|United State/i){
				print OUT2 $tmp,"\n";
			    }
			}
		    
			print $tmp,"\n";
			last;
		    }
		}
		
	    }
	    $flag++;
	}
    }
}

close(OUT1);
close(OUT2);

open IN, "<","US.dat" or die $!;
open OUT3, ">", "STATE.csv" or die $!;


my %State = ();
while(<IN>){
    chomp($_);
    my @data = split /!/,$_;
    ##print $#data,"\n";
    if($#data < 2){
	next;
    }
    my @data2 = split /,/,$data[1];
    if($#data2 < 1){
	next;
    }
    my $state = $data2[1];
    $state =~ s/^\s+|\s+$//g;
    $state = uc $state;
    print $state;
    if(exists $State{$state}){
	++$State{$state};
    }
    else{
	$State{$state} = 1;
    }
}

foreach my $key (keys %State){
    print OUT3 $key,",",$State{$key},"\n"; 
}

close(IN);
close(OUT3);

