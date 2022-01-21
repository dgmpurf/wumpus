// Agent.cc
//
// This code works only for the testworld that comes with the simulator.


#include <iostream>
#include <list>
#include "Agent.h"
#include <algorithm>

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{
	// Works only for test world.
	// You won't initially know safe locations or world size.
	/*
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			searchEngine.AddSafeLocation(x,y);
		}
	}
	searchEngine.RemoveSafeLocation(1,3); // wumpus0
	searchEngine.RemoveSafeLocation(3,1); // pit
	searchEngine.RemoveSafeLocation(3,3); // pit
	searchEngine.RemoveSafeLocation(4,4); // pit

	agentHasGold = false;
	actionList.clear();
	*/


	agentHasGold = false;
	wumpusAlive = true;
	agentHasArrow = true;
	agentOrientation = RIGHT;
	agentLocation = Location(1,1);

	actionList.clear();

	previousAction = CLIMB;

}

Action Agent::Process (Percept& percept)
{
	UpdateState(percept);

	list<Action> actionList2;
	if (actionList.empty()) {

		// Works only for test world (you won't initially know gold location)
		// Goto (2,3) and GRAB
		/*
		actionList2 = searchEngine.FindPath(Location(1,1), RIGHT, Location(2,3), RIGHT);
		actionList.splice(actionList.end(), actionList2);
		actionList.push_back(GRAB);
		agentHasGold = true;
		*/
		if (percept.Glitter){
			actionList2 = searchEngine.FindPath(agentLocation, agentOrientation, worldState.goldLocation, RIGHT);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(GRAB);
		}

		else if (agentHasGold){
			// Goto (1,1) and CLIMB
			actionList2 = searchEngine.FindPath(agentLocation, agentOrientation, Location(1,1), RIGHT);
			actionList.splice(actionList.end(), actionList2);
			actionList.push_back(CLIMB);
		}
		else {
			actionList.push_back(nextAction(percept));
		}

	}

	Action action = actionList.front();
	actionList.pop_front();
	previousAction = action;
	

	return action;
}

void Agent::GameOver (int score)
{

}


void Agent::UpdateState(Percept& percept){
	//add safe location
	int orientationInt = (int) agentOrientation;

	//adjacent location
	switch (previousAction){
	case GOFORWARD:
		if(percept.Bump){
			if (agentOrientation == RIGHT){
				worldState.worldSize = agentLocation.X;
			}
			if (agentOrientation == UP){
				worldState.worldSize = agentLocation.Y;
			}
			if (worldState.worldSize > 0){

			}
		}
		else{
			Location forwardLocation;
			Move(forwardLocation);
			agentLocation = forwardLocation;
			if (worldState.goldLocation == Location(0,0)){
				searchEngine.AddSafeLocation(agentLocation.X,agentLocation.Y);
			}
		}
		break;

	case TURNLEFT:
		agentOrientation = (Orientation) ((orientationInt + 1)%4);
		break;

	case TURNRIGHT:
		orientationInt--;
		if(orientationInt < 0){
			orientationInt = 3;
		}
		agentOrientation = (Orientation) orientationInt;
		break;

	case GRAB:
		agentHasGold = true;
		worldState.goldLocation = agentLocation;
		break;

	case CLIMB:
		break;
	}
	searchEngine.AddSafeLocation(agentLocation.X,agentLocation.Y);
	AddNewLocation(vistLocation, agentLocation);
	if (percept.Stench){
		AddNewLocation(stenchLocation, agentLocation);
	}
	else if (percept.Breeze){
		AddNewLocation(breezeLocation, agentLocation);
	}
	else{
		
		adjLocation(searchEngine.safeLocations, agentLocation);
	}
}

void Agent::Move(Location& location){
	location = agentLocation;
	switch(agentOrientation){
	case RIGHT:
		agentLocation.X++;
		break;
	case UP:
		agentLocation.Y++;
		break;
	case LEFT:
		agentLocation.X--;
		break;
	case DOWN:
		agentLocation.Y--;
		break;
	}
}


Action Agent::nextAction(Percept& percept){
	Action action;
	Location FDLocation;
	Move(FDLocation);

	if(searchEngine.SafeLocation(FDLocation.X, FDLocation.Y) && (! LocationInList(vistLocation,FDLocation))){
		action = GOFORWARD;
	}
	else{
		if (outerWorld(FDLocation)) {
			action = (Action) ((rand() % 2) + 1);
		} else {
			action = (Action) (rand() % 3); 
		}
	}
	return action;
}

void Agent::AddNewLocation(list<Location>& locationList, const Location& location) {
	if (!LocationInList(locationList, location)) {
		locationList.push_back(location);
	}
}

bool Agent::LocationInList(list<Location>& locationList, const Location& location) {
	if (find(locationList.begin(), locationList.end(), location) != locationList.end()) {
		return true;
	}
	return false;
}

bool Agent::outerWorld(Location& location){
	if ((location.X < 1) || (location.Y < 1)){
		return true;
	}
	if ((worldState.worldSize > 0) && ((location.X > worldState.worldSize) || (location.Y > worldState.worldSize))){ 
		return true;
	}
	return false;
}

void Agent::adjLocation(list<Location>& locationList, const Location& location) {
	if ((worldState.worldSize == 0) || (location.Y < worldState.worldSize)) {
		AddNewLocation(locationList, Location(location.X, location.Y + 1)); 
	}
	if ((worldState.worldSize == 0) || (location.X < worldState.worldSize)) {
		AddNewLocation(locationList, Location(location.X + 1, location.Y)); 
	}
	if (location.X > 1) AddNewLocation(locationList, Location(location.X - 1, location.Y)); 
	if (location.Y > 1) AddNewLocation(locationList, Location(location.X, location.Y - 1)); 
}
