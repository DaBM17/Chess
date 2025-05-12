#pragma once
#include "Movement.hpp"

class Node
{
public:
	Node() { m_next = nullptr; }
	Movement getValor() { return m_valor; }
	Node* getNext() { return m_next; }
	void setValor(const Movement& valor) { m_valor = valor; }
	void setNext(Node* next) { m_next = next; }
private:
	Movement m_valor;
	Node* m_next;
};

class QueueMovements
{
public:
	QueueMovements();
	~QueueMovements();
	void afegeix(Movement& valor);
	void treu();
	Movement getPrimer() const;
	Movement getUltim() const;
	bool esBuida() const;
private:
	Node* m_primer;
	Node* m_ultim;
};