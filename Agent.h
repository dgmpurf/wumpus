// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include "Action.h"
#include "Percept.h"

#include "Location.h"
#include "Orientation.h"
#include "Search.h"
#include <list>
#include "WorldState.h"

class Agent
{
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);

	void UpdateState(Percept& percept);
	void Move(Location& location);
	Action nextAction(Percept& percept);
	void AddNewLocation(list<Location>& locationList, const Location& location);
	bool LocationInList(list<Location>& locationList, const Location& location);
	bool outerWorld(Location& location);
	void adjLocation(list<Location>& locationList, const Location& location);
	bool agentHasGold; 
	bool wumpusAlive;
	bool agentHasArrow;

	WorldState worldState;

	Location agentLocation;
	Orientation agentOrientation;
	list<Action> actionList;
	SearchEngine searchEngine;

	Action previousAction;

	list<Location> stenchLocation;
	list<Location> breezeLocation;
	list<Location> wumpusLocation;
	list<Location> pitLocation;
	list<Location> vistLocation;
	


};

#endif // AGENT_H
