pkgs: attrs:
with pkgs;
let defaultAttrs = {
  builder = "${bash}/bin/bash";
  args = [ ./gen_bulider.sh ];
  setup = ./setup.sh;
  baseInputs = [ gnutar gzip gnumake gcc coreutils gawk gnused gnugrep binutils.bintools findutils patchelf ];
  buildInputs = [];
  system = builtins.currentSystem;
};
in derivation (defaultAttrs // attrs)
