#!/bin/bash


RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${RED}===WARNING!===${NC}"
echo "This script only works if you use arch based distro, if you're not using arch based distro, follow the installation guide here: https://github.com/wh1tepearl/Pure-maker"
echo -e "${GREEN}Press enter to continue${NC}"
read

sudo pacman -S --noconfirm g++ zenity
git clone https://github.com/wh1tepearl/Pure-maker pure_maker

cd pure_maker
g++ PureMaker main.cpp

rm -f main.cpp install.sh

cp PureMaker.desktop ~/.local/share/applications/

rm -f PureMaker.desktop
sudo install -Dm755 PureMaker /usr/local/bin/pmaker

echo -e "${GREEN}Done! PureMaker installed.${NC}"
echo -e "usage:"
echo -e "  In terminal: ${YELLOW}pmaker${NC}"
echo -e "  Thru app menu: look for PureMaker"
