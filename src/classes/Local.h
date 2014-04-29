/*
 * Local.h
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#ifndef LOCAL_H_
#define LOCAL_H_

#include <string>

/**
 *  Classe Local.
 *	Esta classe representa um local que poder� ser utilizado como ponto de recolha de passageiros.
 */
class Local {
private:
	/**
	 * Nome do local/Morada.
	 */
	std::string name;
public:
	/**
	 * Construtor da classe.
	 * Recebe por parametro um Local e cria um clone desse local
	 * @param l local a colonar
	 */
	Local(const Local& l);
	/**
	 * Construtor da classe.
	 * Recebe por parametro uma string que ser� o nome do local/morada
	 * @param name nome do local/morada
	 */
	Local(std::string name);

	/**
	 * Esta fun��o retorna o nome do local/morada.
	 */
	std::string getName() const;

	/**
	 * Este metodo poder� ser utilizado para alerar o nome/morada de um determinado local.
	 * @param name nome do local/morada
	 */
	void setName(std::string name);
	/**
	 * Operador igual
	 * Compara dois locais e verifica se s�o iguais (isto �,representem o mesmo local).
	 * @param loc local a comparar com.
	 * @return retorna true caso os dois locais sejam iguais (isto �, representem o mesmo local), false, caso cntr�rio.
	 */
	bool operator==(const Local & loc) const;
};

#endif /* LOCAL_H_ */
