#include "tests.h"

void thisIsATest() {
	ASSERTM("start writing tests", false);
}


void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Testes unit�rios");
}

void tests_main(){
    runSuite();
}
