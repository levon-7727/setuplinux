#include <iostream>

int main(int argc, char* argv[]){
	for(int i = 0; i < argc-1; i++){
		std::cout<<argv[argc-i-1]<<" ";
	}
	std::cout<<"\n";
}
