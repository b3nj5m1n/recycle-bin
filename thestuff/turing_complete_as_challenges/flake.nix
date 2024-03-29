{
  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs";

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        riscv-toolchain =
          import nixpkgs {
            localSystem = "${system}";
            crossSystem = {
              config = "riscv64-none-elf";
              libc = "newlib-nano";
              abi = "ilp64";
            };
          };

      in
      {

        devShells = {

          default = pkgs.mkShell {
            buildInputs = [
              riscv-toolchain.buildPackages.gcc
            ];
          };
        };
      });
}
