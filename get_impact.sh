#!/bin/bash
for i in $(git log | grep Author | cut -d"<" -f 2 | cut -d ">" -f 1 | sort -u) ; do echo "$i $(git log | grep Author | cut -d"<" -f 2 | cut -d ">" -f 1 | grep "$i"| wc -l)" ;done > _impact_
