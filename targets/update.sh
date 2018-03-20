#!/bin/sh

ls -d */ > targets_done.txt
gsed -i 's/\///g' targets_done.txt
