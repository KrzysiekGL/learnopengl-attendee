# OpenGL tutorial
This is a repository committed to my learning of OpenGL.
The guide I'm following here comes from the courtesy of
the creator of [learnopengl.com](https://learnopengl.com/Introduction) -  Joey de Vries.

## Submodules

Since the repository contains [*submodules*](https://git-scm.com/book/en/v2/Git-Tools-Submodules),
clone it with `--recurse-submodules`.

## Building stages
In each stage, begging with the name of it's directory with `\d\d-(stage name)`
there is a `CMakeLists.txt` file for building it. Simply, as usual, create a `build`
dir inside of a chosen stage directory, e.g. `01-Creating_a_window/build` and run the
following commands:
```bash
$ cd 01-Creating_a_window/build
$ cmake ..
$ make -j$(nproc)
$ ./app # to run the stage application
```
## Stages
This project is designed to represent the progress through the stages of learning OpenGL
based on the learn path introduced in the [guide](https://learnopengl.com/Introduction).
But the code isn't the same as presented there. Instead, the project structure evolves
in the way I thought it would look and feel better in the means of structure, usability or
simple preferences.

The stages are numbered from `01` to the latest presented. That means that e.g. stage `04`
is newer than `03` thus, despite it's a copy of `03`, it contains changes in regard to the
previous stage, and contains new contents.

