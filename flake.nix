{
  description = "Development environment for the minios bare-metal C++ project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-darwin" ] (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };

        lib = pkgs.lib;
        cross = pkgs.pkgsCross.riscv32-embedded;

        targetPrefix = cross.buildPackages.gcc.targetPrefix;
        target = lib.removeSuffix "-" targetPrefix;

        hostPackages =
          with pkgs;
            [
              gnumake
              qemu
            ];

        crossPackages =
          with cross.buildPackages; [
            binutils
            gcc
            gdb
          ];
      in {
        devShells.default = pkgs.mkShell {
          name = "minios-dev-shell";
          packages = hostPackages ++ crossPackages;
          shellHook = ''
            export TARGET=${target}
            export CC=${targetPrefix}gcc
            export CXX=${targetPrefix}g++
            export LD=${targetPrefix}ld
            export AS=${targetPrefix}as
            export AR=${targetPrefix}ar
            export OBJCOPY=${targetPrefix}objcopy
            export OBJDUMP=${targetPrefix}objdump
            echo "Loaded minios dev shell for ${target}"
          '';
        };
      });
}
