#!/bin/bash

# Detect architecture
CURRENT_ARCHITECTURE=""
. tools/scipts/detectArchitecture.sh

echo "Architecture : ${CURRENT_ARCHITECTURE}"



# Platform deteching
CURRENT_PLATFORM=""
. tools/scipts/detectPlatform.sh

echo "Platform : ${CURRENT_PLATFORM}"



# Required tools deteching
. tools/scipts/detectTools.sh
