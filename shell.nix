# Build and run environment: `nix-shell`, then see README.md.
{ pkgs ? import (fetchTarball
    "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.xz") { } }:

let
  qtbase = pkgs.libsForQt5.qtbase;
in
pkgs.mkShell {
  packages = [
    qtbase
    pkgs.libsForQt5.qmake
    pkgs.eigen
    pkgs.boost
    pkgs.pkg-config
  ];

  # Let the unwrapped `./Final` find the xcb platform plugin
  QT_PLUGIN_PATH = "${qtbase.bin}/${qtbase.qtPluginPrefix}";
}
