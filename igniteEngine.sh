# DEFINE AREAS
ENGINE=g++
ORIGINAL_SOURCE=ignition.cpp
VCL_SOURCE=ignition.vcl

# COMPILE ENGINES INTO MACHINE CODE
$ENGINE $ORIGINAL_SOURCE -o vcl-1   # Make the first compiler in C++
./vcl-1 $VCL_SOURCE vcl-2           # Make the second in VCL
./vcl-2 $VCL_SOURCE vcl-3           # Make it compile itself

# CLEANUP
rm vcl-1
rm vcl-2