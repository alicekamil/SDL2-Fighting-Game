
# Which Witch Will Win

## Project Info
A local-mutltiplayer fighting game with support for animated spritesheets.

## Patterns used
- [Command](#command)
- [Observer](#observer)
- [Component](#component)
- [Game Loop](#game-loop-and-update-method)
- [Update Method](#game-loop-and-update-method)

### Command
- What does it do?
  - Input Handling
- Why was it chosen?
  - Easy to have different input-schemes for the players
  - Easy to add more inputs with more Commands
- How was it implemented?
  - Base Command- class with a virtual Execute method
  - InputHandler instance which returns a list of Commands
  - CommandManager executes the list Commands on the players

### Observer
- What does it do?
  - Animation
- Why was it chosen?
  - Enabled decoupling of the animation system from the Player component
- How was it implemented?
  - A base Subject class
  - Player Notifies its Observers (the Animator Component) with an Event
  - The Animator plays an Animation based on the Event type

### Component
- What does it do?
  - All GameObject/Actors/Entities are a list of Components
- Why was it chosen?
  - Decoupling an Object’s functionality into several component
- How was it implemented?
  - A Component base class with virtual Start, Update and End methods
  - A GameObject class that contains a list of Components
  - The Player is a GameObject that has a PlayerMovement, Attack, Health, Collider and an Animator Component

### Game Loop and Update Method
- What does it do?
  - Simulate a collection of independent objects frame by frame
- Why was it chosen?
  - Works very well with the Component Pattern
- How was it implemented?
  - The Game Loop processes each frame of the game
  - First the collection of GameObjects get updated each frame and each fixed-timestep ( 60 fps )
  - Rendering of each GameObject happens afterwards



