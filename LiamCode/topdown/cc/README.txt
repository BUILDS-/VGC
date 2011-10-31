

Global update tick. Indie update.

Dirty bit, for optimizing update.

Files

	//Display 
	-main.cc
		keyevents cause change in

		updatefunction()
				handle the create the window, resize it, etc

	-world.cc
		list of existing objects (updated by main.cc)

		field array of entities called "entities"
		updatefunction()
				updates all world variables. Lighting change, surface. 
						won't don't do anything now, other cap num entities 
						spawned
				
				Iterates through each value in "entities" and calles update 
				function.

	-entity.cc
		updates itself, default: does nothing.
		otherwise collision detection and stuff
		Right now just update x,y coordinate
		
	
		updatefunction(Canvace, World variables)
