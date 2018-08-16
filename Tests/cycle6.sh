#!/bin/bash
clear
rm -rf  "$(stat -c "%Y:%n" * | sort -t: -n | tail -1 | cut -d: -f2-)"

