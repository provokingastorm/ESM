## User Story
As a player, I can see a gray rectangle at the bottom of the screen representing the volleyball court, a white vertical line representing the net and a blue background filling the rest of the space. 

## Acceptance Criteria
 - A gray rectangle is rendered at the bottom of the screen representing the volleyball court.
 - A thin, white vertical line is rendered in the middle of the screen, representing the net.
 - A blue background is rendered, filling the rest of the space.

## Status Report
Completed and submitted.

## Next Actions


## Before Submission Tasks
- [ ] 

## Investigation Tasks
- [ ] 

## Deferred Actions
- [ ] 

## Experiments


## Documents


## Links
- 

## Notes
 - Need to calculate the playable area based on the total width and height of the screen.
 - How much space to leave? Should we do percentage? Probably not. We want the player to be able to resize the screen without the playable area changing. Changing the playable area will affect the gameplay. So just add more dead space instead of resizing the playable area.
 - It's unknown how much playable area is in the original slime volleyball. Going to have to eyeball it.
 - Playable area is definitely more like a TV-sized rectangle.

## Finished Tasks
- [x] Figure out how to render a rectangle of a single color in HGE
- [x] Create a fixed playable in the center of the screen