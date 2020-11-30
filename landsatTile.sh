#!/bin/bash
############################################
# Tiling and Conversion of Landsat Imagery #
############################################
# Usage: bash landsatTile.sh <baseName> <tileSize>

name=$1
size=$2
echo "Preparing $size-Pixel Tiles from $name.*..."

make clean
make

convert $name.* $name.ppm
./tiler $name.ppm $name.ppm 0 1 $2

for file in *-$name.ppm;
do

  newName=${file%%.*};
  echo "Converting $newName.ppm..."
  convert $file $newName.png;

done

rm *.ppm
rm $name.png


# End landsatTile.sh  - EWG SDG
