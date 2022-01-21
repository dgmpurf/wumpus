Wumpus-Advance
HW5
I believe, I might miss understand this HW.

Whole thing should be:
agent percept --> agent record --> agent record pit, wumpus, and gold location --> 
agent go back to inital (?) --> agent use FindPath to get the way to Gold --> 
agent move again, and grabe Gold --> againt follow the way come back the initial --> 
agent climb (DONE)

agent percept Stench and Breeze, use this way to assume pit and wumpus location.
Then use AddSafeLocation(agentLocation.X, agentLocation.Y)
Next, Create LocationList to list and store every kinds of location.
there should have 2 kind SafeLocation Stench and Breeze
Also create visitLocation list
There should have 3 kind location I need to create my self: 
	visitLocation, Breeze location, Stench location.
Also use currentlocation, which should be agentLocation to make adjcentLocation

