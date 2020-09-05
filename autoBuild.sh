#!/bin/bash

# Detect architecture
CURRENT_ARCHITECTURE=""
. scipts/detectArchitecture.sh

echo "Architecture : ${CURRENT_ARCHITECTURE}"



# Platform deteching
CURRENT_PLATFORM=""
. scipts/detectPlatform.sh

echo "Platform : ${CURRENT_PLATFORM}"



# Required tools deteching
. scipts/detectTools.sh



# Install packages
. scipts/installPackages.sh
