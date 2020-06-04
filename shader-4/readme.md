### position is passed into fragment shader and used as color

#### negatives are changed to 0

#### example:
#### ( 0.5, -0.5, 0.0) is changed into (0.5, 0.0, 0.0) : resulting in red
#### (-0.5, -0.5, 0.0) is changed into (0.0, 0.0, 0.0) : resulting in black
#### ( 0.5,  0.5, 0.0) is changed into (0.0, 0.5, 0.0) : resulting in green
