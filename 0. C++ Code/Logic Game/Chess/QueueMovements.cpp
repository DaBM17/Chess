#include "QueueMovements.hpp"

QueueMovements::QueueMovements()
{
	m_primer = nullptr;
	m_ultim = nullptr;
}

QueueMovements::~QueueMovements()
{
	Node* actual = m_primer;

	while (actual != nullptr)
	{
		Node* seguent = actual->getNext();
		delete actual;
		actual = seguent;
	}

	m_primer = nullptr;
	m_ultim = nullptr;
}

void QueueMovements::afegeix(Movement& valor)
{
	if (esBuida())
	{
		m_primer = new Node;
		m_primer->setValor(valor);
		m_primer->setNext(nullptr);
		m_ultim = m_primer;
	}
	else
	{
		Node* anticUltim;
		anticUltim = m_ultim;
		m_ultim = new Node;
		m_ultim->setValor(valor);
		m_ultim->setNext(nullptr);
		anticUltim->setNext(m_ultim);
	}
}

void QueueMovements::treu()
{
	if (!esBuida())
	{
		Node* nouPrimer;
		nouPrimer = m_primer->getNext();
		delete m_primer;
		m_primer = nouPrimer;
		if (m_primer == nullptr)
		{
			m_ultim = nullptr;
		}
	}
}

Movement QueueMovements::getPrimer() const
{
	return m_primer->getValor();
}

Movement QueueMovements::getUltim() const
{
	return m_ultim->getValor();
}

bool QueueMovements::esBuida() const
{
	if (m_primer == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}