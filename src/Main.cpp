#include "tests/Tests.h"

#include "libs/tui/TextUserInterface.h"

#include "classes/TransfersSystem.h"
#include "classes/Map.h"
#include "classes/Service.h"

#include <vector>
#include <stack>

/*
 void test_Map(){
 Local * airport = new Local("Francisco Sá Carneiro");
 Local * spo = new Local("S. Paio de Oleiros");
 Local * gaia = new Local("Gaia");

 Map map(*airport);
 map.addVertex(*spo);
 map.addVertex(*gaia);

 Vertex<Local> * vAirport = map.getVertex(*airport);
 Vertex<Local> * vSpo = map.getVertex(*spo);
 Vertex<Local> * vGaia = map.getVertex(*gaia);


 vSpo->addEdge(vAirport,120);
 vGaia->addEdge(vAirport,30);
 vAirport->addEdge(vGaia,30);

 vGaia->addEdge(vSpo,30);
 vSpo->addEdge(vGaia,30);

 ASSERT_EQUAL(120, map.getBestTravelTime(*spo));
 ASSERT_EQUAL(30, map.getBestTravelTime(*gaia));

 }


 void test_Services(){


 Local * airport = new Local("Francisco Sá Carneiro");
 Local * spo = new Local("S. Paio de Oleiros");
 Local * gaia = new Local("Gaia");

 Map * map = new Map(*airport);
 map->addVertex(*spo);
 map->addVertex(*gaia);

 Vertex<Local> * vAirport = map->getVertex(*airport);
 Vertex<Local> * vSpo = map->getVertex(*spo);
 Vertex<Local> * vGaia = map->getVertex(*gaia);


 vSpo->addEdge(vAirport,120);
 vGaia->addEdge(vAirport,30);
 vAirport->addEdge(vGaia,30);

 vGaia->addEdge(vSpo,30);
 vSpo->addEdge(vGaia,30);

 Service * s1 = new Service(50,18*60, spo, map);
 Service * s2 = new Service(52,18*60, spo, map);

 ASSERT_EQUAL(false,(s1 == s2));

 ASSERT_EQUAL(18*60 - map->getBestTravelTime(*spo),s1->getLaterTime());
 ASSERT_EQUAL(18*60 - map->getBestTravelTime(*spo) - 60,s1->getSoonerTime());

 }



 void test_simplePath(){

 Local * airport = new Local("Francisco Sá Carneiro");
 Local * spo = new Local("S. Paio de Oleiros");
 Local * gaia = new Local("Gaia");

 Map * map = new Map(*airport);
 map->addVertex(*spo);
 map->addVertex(*gaia);

 Vertex<Local> * vAirport = map->getVertex(*airport);
 Vertex<Local> * vSpo = map->getVertex(*spo);
 Vertex<Local> * vGaia = map->getVertex(*gaia);


 vSpo->addEdge(vSpo,0);
 vGaia->addEdge(vGaia,0);

 vAirport->addEdge(vSpo,40);
 vSpo->addEdge(vAirport,40);

 vGaia->addEdge(vAirport,30);
 vAirport->addEdge(vGaia,30);

 vGaia->addEdge(vSpo,30);
 vSpo->addEdge(vGaia,30);

 Service * s0 = new Service(5,18*60, gaia, map);
 Service * s2 = new Service(10,18*60, spo, map);
 Service * s4 = new Service(5,17*60+50, spo, map);
 Service * s1 = new Service(5,18*60+30, gaia, map);
 Service * s3 = new Service(5,18*60, spo, map);

 TransfersSystem ts(*map,30);


 std::vector<Service *> services;
 services.push_back(s1);

 std::queue<Service *> ret,ret2,ret3;


 ASSERT_EQUAL(true, ts.calcSimplePath(services,ret));
 ASSERT_EQUAL(1, ret.size());

 services.push_back(s2);
 ASSERT_EQUAL(true, ts.calcSimplePath(services,ret2));
 ASSERT_EQUAL(2, ret2.size());

 services.push_back(s3);
 ASSERT_EQUAL(true, ts.calcSimplePath(services,ret2));

 services.push_back(s0);

 services.push_back(s4);
 ASSERT_EQUAL(true, ts.calcSimplePath(services,ret3));
 while(ret3.size() != 0){

 cout << (ret3.front()->getArrivalTime()/60)  <<  "h" <<(ret3.front()->getArrivalTime()%60) << ret3.front()->getLocal()->getName() << endl;
 ret3.pop();
 }

 }


 }
 */

TextUserInterface tui("Tema 6: Planemanento de Transfers", 70, 13);

void mainAppMenu() {
	unsigned op;
	while (op = tui.printMenu(
			"Importar dados \nAlterar Restrições \nSobre \nSair")) {
		if (op == 1)
			tui.print("Por fazer..");
		else if(op == 2)
			tui.print("Por fazer..");
		else if(op == 3)
			tui.print("Projeto desenvolvido no ambito da unidade curricular de Concepção e Analise de Algoritos @ Feup @ 2014....");
	}
}

int main() {
	unsigned op;
	while (op = tui.printMenu(
			"Iniciar aplicação \nCorrer testes unitários \nSair")) {
		if (op == 1)
			mainAppMenu();
		else {
			tui.clearScreen();
			tests_main();
			tui.printSkipFooter();
		}
	}
	tui.printEnd("Programa terminado.");
	return 0;
}

