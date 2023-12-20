
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
  - Easy to have [different](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/0623047e16334e978ed0fc57f429e04cea68318e/GameEngine/GameObjects/CommandManager.cpp#L12) input-schemes for the players
  - Easy to add more inputs with more Commands
- How was it implemented?
  - [Base Command](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/0623047e16334e978ed0fc57f429e04cea68318e/GameEngine/input.h#L13) class with a virtual Execute method
  - InputHandler instance which [returns](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/0623047e16334e978ed0fc57f429e04cea68318e/GameEngine/input.cpp#L39) a list of Commands
  - CommandManager [executes](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/0623047e16334e978ed0fc57f429e04cea68318e/GameEngine/GameObjects/CommandManager.cpp#L20) the list Commands on the players

### Observer
- What does it do?
  - Animation
- Why was it chosen?
  - Enabled decoupling of the animation system from the Player component
- How was it implemented?
  - A base [Subject](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/main/GameEngine/Events/Subject.h) and [Observer](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/main/GameEngine/Events/Observer.h) class
  - Player [Notifies](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/995d408cc38e229e5344494855a8e99111bceacc/GameEngine/GameObjects/Player.cpp#L160) its Observers (the [Animator Component](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/main/GameEngine/Animator.h) ) with an Event
  - The Animator [plays](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/995d408cc38e229e5344494855a8e99111bceacc/GameEngine/Animator.cpp#L138) an Animation based on the Event type

### Component
- What does it do?
  - All GameObject/Actors/Entities are a list of Components
- Why was it chosen?
  - Decoupling an Object’s functionality into several component
- How was it implemented?
  - A Component [base class](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/main/GameEngine/GameObjects/Component.h) with virtual Start, Update and End methods
  - A GameObject class that contains a [list](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/435a3a83a9f39ec71551b3eba95e8b538395aeff/GameEngine/GameObjects/GameObject.h#L20) of Components
  - The Player is a GameObject that has a PlayerMovement, Attack, Health, Collider and an Animator Component

### Game Loop and Update Method
- What does it do?
  - Simulate a collection of independent objects frame by frame
- Why was it chosen?
  - Works very well with the Component Pattern
- How was it implemented?
  - The Game Loop processes each frame of the game
  - First the collection of GameObjects get [updated](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/435a3a83a9f39ec71551b3eba95e8b538395aeff/GameEngine/game.cpp#L53C3-L53C3) each frame and each fixed-timestep ( 60 fps )
  - [Rendering](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/blob/435a3a83a9f39ec71551b3eba95e8b538395aeff/GameEngine/game.cpp#L66C4-L66C4) of each GameObject happens afterwards

## Media

**Video**: https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/assets/57400375/210eaab5-fae1-4b93-b5ce-cc8ed8b0d89e
</br></br>
![Screenshot 2023-12-14 134445](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/assets/57400375/c8d58702-0502-4c91-bc66-4e262f2c7a7a)
![Screenshot 2023-12-14 134643](https://github.com/FG22-GP/214-design-patterns-assignment-mj-me-ak/assets/57400375/9f6dbc71-ad83-4c3c-98f2-57fb0dfa23b9)


