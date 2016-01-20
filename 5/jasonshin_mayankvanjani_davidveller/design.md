DW APPROVED

David Veller, Mayank Vanjani, Jason Shin

Dungeons and Dragons

We will be trying to create our own version of D&D. Two people will be playing on different computers. The first person will be the dungeon master, and the second person will be the “hero”. The dungeon master can either help or hinder the hero, as he or she sees fit. The hero will have x turns to clear the dungeon. The DM and the hero will have a set of random options from a preset list each turn to choose from, and some will work better than others. However, akin to D&D all actions will have some randomness to them, but better choices will have better chances of success. For example, a turn in the game might go something like this:

(Anything in parentheses is not on the actual screen)

(DM screen)

<What will the hero face next?> 1. Mushroom 2. Goblin 3. Witch 4. Spikes

(DM Input)

1

(Hero screen)(All the hero’s choices will have an inspect option which gives some flavor text about the obstacle)

<You come across a spotted mushroom. What do you do?> 1. Eat it 2. Walk past it 3. Shoot it with an arrow 4. Inspect

(Hero input)

1 (Lets say there is a 75% the mushroom poisons the hero, and 25% is does something beneficial. The hero gets lucky)

You ate the mushroom. Luckily, it restored all your health!

(Another possible input)

2 (95% chance to get out unscathed. You aren’t so lucky)

The mushroom was a noxious trap! It lets out a poisonous cloud, and you breath the gasses in. Take 3 damage each turn for the next 3 turns.

(Branching out again, if the DM had inputed 3)

(Hero Screen)

<You come across an old hag facing away from you. But as you get close, she turns around, and you can see her crooked nose with warts all over  it. She raises her hand to point a magic wand at you. It’s a witch! What do you do?> 1. Swing your sword 2. Fire an arrow 3. Block her attack 4. Inspect

(Hero chooses 3)(80% chance to fail)

Shields aren’t good for blocking magic! Her attack electrifies the shield, and a shock runs through the length of your arm. Take 6 damage. What do you do now? 1. Swing your sword 2. Fire an arrow 3. Block her attack 4. Inspect

This will be the gist of the game. The hero will have an hp bar so that they can die, and cannot progress past an obstacle until he has defeated that obstacle. 

We will be using sockets to connect the two computers, a semaphore to make sure only two people care playing the game at one time, reading in from files for the text options, and randomness.


Things that might be implemented aside from base game:

Map and movement. Instead of just turns, the hero will be able to move around a map drawn on the screen using the cardinal directions. Whenever he lands on a sqaure, the square will internally have either a good, bad, or neutral setting. Then, depending on the setting, the DM will throw an obstacle onto that square. At first the map will be predrawn until we find a way to implement a random algortithm. (Most likely to be implemented)

Party system (4 people playing against the DM)

Classes (Mage, Warrior, Cleric, etc)
