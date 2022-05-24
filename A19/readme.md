# UV Coordinates
- V coordinate is directed inversely [1,0]
- Cube
- Cylinder
  - Need to replicate vertex at the beginning and at the end
    - Adjust resize of vertices with `nSlices+1`
    - When creating vertices, add an additional step to the iteration
    - Update addCircleIndices mod to `nSlices+1` to consider duplicated vertex
    - Update addCylinderSidePos parameter  `nSlices=nSlices+1` 
    - Update addCylinderSideIndices mod to `nSlices+1` to consider duplicated vertex