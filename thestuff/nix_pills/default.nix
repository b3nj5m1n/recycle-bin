let
  nixpkgs = import <nixpkgs> { };
  lib = import ./lib.nix;
  allPkgs = nixpkgs // pkgs;
  callPackage = path: overrides:
    let
      f = import path;
      res = lib.makeOverridable f ((builtins.intersectAttrs (builtins.functionArgs f) allPkgs) // overrides);
    in
    res;
  pkgs = with nixpkgs; rec
  {
    mkDerivation = import ./autotools.nix nixpkgs;
    hello = callPackage ./hello.nix { };
    graphviz = callPackage ./graphviz.nix { };
    graphvizCore = graphviz.override { gdSupport = false; };
  };
in
pkgs 
