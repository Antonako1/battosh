#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "battosh.hxx"
#include "./commands/commands.hxx"

// NOTE Paths need to end in /
void pathing(std::string &input, battosh_info *args){
	// TODO NOTE UNEFFICIENT... LOOPS THROUGH ENTIRE FILE EVERY TIME
	std::string output = "";
	for(char &c : input){
	    if(c == '\\'){
			output += '/';
			continue;
	    }
	    output += c;
	}
	input = output;
}
