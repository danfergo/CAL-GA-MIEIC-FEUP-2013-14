#include "tests/Tests.h"

#include "libs/tui/TextUserInterface.h"

#include "classes/TransfersSystem.h"
#include "classes/Map.h"
#include "classes/Service.h"

#include <vector>
#include <stack>

/*
 void test_Map(){
 Local * airport = new Local("Francisco S� Carneiro");
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


 Local * airport = new Local("Francisco S� Carneiro");
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

 Local * airport = new Local("Francisco S� Carneiro");
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

TextUserInterface tui("Tema 6: Planemanento de Transfers", 70, 15);
TransfersSystem ts(60, 30);
void readDataFile() {
	string loc =
			tui.print(
					"O ficheiro deve seguir o seguinte formato: \n\n"
							"Local \n"
							"morada_do_local \n"
							"morada_do_local \n"
							"Distance\n"
							"id_loc;id_loc;distancia\n"
							"id_loc;id_loc;distancia\n"
							"Service\n"
							"id_loc_partida;nr_passageiros;dropoff;\n"
							"id_loc_partida;nr_passageiros;dropoff;\n\n"
							"Notas: id_loc � a ordem do nome do local no ficheiro. A distancia \n"
							"e o dropoff em minutos."
							"", TextUserInterface::LEFT,
					"Introduza a localiza��o do ficheiro:");
	if (ts.addDataFromFile(loc))
		tui.print("A informa��o foi importada com sucesso.");
	else
		tui.print("N�o foi possivel importar o ficheiro desejado.");

}
void changeSettings() {
	unsigned op;
	stringstream s;

	while (op =
			tui.printMenu(
					"Alterar Overhead \nAlterar lota��o m�xima dos autocarros \nVoltar ao menu anterior")) {
		if (op == 1) {
			ts.setOverhead(
					tui.printInt(
							"Introduza um valor maximo de overhead.\n"
									"Entende-se por overhead o tempo entre o tempo de \n"
									"recolha mais tarde possivel e o efetuado (em minutos)."
									"\n", "Introduza um valor entre 0 e 360:",
							0, 360));
			s.str("");
			s << "O overhead � agora:" << ts.getOverhead();
			tui.print(s.str());
		} else if (op == 2) {
			ts.setBusStocking(
			 tui.printInt(
			 "Introduza um valor maximo para a lota��o dos autocarros.\n"
			 "\n", "Introduza um valor entre 0 e 250:",
			 0, 250));

			s.str("");
			s << "A lota��o m�xima dos autocarros � agora: \n" << ts.getBusStocking();
			tui.print(s.str());

		}
	}
}

void mainAppMenu() {
	unsigned op;
	while (op =
			tui.printMenu(
					"Importar dados \nAlterar Restri��es \nSobre \nVoltar ao menu anterior")) {
		if (op == 1)
			readDataFile();
		else if (op == 2)
			changeSettings();
		else if (op == 3)
			tui.print(
					"Projeto desenvolvido no ambito da unidade curricular de Concep��o e Analise de Algoritos @ Feup @ 2014....");
	}
}

int main() {

	unsigned op;
	while (op = tui.printMenu(
			"Iniciar aplica��o \nCorrer testes unit�rios \nSair")) {
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

