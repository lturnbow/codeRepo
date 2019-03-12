#include "element-factory.h"
#include "element1.h"
#include "element2.h"

CS225::AbstractElement* CS225::ElementFactory::MakeElement(int id,int value) const {
	AbstractElement* p_element = NULL;
	switch (id) {
		case 1: p_element = new Element1(value); break;
		case 2: p_element = new Element2(value); break;
	}
	return p_element;
}
