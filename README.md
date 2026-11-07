# Electricity

A 2017 school team project: an electric circuit simulator in Qt 5 / C++.
Place components on a grid, wire them, and solve the currents with
Kirchhoff's laws (Eigen + Boost.Multiprecision).

This is a reconstruction. The 2017 code split into two branches that
were never joined, and the final version is lost. `master` merges them
and fixes what kept the result from working.

## Build

Linux, Qt 5.15, Eigen 3, Boost headers. With Nix, `shell.nix` has all
of them:

```sh
git clone https://github.com/keyclicker/electricity-ui.git
nix-shell electricity-ui/shell.nix

mkdir build-electricity && cd build-electricity
qmake ../electricity-ui/Final.pro
make -j"$(nproc)"
./Final
```

Without Nix (untested): install Qt 5 (`qmake`), `pkg-config`, Eigen 3
(found via `pkg-config eigen3`) and Boost from your distro. Other
locations: `qmake EIGEN_DIR=/path/to/eigen3 BOOST_DIR=/path/to/boost`.

## Layout

- `Final.pro`, `deps.pri`: the qmake project and its Eigen/Boost setup
- `main.cpp`, `source/`, `include/`: the app
  - `MainWindow`, `Canvas`, `GObject`, `Line`, `Point`, `InputWindow`:
    UI
  - `Resistor`, `Bulb`, ... (`EObject`): circuit elements
  - `Solver`, `Scheme`, `Graph`, `ComputeCycles`: the solver
- `forms/`, `icons/`, `resource.qrc`: UI form and images
- `test/`: Boost.Test projects; written for the older console solver,
  they don't build against this code
- `tk/`: a separate Python 2 Tkinter + OpenCV app that reads an analog
  meter's needle from a webcam (`tk/tkinter_program.py`)

## History

The raw 2017 snapshots are kept as
[tags](https://github.com/keyclicker/electricity-ui/tags), one orphan
commit each; each tag message describes its snapshot. `master` starts
from `qt-2017-11-15.2` (logic branch: save/load, undo/redo), adds `tk/`
from `tk-2017-11-14` (tag `v0-original`), and merges `qt-2017-11-15.4`
(UI branch: polished UI).
