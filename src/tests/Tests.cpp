#include "tests.h"

#include <queue>
void testReadFile() {
	TransfersSystem transSys(13, 60);
	ASSERT_EQUAL(true,
			transSys.addDataFromFile(
					"C:\\Users\\Daniel\\eclipse\\Transferes\\src\\PlaneamentoTransferes-infos.csv"));

	ASSERT_EQUAL(15, transSys.getServices().size());

	std::vector<Vertex<Local *>*> vertexSet = transSys.getMap().getVertexSet();
	ASSERT_EQUAL(16, vertexSet.size());

	for (std::vector<Vertex<Local *>*>::iterator it = vertexSet.begin();
			it != vertexSet.end(); it++) {
		ASSERT_EQUAL(16, (*it)->getAdj().size());
	}

}

void testCalcSimplePath() {
	TransfersSystem transSys(13, 60);
	transSys.addDataFromFile(
			"C:\\Users\\Daniel\\eclipse\\Transferes\\src\\teste_unitario_1.csv");

	queue<Service *> ret;
	ASSERT_EQUAL(true, transSys.calcSimplePath(transSys.getServices(), ret));
}

void testCalcComplexPath() {
	TransfersSystem transSys(13, 60);
	transSys.addDataFromFile(
			"C:\\Users\\Daniel\\eclipse\\Transferes\\src\\teste_unitario_2.csv");

	queue<Service *> ret;
//	ASSERT_EQUAL(false, transSys.calcSimplePath(transSys.getServices(), ret));

	queue<Service *> ret2;
	ASSERT_EQUAL(true, transSys.calcComplexPath(transSys.getServices(), ret2));
}

void runSuite() {
	cute::suite s;

	s.push_back(CUTE(testReadFile));
	s.push_back(CUTE(testCalcSimplePath));
	s.push_back(CUTE(testCalcComplexPath));

	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "Testes unitários");
}

void tests_main() {
	runSuite();
}
