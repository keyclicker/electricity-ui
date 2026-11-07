# Build and run environment: `nix-shell`, then see README.md.
{ pkgs ? import (fetchTarball
    "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.xz") { } }:

let
  qtbase = pkgs.libsForQt5.qtbase;

  # tk/: the webcam meter reader. cv2.imshow needs a GTK build of OpenCV
  python = pkgs.python3.withPackages (ps: [
    ps.tkinter
    (ps.opencv4.override { enableGtk3 = true; })
    ps.pillow
    ps.numpy
  ]);
in
pkgs.mkShell {
  packages = [
    qtbase
    pkgs.libsForQt5.qmake
    pkgs.eigen
    pkgs.boost
    pkgs.pkg-config
    python
  ];

  # Let the unwrapped `./Final` find the xcb platform plugin
  QT_PLUGIN_PATH = "${qtbase.bin}/${qtbase.qtPluginPrefix}";
}
