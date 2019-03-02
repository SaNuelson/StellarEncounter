#ifndef SE_CHARACTER
#define SE_CHARACTER

#include "stdlibs.h"
#include "IListener.h"
#include "Components.h"

class Character : IListener
{
public:
	Character();
	~Character();

	void AddComponent(Component* comp);;

	void ReceiveEvent(UID, Event) override;;

private:

	std::vector<Component*> Components;

};

#endif