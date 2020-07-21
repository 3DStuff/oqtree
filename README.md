# oqtree

The simplest header only quad- and octree implementation.

## Usage:

```cpp
// quad::boundary or oct::boundary and payload type
tree<quad::boundary, mesh::face<id_t>> _xy_tree;
// insert
_xy_tree.insert(glm::vec2(x,y), f);
```

## OpenCV tree view

|                              Eiffel Tower                                  | Side                                                                                | Top                                                                                 |
|:--------------------------------------------------------------------------:|-------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| ![Rendering](https://github.com/3DStuff/ressources/blob/master/eiffel_mesh.png) | ![quad tree top](https://github.com/3DStuff/ressources/blob/master/eiffel_side.png) | ![quad tree side](https://github.com/3DStuff/ressources/blob/master/eiffel_top.png) |
