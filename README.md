# WUMPUS
Your agent should do the following. 
1. In addition to the agent’s state information, you should also keep track of stench locations, the Wumpus location, the gold location, any pit locations, visited locations, safe locations, and the world size, as this information becomes known. You will be playing each world for multiple tries, so keeping track of what you learned from previous tries is useful (and required).
2. You should update location information as you visit new locations: 
  a. If you perceive a stench, then add current location to stench locations. 
  b. If you perceive a glitter, then set gold location to current location. 
  c. Update the world size to max(X,Y) of your current location. 
  d. Add current location to safe locations. If no breeze or stench, then add adjacent locations to safe locations.
  e. Add current location to visited locations.
  f. Implement the logical rule: If there are two stench locations in a diagonal arrangement, and one of their common adjacent locations is safe, then the other common adjacent location contains the Wumpus. For example, if there is a stench in (2,2) and (3,3), and (3,2) is safe, then the Wumpus is in (2,3). Your agent should never die from the Wumpus, nor need to shoot the Wumpus (the gold will not be co-located with the Wumpus)
  g. If your agent dies, then it should only be from doing a GoForward into a pit, so update pit locations accordingly.
3. If you perceive a glitter, then Grab. 
4. 4. If you have the gold and are in the (1,1) location, then Climb. 
5. 5. If you know the gold’s location, and you don’t have the gold, then use the search engine to find a sequence of actions to get you there.
6. If you have the gold, but aren’t in the (1,1) location, then use the search engine to find a sequence of actions to get you to (1,1).
7. Otherwise, determine a safe unvisited location and use the search engine to find a sequence of actions to get there.
