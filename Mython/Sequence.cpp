#include "Sequence.h"


Sequence::Sequence(const bool isTemp) : Type(isTemp)
{
}


Sequence::~Sequence()
{
	for (int i = 0; i < this->_seq.size(); i++)
	{
		delete this->_seq[i];
	}
}
